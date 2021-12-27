#include "io.h"

#include "code.h"
#include "endian.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static uint8_t bit_buf[BLOCK] = { 0 };
static uint8_t sym_buf[BLOCK] = { 0 };

static int bit_index = 0;
static int sym_index = 0;
static int end = -1;

uint8_t bytes(uint8_t bits) {
    if (bits % 8 == 0) {
        bits /= 8;
    } else {
        bits /= 8;
        bits++;
    }
    return bits;
}

int read_bytes(int infile, uint8_t *buf, int to_read) {
    int total = 0;
    int bytes = 0;
    while ((bytes = read(infile, buf, to_read)) > 0) {
        total += bytes;
        to_read -= bytes;
        buf += bytes;
    }
    return total;
}

int write_bytes(int outfile, uint8_t *buf, int to_write) {
    int total = 0;
    int bytes = 0;
    while ((bytes = write(outfile, buf, to_write)) > 0) {
        total += bytes;
        to_write -= bytes;
        buf += bytes;
    }
    return total;
}

void read_header(int infile, FileHeader *header) {
    read_bytes(infile, (uint8_t *) header, sizeof(FileHeader));
    if (big_endian()) {
        swap32(header->magic);
        swap16(header->protection);
    }
}

void write_header(int outfile, FileHeader *header) {
    if (big_endian()) {
        swap32(header->magic);
        swap16(header->protection);
    }
    write_bytes(outfile, (uint8_t *) header, sizeof(FileHeader));
}

bool read_sym(int infile, uint8_t *sym) {
    int bytes_read = 0;
    if (sym_index == 0) {
        bytes_read = read_bytes(infile, sym_buf, BLOCK);
        if (bytes_read < BLOCK) {
            end = bytes_read + 1;
        }
    }

    *sym = sym_buf[sym_index];
    sym_index++;

    if (sym_index == BLOCK) {
        sym_index = 0;
    }
    return sym_index == end ? false : true;
}

void write_pair(int outfile, uint16_t code, uint8_t sym, int bitlen) {
    if (big_endian()) {
        code = swap16(code);
    }
    for (uint16_t i = 0; i < bitlen; i++) {
        if (bit_index == BLOCK * 8) {
            write_bytes(outfile, bit_buf, BLOCK);
            bit_index = 0;
        }
        if ((code & (1 << i % 16)) >> i % 16) {
            bit_buf[bit_index / 8] = bit_buf[(bit_index / 8)] | (1 << bit_index % 8);
        } else {
            bit_buf[bit_index / 8] = bit_buf[(bit_index / 8)] & ~(1 << bit_index % 8);
        }
        bit_index++;
    }

    for (uint16_t i = 0; i < 8; i++) {
        if (bit_index == BLOCK * 8) {
            write_bytes(outfile, bit_buf, BLOCK);
            bit_index = 0;
        }
        if ((sym & (1 << i % 8)) >> i % 8) {
            bit_buf[bit_index / 8] = bit_buf[(bit_index) / 8] | (1 << bit_index % 8);
        } else {
            bit_buf[bit_index / 8] = bit_buf[(bit_index) / 8] & ~(1 << bit_index % 8);
        }
        bit_index++;
    }
}

bool read_pair(int infile, uint16_t *code, uint8_t *sym, int bitlen) {
    uint16_t tempcode = 0;
    uint16_t tempsym = 0;
    for (uint16_t i = 0; i < bitlen; i++) {
        if (bit_index == 0) {
            read_bytes(infile, bit_buf, BLOCK);
        }
        if ((tempcode & (1 << i % 16)) >> i % 16) {
            tempcode = tempcode | (bit_buf[bit_index / 8] << i % 8);
        } else {
            tempcode = tempcode & ~(bit_buf[bit_index / 8] << i % 8);
        }
        if (bit_index == BLOCK * 8) {
            bit_index = 0;
        }
        bit_index++;
    }
    *code = tempcode;
    for (uint16_t i = 0; i < 8; i++) {
        if (bit_index == 0) {
            read_bytes(infile, bit_buf, BLOCK);
        }
        if ((tempsym & (1 << i % 8)) >> i % 8) {
            tempsym = tempsym | (bit_buf[bit_index / 8] << i % 8);
        } else {
            tempsym = tempsym & ~(bit_buf[bit_index / 8] << i % 8);
        }
        if (bit_index == BLOCK * 8) {
            bit_index = 0;
        }
        bit_index++;
    }
    *sym = tempsym;
    if (tempcode == STOP_CODE) {
        return false;
    } else {
        return true;
    }
}

void write_word(int outfile, Word *w) {
    for (uint32_t i = 0; i < w->len; i += 1) {
        sym_buf[sym_index] = w->syms[i];
        if (sym_index == BLOCK) {
            write_bytes(outfile, sym_buf, BLOCK);
            sym_index = 0;
        }
    }
}

void flush_pairs(int outfile) {
    write_bytes(outfile, bit_buf, bytes(bit_index));
}

void flush_words(int outfile) {
    write_bytes(outfile, sym_buf, sym_index);
}
