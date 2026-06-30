#include <stddef.h>
#include <stdint.h>

#include "../arithmetic/s21_arithmetic.h"
#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (result == NULL) return 1;
  *result = (s21_decimal){{0, 0, 0, 0}};
  int scale = s21_get_scale(value);
  int sign = s21_get_sign(value);
  if (scale == 0) {
    *result = value;
    return 0;
  }
  s21_decimal temp = value;
  while (scale > 0) {
    uint64_t carry = 0;
    for (int i = 2; i >= 0; i--) {
      uint64_t value64 = (uint64_t)temp.bits[i] + (carry << 32);
      temp.bits[i] = (uint32_t)(value64 / 10);
      carry = value64 % 10;
    }
    scale--;
  }
  s21_set_scale(&temp, 0);
  s21_set_sign(&temp, sign);
  *result = temp;
  return 0;
}
