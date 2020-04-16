#!/bin/bash

FILE="FinalResults.txt"

echo "School Method changing size of problem and threads: "
echo "School Method changing size of problem and threads: " >> $FILE
g++ -pthread -fopenmp ../schoolMethod.cpp

for j in {0..4}
do
for i in {10..16}
do
	./a.out $((1<<i)) $((1<<j)) >> $FILE
done
echo "--" >> $FILE
echo $((1<<j)) >> $FILE
echo " " >> $FILE
done

echo "" >> $FILE
echo "Karatsuba Method changing number of threads and size: "
echo "Karatsuba Method changing number of threads and size: " >> $FILE
g++ -pthread -fopenmp ../parallelKaratsuba.cpp

for j in {0..3}
do
for i in {10..16}
do
	./a.out $((1<<i)) $((1<<j)) >> $FILE
done
echo "--" >> $FILE
echo $((1<<j)) >> $FILE
echo " " >> $FILE
done

