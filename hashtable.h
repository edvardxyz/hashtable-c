#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

int table_size 100;

typedef struct entry_t {
    char *key;
    char *value;
    struct entry_t *next;
} entry_t;

typedef struct ht_t {
    entry_t **entries;
} ht_t;

ht_t *ht_create(void);
void ht_set(ht_t *hashtable, const char *key, const char *value);
unsigned int hash(const char *key);
entry_t *ht_pair(const char *key, const char *value);
char *ht_get(ht_t *hashtable, const char *key);
void ht_dump(ht_t *hashtable);
