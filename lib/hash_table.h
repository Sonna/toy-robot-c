// == Sourced:
// - [jamesroutley/write\-a\-hash\-table: ✏️ Learn how to write a hash table in C]
//   (https://github.com/jamesroutley/write-a-hash-table)
//
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

typedef struct {
    char* key;
    char* value;
} ht_item;

typedef struct {
    int size;
    int count;
    ht_item** items;
} ht_hash_table;

ht_hash_table* ht_new();
void ht_del_hash_table(ht_hash_table* ht);

#endif
