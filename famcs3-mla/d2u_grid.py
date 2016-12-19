import matplotlib.pyplot as plt
import math
import numpy.linalg as alg

# Defining the problem
k = lambda x: math.e**x
q = lambda x: math.e**x
f = lambda x: math.e**(-x)
a0 = 1.
m0 = 0.
a1 = 1.
m1 = 1.
x0 = 0.
x1 = 1.

solut = lambda x: -0.158 * math.e**(-1.618*x) + 0.018 * math.e**(0.618*x) - math.e**(-2*x)

# Algorithm parameters
n = 10
h = (x1 - x0) / n

def tridiagonal_matrix_algo(matr, rhs):
    print rhs
    #x = alg.solve(matr, rhs)

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
    print be[1]
    for i in range(1, n):
        al[i+1] = b[i] / (c[i] - al[i]*a[i])
    for i in range(1, n+1):
        be[i+1] = (rhs[i] + be[i]*a[i]) / (c[i] - al[i]*a[i])
        #print be[i+1]

    x[n] = be[n+1]
    for i in range(n-1, -1, -1):
        x[i] = al[i+1]*x[i+1] + be[i+1]

    print x
    xi = []
    si = []
    for i in range(0, n+1):
        xi.append(x0+h*i)
        si.append(solut(x0+h*i))
    plt.plot(xi, x)
    plt.plot(xi, si)
    plt.show()

    # Checking the correctness of the solution of system of linear equations.
    print "residual:"
    for i in range (0, n+1):
        temp = 0.
        for j in range(0, n+1):
            temp += matr[i][j] * x[j]
        print temp - rhs[i]
    return

def d2u_grid():
    matr = [[0. for x in range(n+1)] for y in range(n+1)]
    rhs = [0. for x in range(n+1)]
    for i in range(1, n):
        x = x0 + h * i
        x_prev = x - h
        x_next = x + h
        matr[i][i-1] = k(x) / (h * h) - (k(x_next) - k(x_prev)) / (4 * h * h)
        matr[i][i] = - 2 * k(x) / (h * h) - q(x)
        matr[i][i+1] = (k(x_next) - k(x_prev)) / (4 * h * h) + k(x) / (h * h)
        rhs[i] = -f(x)

    dk_dx = lambda x: math.e**x

    #matr[0][0] = - k(x0) / h - a0 - q(x0)*h/2 - dk_dx(x0)/2
    #matr[0][1] = k(x0) / h + dk_dx(x0) / 2
    #rhs[0] = -m0 - f(x0)*h/2

    #matr[n][n-1] = k(x1) / h + dk_dx(x1) / 2
    #matr[n][n] = - k(x1) / n - a1 + q(x1)*h/2 - dk_dx(x1)/2
    #rhs[n] = -m1 + f(x1)*h/2

    # O(h)
    matr[0][0] = - k(x0) / h - a0
    matr[0][1] = k(x0) / h
    rhs[0] = -m0

    matr[n][n-1] = k(x1) / h
    matr[n][n] = - k(x1) / n - a1
    rhs[n] = -m1

    tridiagonal_matrix_algo(matr, rhs)
    return

d2u_grid()
#n = 4
#tridiagonal_matrix_algo([[2.,1.,0,0,0],[1.,3.,2.,0,0],[0,4.,15.,6.,0],[0,0,1.,12.,4.],[0,0,0,3.,13.]], [3., 6., 25., 17., 16.])
