#!/bin/bash

FILE="results.txt"

echo "N: " $1 >> $FILE
echo "P: " $2 >> $FILE

mpicc ../addNumbersNaive.c

mpiexec -n $2 ../a.out $1 >> $FILE

