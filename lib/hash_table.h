// == Sourced:
// - [jamesroutley/write\-a\-hash\-table: ✏️ Learn how to write a hash table in C]
//   (https://github.com/jamesroutley/write-a-hash-table)
//
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define HT_PRIME_1 1049
#define HT_PRIME_2 1051

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

void ht_insert(ht_hash_table* ht, const char* key, const char* value);
char* ht_search(ht_hash_table* ht, const char* key);
void ht_delete(ht_hash_table* h, const char* key);

#endif
