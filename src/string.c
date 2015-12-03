////////////////////////////////////////////////////////////////////////////////
// THE SCOTCH-WARE LICENSE (Revision 0):
// <aaronryool/gmail.com> wrote this file. As long as you retain this notice you
// can do whatever you want with this stuff. If we meet some day, and you think
// this stuff is worth it, you can buy me a shot of scotch in return
////////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <stdlib.h>

///!!!!!!!!!!!!!!!!!!!!!!!!!!! CONVERTION FUNCTIONS !!!!!!!!!!!!!!!!!!!!!!!!!!!!
void reverse(char* s)
{
    int i, j;
    char c;
    for(i = 0, j = strlen(s) - 1;i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

int digits(intmax_t n, int base)
{
    int size = 0;
    while((n /= base) > 0) size++;
    return size;
}

char* itoa(intmax_t n, unsigned int base, bool signess)
{
    if(base > 16) return NULL; 
    
    int i;
    int size = 0;
    bool sign = false;
    char* s;

    if(n < 0 && signess)
    {
        sign = true;
        n = -n;
    }
    size = digits(n, base);
    s = (char*) malloc(size+2);
    memset(s, null, size+2);
    
    i = 0;
    do
    {   // generate digits in reverse order
        s[i++] = n % base < 10 ? (n % base) + '0' : (n % base) - 10 + 'a';
    }while((n /= base) > 0);
    
    if(sign && signess)
        s[i++] = '-';
    
    reverse(s);
    return s;
}

///!!!!!!!!!!!!!!!!!!!!!!!!!!! STRING FUNCTIONS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void* memset(void* s, int c, size_t n)
{
    unsigned char* p = (unsigned char*) s;
    for(;n > 0;n--)
        p[n - 1] = (unsigned char) c;
    return s;
}

void* memcpy(void* dest, const void* src, size_t n)
{
    unsigned char* a = (unsigned char*) dest;
    const unsigned char* b = (const unsigned char*) src;
    int i;
    for(i = 0;i < n;i++) a[i] = b[i];
    return dest;
}

void bcopy(const void* src, void* dest, size_t n)
{
    memcpy(dest, src, n);
}

void* memmove(void* dest, const void* src, size_t n)
{
    char temp[n+1];
    memcpy(temp, src, n);
    return memcpy(dest, temp, n);
}

int strcmp(const char* s1, const char* s2)
{
    int i,c;
    if((c = strlen(s1) - strlen(s2)) != 0)
        return c;
    for(i = 0;i < strlen(s1);i++)
        if(s1[i] != s2[i])
            return -1;
    return 0;
}

char* strcpy(char* dest, const char* src)
{
    return memcpy(dest, src, strlen(src)+1);
}

char* strcat(char* dest, const char* src)
{
    size_t slen = strlen(src) + 1;
    size_t dlen = strlen(dest);
    return memcpy(dest + dlen, src, slen);
}

char* strncat(char* dest, const char* src, size_t n)
{
    size_t dlen = strlen(dest);

    dest[dlen+n] = 0;
    return memcpy(dest + dlen, src, n);
}

size_t strlen(const char* s)
{
    size_t size = 0;
    for(;s[size] != 0;size++);
    return size;
}

int cpos(const char* s, const char c)
{
    int pos;
    for(pos = 0;s[pos] != c;pos++)
        if(s[pos] == null)
            return -1;
    return pos;
}

