#include "s21_string.h"

// Concatenates up to `n` characters from source string to destination string.
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  // Find the end of the destination string.
  char *p = dest;
  while (*p != '\0') {
    p++;  // Move to the next character until the null terminator is found.
  }

  // Copy up to `n` characters from `src` into `dest`, starting at position `p`.
  s21_size_t i = 0;
  while (i < n && src[i] != '\0') {
    *p++ = src[i++];
  }

  // Append the terminating null character to ensure the resulting string is
  // properly terminated.
  *p = '\0';

  return dest;
}
