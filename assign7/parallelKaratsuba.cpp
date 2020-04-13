#include <bits/stdc++.h>
#include <pthread.h>
#include <omp.h>
using namespace std;

int numElements;
// int numThreads;
int maxLevel;

struct thread_data{
	int *a;
	int *b;
	int *c;
	int n;
	int level;
};

void* multiplyPol(void* thread_args){
	thread_data* data = (thread_data*) thread_args;
	int* a = data->a;
	int* b = data->b;
	int* c = data->c;
	int level = data->level;
	int n = data->n;

	// n = a.size();


	if(n==0){
		// return vector<int>(0);
		return NULL;
	}

	if(n==1){
		// vector<int> t(1, a[0]*b[0]);
		// *c = t;
		// c = new int[1];
		c[0] = a[0]*b[0];
		return NULL;
	}

	// vector<int> ah, bh, al, bl;
	int *al = new int[n/2];
	int *ah = new int[n/2];
	int *bh = new int[n-n/2];
	int *bl = new int[n-n/2];
 	for(int i=0;i<n/2;i++){
		// al.push_back(a[i]);
		// bl.push_back(b[i]);
		al[i] = a[i];
		bl[i] = a[i];
	}

	for(int i=n/2;i<n;i++){
		// ah.push_back(a[i]);
		// bh.push_back(b[i]);
		ah[i-n/2] = a[i];
		bh[i-n/2] = b[i];
	}

	// vector<int> t1, t2;
	int *t1 = new int[(n+1)/2];
	int *t2 = new int[(n+1)/2];
	for(int i=0;i<n/2;i++){
		// t1.push_back(al[i] + ah[i]);
		// t2.push_back(bl[i] + bh[i]);
		t1[i] = al[i] + ah[i];
		t2[i] = bl[i] + bh[i];
	}

	if(n%2){
		// t1.push_back(ah[ah.size()-1]);
		// t2.push_back(bh[bh.size()-1]);
		t1[n/2] = ah[n/2];
		t2[n/2] = bh[n/2];
	}

	// vector<int> *c1 = new vector<int>;
	// vector<int> *c2 = new vector<int>;
	// vector<int> *c3 = new vector<int>;

	// int *c1, *c2, *c3;
	int *c1 = new int[n-1+n%2];
	int *c2 = new int[n-1];
	int *c3 = new int[n-1+n%2];

	thread_data oneMultData = {ah, bh, c1, (n+1)/2, level+1};
	thread_data twoMultData = {al, bl, c2, n/2, level+1};
	thread_data threeMultData = {t1, t2, c3, (n+1)/2, level+1};

	// vector<int> oneMult = multiplyPol(ah, bh);
	// vector<int> twoMult = multiplyPol(al, bl);
	// vector<int> threeMult = multiplyPol(t1, t2);

	pthread_t threads[3];

	if(level <= maxLevel){
		pthread_create(&threads[0], NULL, multiplyPol, (void*) &oneMultData);
		pthread_create(&threads[1], NULL, multiplyPol, (void*) &twoMultData);
		pthread_create(&threads[2], NULL, multiplyPol, (void*) &threeMultData);

		pthread_join(threads[0], NULL);
		pthread_join(threads[1], NULL);
		pthread_join(threads[2], NULL);
	}
	else{
		multiplyPol((void*) &oneMultData);
		multiplyPol((void*) &twoMultData);
		multiplyPol((void*) &threeMultData);
	}



	// vector<int> oneMult = *c1;
	// vector<int> twoMult = *c2;
	// vector<int> threeMult = *c3;

	// cout<<n<<" "<<(*c1).size()<<" "<<(*c2).size()<<" "<<(*c3).size()<<endl;

	for(int i=0;i<n-1;i++){
		c3[i] -= c1[i];
		c3[i] -= c2[i];
	}
	if(n%2){
		c3[n-1] -= c1[n-1];
	}

	// int m = (*c3).size();
	// for(int i=0;i<m;i++){
	// 	(*c3)[i] -= (*c1)[i];
	// 	// (*c3)[i] -= (*c2)[i];
	// 	if(i<(*c2).size()){
	// 		(*c3)[i] -= (*c2)[i];	
	// 	}
	// }

	// if(m<(*c1).size()){
	// 	for(int i=m;i<(*c1).size();i++){
	// 		(*c3).push_back(-(*c1)[i]);
	// 	}
	// }

	// vector<int> out;
	int size = n/2;
	size += n/2;
	// c = new int[2*n-1];
	// for(int i=0;i<size;i++){
	// 	(*c).push_back(0);
	// }
	for(int i=0;i<2*n-1;i++){
		c[i] = 0;
	}

	// for(int i=0;i<(*c1).size();i++){
	// 	(*c).push_back((*c1)[i]);
	// }

	for(int i=0;i<n-1;i++){
		// cout<<i<<" ";
		c[size+i] += c1[i];
		c[i+n/2] += c3[i];
		c[i] += c2[i];
	}
	if(n%2){
		c[size+n-1] += c1[n-1];
		c[n/2+n-1] += c3[n-1];
	}

	// for(int i=0;i<(*c3).size();i++){
	// 	(*c)[i+n/2] += (*c3)[i];
	// }


	// for(int i=0;i<(*c2).size();i++){
	// 	(*c)[i] += (*c2)[i];
	// }

	// *c = out;

	delete c1;
	delete c2;
	delete c3;

}

int main(int argc, char** argv){
	numElements = atoi(argv[1]);
	maxLevel = atoi(argv[2]);

	// vector<int> a(numElements);
	// vector<int> b(numElements);
	// vector<int> *c = new vector<int>; 

	int *a = new int[numElements];
	int *b = new int[numElements];
	int *c = new int[2*numElements-1];

	for(int i=0;i<numElements;i++){
		a[i] = 1;
		b[i] = 1;
	}

	thread_data thread_args = {a, b, c, numElements, 1};

	// vector<int> ans = multiplyPol(a, b);

	pthread_t thread;

	double startTime, endTime;
    startTime = omp_get_wtime();

	pthread_create(&thread, NULL, multiplyPol, (void*) &thread_args);
	pthread_join(thread, NULL);
    // multiplyPol((void*) &thread_args);

	endTime = omp_get_wtime();
	cout<<endTime-startTime<<endl;

	// vector<int> ans = *c;

	// for(int i=0;i<2*numElements-1;i++){
	// 	cout<<c[i]<<" ";
	// }    

	// cout<<endl;
	return 0;
}