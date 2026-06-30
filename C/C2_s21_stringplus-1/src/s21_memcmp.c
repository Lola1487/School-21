#include "s21_string.h"

// Compares the first `n` bytes of two memory areas.
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  /* Initialize a variable to store the difference between byte values */
  int delta = 0;

  /* Loop through each byte in the specified range */
  for (s21_size_t i = 0; i < n; i++) {
    /* Calculate the difference between corresponding bytes */
    delta = ((unsigned char *)str1)[i] - ((unsigned char *)str2)[i];

    /* If there is any difference, stop comparing further bytes */
    if (delta != 0) {
      break;  // Exit the loop early when differences are detected
    }
  }

  /* Return the final result based on the accumulated difference */
  return delta;
}
