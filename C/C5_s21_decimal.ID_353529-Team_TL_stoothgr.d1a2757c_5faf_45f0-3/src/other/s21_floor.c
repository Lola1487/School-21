#include <stddef.h>
#include <stdint.h>

#include "../arithmetic/s21_arithmetic.h"
#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (result == NULL) return 1;
  *result = (s21_decimal){{0, 0, 0, 0}};
  int scale = s21_get_scale(value);
  int sign = s21_get_sign(value);
  if (scale == 0) {
    *result = value;
    return 0;
  }
  s21_decimal one;
  s21_from_int_to_decimal(1, &one);
  if (sign == 0) {
    s21_truncate(value, result);
  } else {
    s21_truncate(value, result);
    s21_decimal fractional;
    s21_sub(value, *result, &fractional);
    if (!s21_is_zero(fractional)) {
      s21_sub(*result, one, result);
    }
  }
  return 0;
}
