#!/bin/bash

FILE="parallelFFTResults.txt"

echo "FFT Method changing size of problem and threads: "
echo "FFT Method changing size of problem and threads: " >> $FILE
g++ -pthread -fopenmp ../parallelFFT.cpp

for j in {0..4}
do
echo "--" >> $FILE
echo $((1<<j)) >> $FILE
echo $((1<<j)) 
for i in {12..21}
do
	./a.out $((1<<i)) $((1<<j)) >> $FILE
done
echo " " >> $FILE
done

