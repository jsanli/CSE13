#include "bm.h"

#include "hamming.h"

#include <stdio.h>
#include <stdlib.h>

struct BitMatrix {
    uint32_t rows;
    uint32_t cols;
    uint8_t **mat;
};

BitMatrix *bm_create(uint32_t rows, uint32_t cols) {
    BitMatrix *m = (BitMatrix *) calloc(1, sizeof(BitMatrix));
    m->rows = rows;
    m->cols = cols;
    m->mat = (uint8_t **) calloc(rows, sizeof(uint8_t *));
    uint32_t num_bytes = (cols / 8 == 0) ? cols / 8 : cols / 8 + 1;
    for (uint32_t r = 0; r < rows; r++) {
        m->mat[r] = (uint8_t *) calloc(num_bytes, sizeof(uint8_t));
    }
    return m;
}

void bm_delete(BitMatrix **m) {
    free(*m);
    *m = NULL;
    return;
}

uint32_t bm_rows(BitMatrix *m) {
    return m->rows;
}

uint32_t bm_cols(BitMatrix *m) {
    return m->cols / 8;
}

void bm_set_bit(BitMatrix *m, uint32_t row, uint32_t col) {
    uint8_t mask = 1 << (col % 8);
    m->mat[row][col / 8] = m->mat[row][col / 8] | mask;
}

void bm_clr_bit(BitMatrix *m, uint32_t row, uint32_t col) {
    uint8_t mask = ~(1 << (col % 8));
    m->mat[row][col / 8] = m->mat[row][col / 8] & mask;
}

uint8_t bm_get_bit(BitMatrix *m, uint32_t row, uint32_t col) {
    uint8_t mask = 1 << (col % 8);
    //m->mat[row][col/8] = m->mat[row][col/8] & mask;
    return (m->mat[row][col / 8] & mask) >> (col % 8);
}

void bm_print(BitMatrix *m) {
    for (uint32_t r = 0; r < m->rows; r++) {
        for (uint32_t c = 0; c < m->cols; c++) {
            printf("%d", bm_get_bit(m, r, c));
        }
        printf("\n");
    }
}
