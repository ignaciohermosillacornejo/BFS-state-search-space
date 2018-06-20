#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
/* Queue class created based on the solution to "actividad 01" from this course
 * and heavily modified
 */

/* Helper function to create a node */
Node *node_init(State *value)
{
  // Create our node
  Node *node = malloc(sizeof(Node));

  // Set its values and the next node
  node->value = value;
  node->next = NULL;

  // Return the node
  return node;
}

/* Create an empty queue and return a pointer to it */
Queue *queue_init()
{
  Queue *queue = malloc(sizeof(Queue));


  queue->count = 0;
  queue->first = NULL;


  return queue;
}

/* Insert an element into our queue*/
void queue_push(Queue *queue, State *element)
{
  // Create the node
  Node *node = node_init(element);

  // If the queue is empty
  if (!queue->count)
  {
    // We set the first element to the node
    queue->first = node;
  }
  else
  {
    // We find the last node
    Node *current = queue -> first;
    while(current->next)
    {
      current = current -> next;
    }

    // Our last node points to our new node
    current -> next = node;
  }
  // Increase the count
  queue->count++;
}

/* eliminates the first node in the queue and returns its value
 * if the list has an element, else we return a NULL pointer
 */
State *queue_pop(Queue *queue)
{
  // create the pointer to return
  State *value = NULL;
  // check to see if the list is empty
  if (queue->count)
  {
    // set the value of the pointer to return
    value = queue->first->value;
    // we get the node to remove
    Node *first = queue->first;
    // we remove the node from the queue
    queue->first = first->next;
    // free the memory of the removed node
    free(first);
    // decrease the size by one
    queue->count--;
  }
  // return the value of the node
  return value;
}

/* Remove the given cell from the queue, returns NULL if the queue is empty
 * or the cell wasn't found
 */
State *queue_remove(Queue *queue, State * cell)
{
  State *value = NULL;
  if (queue->count) // we check the queue is not empty
  {
    Node * current = queue -> first;
    Node * previous = NULL;
    // in case the key we are looking is on the first node
    if (current -> value == cell)
    {
      return queue_pop(queue);
    }
    // we iterate over the queue looking for the key
    while (current && current -> value != cell)
    {
      previous = current;
      current = current -> next;
    }

    // the key you are looking for is not here, return NULL pointer
    if (!current)
    {
      return value;
    }
    previous -> next = current -> next;
    value = current -> value;
    free(current);
    queue -> count--;
  }
  return value;

}

/* We free all the resources of the queue */
void queue_destroy(Queue *queue)
{
  // Remove all the nodes until the list is empty
  while (queue_pop(queue))
  {
    //printf("WARNING: Destroyed queue has elements left on it\n");
  }
  // Free the queue
  free(queue);
}
