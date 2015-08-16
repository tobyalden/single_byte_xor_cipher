#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <string.h>

const char HEX_CHARS[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
const double PAIR_WEIGHT = 0.0384848485;

char * fixed_xor(char *hex, char *mask);
double freq_score(char c);
double pair_freq_score(char a, char b);

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
    char decrypt_attempt[hex_length/2+1];
    xor[0] = HEX_CHARS[i/16];
    xor[1] = HEX_CHARS[i%16];
    printf("%s: ", xor);

    // char *message;

    char hex_char[3];
    hex_char[2] = '\0';
    double decrypt_score = 0;
    char prev_letter;
    for(int j = 0; hex[j] != '\0'; j++)
    {
      hex_char[j%2] = hex[j];
      if(j%2 != 0)
      {
        char *xored_char = fixed_xor(hex_char, xor);
        char letter = (char) strtol(xored_char, NULL, 16);
        decrypt_attempt[(j-1)/2] = letter;
        decrypt_score += freq_score(letter);
        if(j != 1)
        {
          decrypt_score += pair_freq_score(prev_letter, letter) * PAIR_WEIGHT;
        }
        prev_letter = letter;
      }
    }
    if(decrypt_score > high_score)
    {
      high_score = decrypt_score;
      strcpy(decrypted_msg, decrypt_attempt);
      // decrypted_msg = decrypt_attempt;
    }
    decrypt_attempt[hex_length/2] = '\0';
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

double pair_freq_score(char a, char b)
{
  if(a == 't' && b == 'h') { return 330; }
  if(a == 'h' && b == 'e') { return 302; }
  if(a == 'a' && b == 'n') { return 181; }
  if(a == 'e' && b == 'r') { return 169; }
  if(a == 'n' && b == 'd') { return 146; }
  if(a == 'r' && b == 'e') { return 133; }
  if(a == 'e' && b == 'd') { return 126; }
  if(a == 'e' && b == 's') { return 115; }
  if(a == 'o' && b == 'u') { return 115; }
  if(a == 't' && b == 'o') { return 115; }
  if(a == 'h' && b == 'a') { return 114; }
  if(a == 'e' && b == 'n') { return 111; }
  if(a == 'e' && b == 'a') { return 110; }
  if(a == 's' && b == 't') { return 109; }
  if(a == 'n' && b == 't') { return 106; }
  if(a == 'o' && b == 'n') { return 106; }
  if(a == 'a' && b == 't') { return 104; }
  if(a == 'h' && b == 'i') { return 97; }
  if(a == 'a' && b == 's') { return 95; }
  if(a == 'i' && b == 't') { return 93; }
  if(a == 'n' && b == 'g') { return 92; }
  if(a == 'i' && b == 's') { return 86; }
  if(a == 'o' && b == 'r') { return 84; }
  if(a == 'e' && b == 't') { return 83; }
  if(a == 'o' && b == 'f') { return 80; }
  if(a == 't' && b == 'i') { return 76; }
  if(a == 'a' && b == 'r') { return 75; }
  if(a == 't' && b == 'e') { return 75; }
  if(a == 's' && b == 'e') { return 74; }
  if(a == 'm' && b == 'e') { return 68; }
  if(a == 's' && b == 'a') { return 67; }
  if(a == 'n' && b == 'e') { return 66; }
  if(a == 'w' && b == 'a') { return 66; }
  if(a == 'v' && b == 'e') { return 65; }
  if(a == 'l' && b == 'e') { return 64; }
  if(a == 'n' && b == 'o') { return 60; }
  if(a == 't' && b == 'a') { return 59; }
  if(a == 'a' && b == 'l') { return 57; }
  if(a == 'd' && b == 'e') { return 57; }
  if(a == 'o' && b == 't') { return 57; }
  if(a == 's' && b == 'o') { return 57; }
  if(a == 'd' && b == 't') { return 56; }
  if(a == 'l' && b == 'l') { return 56; }
  if(a == 't' && b == 't') { return 56; }
  if(a == 'e' && b == 'l') { return 55; }
  if(a == 'r' && b == 'o') { return 55; }
  if(a == 'a' && b == 'd') { return 52; }
  if(a == 'd' && b == 'i') { return 50; }
  if(a == 'e' && b == 'w') { return 50; }
  if(a == 'r' && b == 'a') { return 50; }
  if(a == 'r' && b == 'i') { return 50; }
  if(a == 's' && b == 'h') { return 50; }
  else { return 0; }
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
