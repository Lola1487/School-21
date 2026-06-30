#include <stddef.h>
#include <stdint.h>

#include "../arithmetic/s21_arithmetic.h"
#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (dst == NULL) return 1;
  *dst = 0;
  s21_decimal truncated;
  if (s21_truncate(src, &truncated) != 0) return 1;
  if (truncated.bits[1] != 0 || truncated.bits[2] != 0) return 1;
  uint32_t abs_value = truncated.bits[0];
  int sign = s21_get_sign(truncated);
  if (sign == 0) {
    if (abs_value > 2147483647U) return 1;
    *dst = (int)abs_value;
  } else {
    if (abs_value > 2147483648U) return 1;
    if (abs_value == 2147483648U) {
      *dst = -2147483648;
    } else {
      *dst = -(int)abs_value;
    }
  }
  return 0;
}
