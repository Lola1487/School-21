#include <stddef.h>
#include <stdint.h>

#include "../arithmetic/s21_arithmetic.h"
#include "../s21_decimal.h"

// --- Геттеры и сеттеры ---

int s21_get_scale(s21_decimal value) { return (value.bits[3] >> 16) & 0xFF; }

int s21_get_sign(s21_decimal value) { return (value.bits[3] >> 31) & 1; }

void s21_set_scale(s21_decimal *value, int scale) {
  if (value == NULL || scale < 0 || scale > 28) return;
  value->bits[3] =
      (value->bits[3] & ~0x00FF0000U) | ((uint32_t)(scale & 0xFF) << 16);
}

void s21_set_sign(s21_decimal *value, int sign) {
  if (value == NULL) return;
  if (sign) {
    value->bits[3] |= (1U << 31);
  } else {
    value->bits[3] &= ~(1U << 31);
  }
}

int s21_is_zero(s21_decimal value) {
  return (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0);
}

int s21_is_nan(s21_decimal value) {
  int scale = s21_get_scale(value);
  return (scale > 28) ? 1 : 0;
}

// --- Арифметические помощники ---

int s21_mul_by_ten(s21_decimal *value) {
  if (value == NULL) return 1;
  uint64_t carry = 0;
  for (int i = 0; i < 3; i++) {
    uint64_t cur = (uint64_t)value->bits[i] * 10 + carry;
    value->bits[i] = (uint32_t)(cur & 0xFFFFFFFF);
    carry = cur >> 32;
  }
  return (carry != 0) ? 1 : 0;
}

int s21_shift_left(s21_decimal *value) {
  if (value == NULL) return 1;
  uint64_t carry = 0;
  for (int i = 0; i < 3; i++) {
    uint64_t cur = ((uint64_t)value->bits[i] << 1) | carry;
    value->bits[i] = (uint32_t)(cur & 0xFFFFFFFF);
    carry = cur >> 32;
  }
  return (carry != 0) ? 1 : 0;
}

void s21_shift_right(s21_decimal *value) {
  if (value == NULL) return;
  uint32_t borrow = 0;
  for (int i = 2; i >= 0; i--) {
    uint32_t cur = value->bits[i];
    value->bits[i] = (cur >> 1) | (borrow << 31);
    borrow = cur & 1;
  }
}

void s21_set_bit(s21_decimal *value, int position) {
  if (value == NULL || position < 0 || position >= 96) return;
  int word = position / 32;
  int bit = position % 32;
  if (word < 3) value->bits[word] |= (1U << bit);
}

int s21_add_simple(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result) {
  if (result == NULL) return 1;
  uint64_t carry = 0;
  for (int i = 0; i < 3; i++) {
    uint64_t sum =
        (uint64_t)value_1.bits[i] + (uint64_t)value_2.bits[i] + carry;
    result->bits[i] = (uint32_t)(sum & 0xFFFFFFFF);
    carry = sum >> 32;
  }
  return (carry != 0) ? 1 : 0;
}

void s21_sub_simple(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result) {
  if (result == NULL) return;
  uint64_t borrow = 0;
  for (int i = 0; i < 3; i++) {
    uint64_t a = (uint64_t)value_1.bits[i];
    uint64_t b = (uint64_t)value_2.bits[i];
    if (a < b + borrow) {
      result->bits[i] = (uint32_t)((a + (1ULL << 32)) - b - borrow);
      borrow = 1;
    } else {
      result->bits[i] = (uint32_t)(a - b - borrow);
      borrow = 0;
    }
  }
}

// Сравнение ТОЛЬКО мантисс (без нормализации!)
int s21_compare_absolute(s21_decimal value_1, s21_decimal value_2) {
  for (int i = 2; i >= 0; i--) {
    if (value_1.bits[i] > value_2.bits[i]) return 1;
    if (value_1.bits[i] < value_2.bits[i]) return -1;
  }
  return 0;
}

// --- Масштабирование ---

int s21_normalize_scales(s21_decimal *value_1, s21_decimal *value_2) {
  if (value_1 == NULL || value_2 == NULL) return 1;
  int scale1 = s21_get_scale(*value_1);
  int scale2 = s21_get_scale(*value_2);

  while (scale1 < scale2 && scale1 <= 28) {
    if (s21_mul_by_ten(value_1)) break;
    scale1++;
  }
  while (scale2 < scale1 && scale2 <= 28) {
    if (s21_mul_by_ten(value_2)) break;
    scale2++;
  }

  s21_set_scale(value_1, scale1);
  s21_set_scale(value_2, scale2);

  return (scale1 > 28 || scale2 > 28) ? 1 : 0;
}

int s21_decimal_leveling(s21_decimal *value_1, s21_decimal *value_2) {
  return s21_normalize_scales(value_1, value_2);
}

int s21_remove_trailing_zeros(s21_decimal *value) {
  if (value == NULL) return 1;
  int scale = s21_get_scale(*value);
  while (scale > 0) {
    // Проверяем, делится ли число на 10
    uint64_t remainder = 0;
    for (int i = 2; i >= 0; i--) {
      uint64_t cur = (uint64_t)value->bits[i] + (remainder << 32);
      remainder = cur % 10;
    }
    if (remainder != 0) break;
    // Делим на 10
    uint64_t rem = 0;
    for (int i = 2; i >= 0; i--) {
      uint64_t cur = (uint64_t)value->bits[i] + (rem << 32);
      value->bits[i] = (uint32_t)(cur / 10);
      rem = cur % 10;
    }
    scale--;
  }
  s21_set_scale(value, scale);
  return 0;
}

// Уменьшение масштаба (деление на 10)
int s21_decrease_scale(s21_decimal *result) {
  if (result == NULL) return 1;
  int scale = s21_get_scale(*result);
  if (scale <= 0) return 1;

  uint64_t remainder = 0;
  for (int i = 2; i >= 0; i--) {
    uint64_t cur = (uint64_t)result->bits[i] + (remainder << 32);
    result->bits[i] = (uint32_t)(cur / 10);
    remainder = cur % 10;
  }

  s21_set_scale(result, scale - 1);
  return 0;
}

int s21_int256_binary_compare(s21_decimal value_1, s21_decimal value_2) {
  // Для бинарного сравнения используем просто побитовое
  return s21_compare_absolute(value_1, value_2);
}
