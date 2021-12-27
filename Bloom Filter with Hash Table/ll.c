#include "ll.h"

#include "node.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct LinkedList {
    uint32_t length;
    Node *head;
    Node *tail;
    bool mtf;
};

LinkedList *ll_create(bool mtf) {
    LinkedList *ll = (LinkedList *) malloc(sizeof(LinkedList));
    ll->length = 0;
    ll->mtf = mtf;
    ll->head = node_create(NULL, NULL);
    ll->tail = node_create(NULL, NULL);
    ll->head->next = ll->tail;
    ll->tail->prev = ll->head;
    return ll;
}

void ll_delete(LinkedList **ll) {
    while ((*ll)->head != NULL) {
        Node *temp = (*ll)->head->next;
        node_delete(&(*ll)->head);
        (*ll)->head = temp;
    }
    free(*ll);
    *ll = NULL;
}

uint32_t ll_length(LinkedList *ll) {
    return ll->length;
}

void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
    if (ll_lookup(ll, oldspeak) == NULL) {
        Node *x = node_create(oldspeak, newspeak);
        x->next = ll->head->next;
        x->prev = ll->head;
        ll->head->next->prev = x;
        ll->head->next = x;
        ll->length += 1;
    }
    return;
}

Node *ll_lookup(LinkedList *ll, char *oldspeak) {
    for (Node *n = ll->head->next; n != ll->tail; n = n->next) {
        if (strcmp(n->oldspeak, oldspeak) == 0) {
            if (ll->mtf) {
                n->prev->next = n->next;
                n->next->prev = n->prev;
                n->next = ll->head->next;
                n->prev = ll->head;
                ll->head->next->prev = n;
                ll->head->next = n;
            }
            return n;
        }
    }
    return NULL;
}

void ll_print(LinkedList *ll) {
    for (Node *n = ll->head->next; n != ll->tail; n = n->next) {
        node_print(n);
    }
}
