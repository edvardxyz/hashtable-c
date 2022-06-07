#include "hashtable.h"

void ht_dump(ht_t *hashtable){

    for (int i = 0; i < TABLE_SIZE; i++) {
        entry_t *entry = hashtable->entries[i];

        if(entry == NULL){
            continue;
        }

        printf("slot[%d]: ", i);

        for(;;){
            printf("%s=%s ", entry->key, entry->value);

            if(entry->next == NULL){
                break;
            }
            entry = entry->next;
        }
        printf("\n");
    }
}

entry_t *ht_pair(const char *key, const char *value) {
    entry_t *entry = malloc(sizeof(entry_t) * 1);
    entry->key = malloc(sizeof(char *) * 1);
    entry->value = malloc(sizeof(char *) * 1);
    entry->next = NULL;

    strcpy(entry->key, key);
    strcpy(entry->value, value);

    return entry;
}

char *ht_get(ht_t *hashtable, const char *key) {

    unsigned int slot = hash(key);

    entry_t *entry = hashtable->entries[slot];

    if (entry == NULL) {
        return NULL;
    }

    while (entry != NULL) {

        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }

    return NULL;
}

void ht_set(ht_t *hashtable, const char *key, const char *value) {

    unsigned int slot = hash(key);

    entry_t *entry = hashtable->entries[slot];

    if (entry == NULL) {
        hashtable->entries[slot] = ht_pair(key, value);
        return;
    }

    entry_t *prev;

    while (entry != NULL) {

        if (strcmp(entry->key, key) == 0) {
            free(entry->value);
            entry->value = malloc(strlen(value) + 1);
            strcpy(entry->value, value);
            return;
        }

        prev = entry;
        entry = entry->next;
    }

    prev->next = ht_pair(key, value);
}

unsigned int hash(const char *key) {
    unsigned long int value = 0;
    unsigned key_len = strlen(key);

    for (int i = 0; i < key_len; i++) {

        value = value * 37 + key[i];
    }

    return value % TABLE_SIZE;
}

ht_t *ht_create(void) {
    ht_t *hashtable = malloc(sizeof(ht_t) * 1);
    hashtable->entries = malloc(sizeof(entry_t *) * TABLE_SIZE);

    for (int i = 0; i < TABLE_SIZE; i++) {
        hashtable->entries[i] = NULL;
    }

    return hashtable;
}
