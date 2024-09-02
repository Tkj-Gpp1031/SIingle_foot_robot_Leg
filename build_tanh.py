import numpy as np
import matplotlib.pyplot as plt

plt.rcParams['font.sans-serif'] = ['SimHei']  # 设置字体为SimHei（黑体）
plt.rcParams['axes.unicode_minus'] = False    # 解决负号显示问题
#
angles = np.array([10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120])  # 角度数据
forces_angle = np.array([32, 32, 40, 48, 80, 112, 112, 168, 200, 224, 248, 344])  # 对应的力数据

speeds = np.array([100, 500, 1000, 2000, 3000, 4000, 5000])  # 速度数据
forces_speed = np.array([200, 256, 452, 660, 808, 912, 1000])  # 对应的力数据

from scipy.optimize import curve_fit
import matplotlib.pyplot as plt

# 定义 tanh 函数
def tanh_fit(x, a, b, c, d):
    return a * np.tanh(b * x + c) + d

# 拟合角度-力关系
params_angle, _ = curve_fit(tanh_fit, angles, forces_angle, p0=[5000, 0.01, 0, 50], maxfev=5000)

# 绘制拟合结果
plt.scatter(angles, forces_angle, label='原始数据 (角度-力)')
plt.plot(np.linspace(10, 120, 500), tanh_fit(np.linspace(10, 120, 500), *params_angle), label='拟合曲线', color='red')
plt.xlabel('角度 (°)')
plt.ylabel('力 (N)')
plt.legend()
plt.show()

# 输出拟合参数
print(f'拟合参数: a={params_angle[0]}, b={params_angle[1]}, c={params_angle[2]}, d={params_angle[3]}')

# 拟合速度-力关系
params_speed, _ = curve_fit(tanh_fit, speeds, forces_speed, p0=[1, 0.001, 0, 500])


# 绘制拟合结果
plt.scatter(speeds, forces_speed, label='原始数据 (速度-力)')
plt.plot(np.linspace(100, 5000, 500), tanh_fit(np.linspace(100, 5000, 500), *params_speed), label='拟合曲线', color='blue')
plt.xlabel('速度 (rpm)')
plt.ylabel('力 (N)')
plt.legend()
plt.show()

# 输出拟合参数
print(f'拟合参数: a={params_speed[0]}, b={params_speed[1]}, c={params_speed[2]}, d={params_speed[3]}')


import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

plt.rcParams['font.sans-serif'] = ['SimHei']  # 设置字体为SimHei（黑体）
plt.rcParams['axes.unicode_minus'] = False    # 解决负号显示问题

# 数据
angles = np.array([10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120])  # 角度数据
forces_angle = np.array([32, 32, 40, 48, 80, 112, 112, 168, 200, 224, 248, 344])  # 对应的力数据

speeds = np.array([100, 500, 1000, 2000, 3000, 4000, 5000])  # 速度数据
forces_speed = np.array([200, 256, 452, 660, 808, 912, 1000])  # 对应的力数据

# 定义 tanh 函数
def tanh_fit(x, a, b, c, d):
    return a * np.tanh(b * x + c) + d

# 拟合角度-力关系
params_angle, _ = curve_fit(tanh_fit, angles, forces_angle, p0=[5000, 0.01, 0, 50], maxfev=5000)

# 绘制拟合结果
plt.scatter(angles, forces_angle, label='Raw Data (Angle - Force)')
plt.plot(np.linspace(10, 120, 500), tanh_fit(np.linspace(10, 120, 500), *params_angle), label='fit a curve', color='red')
plt.xlabel('Angle (°)')
plt.ylabel('Force %')
plt.legend()

# 在图像上显示拟合参数
plt.text(0.05, 0.95, f"拟合参数:\na={params_angle[0]:.2f}\nb={params_angle[1]:.2e}\nc={params_angle[2]:.2f}\nd={params_angle[3]:.2f}",
         transform=plt.gca().transAxes, fontsize=12, verticalalignment='top', bbox=dict(facecolor='white', alpha=0.5))

plt.show()

# 输出拟合参数
print(f'拟合参数: a={params_angle[0]}, b={params_angle[1]}, c={params_angle[2]}, d={params_angle[3]}')

# 拟合速度-力关系
params_speed, _ = curve_fit(tanh_fit, speeds, forces_speed, p0=[1, 0.001, 0, 500])

# 绘制拟合结果
plt.scatter(speeds, forces_speed, label='Raw Data (Speed - Force)')
plt.plot(np.linspace(100, 5000, 500), tanh_fit(np.linspace(100, 5000, 500), *params_speed), label='fit a curve', color='blue')
plt.xlabel('Speed (rpm)')
plt.ylabel('Force %')
plt.legend()

# 在图像上显示拟合参数
plt.text(0.05, 0.95, f"fitting parameter:\na={params_speed[0]:.2f}\nb={params_speed[1]:.2e}\nc={params_speed[2]:.2f}\nd={params_speed[3]:.2f}",
         transform=plt.gca().transAxes, fontsize=12, verticalalignment='top', bbox=dict(facecolor='white', alpha=0.5))

plt.show()

# 输出拟合参数
print(f'fitting parameter: a={params_speed[0]}, b={params_speed[1]}, c={params_speed[2]}, d={params_speed[3]}')
import numpy as np

# 已拟合得到的参数值
a, b, c, d = 1180.46, 0.0002626, 0.1981, -78.69

# 实际速度数据
speeds = np.array([100, 500, 1000, 2000, 3000, 4000, 5000])

# 计算理论力值
def calculate_theoretical_force(speed, a, b, c, d):
    return a * np.tanh(b * speed + c) + d

theoretical_forces = calculate_theoretical_force(speeds, a, b, c, d)

print("Theoretical forces:", theoretical_forces)


def combined_tanh_model(angle, speed, a1, b1, c1, d1, a2, b2, c2, d2):
    force_angle = tanh_fit(angle, a1, b1, c1, d1)
    force_speed = tanh_fit(speed, a2, b2, c2, d2)
    return force_angle + force_speed
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
plt.rcParams['font.sans-serif'] = ['SimHei']  # 设置字体为SimHei（黑体）
plt.rcParams['axes.unicode_minus'] = False    # 解决负号显示问题
# 定义 tanh 拟合函数
def tanh_fit(x, a, b, c, d):
    return a * np.tanh(b * x + c) + d

# 角度和力的数据
angles = np.array([10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120])  # 角度数据
forces_angle = np.array([32, 32, 40, 48, 80, 112, 112, 168, 200, 224, 248, 344])  # 对应的力数据

# 速度和力的数据
speeds = np.array([100, 500, 1000, 2000, 3000, 4000, 5000])  # 速度数据
forces_speed = np.array([200, 256, 452, 660, 808, 912, 1000])  # 对应的力数据

# 拟合角度-力关系
params_angle, _ = curve_fit(tanh_fit, angles, forces_angle, p0=[120, 0.01, 0, 100],maxfev=5000)

# 拟合速度-力关系
params_speed, _ = curve_fit(tanh_fit, speeds, forces_speed, p0=[50000, 0.001, 0, 0],maxfev=5000)

# 使用拟合的速度-力函数来计算5000 rpm的力
force_at_5000_rpm = tanh_fit(5000, *params_speed)

# 生成角度-力关系曲线，在5000 rpm下
angles_fit = np.linspace(min(angles), max(angles), 500)
forces_angle_at_5000_rpm = tanh_fit(angles_fit, *params_angle) * (force_at_5000_rpm / max(forces_angle))

# 绘制角度-力图（在5000 rpm下）
plt.figure()
plt.plot(angles_fit, forces_angle_at_5000_rpm, 'r-', label='力-角度曲线 (速度 = 5000 rpm)')
plt.xlabel('角度 (°)')
plt.ylabel('力 (N)')
plt.legend()
plt.show()

