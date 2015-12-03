////////////////////////////////////////////////////////////////////////////////
// THE SCOTCH-WARE LICENSE (Revision 0):
// <aaronryool/gmail.com> wrote this file. As long as you retain this notice you
// can do whatever you want with this stuff. If we meet some day, and you think
// this stuff is worth it, you can buy me a shot of scotch in return
////////////////////////////////////////////////////////////////////////////////


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

extern char* itoa(intmax_t n, unsigned int base, bool signess);

#endif
