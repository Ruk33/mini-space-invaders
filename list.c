#include <stdlib.h>
#include "list.h"

struct List {
        void *value;
        struct List *next;
};

struct List *list_create()
{
        return calloc(1, sizeof(struct List));
}

void list_add
(struct List *list, void *element)
{
        struct List *last = list;
        struct List *new_node = NULL;

        if (!last->value) {
                last->value = element;
                return;
        }

        new_node = list_create();
        new_node->value = element;

        while (last->next) last = last->next;
        last->next = new_node;
}

void list_remove
(struct List *list, void *element)
{
        struct List **node = &list;
        struct List *tmp = NULL;

        while (*node) {
                if ((*node)->value == element) break;
                node = &(*node)->next;
        }

        tmp = *node;
        if (!tmp) return;

        *node = tmp->next;
        free(tmp);
}

struct List *list_next
(struct List *list)
{
        return list->next;
}

void *list_value
(struct List *list)
{
        return list->value;
}
