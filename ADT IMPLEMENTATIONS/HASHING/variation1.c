#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 11
#define EMPTY 0
#define DELETED -1

typedef struct node {
    int key;
    struct node *next;
} *List;

List chainTable[M];

int h(int key) {
    return (key % M + M) % M;
}

void chainInit() {
    for(int i = 0; i < M; i++) {
        chainTable[i] = NULL;
    }
}

void chainInsert(int key) {
    int idx = h(key);
    
    struct node *newNode = malloc(sizeof(struct node));
    newNode->key = key;
    newNode->next = chainTable[idx];
    chainTable[idx] = newNode;
}

int chainSearch(int key) {
    int idx = h(key);
    
    for(List current = chainTable[idx]; current != NULL; current = current->next) {
        if(current->key == key) {
            return 1;
        }
    }
    return 0;
}

void chainDelete(int key) {
    int idx = h(key);
    List prev = NULL;
    
    for(List current = chainTable[idx]; current != NULL; prev = current, current = current->next) {
        if(current->key == key) {
            if(prev == NULL) {
                chainTable[idx] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
    }
}

int chainCount(int bucket) {
    if(bucket < 0 || bucket >= M) return -1;
    
    int count = 0;
    for(List curr = chainTable[bucket]; curr != NULL; curr = curr->next) {
        count++;
    }
    return count;
}

void printChain() {
    printf("Chaining table:\n");
    for(int i = 0; i < M; i++) {
        printf("%2d: ", i);
        for(List p = chainTable[i]; p != NULL; p = p->next) {
            printf("%d -> ", p->key);
        }
        printf("NULL\n");
    }
}

int main(void) {
    chainInit();
    
    int keys[] = {15, 26, 37, 48, 59, 70, 81};
    int n = sizeof(keys) / sizeof(keys[0]);
    
    for(int i = 0; i < n; i++) {
        chainInsert(keys[i]);
    }
    
    printChain();
    printf("Search 37: %s\n", chainSearch(37) ? "found" : "not found");
    
    chainDelete(37);
    printChain();
    
    return 0;
}

