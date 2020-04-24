#include <bits/stdc++.h>
using namespace std;

struct node;

struct pointer{
	node* ptr;
	uint count;
};


struct node{
	int value;
	pointer* next;
};


struct myqueue{
	pointer* head;
	pointer* tail;
};

void initialize(myqueue *q){
	node* temp = new node;
	temp->next=new pointer;
	temp->next->ptr = NULL;
	q->head->ptr = q->tail->ptr = temp;
}

void enqueue(myqueue *q, int value){
	node* temp = new node;
	temp->value = value;
	temp->next = new pointer;
	temp->next->ptr = NULL;
	pointer* tail;
	while(1){
		tail = q->tail;
		pointer* next = tail->ptr->next;
		if(tail == q->tail){
			if(next->ptr == NULL){
				if(__sync_bool_compare_and_swap(&tail->ptr->next,next,new pointer({temp, next->count+1}))){
					break;
				}
			}
			else{
				__sync_bool_compare_and_swap(&q->tail,tail,new pointer({next->ptr, tail->count+1}));	
			}
		}
	}

	__sync_bool_compare_and_swap(&q->tail,tail,new pointer({temp, tail->count+1}));	
}


bool dequeue(myqueue* q, int* value){
	pointer* head;
	while(1){
		head = q->head;
		pointer* tail = q->tail;
		pointer *next = head->ptr->next;
		if(head == q->head){
			if(head->ptr == tail->ptr){
				if(next->ptr == NULL){
					return 0;
				}
				__sync_bool_compare_and_swap(&q->tail,tail,new pointer({next->ptr, tail->count+1}));
			}
			else{
				*value = next->ptr->value;
				if(__sync_bool_compare_and_swap(&q->head,head,new pointer({next->ptr, head->count+1}))){
					break;
				}
			}
		}
	}
	free(head->ptr);
	return 1;
}

int main(){
	
    
	return 0;
}