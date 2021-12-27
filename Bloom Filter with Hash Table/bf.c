#include "bf.h"

#include "speck.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct BloomFilter {
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
};

BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    if (bf) {
        bf->primary[0] = 0x02d232593fbe42ff;
        bf->primary[1] = 0x3775cfbf0794f152;

        bf->secondary[0] = 0xc1706bc17ececc04;
        bf->secondary[1] = 0xe9820aa4d2b8261a;

        bf->tertiary[0] = 0xd37b01df0ae8f8d0;
        bf->tertiary[1] = 0x911d454886ca7cf7;

        bf->filter = bv_create(size);

        if (!bf->filter) {
            free(bf);
            bf = NULL;
        }
    }
    return bf;
}

void bf_delete(BloomFilter **bf) {
    bv_delete(&(*bf)->filter);
    free(*bf);
    *bf = NULL;
    return;
}

uint32_t bf_length(BloomFilter *bf) {
    return bv_length(bf->filter);
}

void bf_insert(BloomFilter *bf, char *oldspeak) {
    bv_set_bit(bf->filter, hash(bf->primary, oldspeak) % bv_length(bf->filter));
    bv_set_bit(bf->filter, hash(bf->secondary, oldspeak) % bv_length(bf->filter));
    bv_set_bit(bf->filter, hash(bf->tertiary, oldspeak) % bv_length(bf->filter));
}

bool bf_probe(BloomFilter *bf, char *oldspeak) {
    return (bv_get_bit(bf->filter, hash(bf->primary, oldspeak) % bv_length(bf->filter))
            && bv_get_bit(bf->filter, hash(bf->secondary, oldspeak) % bv_length(bf->filter))
            && bv_get_bit(bf->filter, hash(bf->tertiary, oldspeak) % bv_length(bf->filter)));
}

void bf_print(BloomFilter *bf) {
    bv_print(bf->filter);
}
