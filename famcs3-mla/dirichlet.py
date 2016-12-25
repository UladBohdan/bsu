import math

# Defining the Dirichlet problem for Poisson equation.
f = lambda x, y: math.abs(math.sin(math.pi * x * y) ** 3)
psi1 = lambda y: 1 - y * y                          # left.
psi2 = lambda y: 1 - y * y                          # right.
psi3 = lambda x: math.abs(math.sin(math.pi * x))    # bottom.
psi4 = lambda x: math.abs(math.sin(math.pi * x))    # top.
a = -1.
b = 1.
c = -1.
d = 1.

# Algorithm parameters.
hx = 0.05
hy = 0.05
nx = (b - a) / hx + 1
ny = (d - c) / hy + 1

EPS = 1e-5

def dirichlet():
    matr = []
    rhs = []
    for i in range(1, nx-1):
        for j in range(1, ny-1):
            row = [0. for x in range((nx+1)*(ny+1))]
            row[(nx+1)*i + j] = -2 * (1 / hx + 1 / hy)
            if i == 1:
                row[0 + j] = psi3
                row[(nx+1)*2 + j] = 1 / (hx * hx)
            elsif i == ny - 1:
                row[(nx+1)*(nx+1)-1][j] = 1 / (hx * hx)
            else:
                row[(nx+1)*(i+1)]
    return

if nx != 41 or ny != 41:
    print "warning: wrong nx/ny:", nx, ny
else:
    dirichlet()
