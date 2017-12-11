#!/bin/bash
mpicc gauss.c || exit 1
# 10 stangs for matrix size (N).
mpirun -np $1 a.out $2
