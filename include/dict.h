#ifndef DICT_H
#define DICT_H


#include <string.h>
#include <stdlib.h>

typedef struct dict_entry {
    char* key;
    void* value;
} dict_entry_t;

typedef struct dict_array {
    int size;
    dict_entry_t** entry;
} dict_t;

dict_t* dict();
extern bool dict_in(dict_t* dict, char* key);
extern bool dict_add(dict_t* dict, char* key, void* value);
extern void* dict_value(dict_t* dict, char* key);
extern void dict_copy(dict_t* from, dict_t* to);
extern void dict_free(dict_t* dict);
extern void dict_remove(dict_t* d, char* key);
extern bool dict_assign(dict_t* d, char* key, void* value);

#endif
