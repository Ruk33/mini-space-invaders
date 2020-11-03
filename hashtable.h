#ifndef HASHTABLE_H
#define HASHTABLE_H

struct Hashtable;

struct Hashtable *hashtable_create();

void hashtable_add
(struct Hashtable *ht, char *key, void *value);

// void hashtable_remove
// (struct Hashtable *ht, char *key);

void *hashtable_get
(struct Hashtable *ht, char *key);

#endif
