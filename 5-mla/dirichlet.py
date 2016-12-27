import math
import sys

# Defining the Dirichlet problem for Poisson equation.
f = lambda x, y: abs(math.sin(math.pi * x * y) ** 3)
psi_left = lambda y: 1 - y * y
psi_right = lambda y: 1 - y * y
psi_bottom = lambda x: abs(math.sin(math.pi * x))
psi_top = lambda x: abs(math.sin(math.pi * x))
a = -1.
b = 1.
c = -1.
d = 1.

# Algorithm parameters.
hx = 0.1
hy = 0.1
nx = int((b - a) / hx + 1)
ny = int((d - c) / hy + 1)

EPS = 1e-4
MAX_ZEIDEL_ITERATIONS = 1000

# (a, d)...........(b, d)
# .......................
# (a, c)...........(b, c)

def dirichlet():
    grid = [[0. for x in range(nx)] for y in range(ny)]

    # Filling grid with border values.
    for i in range(0, nx):
        x = a + i * hx
        grid[0][i] = psi_bottom(x)
        grid[ny-1][i] = psi_top(x)
    for j in range(0, ny):
        y = c + j * hy
        grid[j][0] = psi_left(y)
        grid[j][nx-1] = psi_right(y)

    # Filling inner cells with f(i,j) - approximating.
    for i in range(1, nx-1):
        x = a + i * hx
        for j in range(1, ny-1):
            y = c + j * hy
            grid[i][j] = f(x, y)

    # Updating all inner cells.
    iter = MAX_ZEIDEL_ITERATIONS
    while iter > 0:
        mx_diff = 0
        for i in range(1, nx-1):
            x = a + i * hx
            for j in range(1, ny-1):
                y = c + j * hy
                oldValue = grid[i][j]
                grid[i][j] = 1. / (2/(hx*hx) + 2/(hy*hy)) * (f(x, y) + (grid[i-1][j] + grid[i+1][j])/hx + (grid[i][j+1] + grid[i][j-1])/hy)
                mx_diff = max(mx_diff, abs(oldValue - grid[i][j]))
        if mx_diff < EPS:
            break
        iter -= 1
    if iter == 0:
        print "Zeidel: no convergence"
        return
    else:
        print "Number of iterations:", MAX_ZEIDEL_ITERATIONS - iter

    for i in range(nx-1, -1, -1):
        for j in range(0, ny):
            value = '{0:.4f} '.format(grid[i][j])
            sys.stdout.write(value)
        sys.stdout.write('\n')

    return

if nx != 21 or ny != 21:
    print "warning: wrong nx/ny:", nx, ny
else:
    dirichlet()
