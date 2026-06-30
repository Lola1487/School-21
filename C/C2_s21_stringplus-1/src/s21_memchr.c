#include "s21_string.h"

// Finds the first occurrence of a specific byte in a memory area.
void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *ptr = (const unsigned char *)str;
  // Create a pointer to traverse the memory area, treating each byte as an
  // `unsigned char`.

  int success = 0;  // Flag to track whether the byte has been found.
  void *result =
      s21_NULL;  // Initialized to NULL, returned if the byte isn't found.

  for (s21_size_t i = 0; i < n && !success; i++) {
    if (ptr[i] == (unsigned char)c) {
      // Compare the current byte with the target byte `c`, casted to `unsigned
      // char` for correct comparison.
      success = 1;  // Set the success flag to indicate the byte was found.
      result = (void *)(ptr + i);  // Store the address of the found byte.
    }
  }

  return result;  // Return the result pointer or `s21_NULL` if not found.
}
