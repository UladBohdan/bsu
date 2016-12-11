import math
import sys

du_dx = lambda x, u: - u * math.cos(x) + math.sin(x) * math.cos(x)
x_range = [0., 1.]
x0 = 0
u0 = -1

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

    return

#series(k = 3, n = 10)

def euler_explicit(k, n):
    print "Explicit Euler:"
    f = du_dx
    y = u0
    step = (x_range[1] - x_range[0]) / n
    for i in range(0, n):
        x = x0 + i * step
        y_new = y + step*f(x,y)
        print 'y({0}) = {1}'.format(x + step, y_new)
        y = y_new

    return

euler_explicit(k = 3, n = 10)
