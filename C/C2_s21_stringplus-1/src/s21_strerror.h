#ifndef S21_STRERROR_H
#define S21_STRERROR_H

#include "s21_string.h"
// #include <stddef.h>  // Для size_t (если используется)

// Возвращает строковое описание ошибки по коду errnum
char *s21_strerror(int errnum);

// Вспомогательная функция для форматирования (если нужна в других модулях)
// int s21_sprintf(char *str, const char *format, ...);

#endif  // S21_STRERROR_H
