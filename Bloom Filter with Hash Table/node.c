#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *stringdup(char *s) {
    char *p;

    p = (char *) malloc(strlen(s) + 1);
    if (p != NULL) {
        strcpy(p, s);
    }
    return p;
}

Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (oldspeak != NULL) {
        n->oldspeak = stringdup(oldspeak);
    }
    if (newspeak != NULL) {
        n->newspeak = stringdup(newspeak);
    }
    n->next = NULL;
    n->prev = NULL;
    return n;
}

void node_delete(Node **n) {
    if ((*n)->oldspeak != NULL) {

        free((*n)->oldspeak);
        (*n)->oldspeak = NULL;
    }
    if ((*n)->newspeak != NULL) {
        free((*n)->newspeak);
        (*n)->newspeak = NULL;
    }
    free(*n);
    *n = NULL;
}

void node_print(Node *n) {
    if (n->newspeak == NULL) {
        printf("%s\n", n->oldspeak);
    } else {
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
    }
}
