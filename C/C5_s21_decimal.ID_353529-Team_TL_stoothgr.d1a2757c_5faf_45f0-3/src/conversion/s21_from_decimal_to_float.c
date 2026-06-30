#include <float.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>

#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (dst == NULL) return 1;

  double result = 0.0;

  // Собираем значение по битам, используя ldexp для избежания переполнения long
  // long
  for (int i = 2; i >= 0; i--) {
    for (int bit = 31; bit >= 0; bit--) {
      if ((src.bits[i] >> bit) & 1) {
        int position = i * 32 + bit;
        result += ldexp(1.0, position);
      }
    }
  }

  // Применяем масштаб
  int scale = (src.bits[3] >> 16) & 0xFF;
  for (int i = 0; i < scale; i++) {
    result /= 10.0;
  }

  // Применяем знак
  if ((src.bits[3] >> 31) & 1) {
    result = -result;
  }

  // Проверка на переполнение float
  // LCOV_EXCL_START
  // Эта ветка недостижима, так как макс. decimal (~10^28) < макс. float
  // (~10^38)
  if (fabs(result) > FLT_MAX) {
    return 1;
  }
  // LCOV_EXCL_STOP

  // Проверка на слишком маленькое число (денормализованное)
  if (result != 0.0 && fabs(result) < 1e-28) {
    return 1;
  }

  *dst = (float)result;
  return 0;
}
