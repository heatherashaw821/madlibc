////////////////////////////////////////////////////////////////////////////////
// THE SCOTCH-WARE LICENSE (Revision 0):
// <aaronryool/gmail.com> wrote this file. As long as you retain this notice you
// can do whatever you want with this stuff. If we meet some day, and you think
// this stuff is worth it, you can buy me a shot of scotch in return
////////////////////////////////////////////////////////////////////////////////


#include <string.h>
#include <stdlib.h>
#include <errno.h>


///!!!!!!!!!!!!!!!!!!!!!!!!!!! TIME FUNCTIONS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int nanosleep(const struct timespec* requested_time, struct timespec* remaining)
{
    struct timeval t;
    t.tv_sec  = requested_time->tv_sec;
    t.tv_usec = requested_time->tv_nsec / 1000;

    memcpy(remaining, requested_time, sizeof(struct timespec));

    select(null, (fd_set*) NULL, (fd_set*) NULL, (fd_set*) NULL, &t);

    remaining->tv_sec = t.tv_sec;
    remaining->tv_nsec = t.tv_usec * 1000;

    return (remaining->tv_sec & remaining->tv_nsec) == 0 ? 0 : -1;
}

clock_t times(struct tms *buf)
{
    return syscall(__NR_times, (long int) buf);
}

clock_t clock(void)
{
    return times(NULL);
}



time_t time(time_t* tloc)
{
    return 0;
}






