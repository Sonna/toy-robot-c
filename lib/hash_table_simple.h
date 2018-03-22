// == Sourced:
// - [Associative arrays/Creation/C \- Rosetta Code]
//   (https://rosettacode.org/wiki/Associative_arrays/Creation/C)
//
#include <stdio.h>
#include <stdlib.h>

#ifndef HASH_TABLE_SIMPLE_H
#define HASH_TABLE_SIMPLE_H

typedef struct {
    int size;
    void **keys;
    void **values;
} hash_t;

hash_t *hash_new (int size);
int hash_index (hash_t *h, void *key);
void hash_insert (hash_t *h, void *key, void *value);
void *hash_lookup (hash_t *h, void *key);

#endif
