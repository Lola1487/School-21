#include <float.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>

#include "../arithmetic/s21_arithmetic.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (dst == NULL) return 1;
  *dst = (s21_decimal){{0, 0, 0, 0}};
  if (isnan(src) || isinf(src)) return 1;
  if (src == 0.0f) {
    s21_set_sign(dst, 0);
    return 0;
  }

  int sign = (src < 0.0f) ? 1 : 0;
  double abs_val = fabs((double)src);
  const double max_decimal = 79228162514264337593543950335.0;  // 2^96 - 1
  if (abs_val > max_decimal) return 1;
  if (abs_val > 0.0 && abs_val < 1e-28) return 1;

  int scale = 0;
  double temp = abs_val;

  // Умножаем, пока число не станет >=1 и не приблизится к целому (разница <
  // 0.1)
  while (scale < 28 && (temp < 1.0 || fabs(temp - round(temp)) > 0.1)) {
    temp *= 10.0;
    scale++;
    if (temp > max_decimal * 10.0) break;
  }

  temp = round(temp);
  if (temp > max_decimal) return 1;

  // Разбиваем 96-битную мантиссу на три 32-битных слова
  double low_part = fmod(temp, 4294967296.0);
  double mid_high = (temp - low_part) / 4294967296.0;
  double mid_part = fmod(mid_high, 4294967296.0);
  double high_part = (mid_high - mid_part) / 4294967296.0;

  dst->bits[0] = (uint32_t)(low_part + 0.5);
  dst->bits[1] = (uint32_t)(mid_part + 0.5);
  dst->bits[2] = (uint32_t)(high_part + 0.5);
  s21_set_scale(dst, scale);
  s21_set_sign(dst, sign);
  s21_remove_trailing_zeros(dst);

  return 0;
}
