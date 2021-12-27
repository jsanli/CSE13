#include "hash.h"

#include "speck.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    bool mtf;
    LinkedList **lists;
};

HashTable *ht_create(uint32_t size, bool mtf) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    if (ht) {
        ht->salt[0] = 0x85ae998311115ae3;
        ht->salt[1] = 0xb6fac2ae33a40089;
        ht->size = size;
        ht->mtf = mtf;
        ht->lists = (LinkedList **) calloc(size, sizeof(LinkedList *));
        if (!ht->lists) {
            free(ht);
            ht = NULL;
        }
    }
    return ht;
}

void ht_delete(HashTable **ht) {
    for (uint32_t s = 0; s < (*ht)->size; s++) {
        if ((*ht)->lists[s] != NULL) {
            ll_delete(&(*ht)->lists[s]);
        }
    }
    free((*ht)->lists);
    free(*ht);
    *ht = NULL;
}

uint32_t ht_size(HashTable *ht) {
    return (ht->size);
}

Node *ht_lookup(HashTable *ht, char *oldspeak) {
    uint32_t index = (hash(ht->salt, oldspeak)) % ht->size;
    if ((ht->lists[index] != NULL) && (ll_lookup((ht->lists[index]), oldspeak) != NULL)) {
        return ll_lookup(ht->lists[index], oldspeak);
    } else {
        return NULL;
    }
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    uint32_t index = (hash(ht->salt, oldspeak)) % ht->size;
    if (ht->lists[index] == NULL) {
        ht->lists[index] = ll_create(ht->mtf);
    }
    ll_insert((ht->lists[index]), oldspeak, newspeak);
}

void ht_print(HashTable *ht) {
    for (uint32_t s = 0; s < ht->size; s++) {
        if (ht->lists[s] != NULL && ll_length(ht->lists[s]) > 0) {
            ll_print((ht->lists[s]));
        }
    }
}
