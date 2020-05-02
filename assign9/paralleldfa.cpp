#include <bits/stdc++.h>
#include <omp.h>
using namespace std;


int numThreads;
int numStates;
int characters;
int numFinalStates;
int* finalStates;
int startState;
int** L;
string s;

bool trivialReduction(){
	int state = startState;
	for(int i=0;i<numThreads;i++){
		state = L[i][state];
	}

	// if(finalStates[stat])
	return finalStates[state];

}

bool binaryReduction(){
	int steps = log2(numThreads);
	for(int m=1;m<steps;m++){
		// int nextState = (1<<m);
		// if(numThreads%(1<<m) == 0 && ())
	}

}

int main(int argc, char** argv){
	numThreads = atoi(argv[1]);
	int whichReduction = atoi(argv[2]);

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

	cin>>s;

	L = new int*[numThreads];
	for(int i=0;i<numThreads;i++){
		L[i] = new int[numStates];
		for(int j=0;j<numStates;j++){
			L[i][j] = j;
		}
	}

	omp_set_num_threads(numThreads);
	int sSize = s.size();
	int lenPerThread = sSize/numThreads;
	bool ans;
	double start, end;
	start = omp_get_wtime();

	#pragma omp parallel
	{
		int id = omp_get_thread_num();

		int st = id*lenPerThread;
		int end = (id+1)*lenPerThread;
		for(int i=st;i<end;i++){
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
			// cout<<state<<endl;
		}

	// if(finalStates[stat])
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
	end = omp_get_wtime();
	cout<<(end-start)<<endl;
    
	return 0;
}