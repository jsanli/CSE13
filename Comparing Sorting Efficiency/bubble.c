#include "bubble.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void bubble_sort(uint32_t *A, uint32_t n) {
    bool swapped = true;
    extern int bmoves;
    extern int bcomps;
    uint32_t x = n;
    uint32_t temp = 0;
    while (swapped == true) {
        swapped = false;
        for (uint32_t i = 1; i < x; i++) {
            bcomps++;
            if (A[i] < A[i - 1]) {
                temp = A[i];
                A[i] = A[i - 1];
                A[i - 1] = temp;
                bmoves += 3;
                swapped = true;
            }
        }
        x -= 1;
    }
}
