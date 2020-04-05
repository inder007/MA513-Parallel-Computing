#include <bits/stdc++.h>
// #include <omp.h>
using namespace std;

void merge(int* arr, int l, int mid, int h){
	// int* a, *b;
	vector<int> a(mid-l+1);
	vector<int> b(h-(mid+1)+1);
	// cout<<l<<" "<<mid<<" start "<<h<<endl;
	int lct=0, rct=0;
	for(int i=l;i<=mid;i++){
		a[lct++] = arr[i];
	}
	for(int i=mid+1;i<=h;i++){
		b[rct++] = arr[i];
	// cout<<"ch"<<i<<endl;
	}
	int j=0,k=0;
	for(int i=l;i<=h;i++){
		if(j<lct && k>=rct){
			arr[i] = a[j++];
		}
		else if(j>=lct && k<rct){
			arr[i] = b[k++];
		}
		else if(a[j] > b[k]){
			arr[i] = b[k++];
		}
		else{
			arr[i] = a[j++];
		}
		// cout<<arr[i]<<" ";
	}
	// cout<<endl;
	// cout<<l<<" "<<mid<<" end "<<h<<endl;
}


void mergesort(int *arr, int l, int h){
	if(h>l){
		// cout<<l<<" "<<h<<endl;
		int mid = (l+h)/2;
		mergesort(arr, l, mid);
		mergesort(arr, mid+1, h);
		merge(arr, l, mid, h);
	}
}

int main(int argc, char* argv[]){
	int n = atoi(argv[1]);

	int *arr = new int[n];
	for(int i=0;i<n;i++){
		arr[i] = n-i;
		// cout<<arr[i]<<" ";
	}
	// cout<<endl;
	mergesort(arr, 0, n-1);
	for(int i=0;i<n;i++){
		cout<<arr[i]<<" ";
	}
	cout<<endl;
    
	return 0;
}