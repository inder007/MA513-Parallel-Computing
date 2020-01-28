#include <iostream>
#include <chrono>
#include <cstdlib>
#include <iomanip>
using namespace std;

int* a; 
int* b; 
int* c; 
int n;

void print(){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cout<<c[n*i+j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

void rec(int i1, int j1, int i2, int j2, int i3, int j3, int s){
	if(s==1){
		c[n*i3 + j3] += a[n*i1 + j1]*b[n*i2+j2];
	}
	else{
		int p = s>>1;
		int i1p = i1+p;
		int j1p = j1+p;
		int i2p = i2+p;
		int j2p = j2+p;
		int i3p = i3+p;
		int j3p = j3+p;
		rec(i1, j1, i2, j2, i3, j3, p); 
		rec(i1, j1p, i2p, j2, i3, j3, p);
		rec(i1, j1, i2, j2p, i3, j3p, p);
		rec(i1, j1p, i2p, j2p, i3, j3p, p);
		rec(i1p, j1, i2, j2, i3p, j3, p);
		rec(i1p, j1p, i2p, j2, i3p, j3, p);
		rec(i1p, j1, i2, j2p, i3p, j3p, p);
		rec(i1p, j1p, i2p, j2p, i3p, j3p, p);

		//normal recursion code
		// rec(i1, j1, i2, j2, i3, j3, p); 
		// rec(i1, j1+p, i2+p, j2, i3, j3, p);
		// rec(i1, j1, i2, j2+p, i3, j3+p, p);
		// rec(i1, j1+p, i2+p, j2+p, i3, j3+p, p);
		// rec(i1+p, j1, i2, j2, i3+p, j3, p);
		// rec(i1+p, j1+p, i2+p, j2, i3+p, j3, p);
		// rec(i1+p, j1, i2, j2+p, i3+p, j3+p, p);
		// rec(i1+p, j1+p, i2+p, j2+p, i3+p, j3+p, p);
	}
}

int main(int argc, char *argv[]){
	// int n;
	n=16;
	if(argc >= 2){
		n = atoi(argv[1]);
		// cout << n << endl;
	}
	// cin>>n;
	a = new int[n*n];
	b = new int[n*n];
	c = new int[n*n]();
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			a[n*i+j] = i+j;
			b[n*i+j] = i+j;
		}
	}
	auto start = chrono::high_resolution_clock::now();
	rec(0,0,0,0,0,0,n);
	auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 

    time_taken *= 1e-9; 
  
    cout << "Opt3: Time taken by program is : " << fixed  
         << time_taken << setprecision(9); 
    cout << " sec" << endl; 
    // print();
	return 0;
}