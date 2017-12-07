mpicc gauss.c || exit 1
# 10 stangs for matrix size (N).
mpirun -np 2 a.out 12
