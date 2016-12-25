import matplotlib.pyplot as plt
import math
import numpy.linalg as alg

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

# for Ritz algorithm.
n_ritz = 5
n_integrate = 100
fi0 = lambda x, i: 0
fi0_dx = lambda x, i: 0

# is that a solution?
exact_solution = lambda x: -0.158 * math.e**(-1.618*x) + 0.018 * math.e**(0.618*x) - math.e**(-2*x)

# Algorithm parameters.
n = 10
h = (x_range[1] - x_range[0]) / n
grid = []
for i in range(0, n+1):
    grid.append(x_range[0] + i * h)

def intergrate_simpson(a, b, f):
    sum = 0
    h = (b - a) / n_integrate
    for i in range (1, n_integrate):
        sum += f(a + h*(i-1)) + 4 * f(a + h*(i-0.5)) + f(a + h * i)
    sum = sum * h / 6.
    return sum

def ritz():
    # Defining fi and fi_dx.
    fi = [fi0]
    fi_dx = [fi0_dx]
    for i in range(1, n_ritz+1):
        fi_temp = lambda x, i: (x - x0)**(i + 1) * (x - x1)**2
        fi.append(fi_temp)
        fi_dx_temp = lambda x, i: (i + 1) * (x - x0)**i * 2 * (x - x1)
        fi_dx.append(fi_dx_temp)

    matr = [[0. for x in range(n_ritz)] for y in range(n_ritz)]
    rhs = [0. for x in range(n_ritz)]

    for i in range (1, n_ritz+1):
        for j in range(1, n_ritz+1):
            func1 = lambda x: k(x) * fi_dx[i](x, i) * fi_dx[j](x, j) + q(x) * fi[i](x, i) * fi[j](x, j)
            matr[i-1][j-1] = intergrate_simpson(x0, x1, func1)
        func2 = lambda x: fi[i](x, i) * f(x)
        func3 = lambda x: k(x) * fi_dx[i](x, i) * fi_dx[0](x, 0) + q(x) * fi[i](x, i) * fi[i](x, 0)
        rhs[i-1] = intergrate_simpson(x0, x1, func2) - intergrate_simpson(x0, x1, func3)
    a = alg.solve(matr, rhs)
    print "integrals:"
    print matr
    print rhs
    print "AAA::", a

    x = []
    for i in range(0, len(grid)):
        temp = fi0(grid[i], 0)
        for j in range(0, n_ritz):
            temp += a[j] * fi[j+1](grid[i], j+1)
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

    '''print "vector yi:"
    print x
    xi = []
    si = []
    for i in range(0, n+1):
        xi.append(x0+h*i)
        si.append(exact_solution(x0+h*i))
    plt.plot(xi, x)
    plt.plot(xi, si)
    plt.show()'''

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

    #dk_dx = lambda x: math.e**x

    # O(h^2)
    matr[0][0] = - k(x0) / h - a0 - q(x0)*h/2 - (k(x0 + h) - k(x0))/(2 * h)
    matr[0][1] = k(x0) / h + (k(x0 + h) - k(x0))/(2 * h)
    rhs[0] = -m0 - f(x0)*h/2

    matr[n][n-1] = - k(x1) / h + (k(x1) - k(x1 - h))/(2 * h)
    matr[n][n] = - k(x1) / n - a1 + q(x1)*h/2 + (k(x1) - k(x1 - h))/(2 * h)
    rhs[n] = - m1 - f(x1)*h/2

    #matr[0][0] = - k(x0) / h - a0 - q(x0)*h

    # O(h) - seems to be the same as the version above.
    '''matr[0][0] = - k(x0) / h - a0
    matr[0][1] = - (x0) / h
    rhs[0] = -m0

    matr[n][n-1] = - k(x1) / h
    matr[n][n] = - k(x1) / n - a1
    rhs[n] = -m1'''

    x = tridiagonal_matrix_algo(matr, rhs)
    print "XXX: ", x
    return x

def output(header, x, y):
    print header
    for i in range(0, len(x)):
        print 'y({0}) = {1}'.format(x[i], y[i])

def run_methods():
    y_exact = []
    for i in range(0, len(grid)):
        y_exact.append(exact_solution(grid[i]))
    output("Exact solution:", grid, y_exact)
    plt.plot(grid, y_exact, color="red")

    y_ritz = ritz()
    output("Ritz:", grid, y_ritz)
    plt.plot(grid, y_ritz, color="green")

    y_grids = grid_algorithm()
    output("Grid algorithm:", grid, y_grids)
    plt.plot(grid, y_grids, color="blue")

    plt.show()

run_methods()
#n = 4
#tridiagonal_matrix_algo([[2.,1.,0,0,0],[1.,3.,2.,0,0],[0,4.,15.,6.,0],[0,0,1.,12.,4.],[0,0,0,3.,13.]], [3., 6., 25., 17., 16.])
