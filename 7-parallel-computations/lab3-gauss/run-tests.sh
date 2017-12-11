#!/bin/bash

MATRIX_SIZE=2100

printf "Gauss method to solve system of linear equations.\n"
printf "Matrix size is %s\n" $MATRIX_SIZE
for i in {1..4}
do
  printf "===\n=== NUMBER OF PROCESSES:  %s\n===\n" $i
  bash run.sh $i $MATRIX_SIZE
done
