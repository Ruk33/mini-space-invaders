#ifndef LIST_H
#define LIST_H

struct List;

struct List *list_create();

void list_add
(struct List *list, void *element);

void list_remove
(struct List *list, void *element);

struct List *list_next
(struct List *list);

void *list_value
(struct List *list);

#endif
