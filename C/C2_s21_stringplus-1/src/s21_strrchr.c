#include "s21_string.h"

// Searches for the last occurrence of the character c (an unsigned char) in the
// string pointed to by the argument str. */
char *s21_strrchr(const char *str, int c) {
  char *result = s21_NULL;              // Initialize result pointer to NULL
  s21_size_t length = s21_strlen(str);  // Get the length of the string

  // Convert the input character to unsigned char as per standard
  unsigned char character = (unsigned char)c;

  // Search the string in reverse order (including null terminator)
  for (s21_size_t i = length + 1; i > 0; i--) {
    if (str[i - 1] == character) {
      // When found, store the pointer and break the loop
      result = (char *)&str[i - 1];
      break;
    }
  }

  return result;  // Return the result pointer
}
