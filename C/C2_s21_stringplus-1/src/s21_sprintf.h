#ifndef S21_PRINTF_H
#define S21_PRINTF_H
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_sscanf.h"
#include "s21_string.h"
#include "s21_wchar.h"

// Сокращатель типов переменных, because why not
typedef unsigned int uint;
typedef unsigned short int short_uint;
typedef unsigned long int long_uint;

// Это перечисление отвечает за размер переменных
enum Length {
  regularVariable = 0,  // Если никакой флаг не включён
  shortVariable = 1,    // Если включён флаг h
  longAndWideVariable = 2,  // Если включён флаг l
  longDoubleVariable = 3,   // Если включён флаг L
};

// Дипсик предложил интересную идею: хранить флаги в структуре
typedef struct {
  bool minus;          // Выравнивание по левому краю
  bool plus;           // Вывод плюса
  bool space;          // Вывод пробела
  bool zero;           // Заполнение нулями
  bool hash;           // Альтернативная форма
  uint width;          // Минимальная длина
  bool precision_set;  // Костыль, проверка, что точность была поставлена
  int precision;       // Точность
  enum Length length;  // Размер переменной
  bool capital;  // Заглавные буквы для 16-ричной системы
} format_flags;

bool resize_array(char **buffer, s21_size_t *buf_size,
                  const s21_size_t required_len);

void print_fraction(char **p, const long double fraction,
                    const format_flags flags);
void print_sign(char **p, const bool is_negative, const format_flags flags);
bool print_undefined(const long double val, char **p, const format_flags flags);
void final_conversion_for_signed(char **p, const format_flags flags,
                                 char *start, const bool is_negative);

void digit_converter(uintmax_t val, char **p, const int base,
                     const format_flags flags);
s21_size_t char_converter(char *s, const wchar_t wc);
void partitioner(long double val, bool *is_negative, const format_flags flags,
                 intmax_t *whole, intmax_t *fraction);
char value_to_char(const uint v, const uint base, const format_flags flags);
void left_padding(char **p, const int width, const format_flags flags,
                  const char padding_symbol);
void right_padding(char **p, const int width, const format_flags flags,
                   const char padding_symbol);

void character(const va_list args, char **p, const format_flags flags);
void signed_integer(const va_list args, char **p, const format_flags flags);
void scientific_notation(const va_list args, char **p,
                         const format_flags flags);
void floating_point(const va_list args, char **p, const format_flags flags);
void general_format(const va_list args, char **p, const format_flags flags);
void scientific_general_format(const long double val, char **p, int exponent,
                               const format_flags flags);
void floating_general_format(const long double val, char **p,
                             const format_flags flags);
void unsigned_integer(const va_list args, char **p, const int base,
                      const format_flags flags);
void string(const va_list args, char **p, const format_flags flags);
void address(const va_list args, char **p, const format_flags flags);
void characters_read(const va_list args, const char *start, const char *p,
                     const format_flags flags);
void percent(char **p);

void process_flags(const char **fmt, format_flags *flags);
void process_width(const va_list args, const char **fmt, format_flags *flags);
void process_precision(const va_list args, const char **fmt,
                       format_flags *flags);
void process_length(const char **fmt, format_flags *flags);
void process_specifier(const va_list args, const char *str, const char **fmt,
                       char **p);

int s21_sprintf(char *str, const char *format, ...);

#endif  // S21_PRINTF_H
