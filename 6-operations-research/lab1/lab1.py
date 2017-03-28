import sys

from scipy.optimize import linprog
from numpy.random import random_sample

# What is x vector:
# x = {x_11, x_12, x_21, x_22}

print("\nUladzislau Bohdan, FAMCS 3/3\nOperations Research\nLab 1, var 3\n")

mode = raw_input("Default or custom params? d/c\n")
if mode == "d":
    print "DEFAULT PARAMS:"

    print "A1 oil production cost:\t $ 5"
    print "A2 oil production cost:\t $ 4"
    print "A1-B1 transfer cost:\t $ 2"
    print "A1-B2 transfer cost:\t $ 3"
    print "A2-B1 transfer cost:\t $ 2"
    print "A2-B2 transfer cost:\t $ 3\n"
    c = [7, 8, 7, 8]

    print "Oil products on B1 plant from A1 oil:\t 3"
    print "Oil products on B1 plant from A2 oil:\t 5"
    print "Oil products on B2 plant from A1 oil:\t 4"
    print "Oil products on B2 plant from A2 oil:\t 3\n"
    A_ub = [[-3, 0, -5, 0],
            [0, -4, 0, -3],
            [0, 1, 1, 0]]

    print "Oil products to produce on plant B1:\t 5000"
    print "Oil products to produce on plant B2:\t 5200\n"

    print "Capacity limit on A1-B2 <-> A2-B1 intermediate point:\t 10000\n"
    b_ub = [-5000,
            -5200,
            10000]

    print "Bounds for A1/A2 oil on intermediate point: [1./3, 2./3]"
    z = 1./3. * random_sample() + 1./3.
    print "Z: {}\n".format(z)

    A_eq = [[0, 1, -z, 0]]
    b_eq = [0]

elif mode == "c":

    print "CUSTOM PARAMS:"

    a1_prod = float(raw_input("A1 oil production cost:\t $ "))
    a2_prod = float(raw_input("A2 oil production cost:\t $ "))
    a1b1_transfer = float(raw_input("A1-B1 transfer cost:\t $ "))
    a1b2_transfer = float(raw_input("A1-B2 transfer cost:\t $ "))
    a2b1_transfer = float(raw_input("A2-B1 transfer cost:\t $ "))
    a2b2_transfer = float(raw_input("A2-B2 transfer cost:\t $ "))
    c = [a1_prod + a1b1_transfer,
        a1_prod + a1b2_transfer,
        a2_prod + a2b1_transfer,
        a2_prod + a2b2_transfer]

    prod_b1a1 = float(raw_input("Oil products on B1 plant from A1 oil:\t "))
    prod_b1a2 = float(raw_input("Oil products on B1 plant from A2 oil:\t "))
    prod_b2a1 = float(raw_input("Oil products on B2 plant from A1 oil:\t "))
    prod_b2a2 = float(raw_input("Oil products on B2 plant from A2 oil:\t "))
    A_ub = [[-prod_b1a1, 0, -prod_b1a2, 0],
            [0, -prod_b2a1, 0, -prod_b2a2],
            [0, 1, 1, 0]]

    produce_b1 = float(raw_input("Oil products to produce on plant B1:\t "))
    produce_b2 = float(raw_input("Oil products to produce on plant B2:\t "))

    cap = float(raw_input("Capacity limit on A1-B2 <-> A2-B1 intermediate point:\t "))
    b_ub = [-produce_b1,
            -produce_b2,
            cap]

    print "Bounds for A1/A2 oil on intermediate point (two floats in [0, 1]):"
    a = float(raw_input())
    b = float(raw_input())
    z = (b - a) * random_sample() + a

    print "Z: {}\n".format(z)

    A_eq = [[0, 1, -z, 0]]
    b_eq = [0]

else:
    print("Bad input.")
    sys.exit()

res = linprog(c, A_ub, b_ub, A_eq, b_eq)


print "------------------------------------------------------------------------"
print "\nALGORITHM OUTPUT:"
print res.message

if res.success:
    print "\nMINIMUM COST:"
    print res.fun
    print "\nOPTIMAL PLAN:"
    print res.x
