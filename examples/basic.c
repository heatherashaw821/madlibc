////////////////////////////////////////////////////////////////////////////////
// THE SCOTCH-WARE LICENSE (Revision 0):
// <aaronryool/gmail.com> wrote this file. As long as you retain this notice you
// can do whatever you want with this stuff. If we meet some day, and you think
// this stuff is worth it, you can buy me a shot of scotch in return
////////////////////////////////////////////////////////////////////////////////
// Madlib example 

#include <stdlib.h>
#include <stdio.h>

int main(int argc, const char** argv, const char** envp)
{
    printf("%s %i %x\n", "\nWOOT", 1337, 0xdeadbeef);
    char* const e[] = {"whomai", NULL};
    execv("/usr/bin/whoami", e);
    exit(0);
}



