////////////////////////////////////////////////////////////////////////////////
// THE SCOTCH-WARE LICENSE (Revision 0):
// <aaronryool/gmail.com> wrote this file. As long as you retain this notice you
// can do whatever you want with this stuff. If we meet some day, and you think
// this stuff is worth it, you can buy me a shot of scotch in return
////////////////////////////////////////////////////////////////////////////////

#ifndef STDIO_H
#define STDIO_H

#include <stdlib.h>

typedef int FILE;

extern const char* const sys_errlist[];
extern int sys_nerr;

extern int sprintf(char* str, const char* __restrict format, ...);
extern int snprintf(char* str, size_t size, const char* __restrict format, ...);
extern int fprintf(FILE* stream, const char* __restrict format, ...);
#define printf(format, ...) fprintf(stdout, format, ##__VA_ARGS__)

typedef char* (printf_function) (void*);

extern int register_printf_function(int spec, printf_function handler);

extern int puts(const char* __s);
extern int fputch(FILE* stream, char c);
extern size_t fwrite(const void *array, size_t size, size_t count, FILE* stream);

#define putch(c) fputch(stdout, c)
#define putchar putch

//extern char *getline(char* __s, int __size);
extern char *gets(char* __s);
extern char getch(void);
#define getchar getch

extern void perror(const char *s);

#endif
