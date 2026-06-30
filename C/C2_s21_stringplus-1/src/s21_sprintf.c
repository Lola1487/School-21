#include "s21_sprintf.h"

// Изменение размера массива для обработки строк
bool resize_array(char **buffer, s21_size_t *buf_size,
                  const s21_size_t required_len) {
  // Проверяем, а надо ли нам в целом увеличивать
  if (required_len >= *buf_size) {
    do {
      *buf_size *= 2;  // Увеличиваем массив в 2 раза
    } while (required_len >= *buf_size);

    char *new_buf = realloc(*buffer, *buf_size);
    if (!new_buf) {
      // Ошибка
      free(*buffer);
      *buffer = NULL;
      return false;
    }

    *buffer = new_buf;
  }

  return true;  // Всё получилось
}

void print_fraction(char **p, const long double fraction,
                    const format_flags flags) {
  if (fraction != 0)
    digit_converter(fraction, p, 10, flags);
  else
    for (int i = 0; i < flags.precision; i++) *(*p)++ = '0';
}

void print_sign(char **p, const bool is_negative, const format_flags flags) {
  if (is_negative)
    *(*p)++ = '-';
  else if (flags.plus)
    *(*p)++ = '+';
  else if (flags.space)
    *(*p)++ = ' ';
  else if (flags.zero)
    *(*p)++ = '0';
}

// Печать NaN'ов
bool print_undefined(const long double val, char **p,
                     const format_flags flags) {
  const char *answer = NULL;
  if (isnan(val))
    answer = flags.capital ? "NAN" : "nan";
  else if (isinf(val))
    answer = flags.capital ? "INF" : "inf";
  else
    return false;

  char *start = *p;

  for (int i = 2; i >= 0; i--) *(*p)++ = answer[i];
  if (signbit(val))
    *(*p)++ = '-';
  else if (flags.plus)
    *(*p)++ = '+';
  else if (flags.space)
    *(*p)++ = ' ';

  right_padding(p, flags.width - (*p - start), flags, ' ');

  char *end = *p - 1;
  while (start < end) {
    const char tmp = *start;
    *start++ = *end;
    *end-- = tmp;
  }

  left_padding(p, flags.width - (*p - start), flags, ' ');
  **p = '\0';
  return true;
}

void final_conversion_for_signed(char **p, const format_flags flags,
                                 char *start, const bool is_negative) {
  const char padding_symbol = flags.zero ? '0' : ' ';
  if (padding_symbol == '0')  // Если символ 0, то лучше сейчас его выводить
    right_padding(p, flags.width - (*p - start + 1), flags, padding_symbol);
  print_sign(p, is_negative, flags);
  if (padding_symbol == ' ')  // Иначе печатаем пробелы после знака
    right_padding(p, flags.width - (*p - start), flags, padding_symbol);

  char *end = *p - 1;
  while (start < end) {
    const char tmp = *start;
    *start++ = *end;
    *end-- = tmp;
  }

  // Если у нас выравнивание по левой стороне, то добавляем пробелы сейчас
  left_padding(p, flags.width - (*p - start), flags, ' ');
  **p = '\0';
}

// Добавление цифры в строку
void digit_converter(uintmax_t val, char **p, const int base,
                     const format_flags flags) {
  if (val == 0) {
    *(*p)++ = '0';
    return;
  }

  while (val != 0) {
    const uint rem = val % base;
    *(*p)++ = value_to_char(rem, base, flags);
    val /= base;
  }
}

// Конвертация UTF-8-символа в последовательность char-символов
s21_size_t char_converter(char *s, const s21_wchar_t wc) {
  if (!s) return 0;
  if (wc < 0x80) {
    s[0] = wc;
    return 1;
  }
  if (wc < 0x800) {
    s[0] = 0xC0 | (wc >> 6 & 0x1F);
    s[1] = 0x80 | (wc & 0x3F);
    return 2;
  }
  if (wc < 0x10000) {
    s[0] = 0xE0 | (wc >> 12 & 0x0F);
    s[1] = 0x80 | (wc >> 6 & 0x3F);
    s[2] = 0x80 | (wc & 0x3F);
    return 3;
  }
  if (wc <= 0x10FFFF) {
    s[0] = 0xF0 | (wc >> 18 & 0x07);
    s[1] = 0x80 | (wc >> 12 & 0x3F);
    s[2] = 0x80 | (wc >> 6 & 0x3F);
    s[3] = 0x80 | (wc & 0x3F);
    return 4;
  }

  // Некорректный символ
  return (s21_size_t)-1;
}

// Разделение дробного числа на целую и дробную части
void partitioner(long double val, bool *is_negative, const format_flags flags,
                 intmax_t *whole, intmax_t *fraction) {
  if (val < 0) {
    *is_negative = true;
    val = -val;
  } else
    *is_negative = false;

  *whole = (intmax_t)val;
  val -= *whole;

  const long double scale = pow(10, flags.precision);
  *fraction = (intmax_t)round(val * scale);

  if (*fraction >= (intmax_t)scale) {
    (*whole)++;
    *fraction -= (intmax_t)scale;
  }
}

int get_integer_length(const int val) {
  int abs_integer = abs(val);
  int len = 0;
  if (abs_integer == 0)
    len = 1;
  else
    while (abs_integer != 0) {
      abs_integer /= 10;
      len++;
    }

  return len;
}

char value_to_char(const uint v, const uint base, const format_flags flags) {
  // Это будет побыстрее, пускай это явный оверкилл
  const char lookup[16] = {
      [0] = '0',  [1] = '1',  [2] = '2',  [3] = '3', [4] = '4',  [5] = '5',
      [6] = '6',  [7] = '7',  [8] = '8',  [9] = '9', [10] = 'A', [11] = 'B',
      [12] = 'C', [13] = 'D', [14] = 'E', [15] = 'F'};
  char value = lookup[v];

  // Если в условное десятичное число передали букву, сделай ошибку
  if (v > base)
    value = 0;  // 0 будет кодом ошибки
  else if ('A' <= value && value <= 'F' && flags.capital == false)
    value += 32;  // +32 делает букву прописной
  return value;
}

// Выравнивание по левому краю (добавление пробелов справа)
void left_padding(char **p, const int width, const format_flags flags,
                  const char padding_symbol) {
  if (flags.minus)
    for (int i = 0; i < width; i++) *(*p)++ = padding_symbol;
}

// Выравнивание по правому краю (добавление пробелов слева)
void right_padding(char **p, const int width, const format_flags flags,
                   const char padding_symbol) {
  if (!flags.minus)
    for (int i = 0; i < width; i++) *(*p)++ = padding_symbol;
}

void character(const va_list args, char **p, const format_flags flags) {
  // Создадим массив сразу, даже если мы будем работать просто с char
  // Иначе работа с выравниванием будет адом
  char mbbuf[MB_CUR_MAX];
  s21_size_t len = 0;

  if (flags.length == longAndWideVariable) {
    // Получить переменную
    const s21_wint_t wcharacter = va_arg(args, s21_wint_t);

    // Конвертация в мультибайтовую последовательность,
    // потому что wchar - это не char
    len = char_converter(mbbuf, wcharacter);
    if (len == (s21_size_t)-1) return;  // Ошибка
  } else {
    // Получить переменную
    mbbuf[0] = (unsigned char)va_arg(args, int);
    len = 1;
  }

  // Подсчёт требуемого количества пробелов
  int padding_width = 0;
  if (flags.width > len) padding_width = flags.width - (int)len;

  right_padding(p, padding_width, flags, ' ');
  for (s21_size_t i = 0; i < len; i++) *(*p)++ = mbbuf[i];
  left_padding(p, padding_width, flags, ' ');

  **p = '\0';
}

void signed_integer(const va_list args, char **p, const format_flags flags) {
  // Получить переменную
  intmax_t val;
  if (flags.length == shortVariable)
    val = (short)va_arg(args, int);
  else if (flags.length == longAndWideVariable)
    val = va_arg(args, long);
  else
    val = va_arg(args, int);

  // Если точность = 0 и значение тоже = 0, то выходим и ничего не печатаем
  if (flags.precision_set && flags.precision == 0 && val == 0) return;

  bool is_negative = false;
  char *start = *p;

  if (val < 0) {
    is_negative = true;
    val = -val;
  }

  digit_converter(val, p, 10, flags);

  const int digits_left = flags.precision - (*p - start);
  if (digits_left > 0 && flags.precision_set)
    right_padding(p, digits_left, flags, '0');
  final_conversion_for_signed(p, flags, start, is_negative);
}

void scientific_notation(const va_list args, char **p,
                         const format_flags flags) {
  long double val;
  if (flags.length == longDoubleVariable)  // Получить переменную
    val = va_arg(args, long double);
  else
    val = va_arg(args, double);
  if (print_undefined(val, p, flags)) return;  // Проверка на nan и inf

  // Получение экспоненты
  int exponent = 0;
  if (val != 0.0) {
    exponent = (int)floor(log10(fabsl(val)));
    val /= pow(10.0, exponent);
  }

  bool is_negative;
  intmax_t whole, fraction;
  partitioner(val, &is_negative, flags, &whole, &fraction);

  char *start = *p;
  bool is_exponent_negative = false;
  if (exponent < 0) {
    is_exponent_negative = true;
    exponent = -exponent;
  }

  // Сначала пишем экспоненту
  digit_converter(exponent, p, 10, flags);
  right_padding(p, 2 - (*p - start), flags, '0');
  *(*p)++ = is_exponent_negative ? '-' : '+';  // Теперь знак экспоненты
  *(*p)++ = flags.capital ? 'E' : 'e';  // Потом символ экспоненты
  print_fraction(p, fraction, flags);  // Затем дробная часть
  if (flags.precision > 0 || flags.hash)  // После этого точка
    *(*p)++ = '.';
  *(*p)++ = '0' + whole;  // Под конец целая часть

  final_conversion_for_signed(p, flags, start, is_negative);
}

void floating_point(const va_list args, char **p, const format_flags flags) {
  long double val;  // Получить переменную
  if (flags.length == longDoubleVariable)
    val = va_arg(args, long double);
  else
    val = va_arg(args, double);
  if (print_undefined(val, p, flags)) return;  // Проверка на nan и inf

  bool is_negative = false;
  char *start = *p;

  intmax_t whole = 0, fraction = 0;
  partitioner(val, &is_negative, flags, &whole, &fraction);

  // Этот ужас нужен для того, чтобы напечатать нули в начале дроби
  const int fraction_len = get_integer_length(fraction);

  // Сначала дробь, потом целая часть, потом перевернём
  print_fraction(p, fraction, flags);
  if (fraction != 0)
    for (int i = 0; i < flags.precision - fraction_len; i++) *(*p)++ = '0';
  if (flags.precision != 0 || flags.hash) *(*p)++ = '.';
  digit_converter(whole, p, 10, flags);

  final_conversion_for_signed(p, flags, start, is_negative);
}

void general_format(const va_list args, char **p, const format_flags flags) {
  long double val;
  if (flags.length == longDoubleVariable)  // Получить переменную
    val = va_arg(args, long double);
  else
    val = va_arg(args, double);
  if (print_undefined(val, p, flags)) return;  // Проверка на nan и inf

  int exponent = 0;  // Получение экспоненты
  long double saved_val = val;
  if (saved_val != 0.0) {
    exponent = (int)floor(log10(fabsl(val)));
    saved_val /= pow(10.0, exponent);
  }

  if (exponent < -4 || exponent >= flags.precision)
    scientific_general_format(saved_val, p, exponent, flags);
  else
    floating_general_format(val, p, flags);
}

void scientific_general_format(const long double val, char **p, int exponent,
                               const format_flags flags) {
  // По сути, эта та же функция, что и scientific_notation,
  // Однако здесь другая логика вывода дробной части и точки
  bool is_negative;
  intmax_t whole, fraction;
  partitioner(val, &is_negative, flags, &whole, &fraction);

  char *start = *p;
  bool is_exponent_negative = false;
  if (exponent < 0) {
    is_exponent_negative = true;
    exponent = -exponent;
  }

  // Надо сократить количество цифр в дробной части
  if (fraction != 0)
    while (fraction % 10 == 0) fraction /= 10;

  while (fraction > pow(10, flags.precision)) fraction /= 10;
  if (fraction > pow(10, flags.precision - 1)) {
    if (fraction % 10 > 5)
      fraction = fraction / 10 + 1;
    else
      fraction /= 10;
  }

  int fraction_len = get_integer_length(fraction);
  if (fraction == 0) fraction_len = 0;

  // Сначала пишем экспоненту
  digit_converter(exponent, p, 10, flags);
  right_padding(p, 2 - (*p - start), flags, '0');
  *(*p)++ = is_exponent_negative ? '-' : '+';  // Теперь знак экспоненты
  *(*p)++ = flags.capital ? 'E' : 'e';  // Потом символ экспоненты

  bool something_printed = false;
  for (int i = 0; i < fraction_len; i++) {  // Затем дробная часть
    const uint rem = fraction % 10;
    *(*p)++ = value_to_char(rem, 10, flags);
    fraction /= 10;
    something_printed = true;
  }

  if (flags.hash || something_printed)  // После этого точка
    *(*p)++ = '.';
  *(*p)++ = '0' + whole;  // Под конец целая часть

  final_conversion_for_signed(p, flags, start, is_negative);
}

void floating_general_format(const long double val, char **p,
                             const format_flags flags) {
  bool is_negative = false;
  char *start = *p;

  intmax_t whole = 0, fraction = 0;
  partitioner(val, &is_negative, flags, &whole, &fraction);

  // Здесь надо учесть сначала количество цифр в целой части,
  // потом из точности вычесть количество чисел
  const int whole_len = get_integer_length(whole);

  // Надо сократить количество цифр в дробной части
  if (fraction != 0)
    while (fraction % 10 == 0) fraction /= 10;

  while (fraction > pow(10, flags.precision - whole_len + 2)) fraction /= 10;
  if (fraction > pow(10, flags.precision - whole_len + 1)) {
    if (fraction % 10 > 5)
      fraction = fraction / 10 + 1;
    else
      fraction /= 10;
  }

  int fraction_len = get_integer_length(fraction);
  if (fraction == 0) fraction_len = 0;
  int zero_padding = flags.precision - whole_len - fraction_len;

  bool something_printed = false;
  for (int i = 0; i < fraction_len; i++) {
    const uint rem = fraction % 10;
    *(*p)++ = value_to_char(rem, 10, flags);
    something_printed = true;
    fraction /= 10;
  }

  if (flags.hash)
    for (int i = 0; i < zero_padding; i++) *(*p)++ = '0';

  if (flags.hash || something_printed || fraction != 0) *(*p)++ = '.';

  digit_converter(whole, p, 10, flags);

  final_conversion_for_signed(p, flags, start, is_negative);
}

void unsigned_integer(const va_list args, char **p, const int base,
                      const format_flags flags) {
  uintmax_t val;  // Получить переменную
  if (flags.length == shortVariable)
    val = (short_uint)va_arg(args, uint);
  else if (flags.length == longAndWideVariable)
    val = va_arg(args, long_uint);
  else
    val = va_arg(args, uint);

  // Если точность = 0 и значение тоже = 0, то выходим и ничего не печатаем
  if (flags.precision_set && flags.precision == 0 && val == 0) return;

  char *start = *p;

  digit_converter(val, p, base, flags);

  const int digits_left = flags.precision - (*p - start);
  if (digits_left > 0 && flags.precision_set)
    right_padding(p, digits_left, flags, '0');

  // Печать 0 и X для 16-ричной системы
  if (flags.hash == true && (base == 8 || base == 16)) {
    if (base == 16) {
      if (flags.capital == true)
        *(*p)++ = 'X';
      else
        *(*p)++ = 'x';
    }
    *(*p)++ = '0';
  }

  const int width = flags.width - (*p - start);
  // Если у нас выравнивание по правой стороне, то лучше добавить пробелы сейчас
  char padding_symbol = ' ';
  if (flags.zero == true) padding_symbol = '0';
  right_padding(p, width, flags, padding_symbol);

  char *end = *p - 1;
  while (start < end) {
    char tmp = *start;
    *start++ = *end;
    *end-- = tmp;
  }

  // Если у нас выравнивание по левой стороне, то добавляем пробелы сейчас
  left_padding(p, width, flags, ' ');
  **p = '\0';
}

void string(const va_list args, char **p, const format_flags flags) {
  s21_size_t buf_size = (flags.precision_set) ? flags.precision + 1 : 64;
  s21_size_t current_length = 0;
  char *temp_buffer = malloc(buf_size);  // Играемся с динамическими массивами
  if (!temp_buffer) return;  // Ошибка

  if (flags.length == longAndWideVariable) {  // Работаем с wchar
    const s21_wchar_t *val = va_arg(args, const s21_wchar_t *);
    if (!val) {
      free(temp_buffer);
      return;
    }

    char mbbuf[MB_CUR_MAX];
    while (*val != L'\0') {
      const s21_size_t len = char_converter(mbbuf, *val++);
      if (len == (s21_size_t)-1) {
        free(temp_buffer);
        return;
      }
      // Если длина строки будет превышать точность, то сокращаем её
      if (current_length + len >= buf_size - 1 && flags.precision_set) {
        for (s21_size_t i = 0; i < buf_size - 1; i++)
          temp_buffer[current_length++] = mbbuf[i];
        break;
      }
      if (!resize_array(&temp_buffer, &buf_size, current_length + len)) return;
      for (s21_size_t i = 0; i < len; i++)
        temp_buffer[current_length++] = mbbuf[i];
    }
  } else {
    const char *str = va_arg(args, const char *);
    if (!str) {
      free(temp_buffer);
      return;
    }
    while (*str != '\0') {
      if (current_length == (uint)flags.precision && flags.precision_set) break;

      if (!resize_array(&temp_buffer, &buf_size, current_length)) return;
      temp_buffer[current_length++] = *str++;
    }
  }

  int padding_width = 0;
  if (flags.width > current_length)
    padding_width = flags.width - (int)current_length;
  right_padding(p, padding_width, flags, ' ');
  for (s21_size_t i = 0; i < current_length; i++) *(*p)++ = temp_buffer[i];
  left_padding(p, padding_width, flags, ' ');

  **p = '\0';
  free(temp_buffer);
}

void address(const va_list args, char **p, const format_flags flags) {
  // Получить переменную
  void *val = va_arg(args, void *);
  const uintptr_t int_val = (uintptr_t)val;

  char *start = *p;

  if (!val) {                     // Если адрес - NULL
    s21_strncpy(*p, ")lin(", 5);  // Печать (nil)
    *p += 5;                      // Сдвиг *p
  } else {
    digit_converter(int_val, p, 16, flags);  // Вывод в 16-ричной системе
    s21_strncpy(*p, "x0", 2);                // Печать 0x
    *p += 2;                                 // Сдвиг *p
  }
  const int width = flags.width - (*p - start);
  // Если у нас выравнивание по правой стороне, то лучше добавить пробелы сейчас
  right_padding(p, width, flags, ' ');

  char *end = *p - 1;
  while (start < end) {
    const char tmp = *start;
    *start++ = *end;
    *end-- = tmp;
  }

  // Если у нас выравнивание по левой стороне, то добавляем пробелы сейчас
  left_padding(p, width, flags, ' ');
  **p = '\0';
}

void characters_read(const va_list args, const char *start, const char *p,
                     const format_flags flags) {
  // Получить переменную
  if (flags.length == shortVariable) {
    short *val = va_arg(args, short *);
    *val = p - start;
  } else if (flags.length == longAndWideVariable) {
    long *val = va_arg(args, long *);
    *val = p - start;
  } else {
    int *val = va_arg(args, int *);
    *val = p - start;
  }
}

void percent(char **p) { *(*p)++ = '%'; }

void process_flags(const char **fmt, format_flags *flags) {
  // Прочитать флаги а-ля '-', '+' и т.д.
  while (1) {
    switch (**fmt) {
      case '-':
        flags->minus = true;
        break;
      case '+':
        flags->plus = true;
        break;
      case ' ':
        flags->space = true;
        break;
      case '#':
        flags->hash = true;
        break;
      case '0':
        flags->zero = true;
        break;
      default:
        return;
    }
    (*fmt)++;
  }
}

void process_width(const va_list args, const char **fmt, format_flags *flags) {
  // Прочитать длину
  if (**fmt == '*') {
    (*fmt)++;
    const uint val = va_arg(args, uint);
    if (!val) return;

    flags->width = val;
    return;
  }

  // Думаю, здесь стоит использовать sscanf
  uint width = 0;
  s21_sscanf(*fmt, "%u", &width);
  flags->width = width;

  // После прочтения числа его надо подвинуть
  while ('0' <= **fmt && **fmt <= '9') (*fmt)++;
}

void process_precision(const va_list args, const char **fmt,
                       format_flags *flags) {
  // Прочитать точность
  if (**fmt != '.') return;

  flags->precision_set = true;
  (*fmt)++;
  if (**fmt == '*') {
    (*fmt)++;  // Уйди со звёздочки
    const int val = va_arg(args, int);
    // Если точность ниже нуля, то мы игнорируем то, что было введено
    if (!val || val < 0) return;

    flags->precision = val;
    return;
  }

  // Опять же, sscanf
  int precision = 0;
  s21_sscanf(*fmt, "%d", &precision);
  if (precision < 0) return;
  flags->precision = precision;

  // После прочтения числа его надо подвинуть
  while ('0' <= **fmt && **fmt <= '9') (*fmt)++;
}

void process_length(const char **fmt, format_flags *flags) {
  switch (**fmt) {
    case 'h':
      flags->length = shortVariable;
      break;
    case 'l':
      flags->length = longAndWideVariable;
      break;
    case 'L':
      flags->length = longDoubleVariable;
      break;
    default:
      return;
  }
  (*fmt)++;  // Уйди с длины
}

void process_specifier(const va_list args, const char *str, const char **fmt,
                       char **p) {
  (*fmt)++;  // Уйди с процента

  // Чтение флагов
  format_flags flags = {0};  // {0} даёт всем значениям структуры 0
  process_flags(fmt, &flags);
  process_width(args, fmt, &flags);
  process_precision(args, fmt, &flags);
  process_length(fmt, &flags);

  // Здесь стоит использовать switch-case, но это займёт много строк
  // Да и современные компиляторы умеют ускорять else-if до уровня switch-case
  if (**fmt == 'c')
    character(args, p, flags);
  else if (**fmt == 'd' || **fmt == 'i')
    signed_integer(args, p, flags);
  else if (**fmt == 'e' || **fmt == 'E') {
    if (!flags.precision_set) flags.precision = 6;
    if (**fmt == 'E') flags.capital = true;
    scientific_notation(args, p, flags);
  } else if (**fmt == 'f' || **fmt == 'F') {
    if (!flags.precision_set) flags.precision = 6;
    if (**fmt == 'F') flags.capital = true;
    floating_point(args, p, flags);
  } else if (**fmt == 'g' || **fmt == 'G') {
    if (!flags.precision_set) flags.precision = 6;
    if (**fmt == 'G') flags.capital = true;
    general_format(args, p, flags);
  } else if (**fmt == 'o')
    unsigned_integer(args, p, 8, flags);
  else if (**fmt == 's')
    string(args, p, flags);
  else if (**fmt == 'u')
    unsigned_integer(args, p, 10, flags);
  else if (**fmt == 'x' || **fmt == 'X') {
    if (**fmt == 'X') flags.capital = true;
    unsigned_integer(args, p, 16, flags);
  } else if (**fmt == 'p')
    address(args, p, flags);
  else if (**fmt == 'n')
    characters_read(args, str, *p, flags);
  else if (**fmt == '%')
    percent(p);

  (*fmt)++;  // Уйди со спецификатора
}

// Главная функция
int s21_sprintf(char *str, const char *format, ...) {
  if (!str || !format) return -1;

  va_list args;
  va_start(args, format);

  const char *fmt = format;
  char *p = str;

  while (*fmt != '\0') {
    if (*fmt == '%')
      process_specifier(args, str, &fmt, &p);
    else
      *p++ = *fmt++;
  }

  *p = '\0';
  va_end(args);
  return (int)(p - str);  // Количество записанных символов
}
