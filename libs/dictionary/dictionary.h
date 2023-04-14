typedef struct Dictionary {

} Dictionary;

typedef struct Entry {
     void *key;
     void *val;
} Entry;

Entry entry_init(void *key, int key_size, void *val, int val_size);

void entry_del(Entry *entry);

void insert(void *val);
void display();
void remove(void *key);
void update();
void search(void *key);

