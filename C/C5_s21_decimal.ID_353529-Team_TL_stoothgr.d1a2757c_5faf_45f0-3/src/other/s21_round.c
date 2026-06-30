#include <stddef.h>
#include <stdint.h>

#include "../arithmetic/s21_arithmetic.h"
#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  if (result == NULL) return 1;

  // ✅ ИСПРАВЛЕНИЕ: Проверяем на NaN. Если NaN, возвращаем ошибку (1).
  if (s21_is_nan(value)) return 1;

  // Если число равно 0, результат тоже 0
  if (s21_is_zero(value)) {
    *result = (s21_decimal){{0, 0, 0, 0}};
    return 0;
  }

  // Сохраняем знак и работаем с положительным числом
  int sign = s21_get_sign(value);
  s21_decimal temp = value;
  s21_set_sign(&temp, 0);

  // Создаем число 0.5 (мантисса 5, масштаб 1)
  s21_decimal half = {{5, 0, 0, 0x00010000}};
  s21_decimal plus_half;

  // Прибавляем 0.5 к числу
  s21_add(temp, half, &plus_half);

  // Обрезаем дробную часть (функция s21_truncate удаляет всё после запятой)
  // Это эквивалентно округлению до ближайшего целого для положительного числа
  s21_truncate(plus_half, result);

  // Возвращаем исходный знак
  s21_set_sign(result, sign);

  // Если после округления получился 0, знак должен быть положительным
  if (s21_is_zero(*result)) {
    s21_set_sign(result, 0);
  }

  return 0;
}
