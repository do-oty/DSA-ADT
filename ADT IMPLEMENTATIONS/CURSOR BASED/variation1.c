#include <stdlib.h>
#include <stdio.h>
#define MAX 10

typedef struct {
    int data;
    int next;  
} Node;

typedef struct {
    Node nodes[MAX];
    int head;
    int avail;  
    int count;
} CursorList;

void initializeAvail(CursorList* L) {
    for(int i = 0; i < MAX - 1; i++) {
        L->nodes[i].next = i + 1;
    }
    L->nodes[MAX - 1].next = -1;
    L->avail = 0;
}

CursorList* initialize() {
    CursorList* L = (CursorList*)malloc(sizeof(CursorList));
    L->head = -1;
    L->count = 0;
    initializeAvail(L);
    return L;
}

int allocNode(CursorList* L) {
    if(L->avail == -1) {
        return -1;
    }
    int index = L->avail;
    L->avail = L->nodes[L->avail].next;
    return index;
}

void freeNode(CursorList* L, int index) {
    L->nodes[index].next = L->avail;
    L->avail = index;
}

void insertPos(CursorList* L, int data, int pos) {
    if(pos < 0 || pos > L->count) return;
    
    int newNode = allocNode(L);
    if(newNode == -1) return;
    
    L->nodes[newNode].data = data;
    
    if(pos == 0) {
        L->nodes[newNode].next = L->head;
        L->head = newNode;
    } else {
        int current = L->head;
        for(int i = 0; i < pos - 1; i++) {
            current = L->nodes[current].next;
        }
        L->nodes[newNode].next = L->nodes[current].next;
        L->nodes[current].next = newNode;
    }
    L->count++;
}

void deletePos(CursorList* L, int pos) {
    if(pos < 0 || pos >= L->count || L->head == -1) return;
    
    int toDelete;
    if(pos == 0) {
        toDelete = L->head;
        L->head = L->nodes[L->head].next;
    } else {
        int current = L->head;
        for(int i = 0; i < pos - 1; i++) {
            current = L->nodes[current].next;
        }
        toDelete = L->nodes[current].next;
        L->nodes[current].next = L->nodes[toDelete].next;
    }
    freeNode(L, toDelete);
    L->count--;
}

void insertSorted(CursorList* L, int data) {
    int pos = 0;
    int current = L->head;
    
    for(; current != -1 && L->nodes[current].data < data; current = L->nodes[current].next, pos++);
    
    insertPos(L, data, pos);
}

int locate(CursorList* L, int data) {
    int pos = 0;
    int current = L->head;
    
    for(; current != -1; current = L->nodes[current].next, pos++) {
        if(L->nodes[current].data == data) {
            return pos;
        }
    }
    return -1;
}

int retrieve(CursorList* L, int pos) {
    if(pos < 0 || pos >= L->count) return -1;
    
    int current = L->head;
    for(int i = 0; i < pos; i++) {
        current = L->nodes[current].next;
    }
    return L->nodes[current].data;
}

void display(CursorList* L) {
    if(L->head == -1) {
        printf("List is empty\n");
        return;
    }
    
    int pos = 0;
    int current = L->head;
    printf("Position | Array Index | Data\n");
    for(; current != -1; current = L->nodes[current].next, pos++) {
        printf("  [%2d]   |     [%2d]    |  %d\n", pos, current, L->nodes[current].data);
    }
}

void displayAvail(CursorList* L) {
    printf("Available nodes: ");
    int current = L->avail;
    for(; current != -1; current = L->nodes[current].next) {
        printf("%d -> ", current);
    }
    printf("-1\n");
}

int main() {
    CursorList* L = initialize();
    int data, pos, repeat = 0, found;
    
    while(repeat != 9) {
        printf("\n\nCURSOR-BASED LIST:\n");
        printf("[1] INSERT AT POS\n");
        printf("[2] DELETE AT POS\n");
        printf("[3] LOCATE\n");
        printf("[4] RETRIEVE\n");
        printf("[5] INSERT SORTED\n");
        printf("[6] DISPLAY LIST\n");
        printf("[7] DISPLAY AVAILABLE\n");
        printf("[8] SHOW MEMORY LAYOUT\n");
        printf("[9] EXIT\n\n");
        scanf("%d", &repeat);
        
        switch(repeat) {
            case 1:
                printf("What to insert?: ");
                scanf("%d", &data);
                printf("Where to insert [INDEX]: ");
                scanf("%d", &pos);
                insertPos(L, data, pos);
                break;
                
            case 2:
                printf("What to delete[INDEX]: ");
                scanf("%d", &pos);
                deletePos(L, pos);
                break;
                
            case 3:
                printf("What to locate?: ");
                scanf("%d", &data);
                found = locate(L, data);
                if(found >= 0) {
                    printf("Found at position [%d]!\n", found);
                } else {
                    printf("Element not found!\n");
                }
                break;
                
            case 4:
                printf("What position to retrieve[INDEX]: ");
                scanf("%d", &pos);
                found = retrieve(L, pos);
                if(found != -1) {
                    printf("Element at position %d: %d\n", pos, found);
                }
                break;
                
            case 5:
                printf("What to insert sorted?: ");
                scanf("%d", &data);
                insertSorted(L, data);
                break;
                
            case 6:
                display(L);
                break;
                
            case 7:
                displayAvail(L);
                break;
                
            case 8:
                printf("Memory Layout:\n");
                for(int i = 0; i < MAX; i++) {
                    printf("Index %d: data=%d, next=%d\n", 
                           i, L->nodes[i].data, L->nodes[i].next);
                }
                break;
        }
    }
    
    free(L);
    return 0;
}
