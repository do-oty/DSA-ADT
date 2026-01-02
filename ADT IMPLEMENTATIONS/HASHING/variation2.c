#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 64
#define PRIMARY 32
#define EMPTY 0
#define DELETED -1
#define NIL -1

typedef struct {
    int key;
    int next;
} Slot;

Slot coTable[M];
int freeIdx = PRIMARY;

int h(int key) {
    return (key % PRIMARY + PRIMARY) % PRIMARY;
}

void coInit() {
    for(int i = 0; i < M; i++) {
        coTable[i].key = EMPTY;
        coTable[i].next = NIL;
    }
    freeIdx = PRIMARY;
}

int coFindFree() {
    for(; freeIdx < M && coTable[freeIdx].key != EMPTY && coTable[freeIdx].key != DELETED; freeIdx++);
    if(freeIdx >= M) return -1;
    return freeIdx;
}

void coInsert(int key) {
    int idx = h(key) % PRIMARY;
    
    if(coTable[idx].key == EMPTY || coTable[idx].key == DELETED) {
        coTable[idx].key = key;
        coTable[idx].next = -1;
        return;
    }
    
    int curr = idx;
    for(; coTable[curr].next != -1; curr = coTable[curr].next);
    
    int free = coFindFree();
    if(free == -1) return;
    
    coTable[curr].next = free;
    coTable[free].key = key;
    coTable[free].next = -1;
    freeIdx++;
}

int coSearch(int key) {
    int idx = h(key) % PRIMARY;
    
    if(coTable[idx].key == EMPTY) return 0;
    
    for(int curr = idx; curr != -1; curr = coTable[curr].next) {
        if(coTable[curr].key == key) {
            return 1;
        }
    }
    return 0;
}

void coDelete(int key) {
    int idx = h(key) % PRIMARY;
    
    if(coTable[idx].key == EMPTY) return;
    
    for(int curr = idx; curr != -1; curr = coTable[curr].next) {
        if(coTable[curr].key == key) {
            coTable[curr].key = DELETED;
            return;
        }
    }
}

void printProbe() {
    printf("Coalesced table (primary 0..%d, overflow %d..%d):\n", PRIMARY-1, PRIMARY, M-1);
    for(int i = 0; i < M; i++) {
        if(coTable[i].key == EMPTY) {
            printf("[%2d]: EMPTY  next=%d\n", i, coTable[i].next);
        } else if(coTable[i].key == DELETED) {
            printf("[%2d]: DELETED next=%d\n", i, coTable[i].next);
        } else {
            printf("[%2d]: %d next=%d\n", i, coTable[i].key, coTable[i].next);
        }
    }
}

int main(void) {
    coInit();
    
    int keys[] = {15, 26, 37, 48, 59, 70, 81};
    int n = sizeof(keys) / sizeof(keys[0]);
    
    for(int i = 0; i < n; i++) {
        coInsert(keys[i]);
    }
    
    printProbe();
    printf("Search 37: %s\n", coSearch(37) ? "found" : "not found");
    
    coDelete(37);
    printProbe();
    
    return 0;
}

