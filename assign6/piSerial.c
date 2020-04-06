#include <stdio.h>

int main(){
	double numOfSteps = 100000;
	double oneStep = 1.0/numOfSteps;
	double sum = 0.0;
	for(int i=0;i<numOfSteps;i++){
		double x = (i+0.5)*oneStep;
		sum += 4.0/(1.0 + x*x);
	}
	double pi = sum*oneStep;
	printf("%G\n", pi);
}