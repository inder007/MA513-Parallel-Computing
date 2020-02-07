#!/bin/bash

FILE="sortResults.txt"

echo "P: 2" >> $FILE
mpicc ../oddEvenSorting.c

for i in {17..25}
do
	# echo $((1<<i))
	mpiexec -n 2 ./a.out $((1<<i)) >> $FILE
done

echo "" >> $FILE
echo "-" >> $FILE
echo "" >> $FILE

echo "P: 4" >> $FILE
# mpicc ../oddEvenSorting.c

for i in {17..25}
do
	# echo $((1<<i))
	mpiexec -n 4 ./a.out $((1<<i)) >> $FILE
done

echo "" >> $FILE
echo "-" >> $FILE
echo "" >> $FILE

echo "P: 8" >> $FILE
# mpicc ../oddEvenSorting.c

for i in {17..25}
do
	# echo $((1<<i))
	mpiexec -n 8 ./a.out $((1<<i)) >> $FILE
done

echo "" >> $FILE
echo "-" >> $FILE
echo "" >> $FILE

echo "P: 16" >> $FILE
# mpicc ../oddEvenSorting.c

for i in {17..25}
do
	# echo $((1<<i))
	mpiexec -n 16 ./a.out $((1<<i)) >> $FILE
done

echo "" >> $FILE
echo "-" >> $FILE
echo "" >> $FILE

echo "P: 32" >> $FILE
# mpicc ../oddEvenSorting.c

for i in {17..25}
do
	# echo $((1<<i))
	mpiexec -n 32 ./a.out $((1<<i)) >> $FILE
done