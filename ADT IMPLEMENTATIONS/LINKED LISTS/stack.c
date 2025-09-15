#include <stdlib.h>
#include <stdio.h>
#define MAX 10


typedef struct node {
	
	int data;
	struct node *next;
	
}Node;

typedef struct {
	Node *head;
	int count;
	
}List;



List* initialize (){
	
	List *L= (List*)malloc(sizeof(List));
	 
	L->head= NULL;
	
	L->count = 0;
	
	return L;
	
}

void insertPos(List *L, int data, int pos){
	
	
    Node *newNode = (Node*)malloc(sizeof(Node));
    
    if(newNode == NULL){
    	
    	printf("Allocation failed!");
    
	}
    
	
	newNode->data = data;
    newNode->next = NULL;
    
//    if(L->head == NULL){
//    	printf("Empty List!");
//    	return;
//    	
//	}
//    

	if(pos > L->count){
		printf("Invalid position!");
		return;
		
	}
	
	if(pos == 0){
	
		newNode->next=L->head;
		L->head=newNode;
		printf("Completed insertion!");
		L->count++;
		
	}  else{
		
		
	Node *trav = L->head;
	int i;
	
	for(i = 0; trav != NULL && i < pos-1  ;  trav= trav->next, i++ );
	
	
	newNode->next= trav->next;
	trav->next=newNode;
	
	
	printf("Completed insertion!");
	
	L->count++;
		
	}
	
	
	
}

void deletePos(List *L, int pos){
	
	
	if(pos > L->count){
		printf("Invalid position!");
		return;
		
	}
	
	Node *trav = L->head;
	Node *temp = L->head;

	if(pos == 0){
	
	L->head = temp->next;
	printf("Completed deletion!");
	L->count--;
	
	} 
	 if(pos == L->count){
		for(; trav != NULL  ;  trav= trav->next);
		trav->next= NULL;
		printf("Completed deletion!");
		L->count--;
		
	}else{
		
	trav = L->head;

	int i;
	
	for(i; trav != NULL && i < pos-1  ;  trav= trav->next, i++);
	
	
	trav->next= trav->next->next;

	printf("Complted deletion!");

	
	L->count--;
		
	}
	
	
	
}



void display(List *L){
	
	Node *trav = L->head;

	int i;
	for(i = 0; trav != NULL ;  trav= trav->next, i++ ){
	printf("[%d]\t%d\n",i,trav->data);	
		
		
	}
	
}


int locate(List *L, int data){
	
	Node *trav = L->head;

	int i;
	for(i = 0; trav != NULL ;  trav= trav->next, i++ ){
		if(trav->data == data){
			return i;
		}	
	}
	
	return -1;
	
}

int retrieve(List *L, int pos){
	
	Node *trav = L->head;

	int i;
	
	if(pos > L->count){
		printf("Invalid position!");
		return -1;
		
	}
	
	
	for(i =0 ; trav != NULL && i < pos;  trav= trav->next,i++);
	return trav->data;
	
}




int main (){

	
	int data,pos, repeat;
	int found;
	List *L = initialize();	
	
  while(repeat != 8) {
        printf("\n\nWHAT TO DO: \n"
               "[1] INSERT AT POS\n"
               "[2] DELETE AT POS\n"
               "[3] LOCATE \n"
               "[4] RETRIEVE\n"
               "[5] INSERT SORTED \n"
               "[6] DISPLAY LIST\n"
               "[7] DOUBLE LIST SIZE\n"
               "[8] EXIT \n\n");
        scanf("%d", &repeat);
        
        if (repeat == 1) {
            printf("What to insert?: ");
            scanf("%d", &data);
            
            printf("Where to insert [INDEX]: ");
            scanf("%d", &pos);
            
            insertPos(L,data,pos);
            
        }
        
        if (repeat == 2) {
            printf("What to delete[INDEX]: ");
            scanf("%d", &pos);
            
	 		deletePos(L,pos);
        }
        
        if (repeat == 3) {
            printf("What to Locate?: ");
            scanf("%d", &data);
            found = locate(L,data);
             if(found >= 0){
             	printf("Found at node [%d]!",found);
			 }else{
			 	printf("Element not found!");
			 }
        
        }


        if (repeat == 4) {
            printf("What to Retrieve from[INDEX]: ");
            scanf("%d", &pos);
            
            found = retrieve(L,pos);
            if(found >= 0){
             	printf("Element retrieved [%d]!",found);
			 }else{
			 	printf("Element not found!");
			 }

        }
        
        
        if (repeat == 5) {
            printf("What to insert?: ");
            scanf("%d", &data);
            

        }
        
        if(repeat == 6) {
            printf("\nDISPLAYING ...... \n");
     	 display(L);
        }

        if(repeat == 7) {
   
  
        }
    }
	
	
	
	
	
		
	
	
	
	
	
	
	
	
	
	
	
	return 0;
}
