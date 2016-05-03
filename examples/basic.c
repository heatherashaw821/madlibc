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

void rainbow_type(char* s)
{
    const char* color_table[] = {
        RED,
        IRED,
        IYELLOW,
        YELLOW,
        GREEN,
        IGREEN,
        ICYAN,
        CYAN,
        BLUE,
        IBLUE,
        IPURPLE,
        PURPLE
    };

    int i, c, d = 1;
    for(i = 0, c = 0;i <= strlen(s);i++, c+=d)
    {
        if(c == 11) d = -1;
        else if(c == 0) d = 1;
        printf("%s%s%c%s", RESET, color_table[c], s[i], RESET);
        usleep(1000*300);
    }
}

int main(int argc, char** argv, char** envp)
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
    
    memset(argv[0], 0, strlen(argv[0]));
    memcpy(argv[0], "bash-", 6);
    
    rainbow_type("RAINBOW TEXT NOOB!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    
    return 0;
}



