////////////////////////////////////////////////////////////////////////////////
// THE SCOTCH-WARE LICENSE (Revision 0):
// <aaronryool/gmail.com> wrote this file. As long as you retain this notice you
// can do whatever you want with this stuff. If we meet some day, and you think
// this stuff is worth it, you can buy me a shot of scotch in return
////////////////////////////////////////////////////////////////////////////////

#ifndef STDLIB_H
#define STDLIB_H

// libc stuff
#include <stdint.h>
#include <elf.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>

#include <sys/times.h>
#include <sys/select.h>
#include <sys/syscall.h>

// STUFF
#include <madmath.h>
#include <madconsole.h>
#include <madmacro.h>


typedef __SIZE_TYPE__ size_t;

typedef enum { false, true } bool;

#define null 0

typedef void (*fun_ptr) (void);
#define lambda(type, body) ({ type lambda body lambda; })

#define STR_MAX_LENGTH	1024

#define stdin (FILE*) 0
#define stdout (FILE*) 1
#define stderr (FILE*) 2

extern int errno;

extern intmax_t __syscall0(intmax_t a);
extern intmax_t __syscall1(intmax_t a,intmax_t b);
extern intmax_t __syscall2(intmax_t a,intmax_t b,intmax_t c);
extern intmax_t __syscall3(intmax_t a,intmax_t b,intmax_t c,intmax_t d);
extern intmax_t __syscall4(intmax_t a,intmax_t b,intmax_t c,intmax_t d,intmax_t e);
extern intmax_t __syscall5(intmax_t a,intmax_t b,intmax_t c,intmax_t d,intmax_t e,intmax_t f);
extern intmax_t __syscall6(intmax_t a,intmax_t b,intmax_t c,intmax_t d,intmax_t e,intmax_t f,intmax_t g);

#define M__syscall0(a) \
    __syscall0(((intmax_t) a))
#define M__syscall1(a,b) \
    __syscall1(((intmax_t) a), ((intmax_t) b))
#define M__syscall2(a,b,c) \
    __syscall2(((intmax_t) a), ((intmax_t) b), ((intmax_t) c))
#define M__syscall3(a,b,c,d) \
    __syscall3(((intmax_t) a), ((intmax_t) b), ((intmax_t) c), ((intmax_t) d))
#define M__syscall4(a,b,c,d,e) \
    __syscall4(((intmax_t) a), ((intmax_t) b), ((intmax_t) c), ((intmax_t) d), ((intmax_t) e))
#define M__syscall5(a,b,c,d,e,f) \
    __syscall5(((intmax_t) a), ((intmax_t) b), ((intmax_t) c), ((intmax_t) d), ((intmax_t) e), ((intmax_t) f))
#define M__syscall6(a,b,c,d,e,f,g) \
    __syscall6(((intmax_t) a), ((intmax_t) b), ((intmax_t) c), ((intmax_t) d), ((intmax_t) e), ((intmax_t) f), ((intmax_t) g))

#define GET_MACRO(_0,_1,_2,_3,_4,_5,_6,NAME,...) NAME
 
#define syscall(...) GET_MACRO(__VA_ARGS__, M__syscall6, M__syscall5, M__syscall4, \
    M__syscall3, M__syscall2, M__syscall1)(__VA_ARGS__)


extern int *__errno_location(void);

extern void* malloc(size_t size);
extern void free(void* ptr);
extern void* calloc(size_t nmemb, size_t size);
extern void* realloc(void* ptr, size_t size);

extern void __attribute__((noreturn)) exit(int __e);
extern const char* envpv(const char** envp, const char* key);

extern void srand(unsigned int __seed);
extern int rand(void);

extern long strtol(const char* str);
#define atoi(str) (int) strtol(str)

// for really bad debugging, use this lol
//#define DEBUG

#endif
