#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <string.h>

const char HEX_CHARS[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

char * fixed_xor(char *hex, char *mask);
double freq_score(char c);

int main(int argc, char *argv[])
{
  char *hex = argv[1];
  printf("HEX INPUT: %s\n", hex);

  int hex_length;
  for(hex_length = 0; hex[hex_length] != '\0'; hex_length++) {
    ;
  }

  char xor[3];
  xor[2] = '\0';
  double high_score = 0;
  char *decrypted_msg;
  for(int i = 0; i < 256; i++)
  {
    char decrypt_attempt[hex_length/2];
    xor[0] = HEX_CHARS[i/16];
    xor[1] = HEX_CHARS[i%16];
    printf("%s: ", xor);

    // char *message;

    char hex_char[3];
    hex_char[2] = '\0';
    double decrypt_score = 0;
    for(int j = 0; hex[j] != '\0'; j++)
    {
      hex_char[j%2] = hex[j];
      if(j%2 != 0)
      {
        char *xored_char = fixed_xor(hex_char, xor);
        char letter = (char) strtol(xored_char, NULL, 16);
        decrypt_attempt[(j-1)/2] = letter;
        decrypt_score += freq_score(letter);
      }
    }
    if(decrypt_score > high_score)
    {
      high_score = decrypt_score;
      decrypted_msg = decrypt_attempt;
    }
    printf("%s (Score: %f)\n", decrypt_attempt, decrypt_score);
  }
  printf("Decrypted message: %s (High Score: %f)\n", decrypted_msg, high_score);
}

double freq_score(char c)
{
  switch(c) {
    case 'e':
      return 12.70;
    case 't':
      return 9.056;
    case 'a':
      return 8.167;
    case 'o':
      return 7.507;
    case 'i':
      return 6.966;
    case 'n':
      return 6.749;
    case 's':
      return 6.327;
    case 'h':
      return 6.094;
    case 'r':
      return 5.987;
    case 'd':
      return 4.253;
    case 'l':
      return 4.025;
    case 'c':
      return 2.782;
    case 'u':
      return 2.758;
    case 'm':
      return 2.406;
    case 'w':
      return 2.361;
    case 'f':
      return 2.228;
    case 'g':
      return 2.015;
    case 'y':
      return 1.974;
    case 'p':
      return 1.929;
    case 'b':
      return 1.492;
    case 'v':
      return 0.978;
    case 'k':
      return 0.772;
    case 'j':
      return 0.153;
    case 'x':
      return 0.150;
    case 'q':
      return 0.095;
    case 'z':
      return 0.074;
    default:
      return 0;
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
