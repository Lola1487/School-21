#ifndef S21_ARITHMETIC_H
#define S21_ARITHMETIC_H

#include <stdint.h>

#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_add_simple(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result);
int s21_add_with_rounding(s21_decimal value_1, s21_decimal value_2,
                          s21_decimal *result);
int s21_handle_overflow(s21_decimal *result, int sign);
int s21_handle_overflow_mul(s21_decimal value_1, s21_decimal value_2,
                            s21_decimal *result);
int s21_add_product(s21_decimal *result, uint64_t product, int position);
int s21_decrease_scale(s21_decimal *result);
int s21_mul_by_ten(s21_decimal *value);
int s21_long_division(s21_decimal dividend, s21_decimal divisor,
                      s21_decimal *quotient, s21_decimal *remainder);
int s21_is_overflow(s21_decimal value, int sign);
int s21_compare_absolute(s21_decimal value_1, s21_decimal value_2);
int s21_normalize_scales(s21_decimal *value_1, s21_decimal *value_2);
int s21_sub_with_rounding(s21_decimal value_1, s21_decimal value_2,
                          s21_decimal *result);
void s21_sub_simple(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result);

int s21_get_scale(s21_decimal value);
int s21_get_sign(s21_decimal value);
void s21_set_scale(s21_decimal *value, int scale);
void s21_set_sign(s21_decimal *value, int sign);
int s21_is_zero(s21_decimal value);

int s21_remove_trailing_zeros(s21_decimal *value);

int s21_is_nan(s21_decimal value);
int s21_decimal_leveling(s21_decimal *value_1, s21_decimal *value_2);
int s21_int256_binary_compare(s21_decimal value_1, s21_decimal value_2);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

int s21_shift_left(s21_decimal *value);
void s21_shift_right(s21_decimal *value);
void s21_set_bit(s21_decimal *value, int position);

#endif
