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

1. **helloworld.c**
2. **deadlocktry.c**


---

## Assignment 3

To implement addition of numbers through various parallel methods and compare the results among those. This folder contains following files:

1. **addNumbersNaive.c** - Conatins code to add numbers where P0 first sends n/p items to each processor, then each PE adds n/p items, finally each PE sends partial sum to P0 which adds all these elements and return the sum.
2. **addNumbersRecursive.c** - Contains code to add numbers where the distribution and collection of numbers is done hierarchially as discussed in class.
3. **addNumersReduce.c** - Contains code to add numbers using inbuilt MPI_reduce to compute partial sum.


---