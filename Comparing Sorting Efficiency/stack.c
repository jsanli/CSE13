#include "stack.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Stack {
    uint32_t top;
    uint32_t capacity;
    int64_t *items;
};

Stack *stack_create(void) {
    Stack *s = (Stack *) calloc(1, sizeof(Stack));
    s->top = 0;
    s->capacity = MIN_CAPACITY;
    s->items = (int64_t *) calloc(s->capacity, sizeof(int64_t));
    return s;
}

void stack_delete(Stack **s) {
    free((*s)->items);
    (*s)->items = NULL;
    free(*s);
    *s = NULL;
    return;
}

bool stack_empty(Stack *s) {
    return s->top == 0;
}

bool stack_push(Stack *s, int64_t x) {
    if (s->top == s->capacity) {
        s->capacity = 2 * (s->capacity);
        s->items = (int64_t *) realloc(s->items, s->capacity * sizeof(int64_t));
        if (s->items == NULL) {
            return false;
        }
    }

    s->items[s->top] = x;
    s->top += 1;
    return true;
}

bool stack_pop(Stack *s, int64_t *x) {
    if (s->top == 0) {
        return false;
    }
    s->top -= 1;
    *x = s->items[s->top];
    return true;
}

void stack_print(Stack *s) {
    for (uint32_t y = 0; y < s->capacity; y++) {
        printf("%ld", s->items[y]);
    }
}
