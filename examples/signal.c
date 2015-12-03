////////////////////////////////////////////////////////////////////////////////
// THE SCOTCH-WARE LICENSE (Revision 0):
// <aaronryool/gmail.com> wrote this file. As long as you retain this notice you
// can do whatever you want with this stuff. If we meet some day, and you think
// this stuff is worth it, you can buy me a shot of scotch in return
////////////////////////////////////////////////////////////////////////////////
// Madlib example 

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

void interupt(int signum)
{
    printf("\nCaught: %s\n", signum == SIGINT ? "SIGINT" : signum == SIGTERM ? "SIGTERM" : itoa(signum, 10, false));
    _exit(0);
}

int __attribute__ ((noreturn)) main()
{
    signal(SIGINT, interupt);
    signal(SIGTERM, interupt);
    puts("Press CTRL + c to exit.");
    while(1);
    __builtin_unreachable();
}
