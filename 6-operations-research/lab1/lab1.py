from scipy.optimize import linprog
from numpy.random import random_sample

# x = {x_11, x_12, x_21, x_22}

c = [7, 8, 7, 8]
z = 1./3. * random_sample() + 1./3.
print("Z: ", z)

A_ub = [[-3, 0, -5, 0],
        [0, -4, 0, -3],
        [0, 1, 1, 0]]
b_ub = [-5000,
        -5200,
        10000]
A_eq = [[0, 1, -z, 0]]
b_eq = [0]

res = linprog(c, A_ub, b_ub, A_eq, b_eq)

print(res)
