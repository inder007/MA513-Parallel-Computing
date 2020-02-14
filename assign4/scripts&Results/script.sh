#!/bin/bash

FILE="Results.txt"

# echo "N: " $1 >> $FILE
echo "P:" $1 >> $FILE
echo "Row Division running" >> $FILE
echo "Row Division running"
mpicc ../rowdiv.c
# mpiexec -n $1 ../a.out $1 >> $FILE

for i in {6..14}
do
	# echo $((1<<i))
	mpiexec -n $1 ./a.out $((1<<i)) >> $FILE
done


echo "" >> $FILE
echo "Col Division running" >> $FILE
echo "Col Division running"
mpicc ../coldiv.c
# mpiexec -n $1 ../a.out $1 >> $FILE

echo "" >> $FILE
for i in {6..14}
do
	# echo $((1<<i))
	mpiexec -n $1 ./a.out $((1<<i)) >> $FILE
done

echo "" >> $FILE
echo "Block Division running" >> $FILE
echo "Block Division running"
mpicc ../blockdiv.c -lm
# mpiexec -n $1 ../a.out $1 >> $FILE

for i in {6..14}
do
	# echo $Val >> $FILE
	# echo $((1<<i))
	mpiexec -n $1 ./a.out $((1<<i)) >> $FILE
done
