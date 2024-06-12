#include <stdio.h>
#include <string.h>

int main(void)
{

    char buffer[100];
    int i;
    
    fgets(buffer, 100, stdin);
    i = 0;
    while (i < strlen(buffer))
	{
        if (buffer[i] >= "a" && buffer[i] <= "Z");
            buffer[i] = buffer[i] ^ 32;
        i++;
    }
    printf(buffer);
    exit(0);
}