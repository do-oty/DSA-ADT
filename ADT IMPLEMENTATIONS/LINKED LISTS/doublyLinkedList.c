#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int count;
} List;

List* initialize() {
    // TODO: Allocate List, set head = NULL, tail = NULL, count = 0

    List *L = (List *)malloc(sizeof(List));
    L->head = NULL;
    L->tail = NULL;
    L->count = 0;

    return L;

}

void insertFirst(List* L, int data) {
    // TODO: Insert at beginning
    // Update both next and prev pointers
    // Handle empty list case

    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = L->head;
    newNode->prev = NULL;
    L->head = newNode;

    if(L->tail == NULL) {
        L->tail = newNode;
    }

    if(L->head->next != NULL) {
        L->head->next->prev = newNode;
    }

    L->count++;
}

void insertLast(List* L, int data) {
    // TODO: Insert at end
    // Use tail pointer for efficiency

    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = L->tail;
 

  if(L->tail != NULL) {
        L->tail->next = newNode; // Link old tail to new node
    } else {
        L->head = newNode; // First node: set head
    }

    L->tail = newNode; // Update tail pointer
    L->count++;
}

void insertPos(List* L, int data, int pos) {
    // TODO: Insert at specific position
    // Optimize: traverse from head or tail depending on position

    if(pos == 1) {
        insertFirst(L, data);
    } else {
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = data;
        newNode->next = NULL;
        newNode->prev = NULL;
        L->count++;

        Node *current = L->head;
        for(int i = 1; i < pos - 1 && current != NULL; i++, current = current->next);

        newNode->next = current->next; // Link new node to the next node
        newNode->prev = current; // Link new node to the previous node
        current->next = newNode; // Link previous node to the new node

        if(newNode->next != NULL) { // Update the next node's previous pointer
            newNode->next->prev = newNode;
        }
        if(current->next == NULL) { // Update the tail pointer
            L->tail = newNode;
        }

        L->count++;
    }   

    if(pos == L->count + 1) {
        insertLast(L, data);
    }


}

void deleteFirst(List* L) {
    // TODO: Delete first node
    // Update head and prev pointers

    if(L->head == NULL) return; 

   Node *temp = L->head;

    // Single node check
    if(L->head->next == NULL) {  
        L->head = NULL;
        L->tail = NULL;
        free(temp);
        L->count--;
        return;
    }

    // Normal case
    L->head->next->prev = NULL;
    L->head = L->head->next;
    L->head->prev = NULL;

    free(temp);
    L->count--;
    
}

void deleteLast(List* L) {
    // TODO: Delete last node
    // Use tail pointer for efficiency

    if(L->tail == NULL) return;

    Node *temp = L->tail;

    // Single node check
    if(L->tail->prev == NULL) {
        L->head = NULL;
        L->tail = NULL;
        free(temp);
        L->count--;
        return;
    }

    // Normal case
    L->tail = L->tail->prev;
    L->tail->next = NULL;
    free(temp);
    L->count--;

}

void deletePos(List* L, int pos) {
    // TODO: Delete at specific position
    // Optimize traversal direction

    if(pos <= 0 || pos > L->count || L->head == NULL) return; // Invalid position

    if(pos == 1) { // First position
        deleteFirst(L);
        return;
    } else if(pos == L->count) { // Last position
        deleteLast(L);
        return;
    } 


    Node *current = L->head;

    for(int i = 1; i < pos  && current != NULL; i++, current = current->next); // Traverse to the position

   current->prev->next = current->next; // Update the previous node's next pointer
   current->next->prev = current->prev;     

   L->count--;

   if(current->next == NULL) {
    L->tail = current->prev;
   }
   free(current);


}

int search(List* L, int data) {
    // TODO: Search for data, return position
    // Return -1 if not found
    Node *current = L->head;
      for(int i = 1; current != NULL;current = current->next, i++){
        if(current->data == data) {
            return i;
        }
      }
      return -1;
      
}

void displayForward(List* L) {
    // TODO: Display from head to tail


    Node *current = L->head;

      for(; current != NULL;current = current->next){
        printf("%d ", current->data);
      }

   
}

void displayBackward(List* L) {
    // TODO: Display from tail to head
    // Use prev pointers

     Node *current = L->tail;

      for(; current != NULL;current = current->prev){
        printf("%d ", current->data);
      }

}

int main() {
    List* L = initialize();
    int data, pos, repeat = 0;
    
    while(repeat != 11) {
        printf("\n\nDOUBLY LINKED LIST:\n");
        printf("[1] INSERT FIRST\n");
        printf("[2] INSERT LAST\n");
        printf("[3] INSERT AT POSITION\n");
        printf("[4] DELETE FIRST\n");
        printf("[5] DELETE LAST\n");
        printf("[6] DELETE AT POSITION\n");
        printf("[7] SEARCH\n");
        printf("[8] DISPLAY FORWARD\n");
        printf("[9] DISPLAY BACKWARD\n");
        printf("[10] SHOW COUNT\n");
        printf("[11] EXIT\n\n");
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
                printf("Forward: ");
                displayForward(L);
                break;
                
            case 9:
                printf("Backward: ");
                displayBackward(L);
                break;
                
            case 10:
                printf("Count: %d\n", L->count);
                break;
        }
    }
    
    free(L);
    return 0;
} 