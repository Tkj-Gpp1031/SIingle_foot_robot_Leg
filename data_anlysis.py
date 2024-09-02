# 力长关系
import numpy as np
import matplotlib.pyplot as plt

# 数据
corrected_lengths = [3.2, 3.4, 3.7, 4.2]
forces = [0, 5.6, 13.6, 25.6]

# 线性拟合
slope, intercept = np.polyfit(corrected_lengths, forces, 1)
fit_line = np.polyval([slope, intercept], corrected_lengths)

# 绘制图像
plt.figure(figsize=(8, 6))
plt.plot(corrected_lengths, forces, marker='o', linestyle='-', color='blue', label='Original Data')
plt.plot(corrected_lengths, fit_line, linestyle='--', color='red', label=f'Fit Line: y = {slope:.2f}x + {intercept:.2f}')
plt.title('Force vs Length')
plt.xlabel('Length')
plt.ylabel('Percentage of rated torque %')
plt.grid(True)
plt.legend()
plt.show()

# 输出斜率和截距
print(f"线性拟合的斜率为: {slope:.2f}")
print(f"线性拟合的表达式为: y = {slope:.2f}x + {intercept:.2f}")


# 角度和力的关系
import matplotlib.pyplot as plt

# 数据
angles = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120]
torque_percentages = [3.2, 3.2, 4.0, 4.8, 8.0, 11.2, 11.2, 16.8, 20.0, 22.4, 24.8, 34.4]

# 绘制折线图
plt.figure(figsize=(10, 6))
plt.plot(angles, torque_percentages, marker='o', linestyle='-', color='blue')
plt.title('Torque Percentage vs Rotation Angle')
plt.xlabel('Rotation Angle (°)')
plt.ylabel('Torque Percentage (%)')
plt.grid(True)
plt.show()

# 90 度下 同一角度不同速度的力和速关系
angles = [100, 500, 1000, 2000, 3000, 4000, 5000]
torque_percentages = [20.0, 25.6, 45.2, 66.0, 80.8, 91.2, 100.0]

# 绘制折线图
plt.figure(figsize=(10, 6))
plt.plot(angles, torque_percentages, marker='o', linestyle='-', color='blue')
plt.title('Torque Percentage vs speed(In 90° Angle)')
plt.xlabel('speed(step/s)')
plt.ylabel('Torque Percentage (%)')
plt.grid(True)
plt.show()


#角度图
import matplotlib.pyplot as plt
import numpy as np

# 时间数据
time = np.linspace(1, 18, 18)

# 力数据
force_30 = [32, 40, 40, 40, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32]
force_40 = [32, 42, 48, 48, 48, 42, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32]
force_50 = [32, 41, 48, 80, 80, 80, 76, 41, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32]
force_60 = [32, 40, 46, 80, 112, 112, 110, 80, 76, 32, 32, 32, 32, 32, 32, 32, 32, 32]
force_70 = [32, 40, 47, 80, 112, 112, 134, 134,134, 110, 80, 76, 32, 32, 32, 32, 32, 32]
force_80 = [32, 40, 45, 80, 112, 112, 134, 168,168, 165, 134, 80, 76, 32, 32, 32, 32, 32]
force_90 = [32, 40, 44, 80, 112, 112, 134, 168,200, 200,200, 196, 165, 134, 80, 76, 32, 32]
force_100 = [32, 40, 44, 80, 112, 112, 134, 168,200, 224, 224,223, 196, 165, 134, 80, 76, 32]

# 绘制曲线
plt.plot(time, force_30, label='30°', color='blue')
plt.plot(time, force_40, label='40°', color='orange')
plt.plot(time, force_50, label='50°', color='grey')
plt.plot(time, force_60, label='60°', color='yellow')
plt.plot(time, force_70, label='70°', color='green')
plt.plot(time, force_80, label='80°', color='red')
plt.plot(time, force_90, label='90°', color='purple')
plt.plot(time, force_100, label='100°', color='brown')

# 添加图例和标签
plt.legend()
plt.xlabel('Time(s)')
plt.ylabel('Force(N)')
plt.title('Force vs. Time at Different Angles')
plt.grid(True)

# 显示图表
plt.show()
