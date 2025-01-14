#include "krmllib.h"
#include "Crypto_Symmetric_Chacha20.h"

#define LEN 114
static /* const */ uint8_t plaintext[LEN] =
  "Ladies and Gentlemen of the class of '99: If I could offer you only one tip "
  "for the future, sunscreen would be it.";
static const uint8_t expected[LEN] = {
  0x6e, 0x2e, 0x35, 0x9a, 0x25, 0x68, 0xf9, 0x80, 0x41, 0xba, 0x07, 0x28, 0xdd,
  0x0d, 0x69, 0x81, 0xe9, 0x7e, 0x7a, 0xec, 0x1d, 0x43, 0x60, 0xc2, 0x0a, 0x27,
  0xaf, 0xcc, 0xfd, 0x9f, 0xae, 0x0b, 0xf9, 0x1b, 0x65, 0xc5, 0x52, 0x47, 0x33,
  0xab, 0x8f, 0x59, 0x3d, 0xab, 0xcd, 0x62, 0xb3, 0x57, 0x16, 0x39, 0xd6, 0x24,
  0xe6, 0x51, 0x52, 0xab, 0x8f, 0x53, 0x0c, 0x35, 0x9f, 0x08, 0x61, 0xd8, 0x07,
  0xca, 0x0d, 0xbf, 0x50, 0x0d, 0x6a, 0x61, 0x56, 0xa3, 0x8e, 0x08, 0x8a, 0x22,
  0xb6, 0x5e, 0x52, 0xbc, 0x51, 0x4d, 0x16, 0xcc, 0xf8, 0x06, 0x81, 0x8c, 0xe9,
  0x1a, 0xb7, 0x79, 0x37, 0x36, 0x5a, 0xf9, 0x0b, 0xbf, 0x74, 0xa3, 0x5b, 0xe6,
  0xb4, 0x0b, 0x8e, 0xed, 0xf2, 0x78, 0x5e, 0x42, 0x87, 0x4d };

void hexdump(const uint8_t *buf, size_t len) {
  for (int i = 0; i < len; ++i) {
    if (i == len - 1)
      printf("0x%02" PRIx8 "\n", buf[i]);
    else if (i % 16 == 15)
      printf("0x%02" PRIx8 ",\n", buf[i]);
    else
      printf("0x%02" PRIx8 ", ", buf[i]);
  }
}

#define Crypto_Symmetric_Chacha20_counter_mode counter_mode

int main (int argc, char *argv[]) {
  uint8_t key[32] = { 0 };
  for (uint8_t i = 0; i < 32; ++i)
    key[i] = i;
  uint32_t counter = 1;
  uint8_t iv[12] = { 0, 0, 0, 0, 0, 0, 0, 0x4a, 0, 0, 0, 0 };
  uint32_t constant = 0;
  uint8_t ciphertext[LEN] = { 0 };

  long n = argc > 1 ? strtol(argv[1], NULL, 10) : 1;

  for (long i = 0; i < n; ++i)
    Crypto_Symmetric_Chacha20_counter_mode(key, iv, counter, LEN, plaintext, ciphertext);
  if (memcmp(expected, ciphertext, LEN) != 0) {
    printf("[Chacha]: encryption FAILED\n");
    printf("\nPLAINTEXT:\n");
    hexdump(plaintext, LEN);
    printf("\nCIPHERTEXT:\n");
    hexdump(ciphertext, LEN);
    printf("\nEXPECTED:\n");
    hexdump(expected, LEN);
    return EXIT_FAILURE;
  } else {
    printf("[Chacha]: encryption PASSED\n");
    return EXIT_SUCCESS;
  }
}
