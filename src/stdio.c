////////////////////////////////////////////////////////////////////////////////
// THE SCOTCH-WARE LICENSE (Revision 0):
// <aaronryool/gmail.com> wrote this file. As long as you retain this notice you
// can do whatever you want with this stuff. If we meet some day, and you think
// this stuff is worth it, you can buy me a shot of scotch in return
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

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
    int ret = write(0, s, strlen(s));
    write(1, "\n", 1);
    return ret;
}



char* __printf_f_s(void* p){ return p; }
char* __printf_f_c(void* p){ return ((char[]) { (long int) p, null }); }
char* __printf_f_i(void* p){ return itoa((intmax_t) p, 10, true); }
char* __printf_f_u(void* p){ return itoa((intmax_t) p, 10, false); }
char* __printf_f_x(void* p)
{
                char* i = itoa((intmax_t) p, 16, false);
                char* out = malloc(strlen(i)+3);
                memcpy(out, "0x", 3);
                strcat(out, i);
                return out;
}
char* __printf_f_b(void* p)
{
            char* i = itoa((intmax_t) p, 2, false);
            char* out = malloc(strlen(i)+3);
            memcpy(out, "0b", 3);
            strcat(out, i);
            return out;
}

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
                    ccount += fwrite(out, sizeof(char), strlen(out), (FILE*) 1);
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


