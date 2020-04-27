#include <bits/stdc++.h>
#include<atomic>
#include <omp.h>

using namespace std;


struct node;

struct pointer{
	node* ptr;
	int count;
	int nodeNum;

	pointer() : ptr{NULL}, count{0}, nodeNum{0} {}
	pointer(node* _ptr) : ptr{_ptr}, count{0}, nodeNum{0} {}
	pointer(node* _ptr, int _count, int _nodeNum) :  ptr{_ptr}, count{_count}, nodeNum{_nodeNum} {}

	bool operator ==(const pointer &other) const {
        return ptr == other.ptr && count == other.count && nodeNum == other.nodeNum;
    }

    bool operator !=(const pointer &other) const {
    	if(ptr != other.ptr || count != other.count || nodeNum != other.nodeNum){
    		return 1;
    	}
    	return 0;
        // return ptr != other.ptr || count != other.count || nodeNum != other.nodeNum;
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


int maxQueueSize;
myqueue* q;
int numOfJobsPerProducer;
long long* producerOperations;
long long* consumerOperations;
bool hasProducerStartedProducing;


bool enqueue(myqueue *q, int value){
	node* temp = new node(value);
	// temp->value = value;
	// temp->next.ptr = NULL;
	pointer tail;
	while(1){
		tail = q->tail.load();
		pointer head = q->head.load();
		pointer next = tail.ptr->next;
		if(tail.nodeNum - head.nodeNum >= maxQueueSize){
			// cout<<tail.count - head.count<<endl;
			free(temp);
			return 0;
		}
		if(tail == q->tail){
			if(next.ptr == NULL){
				if(tail.ptr->next.compare_exchange_weak(next, pointer{temp, next.count+1, tail.nodeNum+1})){
					break;
				}
			}
			else{
				q->tail.compare_exchange_weak(tail, pointer{next.ptr, tail.count+1, tail.nodeNum+1});
			}
		}
	}

	q->tail.compare_exchange_weak(tail, pointer{temp, tail.count+1, tail.nodeNum+1});
	return 1;
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
				q->tail.compare_exchange_weak(tail, pointer{next.ptr, tail.count+1, tail.nodeNum+1});
			}
			else{
				*value = next.ptr->value;
				if(q->head.compare_exchange_weak(head, pointer{next.ptr, head.count+1, head.nodeNum+1})){
					break;
				}
			}
		}
	}
	free(head.ptr);
	return 1;
}

void printQueue(){
	pointer head = q->head.load();
	// pointer tail = q->tail.load();
	// cout<<"chec"<<endl;
	while(head.ptr != NULL){
		cout<<head.nodeNum<<" ";
		head = head.ptr->next;
	}
	cout<<endl;
}

void* producerWork(void* id){
	int* tid = (int*)id;
	// cout<<(*tid)<<endl;
	long long operations = 0;
	for(int i=0;i<numOfJobsPerProducer;i++){
		int task = (*tid)%2 + 1;
		// int backoff = 1;
		while(!enqueue(q,task)){
			int backoff = rand()%2+1;
			this_thread::sleep_for(chrono::microseconds(backoff));
			// backoff *= 2;
			// operations++;
		}
		if(i==0){
			hasProducerStartedProducing = true;
		}
		// operations++;
	}
	// producerOperations[(*tid)] = operations;
}

void* consumerWork(void* id){
	int* tid = (int*)id;
	long long operations=0;
	while(!hasProducerStartedProducing);
	while(1){
		int ans;
		// operations++;
		if(!dequeue(q, &ans)){
			// cout<<"exiting"<<endl;
			break;
		}
		this_thread::sleep_for(chrono::microseconds(ans));
	}
	// consumerOperations[(*tid)] = operations;
}


int main(int argc, char** argv){
	
	q = new myqueue;

	srand ( time(NULL) );
	
	int numProducers = atoi(argv[1]);
	int numConsumers = atoi(argv[2]);
	maxQueueSize = atoi(argv[3]);
	int totalOperations = atoi(argv[4]);

	numOfJobsPerProducer = totalOperations/numProducers;

	hasProducerStartedProducing=false;

	// producerOperations = new long long[numProducers]();
	// consumerOperations = new long long[numConsumers]();

	pthread_t producers[numProducers];
	pthread_t consumers[numConsumers];

	int threadIds[numProducers];
	int threadIdsConsumer[numConsumers];

	double startTime, endTime;
    startTime = omp_get_wtime();

	for(int i=0;i<numProducers;i++){
		threadIds[i] = i;
		pthread_create(&producers[i], NULL, producerWork, (void*)&threadIds[i]);
	}

	for(int i=0;i<numConsumers;i++){
		threadIdsConsumer[i] = i;
		pthread_create(&consumers[i], NULL, consumerWork, (void*)&threadIdsConsumer[i]);
	}

	for(int i=0;i<numProducers;i++){
		pthread_join(producers[i], NULL);
	}

	for(int i=0;i<numConsumers;i++){
		pthread_join(consumers[i], NULL);
	}

	endTime = omp_get_wtime();
	double totalTime = endTime - startTime;

	// int ans;
	// dequeue(q, &ans);
	// dequeue(q, &ans);

	// for(int i=0;i<numProducers;i++){
	// 	totalOperations += producerOperations[i];
	// }

	// for(int i=0;i<numConsumers;i++){
	// 	totalOperations += consumerOperations[i];
	// }

	cout<<(double)(totalOperations*2)/totalTime<<endl;

	// printQueue();

	return 0;
}