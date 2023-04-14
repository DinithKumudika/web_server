typedef struct Dictionary {

} Dictionary;

typedef struct Entry {
     void *key;
     void *val;
} Entry;

Entry entry_init(void *key, int key_size, void *val, int val_size);

void entry_del(Entry *entry);

Dictionary dict_init();
void dict_del(Dictionary *dict);

void insert(void *key, int key_size, void *val, int val_size, Dictionary *dict);
void search(void *key, Dictionary *dict);
void display();
void remove(void *key);
void update();


