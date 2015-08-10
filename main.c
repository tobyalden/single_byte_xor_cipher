#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

int main(int argc, char *argv[])
{
  char *hex = argv[1];
  printf("HEX INPUT: %s\n", hex);

  char hex_char[3];
  hex_char[2] = '\0';
  for(int i = 0; hex[i] != '\0'; i++)
  {
    hex_char[i%2] = hex[i];
    if(i%2 != 0)
    {
      printf("%s\n", &hex_char[0]);
    }
  }
  printf("\n");
}
