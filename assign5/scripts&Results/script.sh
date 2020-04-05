#!/bin/bash

FILE="Results.txt"

# echo "N: " $1 >> $FILE
echo "P:" $1 >> $FILE
echo "Gaussian Elimination" >> $FILE
echo "Gaussian Elimination"
mpicc ../gaussionElimination.c
# mpiexec -n $1 ../a.out $1 >> $FILE

for i in {5..14}
do
	# echo $((1<<i))
	mpiexec -n $1 ./a.out $((1<<i)) >> $FILE
done

echo "P:" $1 >> $FILE
echo "Pipelined Gaussian Elimination" >> $FILE
echo "Pipelined Gaussian Elimination"
mpicc ../pipelinedGaussianElimination.c
# mpiexec -n $1 ../a.out $1 >> $FILE

for i in {5..14}
do
	# echo $((1<<i))
	mpiexec -n $1 ./a.out $((1<<i)) >> $FILE
done
