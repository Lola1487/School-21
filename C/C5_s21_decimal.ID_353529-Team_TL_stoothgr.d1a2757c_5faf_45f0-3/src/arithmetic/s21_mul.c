#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "../arithmetic/s21_arithmetic.h"
#include "../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (result == NULL) return 1;
  *result = (s21_decimal){{0, 0, 0, 0}};

  if (s21_is_zero(value_1) || s21_is_zero(value_2)) {
    return 0;
  }

  int sign1 = s21_get_sign(value_1);
  int sign2 = s21_get_sign(value_2);
  int result_sign = sign1 ^ sign2;
  int scale = s21_get_scale(value_1) + s21_get_scale(value_2);

  uint64_t temp[6] = {0};
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      uint64_t product = (uint64_t)value_1.bits[i] * (uint64_t)value_2.bits[j];
      int pos = i + j;
      uint64_t sum = temp[pos] + (product & 0xFFFFFFFF);
      temp[pos] = sum & 0xFFFFFFFF;
      uint64_t carry = sum >> 32;
      sum = temp[pos + 1] + (product >> 32) + carry;
      temp[pos + 1] = sum & 0xFFFFFFFF;
      carry = sum >> 32;
      if (carry && pos + 2 < 6) {
        temp[pos + 2] += carry;
      }
    }
  }

  while (scale > 0 && (temp[3] != 0 || temp[4] != 0 || temp[5] != 0)) {
    uint64_t remainder = 0;
    for (int k = 5; k >= 0; k--) {
      uint64_t cur = (remainder << 32) | temp[k];
      temp[k] = cur / 10;
      remainder = cur % 10;
    }
    if (remainder > 5 || (remainder == 5 && (temp[0] & 1))) {
      for (int k = 0; k < 6; k++) {
        if (++temp[k] <= 0xFFFFFFFF) break;
      }
      if (temp[3] != 0 || temp[4] != 0 || temp[5] != 0) {
        scale--;
        continue;
      }
    }
    scale--;
  }

  if (temp[3] != 0 || temp[4] != 0 || temp[5] != 0) {
    return result_sign ? 2 : 1;
  }
  if (scale > 28) {
    return result_sign ? 2 : 1;
  }

  result->bits[0] = (uint32_t)temp[0];
  result->bits[1] = (uint32_t)temp[1];
  result->bits[2] = (uint32_t)temp[2];
  result->bits[3] = 0;
  s21_set_scale(result, scale);
  s21_set_sign(result, result_sign);

  if (s21_is_zero(*result)) {
    result->bits[3] = 0;
  }
  return 0;
}
