import numpy.linalg as alg
import sys

# Defining the problem.
f = lambda x, t: x * x - 2 * t
x_range = [0., 1.]
t_range = [0., 1.]
u0 = lambda x: 0.
m0 = lambda t: 0.
m1 = lambda t: 2 * t
a0 = 0
a1 = 0
b0 = 0
b1 = 1
s = 0.5
hx = 0.05
ht = 0.05

nx = int((x_range[1] - x_range[0]) / hx) + 1
nt = int((t_range[1] - t_range[0]) / ht) + 1

def tridiagonal_matrix_algo(matr, rhs):
    print "solving..."
    print matr
    print rhs
    return alg.solve(matr, rhs)

def solve_heat_equation():
    grid = [[0. for x in range(nt)] for y in range(nx)]
    for i in range(nx):
        x = x_range[0] + i * hx
        grid[0][i] = u0(x)

    for j in range(1, nt):
        t_temp = t_range[0] + j * ht
        # Running tridiagonal algorithm for each row:
        # Allocating memory.
        matr = [[0. for x in range(nx)] for y in range(nx)]
        rhs = [0. for x in range(nx)]
        for i in range(1, nx-1):
            matr[i][i-1] = -s/(hx*hx)
            matr[i][i] = (1./ht + 2.*s/(hx*hx))
            matr[i][i+1] = -s/(hx*hx)
            x_temp = x_range[0] + i * hx
            rhs[i] = grid[j-1][i] / ht + (1 - s) / (hx * hx) * (grid[j-1][i-1] - 2 * grid[j-1][i] + grid[j-1][i+1]) + f(x_temp, t_temp)

        matr[0][0] = b0/hx - a0 + b0*hx/(2*ht)
        matr[0][1] = -b0/hx
        rhs[0] = -m0(t_temp) + b0*hx/(2*ht)*(grid[j-1][0] + ht * f(x_range[0], t_temp-ht))

        matr[nx-1][nx-2] = -b1/hx
        matr[nx-1][nx-1] = a1 + b1/hx + b1*hx/(2*ht)
        rhs[nx-1] = m1(t_temp) + b1*hx/(2*ht) * (grid[j-1][nx-1] + ht * f(x_range[1], t_temp-ht))

        x = tridiagonal_matrix_algo(matr, rhs)
        for i in range(0, len(x)):
            grid[i][j] = x[i]

    for i in range(nx-1, -1, -1):
        for j in range(0, nt):
            value = '{0:.3f} '.format(grid[i][j])
            sys.stdout.write(value)
        sys.stdout.write('\n')

solve_heat_equation()
