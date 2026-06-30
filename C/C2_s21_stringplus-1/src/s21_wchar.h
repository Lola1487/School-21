#ifndef S21_WCHAR_H
#define S21_WCHAR_H

#include <stdbool.h>

#include "s21_string.h"  // For s21_size_t definition and NULL macro

// Wide character type (similar to standard wchar_t)
// The actual size matches typical wchar_t implementations (4 bytes).
typedef int s21_wchar_t;

// Wide integer type (similar to standard wint_t)
typedef unsigned int s21_wint_t;

// Converts wide character string to multibyte string (UTF-8)
s21_size_t s21_wcstombs(char *mbstr, const s21_wchar_t *wcstr,
                        s21_size_t count);

#endif
