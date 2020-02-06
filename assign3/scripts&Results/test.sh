#!/bin/bash

for i in {17..29}
do
	echo $((1<<i))
done


# FILE="results*10.txt"

# # echo "N: " $1 >> $FILE
# echo "P:" $1 >> $FILE
# echo "Add Numbers Naive" >> $FILE
# mpicc ../addNumbersNaive.c
# # mpiexec -n $1 ../a.out $1 >> $FILE

# for i in {17..29}
# do
# 	Val="0"
# 	for i in {1..10}
# 	do
# 		e=$(mpiexec -n $1 ./a.out $((1<<i)))
# 		# echo $Val $e
# 		Val=$(echo $e + $Val | bc)
# 	done
# 	echo $Val >> $FILE
# 	# echo $((1<<i))
# 	# mpiexec -n $1 ./a.out $((1<<i)) >> $FILE
# done


# echo "" >> $FILE
# echo "Add Numbers Recursive" >> $FILE
# mpicc ../addNumbersRecursive.c
# # mpiexec -n $1 ../a.out $1 >> $FILE

# echo "" >> $FILE
# for i in {17..29}
# do
# 	Val="0"
# 	for i in {1..10}
# 	do
# 		e=$(mpiexec -n $1 ./a.out $((1<<i)))
# 		# echo $Val $e
# 		Val=$(echo $e + $Val | bc)
# 	done
# 	echo $Val >> $FILE
# 	# echo $((1<<i))
# 	# mpiexec -n $1 ./a.out $((1<<i)) >> $FILE
# done

# echo "" >> $FILE
# echo "Add Numbers Reduce" >> $FILE
# mpicc ../addNumersReduce.c
# # mpiexec -n $1 ../a.out $1 >> $FILE

# for i in {17..29}
# do
# 	Val="0"
# 	for i in {1..10}
# 	do
# 		e=$(mpiexec -n $1 ./a.out $((1<<i)))
# 		# echo $Val $e
# 		Val=$(echo $e + $Val | bc)
# 	done
# 	echo $Val >> $FILE
# 	# echo $((1<<i))
# 	# mpiexec -n $1 ./a.out $((1<<i)) >> $FILE
# done
