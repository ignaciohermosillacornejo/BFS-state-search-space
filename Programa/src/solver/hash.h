#pragma once
#include "state.h"
#include <stdbool.h>

typedef struct hashtable Hashtable;
typedef struct hashnode Hashnode;

struct hashtable
{
    int count;
    unsigned long long size;
    Hashnode *array;
    unsigned long long *ships_random_matrix;
    unsigned long long *asteroids_random_matrix;
};

struct hashnode
{
    unsigned long long key;
    State *value;
};

bool hashtable_insert(Hashtable * hash, State *value);
Hashtable *hashtable_init(int total_ships, int total_asteroids);
unsigned long long hashtable_get_key(Hashtable *hashtable, State *value);
void hashtable_destroy(Hashtable *hashtable);