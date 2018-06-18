/* Taken directly from AC0 solution and modified slightly */
#include "arraylist.h"
#include <stdlib.h>
//#include <stdio.h>

/* Helper function to double an array */
void duplicate(ArrayList* list)
{
  // New array with double the size
  int* new_array = malloc(sizeof(int) * 2 * list -> size);

  // Move the data from the old array to the new one
  for (int i = 0; i < list -> count; i++)
  {
    new_array[i] = list -> array[i];
  }

  // Free the old array
  free(list -> array);

  // Switch our pointer
  list -> array = new_array;

  // Set our new size
  list -> size *= 2;
}

/* Init an array and return its pointer */
ArrayList* arraylist_init()
{
  // Allocate memory for our arraylist struct
  ArrayList* arrlist = malloc(sizeof(ArrayList));

  // Start its attributes
  arrlist -> size = 4;
  arrlist -> count = 0;
  arrlist -> array = malloc(sizeof(int) * arrlist -> size);

  // Return the pointer to our new array
  return arrlist;
}

/* Inserts an element at the end of the list
 * O(1) time
 */
void arraylist_append(ArrayList* list, int element)
{
  if (list -> count == list -> size)
  // Duplico la memoria si estoy lleno
  {
    duplicate(list);
  }
  // Guardo el elemento
  list -> array[list -> count] = element;
  // Agrego 1 al contador
  list -> count++;
}

/* Insert an element at a given position */
void arraylist_insert(ArrayList* list, int element, int position)
{
  // Array is full, then we increase the array size before
  if (list -> size == list -> count)
  {
    duplicate(list);
  }

  // Elements to the right of the position to insert, are shifted right
  for (int i = list -> count - 1; i >= position; i--)
  {
    list -> array[i + 1] = list -> array[i];
  }

  // Insert our new element
  list -> array[position] = element;

  // Increase our count by one
  list -> count++;
}

/* Eliminates an int from the list and returns it */
int arraylist_delete(ArrayList* list, int position)
{
  // Get the value at the position
  int value = list -> array[position];

  // All elements past "position" are shifted right
  for (int i = position; i < list -> count - 1; i++)
  {
    list -> array[i] = list -> array[i + 1];
  }

  list -> count--;
  return value;
}

/* Return the value at a given position */
int arraylist_get(ArrayList* list, int position)
{
  return list -> array[position];
}

/* Destroys the arraylist and free's associated resources */
void arraylist_destroy(ArrayList* list)
{
  free(list -> array);
  free(list);
}
