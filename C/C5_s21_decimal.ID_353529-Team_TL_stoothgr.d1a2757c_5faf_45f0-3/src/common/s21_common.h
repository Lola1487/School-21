#ifndef S21_COMMON_H
#define S21_COMMON_H

#include "../s21_decimal.h"

int s21_get_scale(s21_decimal value);
int s21_get_sign(s21_decimal value);
void s21_set_scale(s21_decimal *value, int scale);
void s21_set_sign(s21_decimal *value, int sign);
int s21_is_zero(s21_decimal value);
int s21_normalize_scales(s21_decimal *value_1, s21_decimal *value_2);
int s21_remove_trailing_zeros(s21_decimal *value);

int s21_is_nan(s21_decimal value);
int s21_decimal_leveling(s21_decimal *value_1, s21_decimal *value_2);
s21_decimal s21_abs(s21_decimal value);
int s21_int256_binary_compare(s21_decimal value_1, s21_decimal value_2);

#endif
