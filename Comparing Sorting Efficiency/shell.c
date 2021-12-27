#include "shell.h"

#include "gaps.h"

#include <stdio.h>
#include <stdlib.h>

void shell_sort(uint32_t *A, uint32_t n) {
    uint32_t j = 0;
    uint32_t temp = 0;
    uint32_t swap_temp = 0;
    extern int smoves;
    extern int scomps;
    for (int g = 0; g < 102; g++) {
        for (uint32_t i = gaps[g]; i < n; i++) {
            scomps++;
            swap_temp = A[j];
            j = i;
            temp = A[i];
            while (j >= gaps[g] && temp < A[j - gaps[g]]) {
                A[j] = A[j - gaps[g]];
                A[j - gaps[g]] = swap_temp;
                smoves += 3;
                scomps++;
                j -= gaps[g];
            }
            A[j] = temp;
        }
    }
}
