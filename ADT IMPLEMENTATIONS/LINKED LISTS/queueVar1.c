#include <stdlib.h>
#include <stdio.h>
#define MAX 10


// typedef struct{
	
// 	int items[MAX];
// 	int count;
// }List;

// typedef struct {
// 	List list;
// 	int front;
// 	int rear;
	
	
// }Queue;

typedef struct node{
	int data;
	struct node* next;
}Node;

typedef struct{
	Node* front;
	Node* rear;
	int count;
}Queue;

Queue* initialize(){
	
	Queue *Q= (Queue*)malloc(sizeof(Queue));
	Q->front=NULL;
	Q->rear=NULL;
	Q->count=0;
	return Q;


	
}


void enqueue(Queue* Q, int elem){
    Node* newNode = (Node*)malloc(sizeof(Node));
 
    newNode->data = elem;
    newNode->next = NULL;

    if(isEmpty(Q)){
        Q->front = newNode;
        Q->rear = newNode;
    } else {
        Q->rear->next = newNode;   
        Q->rear = newNode;
    }
    Q->count++;
}



int dequeue(Queue* Q){

	Node* temp = Q->front;

	if(isEmpty(Q)){
		printf("EMPTY QUEUE!");
		return -1;
	}
	
	int prevFront = temp->data;


	Q->front = temp->next;
	Q->count--;


	
	
	return prevFront;
	

}
	





void display(Queue* Q){

	Node* trav= Q->front;
	printf("DISPLAYING.....\n\n");
	
	for(trav = Q->front; trav != Q->rear->next; trav = trav->next){
		printf("%d\n",trav->data );
		
	}	
	

}
	



int front(Queue* Q){

	if(isEmpty(Q)){
		printf("EMPTY QUEUE!");
		return -1;
		
	}
	return Q->front->data;
}
	

int isEmpty(Queue* Q){
	if(Q->front == NULL ){
		return 1;
	}
	return 0;
}



int main (){
	Queue* Q= initialize();
	
	
	int elem;
	int repeat=0;
		
		
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
   			scanf("%d",&elem);
   			
   			enqueue(Q,elem);
            printf("Succesfully queued!");
        }
         if (repeat == 2) {
   		
   		elem= dequeue(Q);

			if(elem != -1){
            printf("Succesfully dequeued %d!", elem);
			}
        }
        if (repeat == 3) {
   			elem= front(Q);
			if(elem != -1){
            printf("Front is %d!!", elem);
			}
   		
        }
         if (repeat == 4) {
			if(!isEmpty(Q)){
   				display(Q);
			}	else{
				printf("EMPTY QUEUE!");
			}
            
        }
        
   
    }
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	return 0;
}
