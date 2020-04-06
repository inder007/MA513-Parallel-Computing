#!/bin/bash

FILE="Results3.txt"

echo "piCritical with different number of processes and 10000000000 of steps: "
echo "piCritical with different number of processes and 10000000000 of steps: " >> $FILE
gcc -fopenmp ../piCritical.c

for i in {0..5}
do
	./a.out $((1<<i)) 10000000000 >> $FILE
done

echo "" >> $FILE
echo "piReduce with different number of processes and 10000000000 of steps: "
echo "piReduce with different number of processes and 10000000000 of steps: " >> $FILE
gcc -fopenmp ../piReduce.c

for i in {0..5}
do
	./a.out $((1<<i)) 10000000000 >> $FILE
done

echo "" >> $FILE
echo "piCritical with different number of steps and 4 processes: "
echo "piCritical with different number of steps and 4 processes: " >> $FILE
gcc -fopenmp ../piCritical.c

x=1
for i in {1..8}
do
	x=$((10*x))
	./a.out 4 $((1000*x)) >> $FILE
done

echo "" >>$FILE
echo "piReduce with different number of steps and 4 processes: "
echo "piReduce with different number of steps and 4 processes: " >> $FILE
gcc -fopenmp ../piReduce.c

y=1
for i in {1..8}
do
	y=$((10*y))
	./a.out 4 $((1000*y)) >> $FILE
done