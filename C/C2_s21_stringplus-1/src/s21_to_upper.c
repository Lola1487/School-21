#include <stdbool.h>
#include <stdlib.h>

#include "s21_string.h"  // Здесь должны быть объявления s21_strlen и s21_NULL

// Указатель на malloc, чтобы можно было подменять в тестах
void *(*malloc_ptr)(size_t) = malloc;

void *s21_to_upper(const char *str) {
  char *result = s21_NULL;
  bool is_error = false;

  if (str == s21_NULL) {
    is_error = true;
  }

  s21_size_t length = 0;
  if (!is_error) {
    length = s21_strlen(str);
    result = (char *)malloc_ptr(length + 1);
    if (result == s21_NULL) {
      is_error = true;
    }
  }

  if (!is_error) {
    for (s21_size_t i = 0; i < length; i++) {
      if (str[i] >= 'a' && str[i] <= 'z') {
        result[i] = str[i] - 32;
      } else {
        result[i] = str[i];
      }
    }
    result[length] = '\0';
  }

  return (void *)result;
}
