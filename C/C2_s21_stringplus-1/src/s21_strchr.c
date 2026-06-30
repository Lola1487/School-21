#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  unsigned char target = (unsigned char)c;
  int counter = 0;

  while (str[counter] != '\0') {
    if ((unsigned char)str[counter] == target) {
      return (char *)&str[counter];
    }
    counter++;
  }

  if (str[counter] == target) {
    return (char *)&str[counter];
  } else {
    return s21_NULL;
  }
}
