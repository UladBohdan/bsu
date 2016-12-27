import matplotlib.pyplot as plt
import math
import numpy.linalg as alg

import scipy.integrate as integrate

EPS = 1e-6

# Defining the problem.
k = lambda x: math.e**x
q = lambda x: math.e**x
f = lambda x: math.e**(-x)
a0 = 1.
m0 = 0.
a1 = 1.
m1 = 1.
x_range = [0., 1.]
x0 = x_range[0]
x1 = x_range[1]

# is that a solution?
exact_solution = lambda x: 1.141 * math.e**(-1.618*x) + 0.339 * math.e**(0.618*x) - math.e**(-2*x)

# for Ritz algorithm.
n_ritz = 5
n_integrate = 100
# in general case we have to calculate that using the border conditions, as we don't have
# an exact solution.
fi0 = lambda x: (exact_solution(1) - exact_solution(0)) * x + exact_solution(0)
fi0_dx = lambda x: exact_solution(1) - exact_solution(0)

# Algorithm parameters.
n = 10
h = (x_range[1] - x_range[0]) / n
grid = [x_range[0] + i * h for i in range(n+1)]

def intergrate_simpson(a, b, f):
    sum = 0
    h = (b - a) / n_integrate
    for i in range (1, n_integrate):
        sum += f(a + h*(i-1)) + 4 * f(a + h*(i-0.5)) + f(a + h * i)
    sum = sum * h / 6.
    return sum

def ritz():
    # Defining fi and fi_dx.
    fi = lambda x, i: (x - x0)**(i + 1) * (x - x1)**2
    fi_dx = lambda x, i: (i + 1) * (x - x0)**i * (x - x1)**2 + (x - x0)**(i + 1) * 2 * (x - x1)

    # Allocating memory for system of linear equations.
    matr = [[0. for x in range(n_ritz)] for y in range(n_ritz)]
    rhs = [0. for x in range(n_ritz)]

    for i in range (1, n_ritz+1):
        for j in range(1, n_ritz+1):
            func1 = lambda x: k(x) * fi_dx(x, i) * fi_dx(x, j) + q(x) * fi(x, i) * fi(x, j)
            matr[i-1][j-1] = intergrate_simpson(x0, x1, func1)
        func2 = lambda x: fi(x, i) * f(x)
        func3 = lambda x: k(x) * fi_dx(x, i) * fi0_dx(x) + q(x) * fi(x, i) * fi0(x)
        rhs[i-1] = intergrate_simpson(x0, x1, func2) - intergrate_simpson(x0, x1, func3)
    a = alg.solve(matr, rhs)

    x = []
    for i in range(0, len(grid)):
        temp = fi0(grid[i])
        for j in range(0, n_ritz):
            temp += a[j] * fi(grid[i], j+1)
        x.append(temp)

    return x

def tridiagonal_matrix_algo(matr, rhs):
    a = [0. for x in range(n+1)]
    c = [0. for x in range(n+1)]
    b = [0. for x in range(n+1)]
    al = [0. for x in range(n+2)]
    be = [0. for x in range(n+2)]
    x = [0. for x in range(n+1)]

    for i in range(1, n):
        a[i] = -matr[i][i-1]
        b[i] = -matr[i][i+1]
        c[i] = matr[i][i]
    b[0] = -matr[0][1]
    c[0] = matr[0][0]
    a[n] = -matr[n][n-1]
    c[n] = matr[n][n]

    al[1] = b[0] / c[0]
    be[1] = rhs[0] / c[0]
    for i in range(1, n):
        al[i+1] = b[i] / (c[i] - al[i]*a[i])
    for i in range(1, n+1):
        be[i+1] = (rhs[i] + be[i]*a[i]) / (c[i] - al[i]*a[i])

    x[n] = be[n+1]
    for i in range(n-1, -1, -1):
        x[i] = al[i+1]*x[i+1] + be[i+1]

    # Checking the correctness of the solution of system of linear equations.
    print "checking the solution..."
    for i in range (0, n+1):
        temp = 0.
        for j in range(0, n+1):
            temp += matr[i][j] * x[j]
        if temp - rhs[i] > EPS:
            print "incorrect"
            return
    print "correct"
    return x

def grid_algorithm():
    matr = [[0. for x in range(n+1)] for y in range(n+1)]
    rhs = [0. for x in range(n+1)]
    for i in range(1, n):
        x = x0 + h * i
        x_prev = x - h
        x_next = x + h
        matr[i][i-1] = k(x) / (h * h) - (k(x_next) - k(x_prev)) / (4 * h * h)
        matr[i][i] = - 2 * k(x) / (h * h) - q(x)
        matr[i][i+1] = (k(x_next) - k(x_prev)) / (4 * h * h) + k(x) / (h * h)
        rhs[i] = - f(x)

    matr[0][0] = - k(x0) / h - a0 - q(x0)*h/2 - (k(x0 + h) - k(x0))/(2 * h)
    matr[0][1] = k(x0) / h + (k(x0 + h) - k(x0))/(2 * h)
    rhs[0] = - m0 - f(x0)*h/2

    matr[n][n-1] = + k(x1) / h - (k(x1) - k(x1 - h))/(2 * h)
    matr[n][n] = - k(x1) / h - a1 - q(x1)*h/2 + (k(x1) - k(x1 - h))/(2 * h)
    rhs[n] = - m1 - f(x1)*h/2

    x = tridiagonal_matrix_algo(matr, rhs)
    return x

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
    for i in range(0, len(grid)):
        y_exact.append(exact_solution(grid[i]))
    output("Exact solution:", grid, y_exact)
    plt.plot(grid, y_exact, color="red")

    y_ritz = ritz()
    output("Ritz:", grid, y_ritz)
    output_diff("Ritz:", grid, y_exact, y_ritz)
    plt.plot(grid, y_ritz, color="green")

    y_grids = grid_algorithm()
    output("Grid algorithm:", grid, y_grids)
    output_diff("Grids:", grid, y_exact, y_grids)
    plt.plot(grid, y_grids, color="blue")

    plt.show()

run_methods()
