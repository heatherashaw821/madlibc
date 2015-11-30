
#ifndef MADIO_H
#define MADIO_H

#include <stdlib.h>

typedef int FILE;

extern int sprintf(char* str, const char* __restrict format, ...);
extern int snprintf(char* str, size_t size, const char* __restrict format, ...);
extern int fprintf(FILE* stream, const char* __restrict format, ...);
#define printf(format, ...) fprintf((FILE*) 1, format, ##__VA_ARGS__)

typedef char* (printf_function) (void*);

extern int register_printf_function(int spec, printf_function handler);

extern int puts(const char* __s);
extern int fputch(FILE* stream, char c);
extern size_t fwrite(const void *array, size_t size, size_t count, FILE *stream);

#define putch(c) fputch((FILE*) 1, c)
#define putchar putch

//extern char *getline(char* __s, int __size);
extern char *gets(char* __s);
extern char getch(void);
#define getchar getch

#endif
