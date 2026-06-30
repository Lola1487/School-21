#include <stddef.h>
#include <stdint.h>

#include "../s21_decimal.h"
#include "s21_arithmetic.h"

static int mul_by_10(s21_decimal *value) {
  uint64_t carry = 0;
  for (int i = 0; i < 3; i++) {
    uint64_t cur = (uint64_t)value->bits[i] * 10 + carry;
    value->bits[i] = (uint32_t)cur;
    carry = cur >> 32;
  }
  return (carry != 0) ? 1 : 0;
}

static int abs_compare(s21_decimal a, s21_decimal b) {
  for (int i = 2; i >= 0; i--) {
    if (a.bits[i] > b.bits[i]) return 1;
    if (a.bits[i] < b.bits[i]) return -1;
  }
  return 0;
}

static int abs_add(s21_decimal a, s21_decimal b, s21_decimal *res) {
  uint64_t carry = 0;
  for (int i = 0; i < 3; i++) {
    uint64_t sum = (uint64_t)a.bits[i] + b.bits[i] + carry;
    res->bits[i] = (uint32_t)sum;
    carry = sum >> 32;
  }
  return (carry != 0) ? 1 : 0;
}

static void abs_sub(s21_decimal a, s21_decimal b, s21_decimal *res) {
  uint64_t borrow = 0;
  for (int i = 0; i < 3; i++) {
    uint64_t diff = (uint64_t)a.bits[i] - b.bits[i] - borrow;
    if (diff > 0xFFFFFFFFULL) {
      diff += 0x100000000ULL;
      borrow = 1;
    } else {
      borrow = 0;
    }
    res->bits[i] = (uint32_t)diff;
  }
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (result == NULL) return 1;
  *result = (s21_decimal){{0, 0, 0, 0}};

  if (s21_is_zero(value_2)) return 3;
  if (s21_is_zero(value_1)) {
    s21_set_sign(result, 0);
    return 0;
  }

  int sign1 = s21_get_sign(value_1);
  int sign2 = s21_get_sign(value_2);
  int result_sign = sign1 ^ sign2;

  s21_decimal abs1 = value_1;
  s21_decimal abs2 = value_2;
  s21_set_sign(&abs1, 0);
  s21_set_sign(&abs2, 0);

  int scale1 = s21_get_scale(abs1);
  int scale2 = s21_get_scale(abs2);

  int target_scale = (scale1 > scale2) ? scale1 : scale2;
  while (scale1 < target_scale) {
    if (mul_by_10(&abs1)) return 1;
    scale1++;
  }
  while (scale2 < target_scale) {
    if (mul_by_10(&abs2)) return 1;
    scale2++;
  }

  s21_set_scale(&abs1, 0);
  s21_set_scale(&abs2, 0);

  s21_decimal quotient = {{0, 0, 0, 0}};
  s21_decimal remainder = abs1;

  if (abs_compare(remainder, abs2) >= 0) {
    s21_decimal divisor = abs2;
    int shift = 0;
    while (shift < 96) {
      s21_decimal temp = divisor;
      if (s21_shift_left(&temp)) break;
      if (abs_compare(remainder, temp) < 0) break;
      divisor = temp;
      shift++;
    }

    for (int i = shift; i >= 0; i--) {
      if (abs_compare(remainder, divisor) >= 0) {
        s21_decimal new_rem;
        abs_sub(remainder, divisor, &new_rem);
        remainder = new_rem;
        s21_set_bit(&quotient, i);
      }
      if (i > 0) s21_shift_right(&divisor);
    }
  }

  s21_decimal fractional = {{0, 0, 0, 0}};
  int frac_scale = 0;
  s21_decimal remainder_bak = remainder;
  const int max_scale = 28;

  while (frac_scale < max_scale && !s21_is_zero(remainder_bak)) {
    if (mul_by_10(&remainder_bak)) break;

    int digit = 0;
    while (abs_compare(remainder_bak, abs2) >= 0) {
      s21_decimal new_rem;
      abs_sub(remainder_bak, abs2, &new_rem);
      remainder_bak = new_rem;
      digit++;
    }

    if (mul_by_10(&fractional)) break;
    frac_scale++;

    s21_decimal digit_dec = {{(uint32_t)digit, 0, 0, 0}};
    s21_decimal temp;
    if (abs_add(fractional, digit_dec, &temp)) break;
    fractional = temp;
  }

  s21_decimal result_abs = {{0, 0, 0, 0}};
  s21_decimal scaled_quotient = quotient;
  for (int i = 0; i < frac_scale; i++) {
    if (mul_by_10(&scaled_quotient)) {
      return 1;
    }
  }
  if (abs_add(scaled_quotient, fractional, &result_abs)) return 1;

  if (frac_scale < max_scale && !s21_is_zero(remainder_bak)) {
    s21_decimal next_rem = remainder_bak;
    if (mul_by_10(&next_rem)) {
      s21_decimal one = {{1, 0, 0, 0}};
      s21_decimal rounded;
      if (abs_add(result_abs, one, &rounded)) return 1;
      result_abs = rounded;
    } else {
      s21_decimal half = abs2;
      s21_shift_right(&half);
      if (abs_compare(next_rem, half) >= 0) {
        s21_decimal one = {{1, 0, 0, 0}};
        s21_decimal rounded;
        if (abs_add(result_abs, one, &rounded)) return 1;
        result_abs = rounded;
      }
    }
  }

  s21_set_scale(&result_abs, frac_scale);
  *result = result_abs;
  s21_set_sign(result, result_sign);
  if (s21_is_zero(*result)) s21_set_sign(result, 0);
  return 0;
}
