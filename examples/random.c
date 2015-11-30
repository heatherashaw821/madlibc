// Madlib example 

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char** argv, const char** envp)
{
    srand(clock());
    int i;
    for(i = 0;i < 10;i++)
        printf(i != 9 ? "%u, " : "%u\n", rand() % 100);
    return 0;
}



