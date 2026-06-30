#include "../arithmetic/s21_arithmetic.h"
#include "../s21_decimal.h"

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int sign1 = s21_get_sign(value_1);
  int sign2 = s21_get_sign(value_2);

  if (sign1 != sign2) {
    return sign1 == 0;  // Положительное > Отрицательного
  }

  s21_decimal v1 = value_1;
  s21_decimal v2 = value_2;
  // Обязательно выравниваем масштабы перед сравнением!
  s21_decimal_leveling(&v1, &v2);

  int cmp = s21_compare_absolute(v1, v2);

  if (sign1 == 0) {
    // Оба положительные: больше то, у чего модуль больше
    return cmp > 0;
  } else {
    // Оба отрицательные: больше то, у чего модуль МЕНЬШЕ
    return cmp < 0;
  }
}
