#pragma once
#include "hash.h"
typedef struct queue Queue;
typedef struct node Node;

/* structure of the node that we use in our queue */
struct node
{
  /* pointer to our next node */
  struct node *next;
  /* value of the node */
  State *value;
};

/* Structure of the queue */
struct queue
{
  Node *first;
  int count;
};



/* Crea an empty queue and return the pointer */
Queue *queue_init();

/* Push an element into the queue */
void queue_push(Queue *queue, State *element);

/* Pop an element from the queue and return it */ 
State *queue_pop(Queue *queue);

/* Free all the memory associated of the queue */
void queue_destroy(Queue *queue);
