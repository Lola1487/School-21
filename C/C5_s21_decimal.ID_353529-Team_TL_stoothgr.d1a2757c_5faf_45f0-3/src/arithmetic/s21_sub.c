#include <stddef.h>
#include <stdint.h>

#include "../s21_decimal.h"
#include "s21_arithmetic.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (result == NULL) return 1;
  *result = (s21_decimal){{0, 0, 0, 0}};

  if (s21_is_zero(value_2)) {
    *result = value_1;
    return 0;
  }
  if (s21_is_zero(value_1)) {
    *result = value_2;
    s21_set_sign(result, !s21_get_sign(value_2));
    return 0;
  }

  int sign1 = s21_get_sign(value_1);
  int sign2 = s21_get_sign(value_2);

  if (sign1 != sign2) {
    s21_set_sign(&value_2, sign1);
    return s21_add(value_1, value_2, result);
  }

  // Нормализуем перед сравнением и вычитанием
  s21_decimal v1 = value_1, v2 = value_2;
  s21_normalize_scales(&v1, &v2);

  int abs_compare = s21_compare_absolute(v1, v2);
  if (abs_compare == 0) {
    *result = (s21_decimal){{0, 0, 0, 0}};
    return 0;
  }

  if (abs_compare > 0) {
    s21_sub_simple(v1, v2, result);
    s21_set_sign(result, sign1);
  } else {
    s21_sub_simple(v2, v1, result);
    s21_set_sign(result, !sign1);
  }

  s21_set_scale(result, s21_get_scale(v1));
  return 0;
}
