#include <bits/stdc++.h>
#include <omp.h>
using namespace std;


int main(int argc, char** argv){
	int numThreads;
	int numStates;
	int characters;
	int numFinalStates;
	int* finalStates;
	int startState;
	int** L;
	char* s;
	numThreads = atoi(argv[1]);
	int stringLength = atoi(argv[2]);
	int whichReduction = atoi(argv[3]);

	srand ( time(NULL) );

	// cout<<"No of states: ";
	cin>>numStates;
	cin>>characters;
	cin>>startState;
	int** transition = new int*[numStates];
	for(int i=0;i<numStates;i++){
		transition[i] = new int[characters]();
	}

	for(int i=0;i<numStates;i++){
		for(int j=0;j<characters;j++){
			cin>>transition[i][j];
		}
	}

	cin>>numFinalStates;
	finalStates = new int[numStates]();
	for(int i=0;i<numFinalStates;i++){
		int r;
		cin>>r;
		finalStates[r] = 1;
	}

	// cin>>s;
	s = new char[stringLength];
	for(int i=0;i<stringLength;i++){
		s[i] = 'a' + int(rand()%characters);
	}

	L = new int*[numThreads];
	for(int i=0;i<numThreads;i++){
		L[i] = new int[numStates];
		for(int j=0;j<numStates;j++){
			L[i][j] = j;
		}
	}

	omp_set_num_threads(numThreads);
	int lenPerThread = stringLength/numThreads;
	bool ans;
	double startTime, endTime;
	startTime = omp_get_wtime();

	#pragma omp parallel
	{
		int id, st, en;
		id = omp_get_thread_num();
		// cout<<id<<endl;

		st = id*lenPerThread;
		en = st + lenPerThread;
		for(int i=st;i<en;i++){
			for(int j=0;j<numStates;j++){
				L[id][j] = transition[L[id][j]][s[i]-'a'];
			}
		}
	}

	#pragma omp barrier

	if(whichReduction<=0){
		// trivialReduction();
		int state = startState;
		for(int i=0;i<numThreads;i++){
			state = L[i][state];
		}

		ans = finalStates[state];
	}
	else{
		// binaryReduction();
		#pragma omp parallel
		{
			int steps = log2(numThreads);
			int id = omp_get_thread_num();
			for(int m=1;m<steps;m++){
				// int nextState = (1<<m);
				if(id%(1<<m) == 0 && (id + (1<<(m-1))) < numThreads){
					for(int x=0;x<numStates;x++){
						L[id][x] = L[id + (1<<(m-1))][L[id][x]];
					}
				}
			}	
		}
		ans = finalStates[L[0][startState]];
	}

	// cout<<ans<<endl;
	endTime = omp_get_wtime();
	cout<<(endTime-startTime)<<endl;
    
	return 0;
}