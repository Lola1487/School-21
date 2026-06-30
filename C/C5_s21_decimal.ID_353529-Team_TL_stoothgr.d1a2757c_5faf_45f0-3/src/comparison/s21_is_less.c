#include "../arithmetic/s21_arithmetic.h"
#include "../s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  if (s21_is_nan(value_1) || s21_is_nan(value_2)) {
    return 0;
  }
  int sign1 = s21_get_sign(value_1);
  int sign2 = s21_get_sign(value_2);
  if (s21_is_zero(value_1) && s21_is_zero(value_2)) {
    return 0;
  }
  if (sign1 && !sign2) {
    return 1;
  }
  if (!sign1 && sign2) {
    return 0;
  }
  s21_decimal v1 = value_1;
  s21_decimal v2 = value_2;
  s21_remove_trailing_zeros(&v1);
  s21_remove_trailing_zeros(&v2);
  s21_decimal_leveling(&v1, &v2);
  int cmp = s21_int256_binary_compare(v1, v2);
  if (sign1 && sign2) {
    return cmp > 0;
  } else {
    return cmp < 0;
  }
}
