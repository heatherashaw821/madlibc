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

int main(int argc, const char** argv, const char** envp)
{
    pid_t pid;
    if((pid = fork()) >= 0)
    {
        if(pid != 0)
            exit(0);
    }
    else
        perror("fork");
    sleep(2);
    
    int i;
    const char* m = "The Matrix has you neo...";
    for(i = 0;i <= strlen(m);i++)
    {
        //printf("%s%s%c", RESET, GREEN, m[i]);
        putch(m[i]);
        usleep(1000*500);
    }
        
    return 0;
}



