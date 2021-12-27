#include "trie.h"

#include "code.h"

#include <stdio.h>
#include <stdlib.h>

TrieNode *trie_node_create(uint16_t code) {
    TrieNode *n = (TrieNode *) calloc(1, sizeof(TrieNode));
    if (n == NULL) {
        return NULL;
    }
    n->code = code;
    for (int x = 0; x < ALPHABET; x++) {
        n->children[x] = NULL;
    }
    return n;
}

TrieNode *trie_create(void) {
    return trie_node_create(EMPTY_CODE);
}

void trie_node_delete(TrieNode *n) {
    free(n);
    n = NULL;
}

void trie_delete(TrieNode *n) {
    if (n != NULL) {
        for (int x = 0; x < ALPHABET; x++) {
            if (n->children[x] != NULL) {
                trie_delete(n->children[x]);
                n->children[x] = NULL;
            }
        }
    }
    trie_node_delete(n);
}

void trie_reset(TrieNode *root) {
    if (root != NULL) {
        for (int x = 0; x < ALPHABET; x += 1) {
            if (root->children[x] != NULL) {
                trie_delete(root->children[x]);
                root->children[x] = NULL;
            }
        }
    }
}

TrieNode *trie_step(TrieNode *n, uint8_t sym) {
    if (n->children[sym] != NULL) {
        return (n->children[sym]);
    }
    return NULL;
    /*for(int i = 0; i< ALPHABET; i++){
		if(n->children[i] != NULL){
			if(n->children[i]->code == sym){
				return n-> children[i];
			}
		}
	}
	return NULL;*/
}
