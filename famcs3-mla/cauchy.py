import math
import matplotlib.pyplot as plt

du_dx = lambda x, u: - u * math.cos(x) + math.sin(x) * math.cos(x)
x_range = [0., 1.]
x0 = 0
u0 = -1

exact_solution = lambda x: -1 + math.sin(x)

d_dx = [
    lambda x, u: u0,
    lambda x, u: du_dx(x, u),
    lambda x, u: u * math.sin(x) + math.cos(2 * x),
    lambda x, u: u * math.cos(x) - 2 * math.sin(2 * x),
]

EPS = 1e-5
MAX_NEWTON_ITERATIONS = 100

def series(grid, k):
    print "Simple Taylor series approximation coefficients:"
    for i in range(0, k+1):
        print 'x^{0} * {1}'.format(i, d_dx[i](x0, u0) / math.factorial(i))

    yi = [u0]
    for i in range(1, len(grid)):
        x = grid[i]
        step = grid[i] - grid[i-1]
        y = yi[-1]
        for j in range(1, k+1):
            y += d_dx[j](x, y) / math.factorial(j) * step**j
        yi.append(y)
    return yi

def euler_explicit(grid):
    yi = [u0]
    f = du_dx
    for i in range(1, len(grid)):
        x = grid[i]
        step = grid[i] - grid[i-1]
        yi.append( yi[-1] + step*f(x,yi[-1]) )
    return yi

def euler_implicit(grid):
    yi = [u0]
    f = du_dx
    for i in range(1, len(grid)):
        step = grid[i] - grid[i-1]
        yi.append(newton_iterations(yi[i-1], step, f, grid[i], yi[i-1]))
    return yi

def newton_iterations(base, step, f, x, y0):
    y_prev = y0
    iter = MAX_NEWTON_ITERATIONS
    while iter > 0:
        y_new = base + step * f(x, y_prev)
        iter -= 1
        if abs(y_prev - y_new) < EPS:
            return y_new
        y_prev = y_new
    print "newton iterations: no convergence"
    return y0

def predictor_corrector(grid):
    yi4 = [u0]
    f = du_dx
    for i in range(1, len(grid)):
        step = grid[i] - grid[i-1]
        y_n4_2 = yi4[i-1] + step * f(grid[i-1], yi4[i-1]) / 4.
        y_n2_3 = yi4[i-1] + step * f(grid[i-1] + step / 4., y_n4_2) / 2.
        y3 = yi4[i-1] + step * f(grid[i-1] + step / 2., y_n2_3)
        y4 = yi4[i-1] + step * ( f(grid[i-1], yi4[i-1]) + 4 * f(grid[i-1] + step/2., y_n2_3) + f(grid[i], y3) ) / 6.
        yi4.append(y4)
    return yi4

def runge_kutta(grid):
    yi = [u0]
    f = du_dx
    a0 = 0.
    a1 = 1.
    for i in range(1, len(grid)):
        step = grid[i] - grid[i-1]
        tetta0 = step * f(grid[i-1], yi[i-1])
        tetta1 = step * f(grid[i-1] + step/2., yi[i-1] + tetta0/2.)
        y_new = yi[i-1] + a0 * tetta0 + a1 * tetta1
        yi.append(y_new)
    return yi

def extra_adams(grid, approx):
    yi = approx
    f = du_dx
    print "Approx len: ", len(yi)
    for i in range(3, len(grid)):
        step = grid[i] - grid[i-1]
        y_new = yi[i-1] + step * (23 * f(grid[i-1], yi[i-1]) - 15 * f(grid[i-2], yi[i-2]) + 5 * f(grid[i-3], yi[i-3])) / 12.
        yi.append(y_new)
    return yi

def output(header, x, y):
    print header
    for i in range(0, len(x)):
        print 'y({0}) = {1}'.format(x[i], y[i])

def run_methods():
    k = 3
    n = 10
    h = (x_range[1] - x_range[0]) / n
    grid = []
    for i in range(0, n):
        grid.append(x_range[0] + i * h)

    y0 = []
    for x in grid:
        y0.append(exact_solution(x))
    plt.plot(grid, y0, color='red')

    y_series = series(grid, k)
    output("Series method:", grid, y_series)
    plt.plot(grid, y_series, color='blue')

    y_euler_explicit  = euler_explicit(grid)
    output("Explicit Euler:", grid, y_euler_explicit)
    plt.plot(grid, y_euler_explicit, color='green')

    y_euler_implicit = euler_implicit(grid)
    output("Implicit Euler: ", grid, y_euler_implicit)
    plt.plot(grid, y_euler_implicit, color="black")

    y_predictor_corrector = predictor_corrector(grid)
    output("Predictor-corrector:", grid, y_predictor_corrector)
    plt.plot(grid, y_predictor_corrector, color="brown")

    y_runge_kutta = runge_kutta(grid)
    output("Runge-Kutta:", grid, y_runge_kutta)
    plt.plot(grid, y_runge_kutta, color="yellow")

    y_extra_adams = extra_adams(grid, y_predictor_corrector[:3])
    output("Extra Adams:", grid, y_extra_adams)
    plt.plot(grid, y_extra_adams, color="red")

    plt.show()

run_methods()
