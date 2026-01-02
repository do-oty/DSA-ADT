#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
    int count;
} Stack;

Stack* initialize() {
    Stack* S = (Stack*)malloc(sizeof(Stack));
    S->top = NULL;
    S->count = 0;
    return S;
}

int isEmpty(Stack* S) {
    if(S->top == NULL) {
        return 1;
    }
    return 0;
}

void push(Stack* S, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = S->top;
    S->top = newNode;
    S->count++;
}

int pop(Stack* S) {
    if(isEmpty(S)) {
        printf("Stack is empty\n");
        return -1;
    }
    Node* temp = S->top;
    int data = temp->data;
    S->top = S->top->next;
    free(temp);
    S->count--;
    return data;
}

int top(Stack* S) {
    if(isEmpty(S)) {
        printf("Stack is empty\n");
        return -1;
    }
    return S->top->data;
}

void display(Stack* S) {
    if(isEmpty(S)) {
        printf("Stack is empty\n");
        return;
    }
    Node* current = S->top;
    for(; current != NULL; current = current->next) {
        printf("%d ", current->data);
    }
    printf("\n");
}

int search(Stack* S, int target) {
    if(isEmpty(S)) {
        printf("Stack is empty\n");
        return 0;
    }
    int tempArray[1000];
    int count = 0;
    int found = 0;
    
    while(!isEmpty(S)) {
        int current = top(S);
        if(current == target) {
            found = 1;
            break;
        }
        tempArray[count++] = pop(S);
    }
    
    for(int i = count - 1; i >= 0; i--) {
        push(S, tempArray[i]);
    }
    
    return found;
}

int main() {
    Stack* S = initialize();
    int data, repeat = 0;
    
    while(repeat != 7) {
        printf("\n\nLINKED LIST STACK:\n");
        printf("[1] PUSH\n");
        printf("[2] POP\n");
        printf("[3] TOP\n");
        printf("[4] IS EMPTY\n");
        printf("[5] DISPLAY\n");
        printf("[6] SEARCH (Stack Ops Only)\n");
        printf("[7] EXIT\n\n");
        scanf("%d", &repeat);
        
        switch(repeat) {
            case 1:
                printf("What to push?: ");
                scanf("%d", &data);
                push(S, data);
                break;
                
            case 2:
                data = pop(S);
                if(data != -1) {
                    printf("Popped: %d\n", data);
                }
                break;
                
            case 3:
                data = top(S);
                if(data != -1) {
                    printf("Top: %d\n", data);
                }
                break;
                
            case 4:
                if(isEmpty(S)) {
                    printf("Stack is empty\n");
                } else {
                    printf("Stack is not empty\n");
                }
                break;
                
            case 5:
                display(S);
                break;
                
            case 6:
                printf("Search for what?: ");
                scanf("%d", &data);
                if(search(S, data)) {
                    printf("Found %d in stack!\n", data);
                } else {
                    printf("%d not found in stack!\n", data);
                }
                break;
        }
    }
    
    free(S);
    return 0;
} 