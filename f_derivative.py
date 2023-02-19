import numpy as np 
import matplotlib.pyplot as plt

def f_x(x):
    return x * x

def f_x_derivative(x):
    return x * 2

def numerical_f_x_derivative(x):
    d = 0.1
    derivative = (f_x(x + d) - f_x(x - d)) / 2
    return derivative

x = np.arange(-2, 2, 0.1)
y = f_x(x)

y_derivative = f_x_derivative(x)

numerical_y_derivative = numerical_f_x_derivative(x)

print(f'y = {y}')
print(f'y_derivative = {y_derivative}')
print(f'numerical_y_derivative = {numerical_y_derivative}')

figurs, axes = plt.subplots(1, 3)
axes[0].plot(x, y)
axes[1].plot(x, y_derivative)
axes[2].plot(x, numerical_y_derivative)

axes[0].set_xlabel('x')
axes[0].set_ylabel('f(x)')

axes[1].set_xlabel('x')
axes[1].set_ylabel("f'(x)")

axes[2].set_xlabel('x')
axes[2].set_ylabel("f'(x) numerical")

plt.show()
