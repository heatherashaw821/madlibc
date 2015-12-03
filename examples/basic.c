////////////////////////////////////////////////////////////////////////////////
// THE SCOTCH-WARE LICENSE (Revision 0):
// <aaronryool/gmail.com> wrote this file. As long as you retain this notice you
// can do whatever you want with this stuff. If we meet some day, and you think
// this stuff is worth it, you can buy me a shot of scotch in return
////////////////////////////////////////////////////////////////////////////////
// Madlib example 

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void type(char* s)
{
    int i;
    for(i = 0;i <= strlen(s);i++)
    {
        printf("%s%s%c%s", RESET, GREEN, s[i], RESET);
        usleep(1000*300);
    }
}

int main(int argc, const char** argv, const char** envp)
{
    pid_t pid;
    if((pid = fork()) >= 0)
    {
        if(pid != 0)
            exit(0);
        else
            usleep(800000);
    }
    else
        perror("fork");
    
    type("The Matrix has you neo...");
    return 0;
}



