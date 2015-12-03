////////////////////////////////////////////////////////////////////////////////
// THE SCOTCH-WARE LICENSE (Revision 0):
// <aaronryool/gmail.com> wrote this file. As long as you retain this notice you
// can do whatever you want with this stuff. If we meet some day, and you think
// this stuff is worth it, you can buy me a shot of scotch in return
////////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>

const char* const sys_errlist[] = {
    "Success",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "No such device or address",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource temporarily unavailable",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Device or resource busy",
    "File exists",
    "Invalid cross-device link",
    "No such device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Numerical result out of range",
    "Resource deadlock avoided",
    "File name too long",
    "No locks available",
    "Function not implemented",
    "Directory not empty",
    "Too many levels of symbolic links",
    NULL
};


int fputch(FILE* stream, char c)
{
    return write((intmax_t) stream, &c, 1);
}

size_t fwrite(const void *array, size_t size, size_t count, FILE *stream)
{
    // flesh out later
    return write((intmax_t) stream, array, count*size);
}


int puts(const char* s)
{
    if(s == NULL) return -1;
    int ret = write(1, s, strlen(s));
    write((intmax_t) stdout, "\n", 1);
    return ret;
}


char* __printf_f_s(void* p){ return p; }
char* __printf_f_c(void* p){ return ((char[]) { (intmax_t) p, null }); }
char* __printf_f_i(void* p){ return itoa((intmax_t) p, 10, true); }
char* __printf_f_u(void* p){ return itoa((intmax_t) p, 10, false); }
char* __printf_f_x(void* p){ return itoa((intmax_t) p, 16, false); }
char* __printf_f_b(void* p){ return itoa((intmax_t) p, 2, false); }

char format_flags[25] = "sciuxb";
char* (*printf_fun_array[25]) (void*) = {
        __printf_f_s,
        __printf_f_c,
        __printf_f_i,
        __printf_f_u,
        __printf_f_x,
        __printf_f_b,
        NULL
};

int register_printf_function(int spec, printf_function handler)
{
    int size = strlen(format_flags);
    if(size >= 128)
        return -1;
    printf_fun_array[size] = handler;
    format_flags[size] = (char) spec;
    
    printf_fun_array[size++] = NULL;
    format_flags[size] = null;

    return 0;
}

int sprintf(char* str, const char* __restrict format, ...)
{
    va_list argp;
    void* p;
    int i, c, ccount = 0;
    va_start(argp, format);
    for(i = 0;format[i] != null;i++)
    {
        switch(format[i])
        {
            case '%':
                i++;
                if(cpos(format_flags, format[i]) != -1)
                {
                    p = (void*) va_arg(argp, void*);
                    char* out = printf_fun_array[cpos(format_flags, format[i])](p);
                    for(c = 0;out[c] != null;c++, ccount++)
                        str[ccount] = out[c];
                }
                else
                {
                    str[ccount] = format[i];
                    ccount++;
                }
                continue;
            default:
                str[ccount] = format[i];
                ccount++;
                continue;
        }
    }
    va_end(argp);
    str[ccount] = null;
    return ccount;
}

int snprintf(char* str, size_t size, const char* __restrict format, ...)
{
    return 0;
}

int fprintf(FILE* stream, const char* __restrict format, ...)
{
    va_list argp;
    void* p;
    int i, ccount = 0;
    va_start(argp, format);
    for(i = 0;format[i] != null;i++)
    {
        switch(format[i])
        {
            case '%':
                i++;
                if(cpos(format_flags, format[i]) != -1)
                {
                    p = (void*) va_arg(argp, void*);
                    char* out = printf_fun_array[cpos(format_flags, format[i])](p);
                    ccount += fwrite(out, sizeof(char), strlen(out), stream);
                }
                else
                {
                    fputch(stream, format[i]);
                    ccount++;
                }
                continue;
            default:
                fputch(stream, format[i]);
                ccount++;
                continue;
        }
    }
    va_end(argp);
    return ccount;
}

void perror(const char *s)
{
    
    if(s != NULL && *s != 0)
        fprintf(stderr, "%s: %s\n", s, sys_errlist[errno]);
}




