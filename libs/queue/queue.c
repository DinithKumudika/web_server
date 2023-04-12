#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

// enqueue a node to queue linked list
void enqueue(queue *queue, void *data)
{
     node *new_node = (node *)malloc(sizeof(*node));
     new_node->data = data;
     new_node->next = NULL;

     if (queue->tail)
     {
          queue->tail->next = new_node;
     }
     else
     {
          queue->head = new_node;
     }
     queue->tail = new_node;
}

// dequeue node from the queue linked list
// returns the pointer to the data, return NULL if the queue is empty
void *dequeue(queue *queue)
{
     if (queue->head)
     {
          void *data = head->data;
          node *temp = queue->head;
          queue->head = queue->head->next;

          if (!queue->head)
          {
               queue->tail = NULL;
          }
          
          free(temp);
          return data;
     }
     else
     {
          return NULL;
     }
}