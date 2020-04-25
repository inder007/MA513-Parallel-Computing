#include <bits/stdc++.h>
#include<atomic>

using namespace std;

struct node;

struct pointer{
	node* ptr;
	int count;

	pointer() : ptr{NULL}, count{0} {}
	pointer(node* _ptr) : ptr{_ptr}, count{0} {}
	pointer(node* _ptr, int _count) :  ptr{_ptr}, count{_count} {}

	bool operator ==(const pointer &other) const {
        return ptr == other.ptr && count == other.count;
    }    
};


struct node{
	int value;
	atomic<pointer> next;

	node() : next{pointer{}} {}
	node(int _value) : value{_value}, next{pointer{}} {}
};


struct myqueue{
	atomic<pointer> head;
	atomic<pointer> tail;
	myqueue() : head{new node{}}, tail{head.load().ptr} {}
};


void enqueue(myqueue *q, int value){
	node* temp = new node(value);
	// temp->value = value;
	// temp->next.ptr = NULL;
	pointer tail;
	while(1){
		tail = q->tail.load();
		pointer next = tail.ptr->next;
		if(tail == q->tail){
			if(next.ptr == NULL){
				if(tail.ptr->next.compare_exchange_weak(next, pointer{temp, next.count+1})){
					break;
				}
			}
			else{
				q->tail.compare_exchange_weak(tail, pointer{next.ptr, tail.count+1});
			}
		}
	}

	q->tail.compare_exchange_weak(tail, pointer{temp, tail.count+1});
}


bool dequeue(myqueue* q, int* value){
	pointer head;
	while(1){
		head = q->head.load();
		pointer tail = q->tail.load();
		pointer next = head.ptr->next;
		if(head == q->head){
			if(head.ptr == tail.ptr){
				if(next.ptr == NULL){
					return 0;
				}
				q->tail.compare_exchange_weak(tail, pointer{next.ptr, tail.count+1});
			}
			else{
				*value = next.ptr->value;
				if(q->head.compare_exchange_weak(head, pointer{next.ptr, head.count+1})){
					break;
				}
			}
		}
	}
	free(head.ptr);
	return 1;
}

int main(int argc, char** argv){
	
	myqueue* q = new myqueue;
	
	// int numProducers = argv[1];
	// int numConsumers = argv[2];    

	enqueue(q, 1);
	enqueue(q, 2);
	enqueue(q, 3);
	enqueue(q, 4);
	int ans;
	cout<<q->tail.load().count<<endl;
	dequeue(q, &ans);
	enqueue(q, 5);
	cout<<q->tail.load().count<<endl;
	dequeue(q, &ans);
	cout<<q->tail.load().count<<endl;
	return 0;
}