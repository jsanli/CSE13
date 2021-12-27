#include "bm.h"
#include "hamming.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "i:o:"

int main(int argc, char **argv) {
    int opt = 0;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i': infile = fopen(optarg, "r"); break;
        case 'o': outfile = fopen(optarg, "w"); break;
        }
    }
    ham_init();
    int b;
    uint8_t lcode;
    uint8_t bcode;
    while ((b = fgetc(infile)) != EOF) {
        ham_encode(b % 16, &lcode);
        fputc(lcode, outfile);
        ham_encode((b >> 4) % 16, &bcode);
        fputc(bcode, outfile);
    }
    ham_destroy();
    fclose(infile);
    fclose(outfile);
    return 0;
}
