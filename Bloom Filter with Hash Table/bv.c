#include "bv.h"

#include <stdio.h>
#include <stdlib.h>

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

BitVector *bv_create(uint32_t length) {
    BitVector *bv = (BitVector *) calloc(1, sizeof(BitVector));
    bv->length = length;
    bv->vector
        = (uint8_t *) calloc(length % 8 == 0 ? length / 8 : (length / 8 + 1), sizeof(uint8_t));
    return bv;
}

void bv_delete(BitVector **bv) {
    free((*bv)->vector);
    (*bv)->vector = NULL;
    free(*bv);
    *bv = NULL;
}

uint32_t bv_length(BitVector *bv) {
    return (bv->length);
}

void bv_set_bit(BitVector *bv, uint32_t i) {
    bv->vector[i / 8] = bv->vector[i / 8] | (1 << i % 8);
}

void bv_clr_bit(BitVector *bv, uint32_t i) {
    bv->vector[i / 8] = bv->vector[i / 8] & ~(1 << i % 8);
}

uint8_t bv_get_bit(BitVector *bv, uint32_t i) {
    return ((bv->vector[i / 8] & (1 << i % 8)) >> i % 8);
}

void bv_print(BitVector *bv) {
    for (uint32_t l = 0; l < bv->length; l++) {
        printf("%u", bv_get_bit(bv, l));
    }
    printf("\n");
}
