# MA 513 Parallel Computing Assignments

This repository contains assignments done for MA 513 course.

---

## Assignment 1

To Study the effect of cache. This folder contains following folders and files:

1. **Scripts&Results**: This folder contains various scripts to get the results, and hence scripts to get the graphs.
2. **Naive.cpp, opt1.cpp, opt2.cpp, opt3.cpp,** and **Theoretical_Calculations.cpp** are files to compute Naive algo, optimisation 1, optimisation 2, optimisation 3 and to theoretical calculations respectively.
3. **allinone.cpp** contains all the algorithms where each algorithm is present as a function.
4. **MA513-assign1-report.pdf** is the final report for assignment 1.

---

## Assignment 2

This is assignment was to get familiar with the MPI syntax. It contains following files:

1. **helloworld.c**: This file has basic code for MPI.
2. **blockingAsyncMPI.c**: This file has code for blocking asynchronous send and receive.
3. **blockingSynchMPI.c**: This file has code for blocking synchronous send and receive.
4. **unblockingSendReceive.c**: This file has code for unblocking send and receive.
5. **Assignment-2.pdf**: This is report containing the descriptions of the experiments done.

---

## Assignment 3

To implement addition of numbers through various parallel methods and compare the results among those. This folder contains following files:

1. **addNumbersNaive.c** - Conatins code to add numbers where P0 first sends n/p items to each processor, then each PE adds n/p items, finally each PE sends partial sum to P0 which adds all these elements and return the sum.
2. **addNumbersRecursive.c** - Contains code to add numbers where the distribution and collection of numbers is done hierarchially as discussed in class.
3. **addNumersReduce.c** - Contains code to add numbers using inbuilt MPI_reduce to compute partial sum.
4. **oddEvenSorting.c** - Contains the code for odd even sorting.
5. **Assignment 3.pdf** - This contains the theory and observations of the experiments conducted.
6. **scripts&Results** - This folder contains the scripts used to get the results and files that hold the results.

---

## Assignment 4

To implement vector matrix multiplication using row division, column division and block division methods. This folder has the following files and folder:

1. **rowdiv.c** - Contains the code to do the vector matrix multiplication using row division method.
2. **coldiv.c** - Contains the code to do the vector matrix multiplication using column division method.
2. **blockdiv.c** - Contains the code to do the vector matrix multiplication using block division method.
3. **Assignment 4.pdf** - This contains the theory and observations of the experiments conducted.
4. **scripts&Results** - This folder contains the scripts used to get the results and files that hold the results.

---

## Assignment 5

To perform gaussian elimination on matrix and also to implement it's pipelined version. This folder has the following files and folder:

1. **gaussionElimination.c** - Contains the code to normal Gaussian Elimination.
2. **pipelinedGaussianElimination.c** - Contains the code to pipelined Gaussian Elimination.
3. **Assignment 5.pdf** - This contains the theory and observations of the experiments conducted.
4. **scripts&Results** - This folder contains the scripts used to get the results and files that hold the results.

---

## OpenMp-Tut

It contains the hello world file to openMP and also serial mergesort code, which was written during lab time.

---

## Assignment 6

Has the serial and two parallel code versions of calculation of pi. This folder has the following files and folder:

1. **piSerial.c** - Contains serial code of calculation of pi.
2. **piCritical.c** - Contains parallel code of calculation of pi using critical section for shared variable.
3. **piReduce.c** - Contains the code of calculation of pi using reduce addition on the shared variable.
4. **Assignment 6** - This contains the theory and observations of the experiments conducted.
5. **scripts&Results** - This folder contains the scripts used to get the results and files that hold the results.

---

## Assignment 7

Solving the problem of multiplying two polynomials in parallel using 3 different methods:
1. School Method
2. Karatsuba's Algorithm
3. FFT Divide and Conquer Algorithm
The folder assign7/ contains following files and folders:

1. **schoolMethod.cpp** - Parallelising School Method.
2. **serialKaratsuba.cpp** - Serial code of Karatsuba algorithm.
3. **parallelKaratsuba.cpp** - Parallel code of Karatsuba algorithm.
4. **serialFFT.cpp** - Serial code of FFT divide and conquer algorithm.
5. **parallelFFT.cpp** - Parallel code of FFT divide and conquer algorithm.
6. **Assignment 7** - This contains the theory and observations of the experiments conducted.
7. **scripts&Results** - This folder contains the scripts used to get the results and files that hold the results.

---

## Assignment 8

Parallelising producer consumer problem with multiple consumers and multiple producers and a single bounded queue
The folder assign8/ contains following files and folders:

1. **queue.cpp** - Contains the parallel code of producer consumer problem.
2. **Assignment 8** - This contains the theory and observations of the experiments conducted.
3. **scripts&Results** - This folder contains the scripts used to get the results and files that hold the results.

---

## Assignment 9

Parallelising the code of Word acceptance on the reduced DFA.
The folder assign9/ contains following files and folders:

1. **paralleldfa.cpp** - Contains the code of given problem.
2. **Assignment 9** - This contains the theory and observations of the experiments conducted.
3. **scripts&Results** - This folder contains the scripts used to get the results and files that hold the results.

---