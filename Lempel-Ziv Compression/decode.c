#include "code.h"
#include "io.h"
#include "trie.h"
#include "word.h"

#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define OPTIONS "vi:o:"

int bit_length(uint8_t next_code) {
    double n = (double) (next_code);
    return ((trunc((log(n) / log(2.0))) - (log(n) / log(2.0))) == 0.0)
               ? (int) (ceil((log(n) / log(2.0))) + 1.0)
               : (int) (ceil((log(n) / log(2.0))));
}

int main(int argc, char **argv) {
    int opt = 0;
    WordTable *table = wt_create();
    uint8_t curr_sym = 0;
    uint16_t curr_code = 0;
    uint16_t next_code = START_CODE;
    bool v = false;
    int infile, outfile;
    FileHeader *header = malloc(sizeof(FileHeader));
    infile = STDIN_FILENO;
    outfile = STDOUT_FILENO;
    while ((opt = getopt(argc, argv, OPTIONS)) != EOF) {
        switch (opt) {
        case 'v': v = true; break;
        case 'i': infile = open(optarg, O_RDONLY); break;
        case 'o': outfile = open(optarg, O_WRONLY); break;
        }
    }
    read_header(infile, header);
    if (header->magic != MAGIC) {
        fprintf(stderr, "%s\n", "Magic Number");
    } else {
        fchmod(outfile, header->protection);
        while (read_pair(infile, &curr_code, &curr_sym, bit_length(next_code))) {
            printf("%s\n", "yo");
            table[next_code] = word_append_sym(table[curr_code], curr_sym);
            write_word(outfile, table[next_code]);
            next_code++;
            if (next_code == MAX_CODE) {
                wt_reset(table);
                next_code = START_CODE;
            }
        }
    }

    flush_words(outfile);
    if (v) {
        struct stat inbuffer;
        struct stat outbuffer;
        fstat(infile, &inbuffer);
        fstat(outfile, &outbuffer);
        printf("%s %ld\n", "Compressed file size:", inbuffer.st_size);
        printf("%s %ld\n", "Uncompressed file size:", outbuffer.st_size);
        printf("%s %.2f\n", "Space saving:", (1.0 - inbuffer.st_size / outbuffer.st_size) * 100);
    }
    free(header);
    header = NULL;
    wt_delete(table);
    close(infile);
    close(outfile);

    return 0;
}
