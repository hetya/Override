#include <stdio.h>

int clear_stdin()
{
  int result;

  while ((char)result != '\n')
    result = getchar();
  return;
}


int get_unum()
{
  int v1[3];

  v1[0] = 0;
  fflush(stdout);
  scanf("%u", v1);
  clear_stdin();
  return v1[0];
}


int store_number(int a1)
{
  unsigned int nb;
  unsigned int index;

  printf(" Number: ");
  nb = get_unum();
  printf(" Index: ");
  index = get_unum();
  if ( index % 3 == 0 || HIBYTE(nb) == 183 )
  {
    puts(" *** ERROR! ***");
    puts("   This index is reserved for wil!");
    puts(" *** ERROR! ***");
    return 1;
  }
  else
  {
    *(_DWORD *)(a1 + 4 * index) = nb;
    return 0;
  }
}



int read_number(int a1)
{
  int index;

  printf(" Index: ");
  index = get_unum();
  printf(" Number at data[%u] is %u\n", index, *(_DWORD *)(a1 + 4 * index));
  return 0;
}


int main(int argc, const char **argv, const char **envp)
{
  _BYTE v6[400];
  int number;
  char s[4];
  int v9;
  int v10;
  int v11;
  int v12;
  unsigned int v13;

  v13 = __readgsdword(0x14u);
  number = 0;
  *(_DWORD *)s = 0;
  v9 = 0;
  v10 = 0;
  v11 = 0;
  v12 = 0;
  memset(v6, 0, sizeof(v6));
  while ( *argv )
  {
    memset((void *)*argv, 0, strlen(*argv));
    ++argv;
  }
  while ( *envp )
  {
    memset((void *)*envp, 0, strlen(*envp));
    ++envp;
  }

  puts(
    "----------------------------------------------------\n"
    "  Welcome to wil's crappy number storage service!   \n"
    "----------------------------------------------------\n"
    " Commands:                                          \n"
    "    store - store a number into the data storage    \n"
    "    read  - read a number from the data storage     \n"
    "    quit  - exit the program                        \n"
    "----------------------------------------------------\n"
    "   wil has reserved some storage :>                 \n"
    "----------------------------------------------------\n");

  while ( 1 )
  {
    printf("Input command: ");
    command_return = 1;
    fgets(s, 20, stdin);
    s[strlen(s) - 1] = 0;
    if ( !memcmp(s, "store", 5u) )
    {
      command_return = store_number((int)v6);
    }
    else if ( !memcmp(s, "read", 4u) )
    {
      command_return = read_number((int)v6);
    }
    else if ( !memcmp(s, "quit", 4u) )
      return 0;

    if ( command_return )
      printf(" Failed to do %s command\n", s);
    else
      printf(" Completed %s command successfully\n", s);
    *(_DWORD *)s = 0;
    v9 = 0;
    v10 = 0;
    v11 = 0;
    v12 = 0;
  }
}