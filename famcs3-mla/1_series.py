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

def series(k, n):
    print "Simple Taylor series approximation coefficients:"
    for i in range(0, k+1):
        print 'x^{0} * {1}'.format(i, d_dx[i](x0, u0) / math.factorial(i))

    ans = []
    print 'Approximating on a regular grid:'
    step = (x_range[1] - x_range[0]) / n
    u = u0
    for i in range(0, n):
        x = x0 + (i+1) * step
        y = u
        for j in range(1, k+1):
            y += d_dx[j](x, u) / math.factorial(j) * step**j
        print 'y({0}) = {1}'.format(x, y)
        u = y
        ans.append(y)

    return ans

#series(k = 3, n = 10)

def euler_explicit(k, n):
    ans = []

    print "Explicit Euler:"
    f = du_dx
    y = u0
    step = (x_range[1] - x_range[0]) / n
    for i in range(0, n):
        x = x0 + i * step
        y_new = y + step*f(x,y)
        print 'y({0}) = {1}'.format(x + step, y_new)
        ans.append(y_new)
        y = y_new

    return ans

#euler_explicit(k = 3, n = 10)

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
    plt.plot(grid, y0)

    plt.plot(grid, series(k, n))

    plt.plot(grid, euler_explicit(k, n))

    plt.show()

run_methods()
