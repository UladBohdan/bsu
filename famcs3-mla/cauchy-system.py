import math

# Defining the problem (system of differential equations).
dy_dx = lambda x, y, z: math.e**(-(y*y + z*z)) + 2 * x
dz_dx = lambda x, y, z: 2 * y * y + z
x_range = [0., 0.5]
x0 = 0
y0 = 0.5
z0 = 1.

f = dy_dx
g = dz_dx

# Defining the grid to make the calculations.
n = 10
h = (x_range[1] - x_range[0]) / n
grid = []
for i in range(0, n):
    grid.append(x_range[0] + i * h)

# Constants for algorithms.
EPS = 1e-5
MAX_ITERATIONS = 100

def euler_explicit_system():
    yi = [y0]
    zi = [z0]
    for i in range(1, len(grid)):
        step = grid[i] - grid[i-1]
        yi.append(yi[i-1] + step * f(grid[i-1], yi[i-1], zi[i-1]))
        zi.append(zi[i-1] + step * g(grid[i-1], yi[i-1], zi[i-1]))
    return (yi, zi)

def euler_implicit_system():
    yi = [y0]
    zi = [z0]
    for i in range(1, len(grid)):
        step = grid[i] - grid[i-1]
        result = simple_iterations(yi[i-1], zi[i-1], step, f, g, grid[i], yi[i-1], zi[i-1])
        yi.append(result[0])
        zi.append(result[1])
    return (yi, zi)

def simple_iterations(base_y, base_z, step, f, g, x, y0, z0):
    y_prev = y0
    z_prev = z0
    iter = MAX_ITERATIONS
    while iter > 0:
        y_new = base_y + step * f(x, y_prev, z_prev)
        z_new = base_z + step * g(x, y_prev, z_prev)
        iter -= 1
        if abs(y_prev - y_new) < EPS and abs(z_prev - z_new) < EPS:
            return (y_prev, z_prev)
        y_prev = y_new
        z_prev = z_new
    print "simple iterations: no convergence"
    return

def predictor_corrector_system():
    yi3 = [y0]
    zi3 = [z0]
    for i in range(1, len(grid)):
        step = grid[i] - grid[i-1]

        y2 = yi3[i-1] + step * f(grid[i-1], yi3[i-1], zi3[i-1])
        y3 = yi3[i-1] + step * (f(grid[i-1], yi3[i-1], zi3[i-1]) + f(grid[i], y2, zi3[i-1])) / 2.
        yi3.append(y3)

        z2 = zi3[i-1] + step * g(grid[i-1], yi3[i-1], zi3[i-1])
        z3 = zi3[i-1] + step * (g(grid[i-1], yi3[i-1], zi3[i-1]) + g(grid[i], yi3[i-1], z2)) / 2.
        zi3.append(z3)
    return (yi3, zi3)

def runge_kutta_system():
    yi = [y0]
    zi = [z0]
    a0 = 0.25
    a1 = 0.
    a2 = 0.75
    for i in range(1, len(grid)):
        step = grid[i] - grid[i-1]

        fi_0_y = step * f(grid[i-1], yi[i-1], zi[i-1])
        fi_0_z = step * g(grid[i-1], yi[i-1], zi[i-1])
        fi_1_y = step * f(grid[i-1] + step/3., yi[i-1] + fi_0_y/3., zi[i-1] + fi_0_z/3.)
        fi_1_z = step * g(grid[i-1] + step/3., yi[i-1] + fi_0_y/3., zi[i-1] + fi_0_z/3.)
        fi_2_y = step * f(grid[i-1] + 2.*step/3., yi[i-1] + 2.*fi_1_y/3., zi[i-1] + 2.*fi_1_z/3.)
        fi_2_z = step * g(grid[i-1] + 2.*step/3., yi[i-1] + 2.*fi_1_y/3., zi[i-1] + 2.*fi_1_z/3.)

        y_new = yi[i-1] + a0 * fi_0_y + a1 * fi_1_y + a2 * fi_2_y
        yi.append(y_new)

        z_new = zi[i-1] + a0 * fi_0_z + a1 * fi_1_z + a2 * fi_2_z
        zi.append(z_new)

    return (yi, zi)

def inter_adams_system(y_approx, z_approx):
    yi = y_approx
    zi = z_approx
    a0 = 5./12
    a1 = 8./12
    a2 = -1./12
    for i in range(2, len(grid)):
        step = grid[i] - grid[i-1]
        f_local = lambda x, y, z: a0 * f(x, y, z) + a1 * f(grid[i-1], yi[i-1], zi[i-1]) + a2 * f(grid[i-2], yi[i-2], zi[i-2])
        g_local = lambda x, y, z: a0 * g(x, y, z) + a1 * g(grid[i-1], yi[i-1], zi[i-1]) + a2 * g(grid[i-2], yi[i-2], zi[i-2])
        result = simple_iterations(yi[i-1], zi[i-1], step, f_local, g_local, grid[i], yi[i-1], zi[i-1])
        yi.append(result[0])
        zi.append(result[1])
    return (yi, zi)

def output_system(label, x, y, z):
    print "---------------------------------"
    print label
    print "Y:"
    for i in range(0, len(x)):
        print 'y({0}) = {1}'.format(x[i], y[i])
    print "Z:"
    for i in range(0, len(x)):
        print 'z({0}) = {1}'.format(x[i], z[i])
    print "---------------------------------"

def run_methods():
    y_euler_explicit, z_euler_explicit = euler_explicit_system()
    output_system("Explicit Euler for system:", grid, y_euler_explicit, z_euler_explicit)

    y_euler_implicit, z_euler_implicit = euler_implicit_system()
    output_system("Implicit Euler for system:", grid, y_euler_implicit, z_euler_implicit)

    y_predictor_corrector, z_predictor_corrector = predictor_corrector_system()
    output_system("Predictor-corrector for system:", grid, y_predictor_corrector, z_predictor_corrector)

    y_runge_kutta, z_runge_kutta = runge_kutta_system()
    output_system("Runge-Kutta for system:", grid, y_runge_kutta, z_runge_kutta)

    y_inter_adams, z_inter_adams = inter_adams_system(y_predictor_corrector[:2], z_predictor_corrector[:2])
    output_system("Interpolative Adams for system:", grid, y_inter_adams, z_inter_adams)

run_methods()
