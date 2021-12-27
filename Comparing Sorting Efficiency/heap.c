#include "heap.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void heap_sort(uint32_t *A, uint32_t n) {
    uint32_t first = 1;
    uint32_t last = n;
    uint32_t left = 0;
    uint32_t right = 0;
    bool found = false;
    uint32_t parent = 0;
    uint32_t great = 0;
    uint32_t temp = 0;
    extern int hmoves;
    extern int hcomps;

    //build_heap

    for (uint32_t x = last / 2; x > first - 1; x--) {
        //fix_heap

        found = false;
        parent = x;

        //max_child

        left = 2 * parent;
        right = left + 1;
        hcomps++;
        if (right <= last && A[right - 1] > A[left - 1]) {
            great = right;
        } else {
            great = left;
        }

        //end max_child

        while (parent <= (last / 2) && found == false) {
            hcomps++;
            if (A[parent - 1] < A[great - 1]) {
                temp = A[parent - 1];
                A[parent - 1] = A[great - 1];
                A[great - 1] = temp;
                hmoves += 3;
                parent = great;

                //max_child

                left = 2 * parent;
                right = left + 1;
                hcomps++;
                if (right <= last && A[right - 1] > A[left - 1]) {
                    great = right;
                } else {
                    great = left;
                }

                //end max_child

            } else {
                found = true;
            }
        }

        //end fix_heap
    }
    //end build_heap

    for (uint32_t z = last; z > first; z--) {
        temp = A[first - 1];
        A[first - 1] = A[z - 1];
        A[z - 1] = temp;
        hmoves += 3;

        //fix_heap

        found = false;
        parent = first;

        //max_child

        left = 2 * parent;
        right = left + 1;
        hcomps++;
        if (right <= (z - 1) && A[right - 1] > A[left - 1]) {
            great = right;
        } else {
            great = left;
        }

        //end max_child

        while (parent <= ((z - 1) / 2) && found == false) {
            hcomps++;
            if (A[parent - 1] < A[great - 1]) {
                temp = A[parent - 1];
                A[parent - 1] = A[great - 1];
                A[great - 1] = temp;
                parent = great;
                hmoves += 3;

                //max_child

                left = 2 * parent;
                right = left + 1;
                hcomps++;
                if (right <= (z - 1) && A[right - 1] > A[left - 1]) {
                    great = right;
                } else {
                    great = left;
                }

                //end max_child

            } else {
                found = true;
            }
        }

        //end fix_heap
    }
}
