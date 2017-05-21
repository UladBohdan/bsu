from scipy.optimize import linprog

# 1st problem.
c = [1, 1, 1, 1]
A = [[-6, -1, 1, -2],
     [-4, -5, -3, -5],
     [-1, -2, -3, 2],
     [-3, -1, 3, -2]]
b = [-1, -1, -1, -1]
x_bounds = ((0, None), (0, None), (0, None), (0, None))

res = linprog(c, A, b, bounds=x_bounds)

print "X vector:"
print res.x

# 2nd problem.
c = [-1, -1, -1, -1]
A = [[6, 4, 1, 3],
     [1, 5, 2, 1],
     [-1, 3, 3, 3],
     [2, 5, -2, -2]]
b = [1, 1, 1, 1]
y_bounds = ((0, None), (0, None), (0, None), (0, None))

res = linprog(c, A, b, bounds=y_bounds)

print "Y vector:"
print res.x
