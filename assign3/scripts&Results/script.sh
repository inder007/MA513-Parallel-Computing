#!/bin/bash

FILE="results2.txt"

# echo "N: " $1 >> $FILE
echo "P:" $1 >> $FILE
echo "Add Numbers Naive" >> $FILE
mpicc ../addNumbersNaive.c
# mpiexec -n $1 ../a.out $1 >> $FILE

for i in {17..29}
do
	# echo $((1<<i))
	mpiexec -n $1 ./a.out $((1<<i)) >> $FILE
done

echo "" >> $FILE
echo "Add Numbers Recursive" >> $FILE
mpicc ../addNumbersRecursive.c
# mpiexec -n $1 ../a.out $1 >> $FILE

echo "" >> $FILE
for i in {17..29}
do
	# echo $((1<<i))
	mpiexec -n $1 ./a.out $((1<<i)) >> $FILE
done

echo "" >> $FILE
echo "Add Numbers Reduce" >> $FILE
mpicc ../addNumersReduce.c
# mpiexec -n $1 ../a.out $1 >> $FILE

for i in {17..29}
do
	# echo $((1<<i))
	mpiexec -n $1 ./a.out $((1<<i)) >> $FILE
done
