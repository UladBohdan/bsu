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

def series(grid, k, n):
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

def euler_explicit(grid, k, n):
    yi = [u0]
    f = du_dx
    for i in range(1, len(grid)):
        x = grid[i]
        step = grid[i] - grid[i-1]
        yi.append( yi[-1] + step*f(x,yi[-1]) )
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

    y_series = series(grid, k, n)
    output("Series method:", grid, y_series)
    plt.plot(grid, y_series, color='blue')

    y_euler_explicit  = euler_explicit(grid, k, n)
    output("Explicit Euler:", grid, y_euler_explicit)
    plt.plot(grid, y_euler_explicit, color='green')

    plt.show()

run_methods()
