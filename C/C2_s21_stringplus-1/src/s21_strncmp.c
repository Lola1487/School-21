#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;

  if (n > 0) {
    if (str1 == s21_NULL || str2 == s21_NULL) {
      result = (str1 == str2) ? 0 : ((str1 == s21_NULL) ? -1 : 1);
    } else {
      while (n-- && *str1 && (*str1 == *str2)) {
        str1++;
        str2++;
      }
      result = (n == (s21_size_t)-1)
                   ? 0
                   : (*(unsigned char *)str1 - *(unsigned char *)str2);
    }
  }

  return result;
}
