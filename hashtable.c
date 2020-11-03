#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "hashtable.h"

#define HASHTABLE_SIZE 64

struct HashtableEntry {
        size_t key_length;
        char *key;
        void *value;
};

struct Hashtable {
        struct List *values[HASHTABLE_SIZE];
};

struct Hashtable *hashtable_create()
{
        return calloc(1, sizeof(struct Hashtable));
}

int hashtable_hash
(struct Hashtable *ht, char *str)
{
        unsigned long hash = 5381;
        int c;

        while (c = *str++) {
                hash = ((hash << 5) + hash) + c;
        }

        return hash;
}

struct List *hashtable_entry
(struct Hashtable *ht, char *key)
{
        int index = hashtable_hash(ht, key) % HASHTABLE_SIZE;
        if (!ht->values[index]) ht->values[index] = list_create();
        return ht->values[index];
}

void *hashtable_get
(struct Hashtable *ht, char *key)
{
        struct List *entries = hashtable_entry(ht, key);
        struct HashtableEntry *entry = NULL;
        void *value = NULL;

        do {
                entry = list_value(entries);
                if (memcmp(entry->key, key, entry->key_length) == 0) {
                        value = entry->value;
                        break;
                }
                entries = list_next(entries);
        } while (entries);

        return value;
}

void hashtable_add
(struct Hashtable *ht, char *key, void *value)
{
        struct List *entries = hashtable_entry(ht, key);
        struct HashtableEntry *new_entry = calloc(1, sizeof(struct HashtableEntry));

        new_entry->key_length = strlen(key) + 1;
        new_entry->key = calloc(new_entry->key_length, sizeof(char));
        new_entry->value = value;

        memcpy(new_entry->key, key, new_entry->key_length);

        list_add(entries, new_entry);
}

void hashtable_remove
(struct Hashtable *ht, void *key);
