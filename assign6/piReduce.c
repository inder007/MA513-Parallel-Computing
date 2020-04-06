#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// static long numOfSteps = 1000000;

int main(int argc, char **argv){

	int num_threads = atoi(argv[1]);
	long numOfSteps = atoi(argv[2]);
	double oneStep = 1.0/(double)numOfSteps;
	double sum = 0.0;
	int i;
	double start, end;

	omp_set_num_threads(num_threads);

	start = omp_get_wtime();

	#pragma omp parallel for reduction(+:sum)
	for(i=0;i<numOfSteps;i++){
		double x = (i+0.5)*oneStep;
		sum = sum + 4.0/(1.0 + x*x);
	}

	double pi = sum*oneStep;
	end = omp_get_wtime();
	// printf("%0.10G\n", pi);
	printf("%G\n", end - start);
}