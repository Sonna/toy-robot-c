// == Sourced:
// - [Hash from two arrays \- Rosetta Code]
//   (https://rosettacode.org/wiki/Hash_from_two_arrays#C)
//
#include <stdio.h>
#include <stdlib.h>

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define KeyType const char *
#define ValType int

#define HASH_SIZE 4096

// hash function useful when KeyType is char * (string)
unsigned strhashkey(const char * key, int max);

typedef struct sHme {
  KeyType key;
  ValType value;
  struct sHme *link;
} *MapEntry;

typedef struct he {
  MapEntry  first, last;
} HashElement;

HashElement hash[HASH_SIZE];

typedef void (*KeyCopyF)(KeyType *kdest, KeyType ksrc);
typedef void (*ValCopyF)(ValType *vdest, ValType vsrc);
typedef unsigned (*KeyHashF)(KeyType key, int upperBound);
typedef int (*KeyCmprF)(KeyType key1, KeyType key2);

void HashAddH(KeyType key, ValType value,
              KeyCopyF copyKey, ValCopyF copyVal,
              KeyHashF hashKey, KeyCmprF keySame);
int HashGetH(ValType *val, KeyType key, KeyHashF hashKey, KeyCmprF keySame);
void copyStr(const char**dest, const char *src);
void copyInt(int *dest, int src);
int strCompare(const char *key1, const char *key2);
void HashAdd(KeyType key, ValType value);
int HashGet(ValType *val, KeyType key);

#endif
