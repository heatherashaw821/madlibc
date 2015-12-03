////////////////////////////////////////////////////////////////////////////////
// THE SCOTCH-WARE LICENSE (Revision 0):
// <aaronryool/gmail.com> wrote this file. As long as you retain this notice you
// can do whatever you want with this stuff. If we meet some day, and you think
// this stuff is worth it, you can buy me a shot of scotch in return
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///!!!!!!!!!!!!!!!!!!!!!!!!! SPECIAL LIBC MAGIX !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
extern void (*__preinit_array_start []) (int, const char**, const char**);
extern void (*__preinit_array_end []) (int, const char**, const char**);

extern void (*__init_array_start []) (int, const char**, const char**);
extern void (*__init_array_end []) (int, const char**, const char**);
extern void (*__fini_array_start []) (void);
extern void (*__fini_array_end []) (void);

extern void _init(void);
extern void _fini(void);

char** __environ;
int errno = 0;

int *__errno_location(void)
{
    return &errno;
}

void __libc_csu_fini(int e)
{
#if defined(DEBUG)
    puts(__FUNCTION__);
#endif
    size_t i = __fini_array_end - __fini_array_start;
    while(i--)
        (*__fini_array_start[i])();
    _fini();
    _exit(e);
}

void __libc_init(int argc, const char** argv, const char** envp)
{
    size_t i = __preinit_array_end - __preinit_array_start;
    while(i--)
        (*__preinit_array_start[i])(argc, argv, envp);
    
}

void __libc_init_first(int argc, const char** argv, const char** envp)
{
    __environ = (void*) envp;
    __libc_init(argc, argv, envp);
}

void __libc_csu_init(int argc, const char** argv, const char** envp)
{
    _init();
    
    size_t i = __init_array_end - __init_array_start;
    while(i--)
        (*__init_array_start[i])(argc, argv, envp);
}


void __attribute__((noreturn)) __libc_start_main(
    int (*main) (int, const char**, const char**),
    int argc, char** ubp_av,
    void (*init) (int, const char**, const char**),
    void (*fini) (int),
    void (*rtld_fini) (void),
    void (*stack_end))
{
#if defined(DEBUG)
    puts(__FUNCTION__);
#endif
    const char** argv = (const char**) ubp_av;
    const char** envp = &argv[argc + 1];
    int ret;

    __libc_init_first(argc, argv, envp);
    init(argc, argv, envp);
    const char* ld_show_auxv = envpv(envp, "LD_SHOW_AUXV");
    if(ld_show_auxv != NULL && ld_show_auxv[0] == '1')
    {
        const char** p = envp;
        while(*p++ != NULL);
#if defined(__x86_64__)
        Elf64_auxv_t* auxv;
        for(auxv = (Elf64_auxv_t*) p; auxv->a_type != AT_NULL; auxv++)
#elif defined(__i386__)
        Elf32_auxv_t* auxv;
        for(auxv = (Elf32_auxv_t*) p; auxv->a_type != AT_NULL; auxv++)
#elif defined(__arm__)
        Elf32_auxv_t* auxv;
        for(auxv = (Elf32_auxv_t*) p; auxv->a_type != AT_NULL; auxv++)
#endif
        {
            switch(auxv->a_type)
            {
                case AT_IGNORE:
                    break;
                case AT_EXECFD:
                    printf("AT_EXECFD:\t\t%i\n", (int) auxv->a_un.a_val);
                    break;
                case AT_PHDR:
                    printf("AT_PHDR:\t\t%x\n", (int) auxv->a_un.a_val);
                    break;
                case AT_PHENT:
                    printf("AT_PHENT:\t\t%i\n", (int) auxv->a_un.a_val);
                    break;
                case AT_PHNUM:
                    printf("AT_PHNUM:\t\t%i\n", (int) auxv->a_un.a_val);
                    break;
                case AT_PAGESZ:
                    printf("AT_PAGESZ:\t\t%i\n", (int) auxv->a_un.a_val);
                    break;
                case AT_BASE:
                    printf("AT_BASE:\t\t%i\n", (int) auxv->a_un.a_val);
                    break;
                case AT_FLAGS:
                    printf("AT_FLAGS:\t\t%x\n", (int) auxv->a_un.a_val);
                    break;
                case AT_ENTRY:
                    printf("AT_ENTRY:\t\t%x\n", (int) auxv->a_un.a_val);
                    break;
                case AT_NOTELF:
                    printf("AT_NOTELF:\t\t%i\n", (int) auxv->a_un.a_val);
                    break;
                case AT_UID:
                    printf("AT_UID:\t\t\t%i\n", (int) auxv->a_un.a_val);
                    break;
                case AT_EUID:
                    printf("AT_EUID:\t\t%i\n", (int) auxv->a_un.a_val);
                    break;
                case AT_GID:
                    printf("AT_GID:\t\t\t%i\n", (int) auxv->a_un.a_val);
                    break;
                case AT_EGID:
                    printf("AT_EGID:\t\t%i\n", (int) auxv->a_un.a_val);
                    break;
                case AT_CLKTCK:
                    printf("AT_CLKTCK:\t\t%i\n", (int) auxv->a_un.a_val);
                    break;
                case AT_PLATFORM:
                    printf("AT_PLATFORM:\t\t%s\n", (char*) auxv->a_un.a_val);
                    break;
                case AT_HWCAP:
                    printf("AT_hwcap:\t\t%x\n", (int) auxv->a_un.a_val);
                    break;
                case AT_FPUCW:
                    printf("AT_FPUCW:\t\t%x\n", (int) auxv->a_un.a_val);
                    break;
                case AT_DCACHEBSIZE:
                    printf("AT_DCACHEBSIZE:\t%i\n", (int) auxv->a_un.a_val);
                    break;
                case AT_ICACHEBSIZE:
                    printf("AT_ICACHEBSIZE:\t%i\n", (int) auxv->a_un.a_val);
                    break;
                case AT_UCACHEBSIZE:
                    printf("AT_UCACHEBSIZE:\t%i\n", (int) auxv->a_un.a_val);
                    break;
                case AT_IGNOREPPC:
                    printf("AT_IGNOREPPC:\t\t%i\n", (int) auxv->a_un.a_val);
                    break;
                case AT_SECURE:
                    printf("AT_SECURE:\t\t%i\n", (int) auxv->a_un.a_val);
                    break;
                case AT_BASE_PLATFORM:
                    printf("AT_BASE_PLATFORM:\t%s\n", (char*) auxv->a_un.a_val);
                    break;
                case AT_RANDOM:
                    printf("AT_RANDOM:\t\t%x\n", (int) auxv->a_un.a_val);
                    break;
                case AT_HWCAP2:
                    printf("AT_HWCAP2:\t\t%x\n", (int) auxv->a_un.a_val);
                    break;
                case AT_EXECFN:
                    printf("AT_EXECFN:\t\t%s\n", (char*) auxv->a_un.a_val);
                    break;
                case AT_SYSINFO:
                    printf("AT_SYSINFO:\t\t%x\n", (int) auxv->a_un.a_val);
                    break;
                case AT_SYSINFO_EHDR:
                    printf("AT_SYSINFO_EHDR:\t%x\n", (int) auxv->a_un.a_val);
                    break;
                case AT_L1I_CACHESHAPE:
                    printf("AT_L1I_CACHESHAPE:\t%x\n", (int) auxv->a_un.a_val);
                    break;
                case AT_L1D_CACHESHAPE:
                    printf("AT_L1D_CACHESHAPE:\t%x\n", (int) auxv->a_un.a_val);
                    break;
                case AT_L2_CACHESHAPE:
                    printf("AT_L2_CACHESHAPE:\t%x\n", (int) auxv->a_un.a_val);
                    break;
                case AT_L3_CACHESHAPE:
                    printf("AT_L3_CACHESHAPE:\t%x\n", (int) auxv->a_un.a_val);
                    break;
                default:
                    break;
            }
        }

    }
    ret = main(argc, argv, envp);
    fini(ret);
    __builtin_unreachable();
}

// This prints an "Assertion failed" message and aborts.
void __attribute__((noreturn)) __assert_fail (
    const char* __assertion, const char* __file,
    unsigned int __line, const char* __function)
{
    printf("%s:%i: %s: Assertion (%s) failed.\n", __file, __line, __function, __assertion);
    exit(-1);
    __builtin_unreachable();
}

// Likewise, but prints the error text for ERRNUM.
void __attribute__((noreturn)) __assert_perror_fail(
    int __errnum, const char* __file,
    unsigned int __line, const char* __function)
{
    printf("Errnum: %i -> %s:%i:%s\n", __errnum, __file, __line, __function);
    exit(-1);
    __builtin_unreachable();
}


// The following is not at all used here but needed for standard compliance.
void __attribute__((noreturn)) __assert(
    const char* __assertion,
    const char* __file, int __line)
{
    printf("%s:%i: Assertion (%s) failed.\n", __file, __line, __assertion);
    exit(-1);
    __builtin_unreachable();
}


///!!!!!!!!!!!!!!!!!!!!!!!!!!! SYSCALL STUFF !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
const char* envpv(const char** envp, const char* key)
{
    int i,c;
    for(i = 0;envp[i] != NULL;i++)
        for(c = 0;envp[i][c] != null;c++)
            if(envp[i][c] == '=')
            {
                char k[c + 1];
                char* v = (char*) envp[i] + c + 1;
                memset(k, 0, sizeof(k));
                memcpy(k, envp[i], c);
                if(strcmp(key, k) == 0)
                    return v;
                break;
            }
    return NULL;
}

void __attribute__((noreturn)) exit(int e)
{
    __libc_csu_fini(e);
    __builtin_unreachable();
}


#if defined(__x86_64__)

intmax_t __syscall0(intmax_t a)
{
    register uint64_t ret asm("rax");
    asm(".intel_syntax noprefix\n"
        "push %0\n"
        "pop rax\n"
        "syscall\n"
        ::"r"((uint64_t) (a))
    );
    errno = -ret;
    return ret;
}
intmax_t __syscall1(intmax_t a, intmax_t b)
{
    register uint64_t ret asm("rax");
    asm(".intel_syntax noprefix\n"
        "push %1\n"
        "push %0\n"
        "pop rax\n"
        "pop rdi\n"
        "syscall\n"
        ::"r"((uint64_t) (a)),
        "r"((uint64_t) (b))
    );
    errno = -ret;
    return ret;
}
intmax_t __syscall2(intmax_t a, intmax_t b, intmax_t c)
{
    register uint64_t ret asm("rax");
    asm(".intel_syntax noprefix\n"
        "push %2\n"
        "push %1\n"
        "push %0\n"
        "pop rax\n"
        "pop rdi\n"
        "pop rsi\n"
        "syscall\n"
        ::"r"((uint64_t) (a)),
        "r"((uint64_t) (b)),
        "r"((uint64_t) (c))
    );
    errno = -ret;
    return ret; 
}
intmax_t __syscall3(intmax_t a, intmax_t b, intmax_t c, intmax_t d)
{
    register uint64_t ret asm("rax");
    asm(".intel_syntax noprefix\n"
        "push %3\n"
        "push %2\n"
        "push %1\n"
        "push %0\n"
        "pop rax\n"
        "pop rdi\n"
        "pop rsi\n"
        "pop rdx\n"
        "syscall\n"
        ::"r"((uint64_t) (a)),
        "r"((uint64_t) (b)),
        "r"((uint64_t) (c)),
        "r"((uint64_t) (d))
    );
    errno = -ret;
    return ret; 
}
intmax_t __syscall4(intmax_t a, intmax_t b, intmax_t c, intmax_t d, intmax_t e)
{
    register uint64_t ret asm("rax");
    asm(".intel_syntax noprefix\n"
        "push %4\n"
        "push %3\n"
        "push %2\n"
        "push %1\n"
        "push %0\n"
        "pop rax\n"
        "pop rdi\n"
        "pop rsi\n"
        "pop rdx\n"
        "pop r10\n"
        "syscall\n"
        ::"r"((uint64_t) (a)),
        "r"((uint64_t) (b)),
        "r"((uint64_t) (c)),
        "r"((uint64_t) (d)),
        "r"((uint64_t) (e))
    );
    errno = -ret;
    return ret; 
}
intmax_t __syscall5(intmax_t a, intmax_t b, intmax_t c, intmax_t d, intmax_t e, intmax_t f)
{
    register uint64_t ret asm("rax");
    asm(".intel_syntax noprefix\n"
        "push %5\n"
        "push %4\n"
        "push %3\n"
        "push %2\n"
        "push %1\n"
        "push %0\n"
        "pop rax\n"
        "pop rdi\n"
        "pop rsi\n"
        "pop rdx\n"
        "pop r10\n"
        "pop r8\n"
        "syscall\n"
        ::"r"((uint64_t) (a)),
        "r"((uint64_t) (b)),
        "r"((uint64_t) (c)),
        "r"((uint64_t) (d)),
        "r"((uint64_t) (e)),
        "r"((uint64_t) (f))
    );
    errno = -ret;
    return ret;
}
    
intmax_t __syscall6(intmax_t a, intmax_t b, intmax_t c, intmax_t d, intmax_t e, intmax_t f, intmax_t g)
{
    register uint64_t ret asm("rax");
    asm(".intel_syntax noprefix\n"
        "push %6\n"
        "push %5\n"
        "push %4\n"
        "push %3\n"
        "push %2\n"
        "push %1\n"
        "push %0\n"
        "pop rax\n"
        "pop rdi\n"
        "pop rsi\n"
        "pop rdx\n"
        "pop r10\n"
        "pop r8\n"
        "pop r9\n"
        "syscall\n"
        ::"r"((uint64_t) (a)),
        "r"((uint64_t) (b)),
        "r"((uint64_t) (c)),
        "r"((uint64_t) (d)),
        "r"((uint64_t) (e)),
        "r"((uint64_t) (f)),
        "r"((uint64_t) (g))
    );
    errno = -ret;
    return ret;
}

#elif defined(__i386__)

#elif defined(__arm__)

#else
#   error "Architecture not supported."
#endif


int unlinkat(int dirfd, const char* pathname, int flags)
{
    return syscall(__NR_unlinkat, dirfd, (intmax_t) pathname, flags);
}



int select (int __nfds, fd_set* __restrict __readfds,
        fd_set* __restrict __writefds,
        fd_set* __restrict __exceptfds,
        struct timeval* __restrict __timeout)
{
    return syscall(__NR_select, (intmax_t) __nfds, (intmax_t) __readfds, (intmax_t) __writefds, (intmax_t) __exceptfds, (intmax_t) __timeout);
}

int pselect (int __nfds, fd_set *__restrict __readfds,
    fd_set *__restrict __writefds,
    fd_set *__restrict __exceptfds,
    const struct timespec *__restrict __timeout,
    const __sigset_t *__restrict __sigmask)
{
    syscall(__NR_pselect6, (intmax_t) __nfds, (intmax_t) __readfds, (intmax_t) __writefds, (intmax_t) __exceptfds, (intmax_t) __timeout, (intmax_t) __sigmask);
    return (__timeout->tv_sec & __timeout->tv_nsec) == 0 ? 0 : -1;
}

///!!!!!!!!!!!!!!!!!!!!!!!!!!! MEMORY AND I/O !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void* malloc(size_t size)
{
    void* request = sbrk(size);
    if(request == (void*) -1)
        return NULL;
    return request;
}

void free(void* ptr)
{
    
}

void* calloc(size_t nmemb, size_t size);
void* realloc(void* ptr, size_t size);


///!!!!!!!!!!!!!!!!!!!!!!!!!!! PRNG FUNCTIONS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

unsigned int __prng_seed;
void srand(unsigned int __seed)
{
    __prng_seed = __seed;
}

int rand(void)
{
    __prng_seed ^= RSL(__prng_seed, 13);
    __prng_seed ^= RSR(__prng_seed, 9);
    __prng_seed ^= RSR(__prng_seed, 7);
    return __prng_seed;
}


long strtol(const char* s)
{
    bool sign = false;
    long i, r, base = 10;
    if(s[1] == 'x')
    {
        s+=2;
        base = 16;
    }
    else if(s[1] == 'b')
    {
        s+=2;
        base = 2;
    }
    
    if(s[0] == '-')
    {
        s+=1;
        sign = true;
    }
    
    for (i = 0, r = 0;s[i] != '\0';++i)
        r = r*base + s[i] - (s[i] >= '0' && s[i] <= '9' ? '0' :
                s[i] >= 'A' && s[i] <= 'Z' ? ('A' - 10) :  ('a' - 10));
    return (sign ? -r : r);
}



