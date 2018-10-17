import urllib
import bz2
import os
import numpy as np

from scipy.sparse import lil_matrix

import matplotlib.pyplot as plt

import time
from scipy.optimize import least_squares

FILE_NAME = "problem-49-7776-pre.txt.bz2"

""" File format:
<num_cameras> <num_points> <num_observations>
<camera_index_1> <point_index_1> <x_1> <y_1>
...
<camera_index_num_observations> <point_index_num_observations> <x_num_observations> <y_num_observations>
<camera_1>
...
<camera_num_cameras>
<point_1>
...
<point_num_points>

Where, there camera and point indices start from 0.
Each camera is a set of 9 parameters - R,t,f,k1 and k2. The rotation R is specified as a Rodrigues' vector.
"""
def read_bal_data(file_name):
    with bz2.BZ2File(file_name, "r") as file:
        n_cameras, n_points, n_observations = map(int, file.readline().split())
        #  49        7776        31843     (in our test case)

        # An observation = a 2d point on one of the "photos".
        # Every observation belongs to an image aka camera.

        camera_indices = np.empty(n_observations, dtype=int)
        point_indices = np.empty(n_observations, dtype=int)
        points_2d = np.empty((n_observations, 2))

        # Reading 2d points. Each one corresponds with camera and 3d point.
        for i in range(n_observations):
            camera_index, point_index, x, y = file.readline().split()
            camera_indices[i] = int(camera_index)
            point_indices[i] = int(point_index)
            points_2d[i] = [float(x), float(y)]

        # Reading inner camera params. Each camera = 9 params R,t,f,k1,k2.
        camera_params = np.empty(n_cameras * 9)
        for i in range(n_cameras * 9):
            camera_params[i] = float(file.readline())
        camera_params = camera_params.reshape((n_cameras, -1))

        # Reading 3d points. Approximations, right?
        # Where they go from in real life?
        points_3d = np.empty(n_points * 3)
        for i in range(n_points * 3):
            points_3d[i] = float(file.readline())
        points_3d = points_3d.reshape((n_points, -1))

    return camera_params, points_3d, camera_indices, point_indices, points_2d

camera_params, points_3d, camera_indices, point_indices, points_2d = read_bal_data(FILE_NAME)

n_cameras = camera_params.shape[0]
n_points = points_3d.shape[0]

# if some data is retrieved from other sources (like photo EXIF) - than 9 -> 6.
n = 9 * n_cameras + 3 * n_points
m = 2 * points_2d.shape[0]

print("n_cameras: {}".format(n_cameras))
print("n_points: {}".format(n_points))
print("Total number of parameters: {}".format(n))
print("Total number of residuals: {}".format(m))

def rotate(points, rot_vecs):
    """Rotate points by given rotation vectors.
    Rodrigues' rotation formula is used.
    """
    # Magic.
    theta = np.linalg.norm(rot_vecs, axis=1)[:, np.newaxis]
    with np.errstate(invalid='ignore'):
        v = rot_vecs / theta
        v = np.nan_to_num(v)
    dot = np.sum(points * v, axis=1)[:, np.newaxis]
    cos_theta = np.cos(theta)
    sin_theta = np.sin(theta)

    return cos_theta * points + sin_theta * np.cross(v, points) + dot * (1 - cos_theta) * v

def project(points, camera_params):
    """Convert 3-D points to 2-D by projecting onto images."""
    # Using a formula of conversion to pixel coordinates. Take a look on your notes.
    points_proj = rotate(points, camera_params[:, :3])
    points_proj += camera_params[:, 3:6]
    points_proj = -points_proj[:, :2] / points_proj[:, 2, np.newaxis]
    f = camera_params[:, 6]
    k1 = camera_params[:, 7]
    k2 = camera_params[:, 8]
    n = np.sum(points_proj**2, axis=1)
    r = 1 + k1 * n + k2 * n**2
    points_proj *= (r * f)[:, np.newaxis]
    return points_proj

def fun(params, n_cameras, n_points, camera_indices, point_indices, points_2d):
    """Compute residuals.
    'params' contains camera parameters and 3-D coordinates.
    """
    # Why it's 'fun'?
    camera_params = params[:n_cameras * 9].reshape((n_cameras, 9))
    points_3d = params[n_cameras * 9:].reshape((n_points, 3))
    points_proj = project(points_3d[point_indices], camera_params[camera_indices])
    # ravel() return a contiguous flattened array.
    # Whatever they mean by saying that.
    return (points_proj - points_2d).ravel()

# camera_index means which camera made current 2d point.
# point_index is a number of 3d point which corresponds with current 2d point.
def bundle_adjustment_sparsity(n_cameras, n_points, camera_indices, point_indices):
    # We know that.
    m = camera_indices.size * 2
    # We're searching for that.
    n = n_cameras * 9 + n_points * 3
    A = lil_matrix((m, n), dtype=int)

    i = np.arange(camera_indices.size)
    for s in range(9):
        A[2 * i, camera_indices * 9 + s] = 1
        A[2 * i + 1, camera_indices * 9 + s] = 1

    for s in range(3):
        A[2 * i, n_cameras * 9 + point_indices * 3 + s] = 1
        A[2 * i + 1, n_cameras * 9 + point_indices * 3 + s] = 1

    # Here we're just marking elements, which are known, as non-zeros.
    # Reason why we need that:
    # To make this process time feasible we provide Jacobian sparsity structure.

    return A

# np.hstack() stack arrays in sequence horizontally (column wise).
x0 = np.hstack((camera_params.ravel(), points_3d.ravel()))

# getting the first approximation. Because we have some 3d points inside the x0, which is 'params'.
f0 = fun(x0, n_cameras, n_points, camera_indices, point_indices, points_2d)

plt.plot(f0)

A = bundle_adjustment_sparsity(n_cameras, n_points, camera_indices, point_indices)
t0 = time.time()

# HERE things happen.
# it's from scipy.optimize
# list of params is here https://docs.scipy.org/doc/scipy-0.17.0/reference/generated/scipy.optimize.least_squares.html

# trf : Trust Region Reflective algorithm, particularly suitable for large sparse problems with bounds. Generally robust method.
# lm : Levenberg-Marquardt algorithm as implemented in MINPACK. Doesn't handle bounds and sparse Jacobians.
# Usually the most efficient method for small unconstrained problems.

# 'lm' requires some conditions which I don't fully understand, so I do not know how to run it.
res = least_squares(fun, x0, jac_sparsity=A, verbose=2, x_scale='jac', ftol=1e-4, method='trf',
                    args=(n_cameras, n_points, camera_indices, point_indices, points_2d))
t1 = time.time()
print("Optimization took {0:.0f} seconds".format(t1 - t0))
plt.plot(res.fun)
plt.show()
