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
    TrieNode *root = trie_create();
    TrieNode *curr_node = root;
    TrieNode *prev_node = NULL;
    TrieNode *next_node = NULL;
    uint8_t curr_sym = 0;
    uint8_t prev_sym = 0;
    uint16_t next_code = START_CODE;
    bool v = false;
    struct stat buffer;
    struct stat outbuffer;
    FileHeader header = { 0, 0 }; /*malloc(sizeof(FileHeader));*/
    int infile, outfile;
    infile = STDIN_FILENO;
    outfile = STDOUT_FILENO;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'v': v = true; break;
        case 'i': infile = open(optarg, O_RDONLY); break;
        case 'o': outfile = open(optarg, O_WRONLY); break;
        }
    }
    fstat(infile, &buffer);
    header.magic = MAGIC;
    header.protection = buffer.st_mode;
    write_header(infile, &header);
    while (read_sym(infile, &curr_sym)) {
        next_node = trie_step(curr_node, curr_sym);
        if (next_node != NULL) {
            prev_node = curr_node;
            curr_node = next_node;
        } else {
            write_pair(outfile, curr_node->code, curr_sym, bit_length(next_code));
            curr_node->children[curr_sym] = trie_node_create(next_code);
            curr_node = root;
            next_code += 1;
        }
        if (next_code == MAX_CODE) {
            trie_reset(root);
            curr_node = root;
            next_code = START_CODE;
        }
        prev_sym = curr_sym;
    }
    if (curr_node != root) {
        write_pair(outfile, prev_node->code, prev_sym, bit_length(next_code));
        next_code = (next_code + 1) % MAX_CODE;
    }
    write_pair(outfile, STOP_CODE, 0, bit_length(next_code));
    flush_pairs(outfile);
    if (v) {
        fstat(outfile, &outbuffer);
        printf("%s %ld\n", "Compressed file size:", outbuffer.st_size);
        printf("%s %ld\n", "Uncompressed file size:", buffer.st_size);
        printf("%s %.2f\n", "Space saving:", (1.0 - buffer.st_size / outbuffer.st_size) * 100);
    }
    trie_delete(root);
    close(infile);
    close(outfile);
    return 0;
}
