import math
import matplotlib.pyplot as plt

# Defining the Cauchy problem for equation.
f = lambda x, u: - u * math.cos(x) + math.sin(x) * math.cos(x)
x_range = [0., 1.]
x0 = 0.
u0 = -1.

du_dx = f

# Defining a grid to make calculations on.
n = 10
h = (x_range[1] - x_range[0]) / n
grid = [x_range[0] + i * h for i in range(n+1)]

# Exact solution of the problem.
exact_solution = lambda x: -1 + math.sin(x)

# Some pre-calculations. k is for highest degree of derivations.
k = 3
d_dx = [
    lambda x, u: u0,
    lambda x, u: du_dx(x, u),
    lambda x, u: u * math.sin(x) + math.cos(2 * x) + f(x, u) * (- math.cos(x)),
    lambda x, u: u * math.cos(x) - 2 * math.sin(2 * x) + 2 * math.sin(x) * f(x, u) - math.cos(x) * d_dx[2](x, u),
]

# Constants for algorithms.
EPS = 1e-5
MAX_NEWTON_ITERATIONS = 100

def series():
    yi = [u0]
    for i in range(1, len(grid)):
        x = grid[i-1]
        step = grid[i] - grid[i-1]
        y = yi[i-1]
        for j in range(1, k+1):
            y += d_dx[j](x, yi[i-1]) / math.factorial(j) * (step**j)
        yi.append(y)
    return yi

def euler_explicit():
    yi = [u0]
    for i in range(1, len(grid)):
        x = grid[i-1]
        step = grid[i] - grid[i-1]
        yi.append( yi[-1] + step*f(x,yi[-1]) )
    return yi

def euler_implicit():
    yi = [u0]
    for i in range(1, len(grid)):
        step = grid[i] - grid[i-1]
        yi.append(newton_iterations(step, grid[i], yi[i-1]))
    return yi

def newton_iterations(step, x, y0):
    y_prev = y0
    iter = MAX_NEWTON_ITERATIONS
    df_dy = lambda x, u: - math.cos(x)
    while iter > 0:
        y_new = y_prev - (y_prev - y0 - step * f(x, y_prev)) / (1. - step * df_dy(x, y_prev))
        iter -= 1
        if abs(y_prev - y_new) < EPS:
            return y_new
        y_prev = y_new
    print "newton iterations: no convergence"
    return

def predictor_corrector():
    yi4 = [u0]
    for i in range(1, len(grid)):
        step = grid[i] - grid[i-1]
        y_n4_2 = yi4[i-1] + step * f(grid[i-1], yi4[i-1]) / 4.
        y_n2_3 = yi4[i-1] + step * f(grid[i-1] + step / 4., y_n4_2) / 2.
        y3 = yi4[i-1] + step * f(grid[i-1] + step / 2., y_n2_3)
        y4 = yi4[i-1] + step * ( f(grid[i-1], yi4[i-1]) + 4 * f(grid[i-1] + step/2., y_n2_3) + f(grid[i], y3) ) / 6.
        yi4.append(y4)
    return yi4

def runge_kutta():
    yi = [u0]
    a0 = 0.
    a1 = 1.
    for i in range(1, len(grid)):
        step = grid[i] - grid[i-1]
        fi0 = step * f(grid[i-1], yi[i-1])
        fi1 = step * f(grid[i-1] + step/2., yi[i-1] + fi0/2.)
        y_new = yi[i-1] + a0 * fi0 + a1 * fi1
        yi.append(y_new)
    return yi

def extra_adams(approx):
    yi = approx
    for i in range(3, len(grid)):
        step = grid[i] - grid[i-1]
        y_new = yi[i-1] + step * (23 * f(grid[i-1], yi[i-1]) - 16 * f(grid[i-2], yi[i-2]) + 5 * f(grid[i-3], yi[i-3])) / 12.
        yi.append(y_new)
    return yi

def output(header, x, y):
    print header
    for i in range(0, len(x)):
        print 'y({0}) = {1}'.format(x[i], y[i])

def output_diff(header, x, u, y):
    print header
    for i in range(0, len(x)):
        print 'u({0}) - y({1}) = {2}'.format(x[i], x[i], u[i] - y[i])

def run_methods():
    y_exact = []
    for x in grid:
        y_exact.append(exact_solution(x))
    output("Exact solution: ", grid, y_exact)
    plt.plot(grid, y_exact, color='red')

    y_series = series()
    output("Series method:", grid, y_series)
    output_diff("Series method", grid, y_exact, y_series)
    plt.plot(grid, y_series, color='blue')

    y_euler_explicit  = euler_explicit()
    output("Explicit Euler:", grid, y_euler_explicit)
    output_diff("Explicit Euler:", grid, y_exact, y_euler_explicit)
    plt.plot(grid, y_euler_explicit, color='green')

    y_euler_implicit = euler_implicit()
    output("Implicit Euler: ", grid, y_euler_implicit)
    output_diff("Implicit Euler: ", grid, y_exact, y_euler_implicit)
    plt.plot(grid, y_euler_implicit, color="black")

    y_predictor_corrector = predictor_corrector()
    output("Predictor-corrector:", grid, y_predictor_corrector)
    output_diff("Predictor-corrector:", grid, y_exact, y_predictor_corrector)
    plt.plot(grid, y_predictor_corrector, color="brown")

    y_runge_kutta = runge_kutta()
    output("Runge-Kutta:", grid, y_runge_kutta)
    output_diff("Runge-Kutta:", grid, y_exact, y_runge_kutta)
    plt.plot(grid, y_runge_kutta, color="yellow")

    y_extra_adams = extra_adams(y_predictor_corrector[:3])
    output("Extra Adams:", grid, y_extra_adams)
    output_diff("Extra Adams:", grid, y_exact, y_extra_adams)
    plt.plot(grid, y_extra_adams, color="blue")

    plt.show()

run_methods()
