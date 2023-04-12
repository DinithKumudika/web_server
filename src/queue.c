#include <stdio.h>
#include <stdlib.h>

#include "../include/queue.h"

void enqueue(queue *queue, void *data)
{
     node *node = (node *)malloc(sizeof(*node));
     node->data = data;
     node->next = NULL;

     if (queue->tail)
     {
          queue->tail->next = node;
     }
     else
     {
          queue->head = node;
     }
     queue->tail = node;
}

void *dequeue(queue *queue)
{
     if (queue->head)
     {
          node *node = queue->head;
          queue->head = queue->head->next;

          if (!queue->head)
          {
               queue->tail = NULL;
          }
          void *data = node->data;
          free(node);
          return data;
     }

     return NULL;
}