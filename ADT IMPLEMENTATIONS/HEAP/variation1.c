#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int tasks[MAX];
    int last;
} MaxHeap;

void insertMaxHeap(MaxHeap *h, int value) {
    if(h->last == MAX - 1) return;
    
    h->tasks[++h->last] = value;
    
    for(int i = h->last; i > 0;) {
        int parent = (i - 1) / 2;
        
        if(h->tasks[i] > h->tasks[parent]) {
            int temp = h->tasks[i];
            h->tasks[i] = h->tasks[parent];
            h->tasks[parent] = temp;
            i = parent;
        } else {
            break;
        }
    }
}

int deleteMax(MaxHeap *h) {
    if(h->last < 0) return -1;
    
    int max = h->tasks[0];
    h->tasks[0] = h->tasks[h->last--];
    
    for(int i = 0; ;) {
        int left = 2*i + 1;
        int right = 2*i + 2;
        int largest = i;
        
        if(left <= h->last && h->tasks[left] > h->tasks[largest]) {
            largest = left;
        }
        if(right <= h->last && h->tasks[right] > h->tasks[largest]) {
            largest = right;
        }
        
        if(largest == i) {
            break;
        } else {
            int temp = h->tasks[i];
            h->tasks[i] = h->tasks[largest];
            h->tasks[largest] = temp;
            i = largest;
        }
    }
    
    return max;
}

int peekMax(MaxHeap *h) {
    if(h->last < 0) return -1;
    return h->tasks[0];
}

void display(MaxHeap *h) {
    if(h->last < 0) {
        printf("Heap is empty\n");
        return;
    }
    
    for(int i = 0; i <= h->last; i++) {
        printf("%d ", h->tasks[i]);
    }
    printf("\n");
}

int main(void) {
    MaxHeap h;
    h.last = -1;
    
    int data, repeat = 0;
    
    while(repeat != 5) {
        printf("\n\nMAX HEAP:\n");
        printf("[1] INSERT\n");
        printf("[2] DELETE MAX\n");
        printf("[3] PEEK MAX\n");
        printf("[4] DISPLAY\n");
        printf("[5] EXIT\n\n");
        scanf("%d", &repeat);
        
        switch(repeat) {
            case 1:
                printf("What to insert?: ");
                scanf("%d", &data);
                insertMaxHeap(&h, data);
                break;
                
            case 2:
                data = deleteMax(&h);
                if(data != -1) {
                    printf("Deleted: %d\n", data);
                } else {
                    printf("Heap is empty\n");
                }
                break;
                
            case 3:
                data = peekMax(&h);
                if(data != -1) {
                    printf("Max: %d\n", data);
                } else {
                    printf("Heap is empty\n");
                }
                break;
                
            case 4:
                display(&h);
                break;
        }
    }
    
    return 0;
}

