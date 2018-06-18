#pragma once

typedef struct arraylist_list ArrayList;

struct arraylist_list
{
  int count;
  int size;
  int* array;
};

ArrayList* arraylist_init();
void arraylist_append(ArrayList* list, int element);
void arraylist_insert(ArrayList* list, int element, int position);
int arraylist_delete(ArrayList* list, int position);
int arraylist_get(ArrayList* list, int position);
void arraylist_destroy(ArrayList* list);
