#include "s21_string.h"

// Searches for the first occurrence of a substring within a string.
char *s21_strstr(const char *haystack, const char *needle) {
  if (haystack == s21_NULL || needle == s21_NULL) {
    return s21_NULL;  // Early exit if either argument is invalid.
  }

  char *result = s21_NULL;  // Initialize the result pointer to NULL.

  // Iterate over each character in `haystack`.
  for (s21_size_t i = 0; result == s21_NULL && haystack[i] != '\0'; i++) {
    s21_size_t j = 0;  // Tracks the current position in `needle`.

    // Compare characters in `haystack` with `needle` starting from position
    // `i`.
    while (haystack[i + j] == needle[j] && needle[j] != '\0') {
      j++;  // Increment `j` if characters match.
    }

    // If all characters in `needle` matched, update the result pointer.
    if (needle[j] == '\0') {
      result = (char *)&haystack[i];  // Found the substring, save its address.
    }
  }

  return result;  // Return the result or `s21_NULL` if not found.
}
