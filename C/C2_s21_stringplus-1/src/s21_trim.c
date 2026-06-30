#include <stdbool.h>
#include <stdlib.h>

#include "s21_string.h"

// Trims leading and trailing characters from a given string.

void *s21_trim(const char *src, const char *trim_chars) {
  char *new_str = s21_NULL;  // Initially set the output string to NULL.

  if (src) {  // Check if the source string exists before proceeding.
    const char *chars = (trim_chars && *trim_chars) ? (char *)trim_chars : " ";
    // Determine which characters to remove: either those passed via
    // `trim_chars` or spaces by default.

    const char *ptr_str = (char *)src;  // Start of the source string.
    char *end_str = (char *)src + s21_strlen(src);  // End of the source string.

    // Trim leading characters from the start of the string.
    while (*ptr_str && s21_strrchr(chars, *ptr_str)) {
      ptr_str++;
    }

    // Trim trailing characters from the end of the string.
    while (end_str != ptr_str && s21_strrchr(chars, *(end_str - 1))) {
      end_str--;
    }

    // Allocate memory for the trimmed string (including room for the null
    // terminator).
    new_str = (char *)calloc(end_str - ptr_str + 1, sizeof(char));

    if (new_str) {  // Ensure successful memory allocation before copying data.
      s21_strncpy(new_str, ptr_str,
                  end_str - ptr_str);           // Copy the trimmed portion.
      *(new_str + (end_str - ptr_str)) = '\0';  // Add the null terminator.
    }
  }

  return new_str;  // Return the pointer to the trimmed string.
}
