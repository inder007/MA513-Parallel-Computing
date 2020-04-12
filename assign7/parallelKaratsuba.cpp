#include <bits/stdc++.h>
#include <pthread.h>
using namespace std;

// int *a;
// int *b; 
// int *c;
// vector<int> a, b, c;

int numElements;
int numThreads;

struct thread_data{
	vector<int> a;
	vector<int> b;
	vector<int> *c;
	int level;
};

void* multiplyPol(void* thread_args){
	thread_data* data = (thread_data*) thread_args;
	vector<int> a = data->a;
	vector<int> b = data->b;
	vector<int> *c = data->c;
	int level = data->level;
	int n = a.size();

	n = a.size();

	if(n==0){
		// return vector<int>(0);
		cout<<"ASD"<<endl;
		return NULL;
	}

	if(n==1){
		// return vector<int>(1, a[0]*b[0]);
		// (*c) = new vector<int>(1);
		// (*c)[0] = a[0]*b[0];
		vector<int> t(1, a[0]*b[0]);
		// cout<<"HI"<<endl;
		*c = t;
		// c = new vector<int>(1, a[0]*b[0]);
		// c = new vector<int>;
		// c->push_back(a[0]*b[0]);
		// c = &t;
		return NULL;
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

	vector<int> *c1 = new vector<int>;
	vector<int> *c2 = new vector<int>;
	vector<int> *c3 = new vector<int>;

	thread_data oneMultData = {ah, bh, c1, level+1};
	thread_data twoMultData = {al, bl, c2, level+1};
	thread_data threeMultData = {t1, t2, c3, level+1};

	// vector<int> oneMult = multiplyPol(ah, bh);
	// vector<int> twoMult = multiplyPol(al, bl);
	// vector<int> threeMult = multiplyPol(t1, t2);

	multiplyPol((void*) &oneMultData);
	multiplyPol((void*) &twoMultData);
	multiplyPol((void*) &threeMultData);

	vector<int> oneMult = *c1;
	vector<int> twoMult = *c2;
	vector<int> threeMult = *c3;

	// cout<<n<<" "<<oneMult.size()<<" "<<twoMult.size()<<" "<<threeMult.size()<<endl;

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

	// return out;
	*c = out;

	// vector<int> x = 

}

int main(int argc, char** argv){
	numElements = atoi(argv[1]);
	// numThreads = atoi(argv[2]);

	vector<int> a(numElements);
	vector<int> b(numElements);
	vector<int> *c = new vector<int>; 

	for(int i=0;i<numElements;i++){
		a[i] = 1;
		b[i] = 1;
	}

	thread_data thread_args = {a, b, c, 1};

	// vector<int> ans = multiplyPol(a, b);

	pthread_t thread;

	pthread_create(&thread, NULL, multiplyPol, (void*) &thread_args);

	pthread_join(thread, NULL);

	vector<int> ans = *c;

	// cout<<ans.size()<<endl;

	for(int i=0;i<ans.size();i++){
		cout<<ans[i]<<" ";
	}    

	cout<<endl;
	return 0;
}