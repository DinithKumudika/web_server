#include <stdlib.h>

typedef struct threadNode {
     struct node* next;
     int *client_socket;
} threadNode;

// TODO:implement enqueue
void enqueue(int *client_socket);
// TODO:implement dequeue
int* dequeue();

// convert string to lowercase
char *str_to_lower(char *str)
{
     for(char *ptr = str; *ptr != '\0'; ptr++)
     {
          *ptr = tolower(*ptr);
     }

     return str;
}

// get a size of a file
long int get_file_size(FILE *fptr)
{
     fseek(fptr, 0L, SEEK_END);
     long int size = ftell(fptr);
     return size;
}