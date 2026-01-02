#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int count;
} List;

List* initialize() {
    // TODO: Allocate List, set head = NULL, count = 0

    List* L = (List*)malloc(sizeof(List));
    L->head = NULL;
    L->count = 0;
    return L;
}

void insertFirst(List* L, int data) {
    // TODO: Insert at beginning of list

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = L->head;
    L->head = newNode;
    L->count++;


}

void insertLast(List* L, int data) {
    // TODO: Insert at end of list
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    Node* current = L->head;

    if(L->head == NULL) {
        L->head = newNode;
    } else {
    
    for(; current->next != NULL; current = current->next);
        current->next = newNode;
    }

    L->count++;

}

void insertPos(List* L, int data, int pos) {
    // TODO: Insert at specific position
    // Handle edge cases (pos = 0, pos > count)

    if(pos <= 0 || pos > L->count + 1 || L->head == NULL) return; // Invalid position

    if(pos == 1) {
        insertFirst(L, data);
        return;
    }

    if(pos == L->count + 1) {
        insertLast(L, data);
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    Node* current = L->head;
 

    for(int i = 1; i < pos - 1 && current != NULL; i++, current = current->next); 

    newNode->next = current->next;
    current->next = newNode;
    L->count++;
    
    

}

void deleteFirst(List* L) {
    // TODO: Delete first node
    // Check if list is empty

    if(L->head == NULL) return;

    Node* temp = L->head;
    L->head = L->head->next;
    free(temp);
    L->count--;

  
}

void deleteLast(List* L) {
    // TODO: Delete last node
    // Handle single node case

    if(L->head == NULL) return;

    if(L->head->next == NULL) {
        free(L->head);
        L->head = NULL;
        L->count--;
        return;
    }

    Node* current = L->head;
    for(; current->next->next != NULL; current = current->next);
    free(current->next);
    current->next = NULL;
    L->count--;

}

void deletePos(List* L, int pos) {
    // TODO: Delete node at specific position
    // Handle edge cases

    if(pos <= 0 || pos > L->count || L->head == NULL) return; // Invalid position

    if(pos == 1) {
        deleteFirst(L);
        return;
    }

    if(pos == L->count) {
        deleteLast(L);
        return;
    }

    Node* current = L->head;

    for(int i = 1; i < pos - 1 && current != NULL; i++, current = current->next);

    Node* temp = current->next;
    current->next = current->next->next;
    free(temp);
    L->count--;


}

int search(List* L, int data) {
    // TODO: Search for data, return position
    // Return -1 if not found

    if(L->head == NULL) return -1;

    Node* current = L->head;
    for(int i = 1; i <= L->count && current != NULL; i++, current = current->next){
         if(current->data == data){
             return i;
        }
        
    }
    return -1;
}

void display(List* L) {
    // TODO: Display all elements

    if(L->head == NULL) return;

    Node* current = L->head;
    for(; current != NULL; current = current->next){

        printf("%d ", current->data);
    }

}

void displayReverse(List* L) {
    // TODO: Display elements in reverse (using recursion?)

    if(L->head == NULL) return;

    Node* current = L->head;
    
    int arr[L->count];
    for(int i = 0; i < L->count; i++, current = current->next){
        arr[i] = current->data;
    }

    for(int i = L->count - 1; i >= 0; i--){
        printf("%d ", arr[i]);
    }




}

int main() {
    List* L = initialize();
    int data, pos, repeat = 0;
    
    while(repeat != 10) {
        printf("\n\nSINGLY LINKED LIST:\n");
        printf("[1] INSERT FIRST\n");
        printf("[2] INSERT LAST\n");
        printf("[3] INSERT AT POSITION\n");
        printf("[4] DELETE FIRST\n");
        printf("[5] DELETE LAST\n");
        printf("[6] DELETE AT POSITION\n");
        printf("[7] SEARCH\n");
        printf("[8] DISPLAY\n");
        printf("[9] DISPLAY REVERSE\n");
        printf("[10] EXIT\n\n");
        scanf("%d", &repeat);
        
        switch(repeat) {
            case 1:
                printf("What to insert?: ");
                scanf("%d", &data);
                insertFirst(L, data);
                break;
                
            case 2:
                printf("What to insert?: ");
                scanf("%d", &data);
                insertLast(L, data);
                break;
                
            case 3:
                printf("What to insert?: ");
                scanf("%d", &data);
                printf("At what position?: ");
                scanf("%d", &pos);
                insertPos(L, data, pos);
                break;
                
            case 4:
                deleteFirst(L);
                break;
                
            case 5:
                deleteLast(L);
                break;
                
            case 6:
                printf("Delete at what position?: ");
                scanf("%d", &pos);
                deletePos(L, pos);
                break;
                
            case 7:
                printf("Search for what?: ");
                scanf("%d", &data);
                pos = search(L, data);
                if(pos != -1) {
                    printf("Found at position %d\n", pos);
                } else {
                    printf("Not found\n");
                }
                break;
                
            case 8:
                display(L);
                break;
                
            case 9:
                displayReverse(L);
                break;
        }
    }
    
    free(L);
    return 0;
} 