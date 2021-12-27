#include "quick.h"

#include "stack.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void quick_sort(uint32_t *A, uint32_t n) {
    uint32_t left = 0;
    uint32_t right = n - 1;

    extern int qmoves;
    extern int qcomps;

    Stack *s = stack_create();
    stack_push(s, left);
    stack_push(s, right);

    int64_t hi = 0;
    int64_t lo = 0;
    uint32_t pivot = 0;
    uint32_t i = 0;
    uint32_t j = 0;
    uint32_t temp = 0;
    while (stack_empty(s) != true) {
        stack_pop(s, &hi);
        stack_pop(s, &lo);
        pivot = A[lo + (hi - lo) / 2];
        i = lo - 1;
        j = hi + 1;
        do {
            qcomps++;
            i++;
            while (A[i] < pivot) {
                qcomps++;
                i += 1;
            }

            j--;
            while (A[j] > pivot) {
                qcomps++;
                j--;
            }
            if (i < j) {
                qcomps++;
                temp = A[i];
                A[i] = A[j];
                A[j] = temp;
                qmoves += 3;
            }
        } while (i < j);

        if (j + 1 < hi) {
            qcomps++;
            stack_push(s, j + 1);
            stack_push(s, hi);
        }
        if (lo < j) {
            qcomps++;
            stack_push(s, lo);
            stack_push(s, j);
        }
    }
    stack_delete(&s);
}
