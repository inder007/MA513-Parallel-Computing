#!/bin/bash
# read -p 'n_size=' n_size
# read -p 's_size=' s_size
# read -p 'file=' file
echo "Value of N: " $1
echo "Value of S: " $2
g++ Naive.cpp 
echo "results of Naive with " $1 >> results.txt
./a.out $1 >> results.txt
g++ opt1.cpp 
echo "results of opt1 with " $1 >> results.txt
./a.out $1 >> results.txt
g++ opt2.cpp 
echo "results of opt2 with " $1 " and " $2 >> results.txt
./a.out $1 $2 >> results.txt
g++ opt3.cpp 
echo "results of opt3 with " $1 >> results.txt
./a.out $1 >> results.txt

