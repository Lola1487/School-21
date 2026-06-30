#include "s21_string.h"

void* s21_memset(void* str, int c, s21_size_t n) {
  unsigned char* buffer = (unsigned char*)str;
  unsigned char value = (unsigned char)c;
  for (s21_size_t j = 0; j < n; j++) {
    buffer[j] = value;
  }
  return str;
}
