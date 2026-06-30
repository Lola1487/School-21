#include "s21_string.h"

// Finds the first character in the string str1 that matches any character
// specified in str2
char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = s21_NULL;

  // Search for any char from str2 in str1
  for (s21_size_t i = 0; result == s21_NULL && str1[i] != '\0'; i++) {
    char current_char = str1[i];

    // Compare current char with all chars in str2
    for (s21_size_t j = 0; result == s21_NULL && str2[j] != '\0'; j++) {
      if (current_char == str2[j]) {
        result = (char *)&str1[i];  // Return pointer to first match
      }
    }
  }

  return result;  // NULL if no match found
}
