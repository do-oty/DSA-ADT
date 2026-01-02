#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define WORD_SIZE 32

typedef struct {
    unsigned int bits[(MAX + WORD_SIZE - 1) / WORD_SIZE];
    int size;
} BitVector;

BitVector* initialize(int size) {
    BitVector* bv = (BitVector*)malloc(sizeof(BitVector));
    bv->size = size;
    for(int i = 0; i < (size + WORD_SIZE - 1) / WORD_SIZE; i++) {
        bv->bits[i] = 0;
    }
    return bv;
}

void setBit(BitVector* bv, int pos) {
    if(pos < 0 || pos >= bv->size) return;
    int word = pos / WORD_SIZE;
    int bit = pos % WORD_SIZE;
    bv->bits[word] |= (1u << bit);
}

void clearBit(BitVector* bv, int pos) {
    if(pos < 0 || pos >= bv->size) return;
    int word = pos / WORD_SIZE;
    int bit = pos % WORD_SIZE;
    bv->bits[word] &= ~(1u << bit);
}

int getBit(BitVector* bv, int pos) {
    if(pos < 0 || pos >= bv->size) return 0;
    int word = pos / WORD_SIZE;
    int bit = pos % WORD_SIZE;
    return (bv->bits[word] >> bit) & 1u;
}

void unionSet(BitVector* result, BitVector* a, BitVector* b) {
    if(a->size != b->size || result->size != a->size) return;
    
    int words = (a->size + WORD_SIZE - 1) / WORD_SIZE;
    for(int i = 0; i < words; i++) {
        result->bits[i] = a->bits[i] | b->bits[i];
    }
}

void intersectSet(BitVector* result, BitVector* a, BitVector* b) {
    if(a->size != b->size || result->size != a->size) return;
    
    int words = (a->size + WORD_SIZE - 1) / WORD_SIZE;
    for(int i = 0; i < words; i++) {
        result->bits[i] = a->bits[i] & b->bits[i];
    }
}

void display(BitVector* bv) {
    printf("Bit Vector: ");
    for(int i = 0; i < bv->size; i++) {
        printf("%d", getBit(bv, i));
    }
    printf("\n");
}

int main(void) {
    BitVector* bv1 = initialize(20);
    BitVector* bv2 = initialize(20);
    BitVector* result = initialize(20);
    
    setBit(bv1, 0);
    setBit(bv1, 2);
    setBit(bv1, 5);
    
    setBit(bv2, 1);
    setBit(bv2, 2);
    setBit(bv2, 3);
    
    printf("Set 1: ");
    display(bv1);
    printf("Set 2: ");
    display(bv2);
    
    unionSet(result, bv1, bv2);
    printf("Union: ");
    display(result);
    
    intersectSet(result, bv1, bv2);
    printf("Intersection: ");
    display(result);
    
    free(bv1);
    free(bv2);
    free(result);
    
    return 0;
}

