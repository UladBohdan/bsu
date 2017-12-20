#!/bin/bash

mpicc gauss.c || exit 1
# $1 is for number of processes, $2 - matrix size, 5 - R1 (sample value), 10 - R3 (sample)
mpirun -np $1 a.out $2 5 10
