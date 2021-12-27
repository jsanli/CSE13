#include "set.h"

#include <stdio.h>
#include <stdlib.h>

typedef uint32_t Set;

Set set_empty() {
    return 0;
}

bool set_member(Set s, uint8_t x) {
    uint8_t mask = 1 << x;
    uint8_t result = s & mask;
    return result >> x;
}

Set set_insert(Set s, uint8_t x) {
    return s | (1 << x);
}

Set set_remove(Set s, uint8_t x) {
    return s & ~(1 << x);
}

Set set_intersect(Set s, Set t) {
    return s & t;
}

Set set_union(Set s, Set t) {
    return s | t;
}

Set set_complement(Set s) {
    return ~s;
}

Set set_difference(Set s, Set t) {
    return s & ~t;
}
