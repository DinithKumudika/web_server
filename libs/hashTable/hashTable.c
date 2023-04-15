#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashTable.h"

#define TABLE_SIZE 1024

typedef struct Node {
     
} Node;

Node hash_table[TABLE_SIZE];

unsigned int hash (char *value, int hashmap_size)
{
     int len = strlen(value);
     unsigned int hash_value = 0;

     for(int i = 0; i < len; i++)
     {
          hash_value += value[i];
          hash_value = (hash_value * value[i]) % hashmap_size;
     }
     
     return hash_value;
}

bool

