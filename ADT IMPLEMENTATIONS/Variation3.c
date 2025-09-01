#include <stdlib.h>
#include <stdio.h>
#define MAX 10

typedef struct {
    int *elem;
    int count;
    int size;
} List;


List initialize(List L) {
    L.count = 0;
    L.elem = (int*)malloc(MAX * sizeof(int));
    L.size = MAX;
    return L;
}

List resize(List L) {
    L.size = L.size * 2;
    L.elem = (int*)realloc(L.elem, L.size * sizeof(int));
    
    return L;
}


List insertPos(List L, int data, int pos) {
    int i;
       if(L.count >= L.size){
    	resize(L);
     printf("List resized to %d", L.size);
	}
    if (pos >= L.count) {
        L.elem[pos] = data;
        L.count++;
    } else {
        for(i = L.count; i > pos; i--) {
            L.elem[i] = L.elem[i-1];
        }
        L.elem[pos] = data;
        L.count++;
    }
    return L;
}

List insertSorted(List L, int data) {
    int i;
    int pos = L.count;
       if(L.count >= L.size){
    	resize(L);
     printf("List resized to %d", L.size);
	}
    for(i = 0; i < L.count-1; i++) {
        if(data < L.elem[i]) {
            pos = i;
            break;
        }
    }

    for(i = L.count; i > pos; i--) {
        L.elem[i] = L.elem[i-1];
    }
    
    L.elem[pos] = data;
    L.count++;
    return L;
}

List deletePos(List L, int pos) {
    int i;
    
    for(i = pos; i < L.count-1; i++) {
        L.elem[i] = L.elem[i+1];
    }
    
    L.count--;
    return L;
}

int locate(List L, int data) {
    int i;
    for(i = 0; i < L.count; i++) {
        if(L.elem[i] == data) {
            return 1;
        }
    }
    return 0;
}




int main() {
    List L;
    
    L = initialize(L);

    int i, pos, data, size;
    
	printf("VARIATION 3\n");

    printf("Input size: ");
    scanf("%d", &size);
    
    for(i = 0; i < size; i++) {
        printf("What to insert[%d]?: ", i);
        scanf("%d", &L.elem[i]);
    }
    
    L.count = size;
    
    int repeat = 0;
    
    while(repeat != 7) {
        printf("\n\nWHAT TO DO: \n"
               "[1] INSERT AT POS\n"
               "[2] DELETE AT POS\n"
               "[3] LOCATE \n"
               "[4] INSERT SORTED \n"
               "[5] DISPLAY LIST\n"
               "[6] EXIT \n\n");
        scanf("%d", &repeat);
        
        if (repeat == 1) {
            printf("What to insert?: ");
            scanf("%d", &data);
            
            printf("Where to insert [INDEX]: ");
            scanf("%d", &pos);
            
            L = insertPos(L, data, pos);
        }
        
        if (repeat == 2) {
            printf("What to delete[INDEX]: ");
            scanf("%d", &pos);
            
            L = deletePos(L, pos);
        }
        
        if (repeat == 3) {
            printf("What to Locate?: ");
            scanf("%d", &data);
            
            if(locate(L, data)) {
                printf("Found!");
            } else {
                printf("Not found!");
            }
        }
        
        if (repeat == 4) {
            printf("What to insert?: ");
            scanf("%d", &data);
            
            L = insertSorted(L, data);
        }
        
        if(repeat == 5) {
            printf("\nDISPLAYING ...... \n");
            for(i = 0; i < L.count; i++) {
                printf("%d\n", L.elem[i]);
            }
        }
        
          if(repeat == 6) {
            L=resize(L);
            printf("List resized to %d", L.size);
        }
    }
    
  
    free(L.elem);
    
    return 0;
}
