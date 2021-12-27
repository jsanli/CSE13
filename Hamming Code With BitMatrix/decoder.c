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
    ham_rc low;
    ham_rc high;
    uint8_t lcode = 0;
    uint8_t bcode = 0;
    uint8_t ldata = 0;
    uint8_t bdata = 0;
    //uint8_t fdata = 0;
    double ok = 0.0;
    double fail = 0.0;
    double okfail = 0.0;
    int counter = 1;
    while ((b = fgetc(infile)) != EOF) {
        if (counter % 2 != 0) {
            lcode = b;
        } else {
            bcode = b;
            low = ham_decode(lcode, &ldata);
            high = ham_decode(bcode, &bdata);
            //printf("%u %u\n", ldata, bdata);
            //((ldata << 4) | (bdata & 0xF));
            fputc(((ldata << 4) | (bdata & 0xF)), outfile);
            if (low == HAM_OK) {
                ok++;
            } else if (low == HAM_ERR) {
                fail++;
            } else {
                okfail++;
            }
            if (high == HAM_OK) {
                ok++;
            } else if (high == HAM_ERR) {
                fail++;
            } else {
                okfail++;
            }
        }
        counter++;
    }
    counter--;
    ham_destroy();
    fprintf(outfile, "%s %d\n", "Total bytes processed:", counter);
    fprintf(outfile, "%s %.0f\n", "Uncorrected errors:", fail);
    fprintf(outfile, "%s %.0f\n", "Corrected Errors:", okfail);
    fprintf(outfile, "%s %f\n", "Error Rate:", fail / counter);
    fclose(infile);
    fclose(outfile);
    return 0;
}
