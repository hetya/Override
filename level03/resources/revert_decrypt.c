#include <stdio.h>
#include <string.h>

int main(void) {
    char buffer[17] = "Q}|u`sfg~sf{}|a3";
    char tmp[17];
    int i = 0;

    while (i < 21) {
        bzero(&tmp, 17);

        int y = 0;
        while (y < 17) {
            tmp[y] = buffer[y] ^ i;
            y++;
        }
        printf("key : %d \nstring : %s\n\n", i,tmp);

        if (strncmp("Congratulations!", tmp, 16) == 0) {
            printf("%d %d\n", 322424845 - i, i);
            break;
        }
        i++;
    }

    return 0;
}