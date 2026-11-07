// The list does not own the values: clear()/erase() free only
// the list elements themselves. The lifetime of the objects
// pointed to by value is the caller's responsibility.
#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>

typedef enum { T_INT, T_STR, T_DOUBLE } data_type_t;

typedef struct _element element;
struct _element {
    int idx;
    void *value;
    data_type_t type;
    element *next;
};

typedef struct _list list;
struct _list {
    element *first;
    int nidx;
    int number;
};

void init(list *l);
void insert(list *l, void *value, data_type_t type);
void erase(list *l, int index);
void print_addresses(list *l);
void print_values(list *l);
// O(N) linear search by index.
// Use an array/vector if you need frequent index-based access.
element *element_by_index(list *l, int index);
void clear(list *l);

#endif
