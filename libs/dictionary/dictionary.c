#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

Entry entry_init(void *key, int key_size, void *val, int val_size)
{
     Entry entry;
     entry.key = malloc(key_size);
     entry.val = malloc(val_size);
     memcpy(entry.key, key, key_size);
     memcpy(entry.val, val, val_size);
     return Entry;
};

void entry_del(Entry *entry) 
{
     free(entry->key);
     free(entry->val);
     free(entry);
}