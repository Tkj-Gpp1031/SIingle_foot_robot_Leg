import math
import numpy as np
import plotly.graph_objects as go


# 定义转换矩阵函数
def transformation_matrix(theta):
    theta_z = theta[0]  # Z轴旋转角
    theta1 = theta[1]  # 大腿旋转角度
    theta2 = theta[2]  # 小腿旋转角度

    # 连杆长度
    L1 = 15.0  # 大腿连杆长度
    L2 = 9.65  # 小腿连杆长度

    # 计算位置
    # 使用旋转矩阵计算在三维空间中的位置
    x = (L1 * math.cos(theta1) + L2 * math.cos(theta1 + theta2)) * math.cos(theta_z)
    y = (L1 * math.cos(theta1) + L2 * math.cos(theta1 + theta2)) * math.sin(theta_z)
    z = L1 * math.sin(theta1) + L2 * math.sin(theta1 + theta2)

    return x, y, z


# 使用蒙特卡洛方法计算工作空间
workspace = []

for _ in range(20000):  # 这里我们使用2000个样本点
    # 对每个关节随机生成角度
    theta_z = np.random.uniform(0, 2 * np.pi)  # Z轴旋转，0 到 360 度
    theta1 = np.random.uniform(-np.pi / 4, np.pi / 4)  # 大腿旋转，±45 度
    theta2 = np.random.uniform(-np.pi / 5.14, np.pi / 5.14)  # 小腿旋转，±35 度

    pos = transformation_matrix([theta_z, theta1, theta2])
    workspace.append(pos)

workspace = np.array(workspace)

# 绘制工作空间
x, y, z = workspace[:, 0], workspace[:, 1], workspace[:, 2]

# 创建一个3D散点图
scatter = go.Scatter3d(
    x=x,
    y=y,
    z=z,
    mode='markers',
    marker=dict(
        size=4,
        color=z,  # 设置颜色为z轴的值
        colorscale='Viridis',  # 选择一种颜色映射
        opacity=0.8
    )
)

# 创建图形
fig = go.Figure(data=[scatter])

# 设置布局
fig.update_layout(
    scene=dict(
        xaxis=dict(range=[-20, 20]),
        yaxis=dict(range=[-20, 20]),
        zaxis=dict(range=[-20, 20])
    ),
    margin=dict(l=0, r=0, b=0, t=0)
)

# 显示图形
fig.show()
