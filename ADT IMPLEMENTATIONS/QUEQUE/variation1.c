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
	
	Queue *Q= (Queue*)malloc(sizeof(Queue));
	
	Q->front=-1;
	Q->rear=-1;
	Q->list.count=0;
	
	
	return Q;

	
}


void enqueue(Queue* Q, int elem){
	
	if(Q->list.count == MAX){
		printf("FULL QUEUE!");
		return;
	}
	
	if(Q->list.count == 0){
		Q->front=0;
		Q->rear=0;
		Q->list.items[0]=elem;
		Q->list.count++;		 
	} else{
		
		Q->list.items[(Q->rear+1) % MAX] = elem;
		Q->list.count++;
	}
	
}


void display(Queue* Q){
	
	int i=0;
	
	printf("DISPLAYING.....\n\n");
	
	for(i= Q->front; i < Q->list.count - 1; i++){
		printf("%d\n",Q->list.items[i]);
	}	
	
	if(Q->rear < Q->front){
		for (i= Q->rear; i < Q->front - 1; i++){
		printf("%d\n",Q->list.items[i]);
		
		}
		
	}

}




int main (){
	Queue* Q= initialize();
	
	
	int elem;
	int repeat=0;
		
		
  while(repeat != 5) {
        printf("\n\nWHAT TO DO: \n"
               "[1] ENQUEUE\n"
               "[2]	DEQUEUE\n"
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
         if (repeat == 4) {
   			display(Q);
            
        }
        
   
    }
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	return 0;
}
