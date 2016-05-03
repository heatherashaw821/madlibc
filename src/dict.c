
#include <string.h>
#include <stdlib.h>
#include <dict.h>

dict_t* dict()
{
    dict_t* d = malloc(sizeof(dict_t));
    d->size = 0;
    return d;
}

bool dict_in(dict_t* d, char* key)
{
    int i;
    for(i = 1;i <= d->size;i++)
        if(strcmp(key, d->entry[i]->key) == 0)
            return true;
    return false;
}

bool dict_add(dict_t* d, char* key, void* value)
{
    if(dict_in(d, key)) return false;
    d->size++;
    d->entry[d->size] = malloc(sizeof(dict_entry_t));
    d->entry[d->size]->key = key;
    d->entry[d->size]->value = value;
    return true;
}

void* dict_value(dict_t* d, char* key)
{
    int i;
    for(i = 1;i <= d->size;i++)
        if(strcmp(key, d->entry[i]->key) == 0)
            return d->entry[i]->value;
    return (void*) -1;
}

void dict_copy(dict_t* from, dict_t* to)
{
    int i;
    for(i = 1;i <= from->size;i++)
        dict_add(to, from->entry[i]->key, from->entry[i]->value);
}

void dict_free(dict_t* d)
{
    int i;
    for(i = 1;i <= d->size;i++)
        free(d->entry[i]);
    free(d);
}

void dict_remove(dict_t* d, char* key)
{
    int i, c;
    for(i = 0, c = 0;i <= d->size + 1;i++)
    {
        if(strcmp(d->entry[i]->key, key) == 0)
        {
            free(d->entry[i]);
            d->size--;
        }
        else
        {
            d->entry[c] = d->entry[i];
            c++;
        }
    }
}

bool dict_assign(dict_t* d, char* key, void* value)
{
    int i;
    for(i = 1;i <= d->size;i++)
    {
        if(strcmp(key, d->entry[i]->key) == 0)
        {
            d->entry[i]->value = value;
            return true;
        }
    }
    return false;
}


