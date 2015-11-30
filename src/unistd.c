////////////////////////////////////////////////////////////////////////////////
// THE SCOTCH-WARE LICENSE (Revision 0):
// <aaronryool/gmail.com> wrote this file. As long as you retain this notice you
// can do whatever you want with this stuff. If we meet some day, and you think
// this stuff is worth it, you can buy me a shot of scotch in return
////////////////////////////////////////////////////////////////////////////////


#include <stdlib.h>
#include <stdarg.h>


/*
int          fchown(int, uid_t, gid_t);
int          fchdir(int);
int          fdatasync(int);
pid_t        fork(void);
long int     fpathconf(int, int);
int          fsync(int);
int          ftruncate(int, off_t);
char        *getcwd(char *, size_t);
int          getdtablesize(void); (LEGACY)
gid_t        getegid(void);
uid_t        geteuid(void);
gid_t        getgid(void);
int          getgroups(int, gid_t []);
long         gethostid(void);
char        *getlogin(void);
int          getlogin_r(char *, size_t);
int          getopt(int, char * const [], const char *);
int          getpagesize(void); (LEGACY)
char        *getpass(const char *); (LEGACY)
pid_t        getpgid(pid_t);
pid_t        getpgrp(void);
pid_t        getpid(void);
pid_t        getppid(void);
pid_t        getsid(pid_t);
uid_t        getuid(void);
char        *getwd(char *);
int          isatty(int);
int          lchown(const char *, uid_t, gid_t);
int          link(const char *, const char *);
int          lockf(int, int, off_t);
off_t        lseek(int, off_t, int);
int          nice(int);
long int     pathconf(const char *, int);
int          pause(void);
int          pipe(int [2]);
ssize_t      pread(int, void *, size_t, off_t);
int          pthread_atfork(void (*)(void), void (*)(void), void(*)(void));
ssize_t      pwrite(int, const void *, size_t, off_t);
ssize_t      read(int, void *, size_t);
int          readlink(const char *, char *, size_t);
int          setgid(gid_t);
int          setpgid(pid_t, pid_t);
pid_t        setpgrp(void);
int          setregid(gid_t, gid_t);
int          setreuid(uid_t, uid_t);
pid_t        setsid(void);
int          setuid(uid_t);
void         swab(const void *, void *, ssize_t);
int          symlink(const char *, const char *);
void         sync(void);
long int     sysconf(int);
pid_t        tcgetpgrp(int);
int          tcsetpgrp(int, pid_t);
int          truncate(const char *, off_t);
char        *ttyname(int);
int          ttyname_r(int, char *, size_t);
useconds_t   ualarm(useconds_t, useconds_t);
pid_t        vfork(void);
*/



/*TODO: 
size_t confstr(int name, char* buf, size_t len)
{
    // I dont want to code this yet... deal with it lol
    return null;
}

char* crypt(const char* key, const char* salt)
{
    // I dont want to code this yet... deal with it lol
    return NULL;
}

char* ctermid(char* s)
{
    // I dont want to code this yet... deal with it lol
    return NULL;
}
*/

char *optarg;
int optind, opterr, optopt;


void __attribute__ ((noreturn)) _exit(int __status)
{
    syscall(__NR_exit, __status);
    __builtin_unreachable();
}

int access(const char* pathname, int mode)
{
    return syscall(__NR_access, pathname, mode);
}

int chdir(const char* path)
{
    return (errno = syscall(__NR_chdir, path)) != 0 ? -1 : 0;
}

int chroot(const char* path)
{
    return (errno = syscall(__NR_chroot, path)) != 0 ? -1 : 0;
}

int chown(const char* pathname, uid_t owner, gid_t group)
{
    return (errno = syscall(__NR_chown, pathname, owner, group)) != 0 ? -1 : 0;
}

int close(int fd)
{
    return (errno = syscall(__NR_close, fd)) != 0 ? -1 : 0;
}

int dup(int oldfd)
{
    return (errno = syscall(__NR_dup, oldfd) > 0 ? errno : -1);
}

int dup2(int oldfd, int newfd)
{
    return (errno = syscall(__NR_dup, oldfd, newfd) > 0 ? errno : -1);
}

int execv(const char *path, char *const argv[])
{
    return syscall(__NR_execve, path, argv, __environ);
}

int execlp(const char *file, const char *arg, ... /* (char  *) NULL */)
{
    va_list argp;
    unsigned int argc = 0, i = 1;
    va_start(argp, arg);
    while(((char**) va_arg(argp, void*)) != NULL) argc++;
    va_end(argp);
    
    const char* argv[argc];
    argv[0] = arg;
    va_start(argp, arg);
    while((argv[i] = (char*) va_arg(argp, char*)) != NULL) i++;
    argv[i++] = NULL;
    va_end(argp);
    return syscall(__NR_execve, file, argv, __environ);
}

int execl(const char *path, const char *arg, ... /* (char  *) NULL */)
{
    va_list argp;
    unsigned int argc = 0, i = 1;
    va_start(argp, arg);
    while(((char**) va_arg(argp, void*)) != NULL) argc++;
    va_end(argp);
    
    const char* argv[argc];
    argv[0] = arg;
    va_start(argp, arg);
    while((argv[i] = (char*) va_arg(argp, char*)) != NULL) i++;
    argv[i++] = NULL;
    va_end(argp);
    return syscall(__NR_execve, path, argv, __environ);
}

int execvp(const char *file, char* const argv[])
{
    return syscall(__NR_execve, file, argv, __environ);
}

int execle(const char *path, const char *arg, ... /*, (char *) NULL, char * const envp[] */)
{
    va_list argp;
    unsigned int argc = 0, i = 1;
    
    char** envp;
    va_start(argp, arg);
    while((envp = (char**) va_arg(argp, void*)) != NULL) argc++;
    envp = (char**) va_arg(argp, char**);
    va_end(argp);
    
    const char* argv[argc];
    argv[0] = arg;
    va_start(argp, arg);
    while((argv[i] = (char*) va_arg(argp, char*)) != NULL) i++;
    argv[i++] = NULL;
    va_end(argp);
    return syscall(__NR_execve, path, argv, envp);
}

int execvpe(const char *file, char *const argv[], char *const envp[])
{
    return syscall(__NR_execve, file, argv, envp);
}

unsigned int alarm(unsigned int seconds)
{
    return syscall(__NR_access, seconds);
}

int brk(void* addr)
{
    return syscall(__NR_brk, 0) != syscall(__NR_brk, addr) ? -1 : 0;
}

void* sbrk(intptr_t increment)
{
    intptr_t start = syscall(__NR_brk, 0);
    intptr_t new = syscall(__NR_brk, start+increment);
    intptr_t newp = syscall(__NR_brk, 0);
    return (new == newp && new != start) ? (void*) new : (void*) -1;
}

int rmdir(const char* pathname)
{
    return syscall(__NR_rmdir, pathname);
}

int unlink(const char* pathname)
{
    return syscall(__NR_unlink, pathname);
}

int usleep(useconds_t usec)
{
    /*
       Some code calls select() with all three sets empty, nfds zero, and a
       non-NULL timeout as a fairly portable way to sleep with subsecond
       precision.
    */
    struct timeval t;
    t.tv_sec  = null;
    t.tv_usec = usec;

    select(null, (fd_set*) NULL, (fd_set*) NULL, (fd_set*) NULL, &t);

    return (t.tv_sec & t.tv_usec) == 0 ? 0 : -1;
}

unsigned int sleep(unsigned int seconds)
{
    struct timeval t;
    t.tv_sec = seconds;
    select(null, (fd_set*) NULL, (fd_set*) NULL, (fd_set*) NULL, &t);
    return t.tv_sec;
}


ssize_t write(int fildes, const void *buf, size_t nbyte)
{
    return syscall(__NR_write, fildes, buf, nbyte);
}


