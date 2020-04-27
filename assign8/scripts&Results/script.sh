#!/bin/bash

FILE="results.txt"

echo "changing number of producers and consumers when queue not enough: "
echo "changing number of producers and consumers(10^6(2^20) total operations and queue size:2^16): " >> $FILE
g++ ../queue.cpp -pthread -fopenmp -latomic

for i in {0..3}
do
echo $((1<<i)) >> $FILE
echo "---" >> $FILE
echo $((1<<i))
echo "----"
for j in {0..3}
do
	echo $((1<<j)) >> $FILE
	echo $((1<<j))
	./a.out $((1<<i)) $((1<<j)) 100000 $((1<<20)) >> $FILE
done
echo " " >> $FILE
echo " "
done

echo "changing number of producers and consumers when queue size is enough: "
echo "changing number of producers and consumers(10^6(2^20) total operations and queue size:2^21): " >> $FILE
g++ ../queue.cpp -pthread -fopenmp -latomic

for i in {0..3}
do
echo $((1<<i)) >> $FILE
echo "---" >> $FILE
echo $((1<<i))
echo "----"
for j in {0..3}
do
	echo $((1<<j)) >> $FILE
	echo $((1<<j))
	./a.out $((1<<i)) $((1<<j)) 100000 $((1<<20)) >> $FILE
done
echo " " >> $FILE
echo " "
done

echo "changing queue size and number of operations with producers and consumers being 1 each: "
echo "changing queue size and number of operations with producers and consumers being 1 each: " >> $FILE
g++ ../queue.cpp -pthread -fopenmp -latomic

for i in {15..21}
do
echo $((1<<i)) >> $FILE
echo "---" >> $FILE
echo $((1<<i))
echo "----"
for j in {16..20}
do
	echo $((1<<j)) >> $FILE
	echo $((1<<j))
	./a.out 1 1 $((1<<i)) $((1<<j)) >> $FILE
done
echo " " >> $FILE
echo " "
done

echo "changing queue size and number of operations with producers and consumers being 2 each: "
echo "changing queue size and number of operations with producers and consumers being 2 each: " >> $FILE
g++ ../queue.cpp -pthread -fopenmp -latomic

for i in {15..21}
do
echo $((1<<i)) >> $FILE
echo "---" >> $FILE
echo $((1<<i))
echo "----"
for j in {16..20}
do
	echo $((1<<j)) >> $FILE
	echo $((1<<j))
	./a.out 2 2 $((1<<i)) $((1<<j)) >> $FILE
done
echo " " >> $FILE
echo " "
done

