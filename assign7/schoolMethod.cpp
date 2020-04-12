#include <bits/stdc++.h>
using namespace std;

int *a;
int *b;
int *c;
clock_t *startTime;
clock_t *endTime;

int numElements;
int num_threads;

void* schoolMethod(void* vIdPtr){
	auto start = clock();
	int* idPtr = (int*)vIdPtr;
	int id = *idPtr;
	// printf("sadas %d\n", *idPtr);
	for(int i=id;i<2*numElements;i+=num_threads){
		int sum=0;
		if(i<numElements){
			for(int j=0;j<=i;j++){
				sum+=a[j]*b[i-j];
			}
		}
		else{
			for(int j=i-numElements+1;j<numElements;j++){
				sum += a[j]*b[i-j];
			}
		}
		c[i] = sum;
	}
	auto end = clock();
	startTime[id] = start;
	endTime[id] = end;
}

int main(int argc, char** argv){
	
	numElements = atoi(argv[1]);
	num_threads = atoi(argv[2]);

	a = new int[numElements];
	b = new int[numElements];
	c = new int[2*numElements];
	startTime = new clock_t[num_threads];
	endTime = new clock_t[num_threads];

	int* threadId = new int[num_threads];

	for(int i=0;i<numElements;i++){
		a[i] = 1;
		b[i] = 1;
	}

	for(int i=0;i<num_threads;i++){
		threadId[i] = i;
	}

	pthread_t threads[num_threads];

	for(int i=0;i<num_threads;i++){
		// printf("hiii\n");
		int x = i;
		int retVal = pthread_create(&threads[i], NULL, schoolMethod, (void*) &threadId[i]);
		if(retVal){
			cout<<"Error from pthread_create()"<<endl;
			exit(-1);
		}
	}
	void* status;
	for(int i=0;i<num_threads;i++){
		int retVal = pthread_join(threads[i], &status);
		if(retVal){
			cout<<"Error while joining"<<endl;
		}

	}

	// for(int i=0;i<2*numElements-1;i++){
	// 	printf("%d ", c[i]);
	// }
	// printf("\n");

	clock_t minStart = startTime[0], maxEnd = endTime[0];
	for(int i=1;i<num_threads;i++){
		minStart = min(minStart, startTime[i]);
		maxEnd = max(maxEnd, endTime[i]);
	}

	double time_taken = double(maxEnd - minStart) / double(CLOCKS_PER_SEC); 

	cout<<time_taken<<setprecision(6)<<endl;

	// pthread_join(NULL);

    
	return 0;
}