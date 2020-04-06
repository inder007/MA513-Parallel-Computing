#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// static long numOfSteps = 100000;

int main(int argc, char **argv){

	int num_threads = atoi(argv[1]);
	long numOfSteps = atoi(argv[2]);
	double oneStep = 1.0/(double)numOfSteps;
	double sum = 0.0;
	int i;
	double start, end;
	
	omp_set_num_threads(num_threads);

	start = omp_get_wtime();	
	#pragma omp parallel
	{
		double temp;
		#pragma omp for schedule(static)
		for(i=0;i<numOfSteps;i++){
			double x = (i+0.5)*oneStep;
			temp +=  4.0/(1.0 + x*x);
		}

		#pragma omp critical
		sum += temp*oneStep;
	
	}
	
	double pi = sum*oneStep;
	end = omp_get_wtime();
	// printf("%G\n", pi);
	printf("%G\n", end - start);

}