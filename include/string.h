#ifndef MADSTR_H
#define MADSTR_H

#include <stdlib.h>

extern void* memset(void* s, int c, size_t n);
extern void* memmove(void* dest, const void* src, size_t n);
extern void *memcpy(void* dest, const void* src, size_t n);
extern void bcopy(const void* src, void* dest, size_t n);

extern size_t strlen(const char* s);
extern int cpos(const char* s, const char c);
extern int strcmp(const char* s1, const char* s2);
extern char* strcpy(char* dest, const char* src);
extern char* strcat(char* dest, const char* src);
extern char* strncat(char* dest, const char* src, size_t n);

extern size_t digits(intmax_t n, int base);
extern char* itoa(intmax_t n, unsigned int base, bool signess);

#endif
