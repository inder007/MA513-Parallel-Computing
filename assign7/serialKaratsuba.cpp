#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

// int *a;
// int *b; 
// int *c;
// vector<int> a, b, c;

int numElements;
int numThreads;

vector<int> multiplyPol(vector<int> a, vector<int> b){
	int n = a.size();

	n = a.size();

	if(n==0){
		return vector<int>(0);
	}
	if(n==1){
		return vector<int>(1, a[0]*b[0]);
	}

	vector<int> ah, bh, al, bl;
	for(int i=0;i<n/2;i++){
		al.push_back(a[i]);
		bl.push_back(b[i]);
	}

	for(int i=n/2;i<n;i++){
		ah.push_back(a[i]);
		bh.push_back(b[i]);
	}

	vector<int> t1, t2;
	for(int i=0;i<n/2;i++){
		t1.push_back(al[i] + ah[i]);
		t2.push_back(bl[i] + bh[i]);
	}

	if(n%2){
		t1.push_back(ah[ah.size()-1]);
		t2.push_back(bh[bh.size()-1]);
	}

	vector<int> oneMult = multiplyPol(ah, bh);
	vector<int> twoMult = multiplyPol(al, bl);
	vector<int> threeMult = multiplyPol(t1, t2);

	int m = threeMult.size();
	for(int i=0;i<m;i++){
		threeMult[i] -= oneMult[i];
		// threeMult[i] -= twoMult[i];
		if(i<twoMult.size()){
			threeMult[i] -= twoMult[i];	
		}
	}

	if(m<oneMult.size()){
		for(int i=m;i<oneMult.size();i++){
			threeMult.push_back(-oneMult[i]);
		}
	}
	if(m<twoMult.size()){
		for(int i=m;i<twoMult.size();i++){
			threeMult[i] -= twoMult[i];
		}
	}

	vector<int> out;
	int size = n/2;
	size += n/2;
	for(int i=0;i<size;i++){
		out.push_back(0);
	}

	for(int i=0;i<oneMult.size();i++){
		out.push_back(oneMult[i]);
	}

	for(int i=0;i<threeMult.size();i++){
		out[i+n/2] += threeMult[i];
	}

	for(int i=0;i<twoMult.size();i++){
		out[i] += twoMult[i];
	}

	// cout<<n<<" ";
	// for(int i=0;i<out.size();i++){
	// 	cout<<out[i]<<" ";
	// }
	// cout<<endl;

	return out;

	// vector<int> x = 

}

int main(int argc, char** argv){
	numElements = atoi(argv[1]);
	// numThreads = atoi(argv[2]);

	vector<int> a(numElements);
	vector<int> b(numElements);
	// vector<int> c(2*numElements); 

	for(int i=0;i<numElements;i++){
		a[i] = 1;
		b[i] = 1;
	}

	double startTime, endTime;
    startTime = omp_get_wtime();
    
	vector<int> ans = multiplyPol(a, b);

    endTime = omp_get_wtime();
	cout<<endTime-startTime<<endl;


	// for(int i=0;i<ans.size();i++){
	// 	cout<<ans[i]<<" ";
	// }    

	// cout<<endl;
	return 0;
}