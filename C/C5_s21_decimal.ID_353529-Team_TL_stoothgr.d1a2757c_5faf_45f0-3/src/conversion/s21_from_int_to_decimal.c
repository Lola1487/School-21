#include <stddef.h>

#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (dst == NULL) return 1;
  dst->bits[0] = 0;
  dst->bits[1] = 0;
  dst->bits[2] = 0;
  dst->bits[3] = 0;
  if (src < 0) {
    dst->bits[3] = (unsigned int)1 << 31;
    if (src == -2147483648) {
      dst->bits[0] = 2147483648U;
    } else {
      dst->bits[0] = (unsigned int)(-src);
    }
  } else {
    dst->bits[0] = (unsigned int)src;
  }
  return 0;
}
