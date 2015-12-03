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
    printf("%s %x %x %x\n", "\nWOOT", atoi("0b1111000011110000"), atoi("0xbadc0DE"), 0xdeadbeef);
    
    pid_t pid;
    if((pid = fork()) >= 0)
    {
        if(pid == 0)
        {
            sleep(1);
            printf("child\n");
        }
        else
            printf("parent\n");
    }
    else
        perror("fork");
    sleep(2);
    
    return 0;
}



