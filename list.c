#include "list.h"
#include <stdio.h>

void init(list *l) {
    l->first = NULL;
    l->nidx = -1;
    l->number = 0;
}

static element *create(void *value, data_type_t type) {
    element *elm = malloc(sizeof(element));
    if (!elm) { perror("malloc"); exit(1); }
    elm->value = value;
    elm->type = type;
    elm->next = NULL;
    return elm;
}

void insert(list *l, void *value, data_type_t type) {
    element *elm = create(value, type);
    l->nidx++; // increment the index for each new element (should also work in reverse order)
    elm->idx = l->nidx; // assign the element index from the list's current index
    l->number++;
    element **p = &l->first;
    while (*p) p = &(*p)->next;
    *p = elm;
}

void erase(list *l, int index) {
    element **p = &l->first;
    while (*p) {
        if ((*p)->idx == index) {
            element *victim = *p;
            *p = victim->next;
            free(victim);
            l->nidx = -1;
            l->number--;
            for (element *elm = l->first; elm != NULL; elm = elm->next) {
                l->nidx++;
                elm->idx = l->nidx;
            }
            return;
        }
        p = &(*p)->next;
    }
    fprintf(stderr, "erase: index %d not found\n", index);
}

void print_addresses(list *l) {
    element *elm;
    printf("%d\n", l->nidx);
    for(elm = l->first; elm != NULL; elm = elm->next)
        printf("%p\n", elm->value);
}

void print_values(list *l) {
    element *elm;
    printf("%d\n", l->nidx);
    for(elm = l->first; elm != NULL; elm = elm->next)
        switch (elm->type) {
            case T_INT:    printf("%d\n",   *(int *)elm->value);    break;
            case T_STR:    printf("%s\n",   (char *)elm->value);    break;
            case T_DOUBLE: printf("%f\n",   *(double *)elm->value); break;
            default:
                fprintf(stderr, "print_values: unknown type %d\n", elm->type);
                break;
        }

}

element *element_by_index(list *l, int index) {
    if (l != NULL) {
        for (element *elm = l->first; elm != NULL; elm = elm->next) {
            if (elm->idx == index) {
                return elm;
            }
        }
    }
    return NULL;
}

void clear(list *l) {
    element *elm;
    while((elm = l->first) != NULL) {
        l->first = l->first->next;
        free(elm);
    }
    l->nidx = -1;
    l->number = 0;
}
