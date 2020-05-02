#!/bin/bash

FILE="results2.txt"

echo "changing number of number of threads and size of string for trivial reduction: "
echo "changing number of number of threads and size of string for trivial reduction: " >> $FILE
g++ ../paralleldfa.cpp -fopenmp

for i in {0..4}
do
echo $((1<<i)) >> $FILE
echo "---" >> $FILE
echo $((1<<i))
echo "----"
for j in {22..30}
do
	echo $((1<<j))
	./a.out $((1<<i)) $((1<<j)) 0 < 3DFAinput.txt >> $FILE
done
echo " " >> $FILE
echo " "
done

echo " "

echo "changing number of number of threads and size of string for binary reduction: "
echo "changing number of number of threads and size of string for binary reduction: " >> $FILE
g++ ../paralleldfa.cpp -fopenmp

for i in {0..4}
do
echo $((1<<i)) >> $FILE
echo "---" >> $FILE
echo $((1<<i))
echo "----"
for j in {22..30}
do
	echo $((1<<j))
	./a.out $((1<<i)) $((1<<j)) 1 < 3DFAinput.txt >> $FILE
done
echo " " >> $FILE
echo " "
done
