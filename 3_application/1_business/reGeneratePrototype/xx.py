import numpy as np
from scipy.optimize import minimize
import matplotlib.pyplot as plt

# 定义物体数量
num_objects = 4

# 定义初始位置
initial_positions = np.random.rand(num_objects, 2)

# 定义约束函数
def constraint_func(positions):
    positions = positions.reshape((num_objects, 2))
    constraints = []
    for i in range(num_objects):
        for j in range(i + 1, num_objects):
            # 假设每个物体之间的距离约束为1
            constraints.append(np.linalg.norm(positions[i] - positions[j]) - 1)
    return constraints

# 定义目标函数（可以是任意函数，这里使用总距离作为示例）
def objective_func(positions):
    positions = positions.reshape((num_objects, 2))
    total_distance = 0
    for i in range(num_objects):
        for j in range(i + 1, num_objects):
            total_distance += np.linalg.norm(positions[i] - positions[j])
    return total_distance

# 设置约束条件
constraints = [{'type': 'eq', 'fun': lambda x: constraint_func(x)}]

# 使用优化算法求解
result = minimize(objective_func, initial_positions.flatten(), constraints=constraints)

# 输出结果
final_positions = result.x.reshape((num_objects, 2))

# 可视化初始位置和最终位置
plt.figure(figsize=(8, 8))

# 初始位置
plt.scatter(initial_positions[:, 0], initial_positions[:, 1], color='blue', label='Initial Positions')
for i, pos in enumerate(initial_positions):
    plt.text(pos[0], pos[1], f'P{i}', color='blue')

# 最终位置
plt.scatter(final_positions[:, 0], final_positions[:, 1], color='red', label='Final Positions')
for i, pos in enumerate(final_positions):
    plt.text(pos[0], pos[1], f'P{i}', color='red')

plt.legend()
plt.title('Initial and Final Positions of Objects')
plt.xlabel('X')
plt.ylabel('Y')
plt.grid(True)
plt.savefig('positions.jpg')
# plt.show()