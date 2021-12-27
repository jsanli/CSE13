#include "bubble.h"
#include "heap.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stack.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "absqhr:n:p:"

enum Sorting { bubble = 0, shell = 1, quick = 2, heap = 3 } st;

int bmoves = 0;
int bcomps = 0;
int smoves = 0;
int scomps = 0;
int qmoves = 0;
int qcomps = 0;
int hmoves = 0;
int hcomps = 0;

int main(int argc, char **argv) {
    Set sorts = set_empty();
    uint seed = 7092016;
    uint size = 100;
    uint amount = size;
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            sorts = set_insert(sorts, bubble);
            sorts = set_insert(sorts, shell);
            sorts = set_insert(sorts, quick);
            sorts = set_insert(sorts, heap);
            break;
        case 'b': sorts = set_insert(sorts, bubble); break;
        case 's': sorts = set_insert(sorts, shell); break;
        case 'q': sorts = set_insert(sorts, quick); break;
        case 'h': sorts = set_insert(sorts, heap); break;
        case 'r': seed = atoi(optarg); break;
        case 'n': size = atoi(optarg); break;
        case 'p': amount = atoi(optarg); break;
        }
    }
    uint32_t *B = (uint32_t *) (calloc(size, sizeof(uint32_t)));
    uint32_t *S = (uint32_t *) (calloc(size, sizeof(uint32_t)));
    uint32_t *Q = (uint32_t *) (calloc(size, sizeof(uint32_t)));
    uint32_t *H = (uint32_t *) (calloc(size, sizeof(uint32_t)));
    srandom(seed);
    uint32_t f = 0;
    for (uint e = 0; e < size; e++) {
        f = random() & 1073741823;
        B[e] = f;
        S[e] = f;
        Q[e] = f;
        H[e] = f;
    }
    uint counter = 0;
    for (int i = bubble; i <= heap; i += 1) {
        if (set_member(sorts, i)) {
            switch (i) {
            case 0:
                printf("%s\n", "Bubble Sort");
                bubble_sort(B, size);
                printf(
                    "%u %s %d %s %d %s\n", size, "elements,", bmoves, "moves,", bcomps, "compares");
                counter = 0;
                for (uint q = 0; q < size; q++) {
                    if (counter < amount) {
                        printf("%13" PRIu32, B[q]);
                    }
                    counter++;
                    if ((counter % 5 == 0 && counter < amount) || q == size - 1) {
                        printf("\n");
                    }
                }
                break;
            case 1:
                printf("%s\n", "Shell Sort");
                shell_sort(S, size);
                printf(
                    "%u %s %d %s %d %s\n", size, "elements,", smoves, "moves,", scomps, "compares");
                counter = 0;
                for (uint q = 0; q < size; q++) {
                    if (counter < amount) {
                        printf("%13" PRIu32, S[q]);
                    }
                    counter++;
                    if ((counter % 5 == 0 && counter < amount) || q == size - 1) {
                        printf("\n");
                    }
                }
                break;
            case 2:
                printf("%s\n", "Quick Sort");
                quick_sort(Q, size);
                printf(
                    "%u %s %d %s %d %s\n", size, "elements,", qmoves, "moves,", qcomps, "compares");
                counter = 0;
                for (uint q = 0; q < size; q++) {
                    if (counter < amount) {
                        printf("%13" PRIu32, Q[q]);
                    }
                    counter++;
                    if ((counter % 5 == 0 && counter < amount) || q == size - 1) {
                        printf("\n");
                    }
                }
                break;
            case 3:
                printf("%s\n", "Heap Sort");
                heap_sort(H, size);
                printf(
                    "%u %s %d %s %d %s\n", size, "elements,", hmoves, "moves,", hcomps, "compares");
                counter = 0;
                for (uint q = 0; q < size; q++) {
                    if (counter < amount) {
                        printf("%13" PRIu32, H[q]);
                    }
                    counter++;
                    if ((counter % 5 == 0 && counter < amount) || q == size - 1) {
                        printf("\n");
                    }
                }
                break;
            }
        }
    }
    free(H);
    free(Q);
    free(S);
    free(B);
}
