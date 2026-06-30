#include <stdlib.h>

#include "s21_string.h"

void *s21_to_lower(const char *str) {
  if (str == s21_NULL) {
    return s21_NULL;
  }

  s21_size_t length = s21_strlen(str);
  char *result = (char *)malloc(length + 1);

  if (result == s21_NULL) {
    return s21_NULL;
  }

  for (s21_size_t i = 0; i < length; i++) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      result[i] = str[i] + 32;
    } else {
      result[i] = str[i];
    }
  }

  result[length] = '\0';
  return result;
}
