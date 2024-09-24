#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    int serial;

    serial = 0;
    if (argc != 2)
    {
        printf("1 arg required\n");
        return 1;
    }
    if (strlen(argv[1]) < 6)
    {
        printf("arg should be at least 6 character long\n");
        return 1;
    }
    argv[1][strcspn(argv[1], "\n")] = 0;
    serial = (argv[1][3] ^ 4919) + 6221293;
    for (int i = 0; i < strnlen(argv[1], 32); ++i )
    {
      if ( argv[1][i] <= 31 )
      {
        printf("There must not be ascii char lower than 31\n");
        return 1;
      }
      serial += (serial ^ (unsigned int)argv[1][i]) % 1337;
    }
    printf("Serial : %d\n", serial);
    return 0;
}