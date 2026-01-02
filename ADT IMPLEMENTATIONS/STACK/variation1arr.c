#include <stdlib.h>
#include <stdio.h>
#define MAX 10

typedef struct {
	int items[MAX];
	int top;
} Stack;

Stack* initialize() {
    // TODO: Allocate Stack, set top = -1

    Stack* S = (Stack*)malloc(sizeof(Stack));
    S->top = -1;
    return S;


}

int isEmpty(Stack* S) {
    // TODO: Return 1 if empty, 0 otherwise

    if(S->top ==  -1){
        return 1;
    }
    return 0;
}

int isFull(Stack* S) {
    // TODO: Return 1 if full, 0 otherwise

    if(S->top == MAX - 1){
        return 1;
    }
    return 0;
}

void push(Stack* S, int data) {
    // TODO: Add element to top of stack
    // Check if stack is full 

    if(isFull(S)){
        printf("Stack is full\n");
        return;
    }
        
    S->top++;

    S->items[S->top] = data;

}

int pop(Stack* S) {
    // TODO: Remove and return top element
    // Check if stack is empty first
    // Return -1 if empty
    
    if(isEmpty(S)){
        printf("Stack is empty\n");
        return -1;
    }

    int popped = S->items[S->top];
    S->top--;
    return popped;
}

int top(Stack* S) {
    // TODO: Return top element without removing
    // Check if stack is empty first
    // Return -1 if empty

     if(isEmpty(S)){
        printf("Stack is empty\n");
        return -1;
    }

    return S->items[S->top];


}

void display(Stack* S) {
    // TODO: Display all elements from top to bottom
    if(isEmpty(S)){
        printf("Stack is empty\n");
        return;
    }

    for(int i = S->top; i >= 0 ; i--){
        printf("%d ", S->items[i]);
    }
    printf("\n");
}

int search(Stack* S, int target) {
    // TODO: Search for target using ONLY pop() and top() functions
    // DESTRUCTIVE TRAVERSAL - must restore stack after searching
    
    // Step 1: Create temporary storage for popped elements
    // int tempArray[MAX];
    // int count = 0;
    
    // Step 2: Use while loop with !isEmpty(S)
    // - Use top(S) to peek at current element
    // - If matches target, set found flag and break
    // - If no match, pop() and store in tempArray
    
    // Step 3: Restore original stack order
    // - Push back elements from tempArray in REVERSE order
    // - Use for loop: i = count-1; i >= 0; i--
    
    // Return 1 if found, 0 if not found



    int tempArray[MAX];
    int count = 0;
    int found = 0;
    if (isEmpty(S)){
        printf("Stack is empty\n");
        return 0;
    }
    int current;
    for(int i = 0;!isEmpty(S); tempArray[i] = pop(S) , i++, count++){
        current = top(S);
        if(current == target){
            found = 1;
            break;
        }
    }

    for(int i = count - 1; i >= 0; i--){
        push(S, tempArray[i]);
    }


    return found;
    

}

int main() {
    Stack* S = initialize();
    int data, repeat = 0;
    
    while(repeat != 7) {
        printf("\n\nARRAY STACK:\n");
        printf("[1] PUSH\n");
        printf("[2] POP\n");
        printf("[3] TOP\n");
        printf("[4] IS EMPTY\n");
        printf("[5] DISPLAY\n");
        printf("[6] SEARCH (Destructive)\n");
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
