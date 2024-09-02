import pybullet as p
import pybullet_data
import numpy as np
import time
import torch
import torch.nn as nn
import torch.optim as optim

# 定义神经网络模型
class SimpleNN(nn.Module):
    def __init__(self):
        super(SimpleNN, self).__init__()
        self.fc1 = nn.Linear(12, 64)
        self.fc2 = nn.Linear(64, 64)
        self.fc3 = nn.Linear(64, 6)  # 输出6个参数（速度和目标位置）

    def forward(self, x):
        x = torch.relu(self.fc1(x))
        x = torch.relu(self.fc2(x))
        x = self.fc3(x)
        return x

# 初始化PyBullet仿真环境
p.connect(p.GUI)
p.setAdditionalSearchPath(pybullet_data.getDataPath())
p.setGravity(0, 0, -9.8)

# 创建平面和机器人
planeId = p.loadURDF("plane.urdf")
startPos = [0, 0, 0.3]
startOrientation = p.getQuaternionFromEuler([0, 0, 0])
robotId = p.loadURDF("robot_model.urdf", startPos, startOrientation)

# 打印机器人关节信息
num_joints = p.getNumJoints(robotId)
for i in range(num_joints):
    joint_info = p.getJointInfo(robotId, i)
    print(f"Joint {i}: {joint_info}")

# 仿真参数
max_force = 200  # 最大力

# 神经网络初始化
model = SimpleNN()
criterion = nn.MSELoss()
optimizer = optim.Adam(model.parameters(), lr=0.001)


input_data = torch.tensor([
    [4500, 0, 4500, 0, 5000, 0,
     4500, 1200, 4500, 500, 5000, 1400]
], dtype=torch.float32)

# 训练模型
epochs = 1000
for epoch in range(epochs):
    optimizer.zero_grad()
    outputs = model(input_data)
    loss = criterion(outputs, input_data)  # 假设目标数据为输入数据
    loss.backward()
    optimizer.step()

    if epoch % 100 == 0:
        print(f'Epoch {epoch}, Loss: {loss.item()}')

# 仿真步骤
for i in range(1000):
    # 通过神经网络预测速度和目标位置
    predictions = model(input_data)

    # 提取预测值并应用到仿真中
    new_speed_2_6 = predictions[0, 0].item()
    new_target_position_2 = predictions[0, 1].item()
    new_speed_4_6 = predictions[0, 2].item()
    new_target_position_4 = predictions[0, 3].item()
    new_speed_1_5 = predictions[0, 4].item()
    new_target_position_1 = predictions[0, 5].item()

    # 在PyBullet中控制舵机
    p.setJointMotorControl2(robotId, 0, p.POSITION_CONTROL, targetPosition=new_target_position_2, force=max_force)
    p.setJointMotorControl2(robotId, 1, p.POSITION_CONTROL, targetPosition=new_target_position_4, force=max_force)
    p.setJointMotorControl2(robotId, 2, p.POSITION_CONTROL, targetPosition=new_target_position_1, force=max_force)

    # 仿真步进
    p.stepSimulation()
    time.sleep(1./240.)

# 仿真结束
p.disconnect()
