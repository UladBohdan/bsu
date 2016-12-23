import math
import matplotlib.pyplot as plt

dy_dx = lambda x, y, z: math.e**(-(y*y + z*z)) + 2 * x
dz_dx = lambda x, y, z: 2 * y * y + z
x_range = [0., 0.5]
x0 = 0
y0 = 0.5
z0 = 1.

f = dy_dx
g = dz_dx

EPS = 1e-5
MAX_ITERATIONS = 100

def euler_explicit_system(grid):
    yi = [y0]
    zi = [z0]
    for i in range(1, len(grid)):
        step = grid[i] - grid[i-1]
        yi.append(yi[i-1] + step * f(grid[i-1], yi[i-1], zi[i-1]))
        zi.append(zi[i-1] + step * g(grid[i-1], zi[i-1], zi[i-1]))
    return (yi, zi)

def euler_implicit_system(grid):
    yi = [y0]
    zi = [z0]
    for i in range(1, len(grid)):
        step = grid[i] - grid[i-1]
        result = simple_iterations(yi[i-1], zi[i-1], step, f, g, grid[i], yi[i-1], zi[i-1])
        yi.append(result[0])
        zi.append(result[1])
        #zi.append(simple_iterations(zi[i-1], step, g, grid[i], yi[i-1], zi[i-1]))
    return (yi, zi)

def simple_iterations(base_y, base_z, step, f, g, x, y0, z0):
    y_prev = y0
    z_prev = z0
    iter = MAX_ITERATIONS
    while iter > 0:
        y_new = base_y + step * f(x, y_prev, z_prev)
        iter -= 1
        if abs(y_prev - y_new) < EPS:
            break
        y_prev = y_new
    if iter == 0:
        print "simple iterations: no convergence"
    iter = MAX_ITERATIONS
    while iter > 0:
        z_new = base_z + step * g(x, y_prev, z_prev)
        iter -= 1
        if abs(z_prev - z_new) < EPS:
            break
        z_prev = z_new
    if iter == 0:
        print "simple iterations: no convergence"
    return (y_prev, z_prev)

def predictor_corrector_system(grid):
    return

def output_system(label, x, y, z):
    print label
    print "Y:"
    for i in range(0, len(x)):
        print 'y({0}) = {1}'.format(x[i], y[i])
    print "---------------------------------"
    print "Z:"
    for i in range(0, len(x)):
        print 'z({0}) = {1}'.format(x[i], z[i])

def run_methods():
    n = 10
    h = (x_range[1] - x_range[0]) / n
    grid = []
    for i in range(0, n):
        grid.append(x_range[0] + i * h)

    y_euler_explicit, z_euler_explicit = euler_explicit_system(grid)
    output_system("Explicit Euler for system", grid, y_euler_explicit, z_euler_explicit)

    y_euler_implicit, z_euler_implicit = euler_implicit_system(grid)
    output_system("Implicit Euler for system", grid, y_euler_implicit, z_euler_implicit)

run_methods()
