#include "../arithmetic/s21_arithmetic.h"
#include "../s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  if (s21_is_nan(value_1) || s21_is_nan(value_2)) {
    return 0;
  }

  if (s21_is_zero(value_1) && s21_is_zero(value_2)) {
    return 1;
  }

  int sign1 = s21_get_sign(value_1);
  int sign2 = s21_get_sign(value_2);

  if (sign1 != sign2) {
    return 0;
  }

  s21_decimal v1 = value_1;
  s21_decimal v2 = value_2;
  s21_decimal_leveling(&v1, &v2);

  for (int i = 0; i < 3; i++) {
    if (v1.bits[i] != v2.bits[i]) {
      return 0;
    }
  }

  return 1;
}
