#!/bin/bash

FILE="Results.txt"

echo "School Method changing size of problem: "
echo "School Method changing size of problem: " >> $FILE
g++ -pthread -fopenmp ../schoolMethod.cpp

for i in {9..16}
do
	./a.out $((1<<i)) 4 >> $FILE
done

echo "" >> $FILE
echo "School Method changing number of threads: "
echo "School Method changing number of threads: " >> $FILE
g++ -pthread -fopenmp ../schoolMethod.cpp

for i in {0..4}
do
	./a.out $((1<<16)) $((1<<i)) >> $FILE
done

