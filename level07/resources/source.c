#include <stdio.h>

void clear_stdin()
{
  int result;

  while ((char)result != '\n')
    result = getchar();
  return;
}


int get_unum()
{
  int input[3];

  input[0] = 0;
  fflush(stdout);
  scanf("%u", input);
  clear_stdin();
  return input[0];
}


int store_number(int *tab)
{
  unsigned int nb;
  unsigned int index;

  printf(" Number: ");
  nb = get_unum();
  printf(" Index: ");
  index = get_unum();
  if ( index % 3 == 0 || nb >> 24 == 183 ) //#define HIBYTE(x) ((x >> 8) & 0xFF)
  {
    puts(" *** ERROR! ***");
    puts("   This index is reserved for wil!");
    puts(" *** ERROR! ***");
    return 1;
  }
  else
  {
    tab[4 * index] = nb;
    return 0;
  }
}



int read_number(int *tab)
{
  int index;

  printf(" Index: ");
  index = get_unum();
  printf(" Number at data[%u] is %u\n", index, tab[4 * index]);
  return 0;
}


int main(int argc, const char **argv, const char **envp)
{
	int		ret = 0;
	char	buffer[4];
	int		tab[100];

  memset(tab, 0, sizeof(tab));
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
    ret = 1;
    fgets(buffer, 20, stdin);
    buffer[strlen(buffer) - 1] = 0;
    if ( !memcmp(buffer, "store", 5u) )
    {
      ret = store_number(tab);
    }
    else if ( !memcmp(buffer, "read", 4u) )
    {
      ret = read_number(tab);
    }
    else if ( !memcmp(buffer, "quit", 4u) )
      return 0;

    if ( ret )
      printf(" Failed to do %s command\n", buffer);
    else
      printf(" Completed %s command successfully\n", buffer);
    bzero(buffer);
  }
}