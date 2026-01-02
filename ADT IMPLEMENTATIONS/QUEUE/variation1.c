#include <stdlib.h>
#include <stdio.h>
#define MAX 10

typedef struct{
	int items[MAX];
	int count;
}List;

typedef struct {
	List list;
	int front;
	int rear;
}Queue;

Queue* initialize(){
	Queue *Q = (Queue*)malloc(sizeof(Queue));
	Q->front = 0;
	Q->rear = -1;
	Q->list.count = 0;
	return Q;
}

void enqueue(Queue* Q, int elem){
	if(Q->list.count == MAX){
		printf("QUEUE IS FULL!");
		return;
	}
	
	Q->rear = (Q->rear + 1) % MAX;
	Q->list.items[Q->rear] = elem;
	Q->list.count++;
}

int dequeue(Queue* Q){
	if(Q->list.count == 0){
		printf("EMPTY QUEUE!");
		return -1;
	}
	
	int prevFront = Q->list.items[Q->front];
	Q->front = (Q->front + 1) % MAX;
	Q->list.count--;
	
	return prevFront;
}

int front(Queue* Q){
	if(Q->list.count == 0){
		printf("EMPTY QUEUE!");
		return -1;
	}
	return Q->list.items[Q->front];
}

void display(Queue* Q){
	if(Q->list.count == 0){
		printf("EMPTY QUEUE!\n");
		return;
	}
	
	printf("DISPLAYING QUEUE.....\n");
	int i;
	int current = Q->front;
	
	for(i = 0; i < Q->list.count; i++){
		printf("%d\n", Q->list.items[current]);
		current = (current + 1) % MAX;
	}
}

int main(){
	Queue* Q = initialize();
	
	int elem;
	int repeat = 0;
		
	while(repeat != 5) {
		printf("\n\nWHAT TO DO: \n"
			   "[1] ENQUEUE\n"
			   "[2] DEQUEUE\n"
			   "[3] CHECK FRONT\n"	
			   "[4] DISPLAY \n"
			   "[5] EXIT \n\n");
		scanf("%d", &repeat);
		
		if (repeat == 1) {
			printf("What to enqueue?: ");
			scanf("%d", &elem);
			
			enqueue(Q, elem);
			printf("Successfully queued!");
		}
		if (repeat == 2) {
			elem = dequeue(Q);
			if(elem != -1){
				printf("Successfully dequeued %d!", elem);
			}
		}
		if (repeat == 3) {
			elem = front(Q);
			if(elem != -1){
				printf("Front is %d!!", elem);
			}
		}
		if (repeat == 4) {
			display(Q);
		}
	}
	

	return 0;
}
