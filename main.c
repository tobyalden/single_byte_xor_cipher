#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

const char HEX_CHARS[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

char * fixed_xor(char *hex, char *mask);

int main(int argc, char *argv[])
{
  char *hex = argv[1];
  printf("HEX INPUT: %s\n", hex);


  char xor[3];
  xor[2] = '\0';
  for(int i = 0; i < 256; i++)
  {
    xor[0] = HEX_CHARS[i/16];
    xor[1] = HEX_CHARS[i%16];
    printf("%s: ", xor);

    char hex_char[3];
    hex_char[2] = '\0';
    for(int j = 0; hex[j] != '\0'; j++)
    {
      hex_char[j%2] = hex[j];
      if(j%2 != 0)
      {
        char *xored_char = fixed_xor(hex_char, xor);
        char letter = (char) strtol(xored_char, NULL, 16);
        printf("%c", letter);
      }
    }
    printf("\n");
  }

}

char * fixed_xor(char *hex, char *mask)
{
  mpz_t decimal;
  mpz_t decimal_mask;
  mpz_t xored_decimal;
  mpz_init_set_str (decimal, hex, 16);
  mpz_init_set_str (decimal_mask, mask, 16);
  mpz_init(xored_decimal);
  mpz_xor(xored_decimal, decimal, decimal_mask);
  char *xored_hex = mpz_get_str(NULL, 16, xored_decimal);
  return xored_hex;
}
