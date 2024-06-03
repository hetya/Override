#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main()
{
    unsigned int v0;
    char v1;

    puts("***********************************");
    puts("* \t     -Level00 -\t\t  *");
    puts("***********************************");
    printf("Password:");
    v0 = &v1;
    scanf("%d");
    if (*((int *)&v1) != 5276)
    {
        puts("\nInvalid Password!");
        return 1;
    }
    puts("\nAuthenticated!");
    system("/bin/sh");
    return 0;
}
