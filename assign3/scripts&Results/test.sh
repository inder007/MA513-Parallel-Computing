#!/bin/bash

mpicc ../addNumbersNaive.c

Val="0"
for i in {1..10}
do
	e=$(mpiexec -n 2 ./a.out 8)
	echo $Val $e
	Val=$(echo $e + $Val | bc)
done

echo $Val
Val=$(echo $Val / 10.0 | bc) 

echo $Val