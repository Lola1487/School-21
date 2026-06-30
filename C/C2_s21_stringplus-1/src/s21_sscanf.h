#ifndef S21_SSCANF_H
#define S21_SSCANF_H

#include <float.h>   // Для FLT_MAX, DBL_MAX
#include <limits.h>  // Для лимитов int, long и др.
#include <math.h>    // Для NAN, INFINITY, powl()
#include <stdarg.h>  // Для va_list и вариадических функций
#include <stdlib.h>  // Для free()

#include "s21_string.h"  // Для S21_NULL, s21_strncmp и т.д.
#include "s21_wchar.h"   // Для wide char и wchar_t

enum DataType { REGULAR_CHAR, WIDE_CHAR };
enum NumberFormat { INTEGER_NUMBER, FLOATING_POINT_NUMBER };
enum SpecialNumber { NOT_A_NUMBER_VALUE, INFINITY_VALUE };

struct FormatSpecifier {
  bool suppress_assignment;  // Флаг '*' (пропуск присвоения)
  int width;                 // Максимальная ширина поля
  char length;               // Модификатор длины (h, l, L)
  char format;  // Спецификатор формата (d, s, c и т.д.)
};

/* Объявления функций */

int s21_is_whitespace(int character);
int s21_is_hex_digit(int character);
int s21_is_decimal_digit(int character);
int s21_is_octal_digit(int character);
int s21_char_is_in_set(int character, char* character_set);

// Исправлено: char** вместо const char**
void s21_skip_whitespace_characters(char** string_position);
int s21_assign_parsed_value(char** string_position,
                            struct FormatSpecifier spec_info, va_list args,
                            int* arguments_read);
int s21_parse_format_specifier(struct FormatSpecifier* spec_info,
                               char** format_string);  // ← char**
long s21_string_to_long(const char* string_value, char** end_position,
                        int number_base, int max_width);
int s21_convert_char_to_digit(char character);
long double s21_string_to_long_double(const char* string_value,
                                      char** end_position);
int s21_read_string_or_char(char** string_position,
                            struct FormatSpecifier spec_info,
                            void* output_buffer, enum DataType data_type,
                            bool is_string_format);
int s21_read_pointer_value(char** string_position,
                           struct FormatSpecifier spec_info,
                           void** output_pointer);
bool s21_string_is_special_value(const char* string_value,
                                 enum SpecialNumber special_type);
void s21_process_string_or_char_format(char** string_position,
                                       struct FormatSpecifier spec_info,
                                       va_list args, int* arguments_read);
int s21_parse_and_store_number(char** string_position,
                               struct FormatSpecifier spec_info, va_list args,
                               int* arguments_read,
                               enum NumberFormat number_type);
int s21_detect_number_base(const char* string_value);
int s21_get_base_for_integer_format(char format);
void s21_store_integer_value(long value, char length_modifier, va_list args);
void s21_store_float_value(long double value, char length_modifier,
                           va_list args);

#endif  // S21_SSCANF_H
