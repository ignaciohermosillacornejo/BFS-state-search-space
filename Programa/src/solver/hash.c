#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "hash.h"
#include "random.h"

/* Helper function to calculate the key to a value (state) 
 * slow function, so it is only used when rehashing
 */
unsigned long long hashtable_get_key(Hashtable * hashtable, State *value)
{
    unsigned long long key = 0;
    for (int i = 0; i < value->ships->count; i++)
    {
        if (key)
        {
            key = key ^ hashtable->ships_random_matrix[4 * i + arraylist_get(value->ships, i)];
        }
        else
        {
            key = hashtable->ships_random_matrix[4 * i + arraylist_get(value->ships, i)];
        }
    }
    for (int i = 0; i < value->asteroids->count; i++)
    {
        key = key ^ hashtable->asteroids_random_matrix[2 * i + arraylist_get(value->asteroids, i)];
    }
    return key % hashtable->size;
}

void hashtable_print_state(State * value)
{
    printf("Asteroids: %d\n", value->count_asteroids);
    printf("Ships: ");
    for (int i = 0; i < value->ships->count; i++)
    {
        printf("%d ", arraylist_get(value->ships, i));
    }
    printf("\nAsteroids: ");
    for (int i = 0; i < value->asteroids->count; i++)
    {
        printf("%d ", arraylist_get(value->asteroids, i));
    }
    printf("\n");
}


/* Helper function to compare if two states are equal or not */
bool hashtable_compare(State *state_a, State *state_b)
{
    if (state_a == NULL || state_b == NULL)
    {
        return false;
    }
    if (state_a->count_asteroids != state_b->count_asteroids)
    {
        return false;
    }
    for (int i = 0; i < state_a->ships->count; i++)
    {
        if (arraylist_get(state_a->ships, i) != arraylist_get(state_b->ships, i))
        {
            return false;
        }
    }
    for (int i = 0; i < state_a->asteroids->count; i++)
    {
        if (arraylist_get(state_a->asteroids, i) != arraylist_get(state_b->asteroids, i))
        {
            return false;
        }
    }
    return true;
}

/* Init an array and return its pointer */
Hashtable *hashtable_init(int total_ships, int total_asteroids)
{
    // Allocate memory for our arraylist struct
    Hashtable *hashtable = malloc(sizeof(Hashtable));

    // Start its attributes
    hashtable->size = 1132463;
    hashtable->count = 0;
    hashtable->array = (Hashnode *)malloc(hashtable->size * sizeof(Hashnode));
    hashtable->ships_random_matrix = malloc(sizeof(unsigned long long) * total_ships * 4);
    hashtable->asteroids_random_matrix = malloc(sizeof(unsigned long long) * total_asteroids * 2);

    for (int i = 0; i < total_ships * 4; i++)
    {
        hashtable->ships_random_matrix[i] = get_random_number();
    }
    for (int i = 0; i < total_asteroids * 2; i++)
    {
        hashtable->asteroids_random_matrix[i] = get_random_number();
    } 
    for (int i = 0; i < hashtable->size; i++)
    {
       Hashnode *node = hashtable->array + i;
       node->key = -1;
       node->value = NULL;
    }
    // Return the pointer to our new array
    return hashtable;
}


/* Inserts a new value into the hash table, 
 * returns true if it isn't on the table, false otherwise
 * */
bool hashtable_insert(Hashtable * hashtable, State *value)
{
    unsigned long long key = hashtable_get_key(hashtable, value);
    Hashnode * node = hashtable->array + key;
    if (node->key == -1)
    {
        node->key = key;
        node->value = value;
        return true;
    }
    else
    {
        while(!hashtable_compare(value, node->value))
        {
            if (node->key == -1)
            {

                node->key = key;
                node->value = value;
                return true;
            }
            node++;
        }
        return false;
    }
}

void hashtable_destroy(Hashtable *hashtable)
{
    free(hashtable->array);
    free(hashtable->ships_random_matrix);
    free(hashtable->asteroids_random_matrix);
    free(hashtable);
}