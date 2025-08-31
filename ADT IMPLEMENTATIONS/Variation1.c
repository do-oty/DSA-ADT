#include <stdlib.h>
#include <stdio.h>
#define MAX 10


typedef struct {
    int elem[MAX];
    int count;
}List;


List initialize(List L){
	L.count=0;
	return L;
}

List insertPos(List L, int data, int pos){
	
	int i;
	
	if ( pos >= L.count ){
	L.elem[pos]= data;
	L.count++;
	return L;
	} else{
			for(i = L.count; i > pos ; i--){
		L.elem[i] = L.elem[i-1];
	}
	
	L.elem[pos]= data;
	L.count++;
		
	}

	
	return L;
}


List insertSorted(List L, int data){
	
	int i;
	int pos=L.count;
	
	for(i=0; i < L.count-1;i++){
		if(data < L.elem[i]){
			pos= i;
			break;
		}
	}

	for(i = L.count; i > pos ; i--){
	L.elem[i] = L.elem[i-1];

		
	}
	
		L.elem[pos]= data;
	L.count++;

	
	return L;
}


List deletePos(List L, int pos){
	
	int i;
		
	for( i = pos; i < L.count-1; i++){
		
		L.elem[i] = L.elem[i+1];
		
	}
	
	L.count--;
	

	
	return L;
}



int locate(List L, int data){
	int i;
	for( i =0 ; i < L.count; i++){
		if(L.elem[i] == data){
			return i;
		}
			
	}
	
	return 0;
	
}

void display(List L) {
    int i;
    for(i = 0; i < L.count; i++) {
        printf("%d\n", L.elem[i]);
    }
}

	
int main ( ){
    List L;
    
    L = initialize(L);

    int i,pos, data, size;

	printf("VARIATION 1\n");
    
    printf("Input size: ");
    scanf("%d",&size);
    
    for( i=0; i < size; i++){
    printf("What to insert[%d]?: ",i);
    scanf("%d",&L.elem[i]);
    
    	
	}
	
	L.count= size;
	

	int repeat=0;

	
	
		while(repeat != 6){
			
			printf("\n\nWHAT TO DO: \n"
			"[1] INSERT AT POS\n"
			"[2] DELETE AT POS\n"
			"[3] LOCATE \n"
			"[4] INSERT SORTED \n"
			"[5] DISPLAY LIST\n"
			"[6] EXIT \n\n");
			scanf("%d",&repeat);
			
			
			if (repeat == 1){
				 printf("What to insert?: ");
			    scanf("%d",&data);
			    
			    printf("Where to insert [INDEX]: ");
			    scanf("%d",&pos);
			    
			    L = insertPos(L,data,pos);
		
			}
			
			if (repeat == 2){
			    printf("What to delete[INDEX]: ");
			    scanf("%d",&pos);
			    
			    L = deletePos(L,pos);
			    
			 
	
		
			}
			
			
				if (repeat == 3){
			    printf("What to Locate?: ");
			    scanf("%d",&data);
			    
			    if(locate(L,data)){
			    	printf("Found at index %d!",locate(L,data));
				} else {
					printf("Not found!");
				}
			    
			    
				}
			    
			    if (repeat == 4){
			  	printf("What to insert?: ");
			    scanf("%d",&data);
					
			    L = insertSorted(L,data);
			
				}
				
				if(repeat == 5){
					display(L);
				}
			
			
		
	}
	


    return 0;
}
