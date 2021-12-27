#include "word.h"

#include "code.h"

#include <stdio.h>
#include <stdlib.h>

Word *word_create(uint8_t *syms, uint32_t len) {
    Word *w = (Word *) calloc(1, sizeof(Word));
    w->len = len;
    w->syms = (uint8_t *) calloc(len, sizeof(uint8_t));
    for (uint32_t i = 0; i < w->len; i++) {
        w->syms[i] = syms[i];
    }
    return w;
}

Word *word_append_sym(Word *w, uint8_t sym) {
    w->syms = (uint8_t *) realloc(w->syms, w->len + 1);
    w->syms[w->len] = sym;
    w->len += 1;
    return w;
}

void word_delete(Word *w) {
    free(w->syms);
    w->syms = NULL;
    free(w);
    w = NULL;
}

WordTable *wt_create(void) {
    WordTable *wt = (WordTable *) calloc(MAX_CODE, sizeof(Word *));
    wt[EMPTY_CODE] = (Word *) calloc(1, sizeof(Word));
    return wt;
}

void wt_delete(WordTable *wt) {
    for (int i = EMPTY_CODE; i < MAX_CODE; i += 1) {
        if (wt[i] != NULL) {
            word_delete(wt[i]);
        }
        wt[i] = NULL;
    }
    free(wt);
}

void wt_reset(WordTable *wt) {
    for (int i = START_CODE; i < MAX_CODE; i += 1) {
        word_delete(wt[i]);
        wt[i] = NULL;
    }
}
