
typedef struct node {
     struct node* next;
     void *data;
} node;

typedef struct queue {
     struct node *head;
     struct node *tail;
} queue;

void enqueue(queue *queue, void* data);
void *dequeue(queue *queue);