#include "s21_string.h"

// Copies up to n characters from the string pointed to, by src to dest.
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *result = dest;  // save original dest for return
  s21_size_t i;

  // Copy up to n chars from src (stop at null terminator)
  for (i = 0; i < n && src[i]; i++) {
    dest[i] = src[i];
  }

  // Pad remaining space with nulls if needed
  for (; i < n; i++) {
    dest[i] = '\0';
  }

  return result;
}
