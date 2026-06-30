#include <stddef.h>

#include "../arithmetic/s21_arithmetic.h"
#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (result == NULL) return 1;
  *result = value;
  int current_sign = s21_get_sign(value);
  s21_set_sign(result, !current_sign);
  return 0;
}
