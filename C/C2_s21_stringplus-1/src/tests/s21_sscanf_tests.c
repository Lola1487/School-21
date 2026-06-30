#include <float.h>
#include <wchar.h>

#include "../s21_sscanf.h"
#include "s21_test_runner.h"

/* Test for s21_is_whitespace */
START_TEST(s21_is_whitespace_test) {
  int c1 = ' ';
  int c2 = '\t';
  int c3 = '\0';
  int c4 = 'y';

  int result1 = s21_is_whitespace(c1);
  int result2 = s21_is_whitespace(c2);
  int result3 = s21_is_whitespace(c3);
  int result4 = s21_is_whitespace(c4);

  ck_assert_int_eq(result1, 1);
  ck_assert_int_eq(result2, 1);
  ck_assert_int_eq(result3, 0);
  ck_assert_int_eq(result4, 0);
}
END_TEST

/* Test for s21_parse_format_specifier */
START_TEST(s21_parse_format_specifier_test) {
  struct FormatSpecifier spec = {0};  // ✅ Обнуление — правильно!
  char *format = "%*5ld";

  int result = s21_parse_format_specifier(&spec, &format);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(spec.suppress_assignment, 1);
  ck_assert_int_eq(spec.width, 5);
  ck_assert_int_eq(spec.length, 'l');
  ck_assert_int_eq(spec.format, 'd');
}
END_TEST

/* Test for s21_read_string_or_char */
START_TEST(s21_read_string_or_char_test) {
  struct FormatSpecifier spec = {
      .suppress_assignment = false, .width = 5, .length = '\0', .format = 's'};
  char *input = "   qwertyuiop";
  char output[20] = {0};

  s21_read_string_or_char(&input, spec, output, REGULAR_CHAR, true);

  ck_assert_str_eq(output, "qwert");
  ck_assert_str_eq(input, "yuiop");
}
END_TEST

/* Test for s21_string_to_long */
START_TEST(s21_string_to_long_test) {
  long a, b;
  char *end1, *end2;

  a = strtol("12345", &end1, 0);
  b = s21_string_to_long("12345", &end2, 0, 0);

  ck_assert_int_eq(a, b);
  ck_assert_ptr_eq(end1, end2);
}
END_TEST

/* Test for s21_string_to_long_double */
START_TEST(s21_string_to_long_double_test) {
  long double a, b;
  char *end1, *end2;

  a = strtold("123.45", &end1);
  b = s21_string_to_long_double("123.45", &end2);

  ck_assert_ldouble_eq_tol(a, b, 1e-6);
  ck_assert_ptr_eq(end1, end2);
}
END_TEST

/* Test for s21_read_pointer_value */
START_TEST(s21_read_pointer_value_test) {
  void *ptr1, *ptr2;
  char *input = "0x1234";
  struct FormatSpecifier spec = {
      .suppress_assignment = false, .width = 0, .length = '\0', .format = 'p'};

  s21_read_pointer_value(&input, spec, &ptr1);
  sscanf("0x1234", "%p", &ptr2);

  ck_assert_ptr_eq(ptr1, ptr2);
}
END_TEST

/* Test for s21_sscanf - reading integers */
START_TEST(s21_sscanf_read_integer_test) {
  int a = 0, b = 0;
  const char *input = "42 123";
  const char *format = "%d %d";

  int result = s21_sscanf(input, format, &a, &b);

  ck_assert_int_eq(result, 2);
  ck_assert_int_eq(a, 42);
  ck_assert_int_eq(b, 123);
}
END_TEST

/* Test for s21_sscanf - reading floating-point numbers */
START_TEST(s21_sscanf_read_float_test) {
  float a = 0.0f, b = 0.0f;
  const char *input = "3.14 2.71";
  const char *format = "%f %f";

  int result = s21_sscanf(input, format, &a, &b);

  ck_assert_int_eq(result, 2);
  ck_assert_float_eq_tol(a, 3.14f, 1e-6);
  ck_assert_float_eq_tol(b, 2.71f, 1e-6);
}
END_TEST

/* Test for s21_sscanf - reading strings */
START_TEST(s21_sscanf_read_string_test) {
  char str1[20] = {0}, str2[20] = {0};
  const char *input = "Hello World";
  const char *format = "%s %s";

  int result = s21_sscanf(input, format, str1, str2);

  ck_assert_int_eq(result, 2);
  ck_assert_str_eq(str1, "Hello");
  ck_assert_str_eq(str2, "World");
}
END_TEST

/* Test for s21_sscanf - reading pointers */
START_TEST(s21_sscanf_read_pointer_test) {
  void *ptr1 = NULL, *ptr2 = NULL;
  const char *input = "0x1234 0x5678";
  const char *format = "%p %p";

  int result = s21_sscanf(input, format, &ptr1, &ptr2);

  ck_assert_int_eq(result, 2);
  ck_assert_ptr_eq(ptr1, (void *)0x1234);
  ck_assert_ptr_eq(ptr2, (void *)0x5678);
}
END_TEST

/* Test for s21_sscanf - reading mixed types */
START_TEST(s21_sscanf_read_mixed_test) {
  int a = 0;
  float b = 0.0f;
  char str[20] = {0};
  const char *input = "42 3.14 Hello";
  const char *format = "%d %f %s";

  int result = s21_sscanf(input, format, &a, &b, str);

  ck_assert_int_eq(result, 3);
  ck_assert_int_eq(a, 42);
  ck_assert_float_eq_tol(b, 3.14f, 1e-6);
  ck_assert_str_eq(str, "Hello");
}
END_TEST

/* Test for s21_sscanf - reading with suppressed assignment */
START_TEST(s21_sscanf_suppressed_assignment_test) {
  int a = 0;
  const char *input = "42 123";
  const char *format = "%*d %d";

  int result = s21_sscanf(input, format, &a);

  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(a, 123);
}
END_TEST

/* Test for s21_sscanf - reading with width specifier */
START_TEST(s21_sscanf_width_specifier_test) {
  char str[20] = {0};
  const char *input = "HelloWorld";
  const char *format = "%5s";

  int result = s21_sscanf(input, format, str);

  ck_assert_int_eq(result, 1);
  ck_assert_str_eq(str, "Hello");
}
END_TEST

/* Test for s21_sscanf - reading with invalid format */
START_TEST(s21_sscanf_invalid_format_test) {
  int a = 0;
  const char *input = "42";
  const char *format = "%k";

  int result = s21_sscanf(input, format, &a);

  ck_assert_int_eq(result, 0);
}
END_TEST

/* Test for s21_sscanf - reading empty input */
START_TEST(s21_sscanf_empty_input_test) {
  int a = 0;
  const char *input = "";
  const char *format = "%d";

  int result = s21_sscanf(input, format, &a);

  ck_assert_int_eq(result, -1);
}
END_TEST

/* Test for s21_sscanf - reading NaN */
START_TEST(s21_sscanf_read_nan_test) {
  float a = 0.0f;
  const char *input = "nan";
  const char *format = "%f";

  int result = s21_sscanf(input, format, &a);

  ck_assert_int_eq(result, 1);
  ck_assert(isnan(a));
}
END_TEST

/* Test for s21_sscanf - reading Infinity */
START_TEST(s21_sscanf_read_inf_test) {
  float a = 0.0f;
  const char *input = "inf";
  const char *format = "%f";

  int result = s21_sscanf(input, format, &a);

  ck_assert_int_eq(result, 1);
  ck_assert(isinf(a));
}
END_TEST

/* Test for s21_sscanf - reading scientific notation */
START_TEST(s21_sscanf_read_scientific_test) {
  float a = 0.0f;
  const char *input = "1.23e-10";
  const char *format = "%f";

  int result = s21_sscanf(input, format, &a);

  ck_assert_int_eq(result, 1);
  ck_assert_float_eq_tol(a, 1.23e-10f, 1e-6);
}
END_TEST

/* Test for s21_sscanf - reading hexadecimal numbers */
START_TEST(s21_sscanf_read_hex_test) {
  unsigned int a = 0, b = 0;
  const char *input = "0x1A 0x2B";
  const char *format = "%x %x";

  int result = s21_sscanf(input, format, &a, &b);

  ck_assert_int_eq(result, 2);
  ck_assert_uint_eq(a, 0x1A);
  ck_assert_uint_eq(b, 0x2B);
}
END_TEST

/* Test for s21_sscanf - reading octal numbers */
START_TEST(s21_sscanf_read_octal_test) {
  unsigned int a = 0, b = 0;
  const char *input = "0123 0456";
  const char *format = "%o %o";

  int result = s21_sscanf(input, format, &a, &b);

  ck_assert_int_eq(result, 2);
  ck_assert_uint_eq(a, 0123);
  ck_assert_uint_eq(b, 0456);
}
END_TEST

/* Test for s21_sscanf - reading with complex format */
START_TEST(s21_sscanf_complex_format_test) {
  int a = 0;
  float b = 0.0f;
  char str[20] = {0};
  const char *input = "42 3.14 Hello";
  const char *format = "%d %f %5s";

  int result = s21_sscanf(input, format, &a, &b, str);

  ck_assert_int_eq(result, 3);
  ck_assert_int_eq(a, 42);
  ck_assert_float_eq_tol(b, 3.14f, 1e-6);
  ck_assert_str_eq(str, "Hello");
}
END_TEST

/* Test for s21_sscanf - reading maximum integer value */
START_TEST(s21_sscanf_read_max_int_test) {
  int a = 0;
  const char *input = "2147483647";
  const char *format = "%d";

  int result = s21_sscanf(input, format, &a);

  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(a, INT_MAX);
}
END_TEST

/* Test for s21_sscanf - reading minimum integer value */
START_TEST(s21_sscanf_read_min_int_test) {
  int a = 0;
  const char *input = "-2147483648";
  const char *format = "%d";

  int result = s21_sscanf(input, format, &a);

  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(a, INT_MIN);
}
END_TEST

/* Test for s21_sscanf - reading maximum unsigned integer value */
START_TEST(s21_sscanf_read_max_unsigned_test) {
  unsigned int a = 0;
  const char *input = "4294967295";
  const char *format = "%u";

  int result = s21_sscanf(input, format, &a);

  ck_assert_int_eq(result, 1);
  ck_assert_uint_eq(a, UINT_MAX);
}
END_TEST

/* Test for s21_sscanf - reading maximum float value */
START_TEST(s21_sscanf_read_max_float_test) {
  float a = 0.0f;
  const char *input = "3.402823e+38";
  const char *format = "%f";

  int result = s21_sscanf(input, format, &a);

  ck_assert_int_eq(result, 1);
  float relative_error = fabsf((a - FLT_MAX) / FLT_MAX);
  ck_assert(relative_error < 1e-6);
}
END_TEST

/* Test for s21_sscanf - reading numbers with leading zeros */
START_TEST(s21_sscanf_read_leading_zeros_test) {
  int a = 0;
  const char *input = "00123";
  const char *format = "%d";

  int result = s21_sscanf(input, format, &a);

  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(a, 123);
}
END_TEST

/* Test for s21_sscanf - reading numbers with spaces */
START_TEST(s21_sscanf_read_spaces_test) {
  int a = 0, b = 0;
  const char *input = "   42   123";
  const char *format = "%d %d";

  int result = s21_sscanf(input, format, &a, &b);

  ck_assert_int_eq(result, 2);
  ck_assert_int_eq(a, 42);
  ck_assert_int_eq(b, 123);
}
END_TEST

/* Test for s21_sscanf - reading numbers with invalid characters */
START_TEST(s21_sscanf_read_invalid_characters_test) {
  int a = 0;
  const char *input = "42abc";
  const char *format = "%d";

  int result = s21_sscanf(input, format, &a);

  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(a, 42);
}
END_TEST

/* Test for s21_sscanf - reading invalid floating-point number */
START_TEST(s21_sscanf_read_invalid_float_test) {
  float a = 0.0f;
  const char *input = "abc";
  const char *format = "%f";

  int result = s21_sscanf(input, format, &a);

  ck_assert_int_eq(result, 0);
}
END_TEST

/* Test for s21_sscanf - reading invalid integer */
START_TEST(s21_sscanf_read_invalid_int_test) {
  int a = 0;
  const char *input = "abc";
  const char *format = "%d";

  int result = s21_sscanf(input, format, &a);

  ck_assert_int_eq(result, 0);
}
END_TEST

/* Test for s21_sscanf - reading wide characters */
START_TEST(s21_sscanf_read_wide_char_test) {
  wchar_t wc = 0;
  const char *input = "A";
  const char *format = "%lc";

  int result = s21_sscanf(input, format, &wc);

  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(wc, L'A');
}
END_TEST

/* Test for s21_sscanf - reading wide strings */
START_TEST(s21_sscanf_read_wide_string_test) {
  wchar_t ws[20] = {0};
  const char *input = "Hello";
  const char *format = "%ls";

  int result = s21_sscanf(input, format, ws);

  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(wcscmp(ws, L"Hello"), 0);
}
END_TEST

/* Test for octal number detection (base 8) */
START_TEST(test_octal_numbers) {
  const char *valid_octal = "0123";
  const char *zero_only = "0";
  const char *max_digit = "07";
  const char *invalid_digit = "08";

  int base_valid = s21_detect_number_base(valid_octal);
  int base_zero = s21_detect_number_base(zero_only);
  int base_max = s21_detect_number_base(max_digit);
  int base_invalid = s21_detect_number_base(invalid_digit);

  ck_assert_int_eq(base_valid, 8);
  ck_assert_int_eq(base_zero, 8);
  ck_assert_int_eq(base_max, 8);
  ck_assert_int_eq(base_invalid, 8);
}
END_TEST

/* Test for decimal number detection (base 10) */
START_TEST(test_decimal_numbers) {
  const char *standard_num = "123";
  const char *positive_num = "+42";
  const char *negative_num = "-100";
  const char *single_digit = "9";

  int base_standard = s21_detect_number_base(standard_num);
  int base_positive = s21_detect_number_base(positive_num);
  int base_negative = s21_detect_number_base(negative_num);
  int base_single = s21_detect_number_base(single_digit);

  ck_assert_int_eq(base_standard, 10);
  ck_assert_int_eq(base_positive, 10);
  ck_assert_int_eq(base_negative, 10);
  ck_assert_int_eq(base_single, 10);
}
END_TEST

/* Test for hexadecimal number detection (base 16) */
START_TEST(test_hex_numbers) {
  const char *lowercase_hex = "0x1A";
  const char *uppercase_hex = "0XFF";
  const char *invalid_hex = "0xG";
  const char *zero_hex = "0x0";

  int base_lower = s21_detect_number_base(lowercase_hex);
  int base_upper = s21_detect_number_base(uppercase_hex);
  int base_invalid = s21_detect_number_base(invalid_hex);
  int base_zero = s21_detect_number_base(zero_hex);

  ck_assert_int_eq(base_lower, 16);
  ck_assert_int_eq(base_upper, 16);
  ck_assert_int_eq(base_invalid, 16);
  ck_assert_int_eq(base_zero, 16);
}
END_TEST

/* Test for invalid number formats */
START_TEST(test_invalid_formats) {
  const char *binary_num = "0b101";
  const char *no_prefix = "x123";
  const char *empty_str = "";
  const char *non_numeric = "abc";

  int base_binary = s21_detect_number_base(binary_num);
  int base_no_prefix = s21_detect_number_base(no_prefix);
  int base_empty = s21_detect_number_base(empty_str);
  int base_non_num = s21_detect_number_base(non_numeric);

  ck_assert_int_eq(base_binary, -1);
  ck_assert_int_eq(base_no_prefix, -1);
  ck_assert_int_eq(base_empty, -1);
  ck_assert_int_eq(base_non_num, -1);
}
END_TEST

/* Test for invalid string to long */
START_TEST(test_s21_string_to_long_invalid) {
  char *input = "abc";
  char *end;

  long val = s21_string_to_long(input, &end, 10, 0);

  ck_assert_int_eq(val, 0);
  ck_assert_ptr_eq(end, input);
}
END_TEST

/* Test for %n after successful parse */
START_TEST(test_s21_sscanf_n_after_success) {
  const char *input = "123 abc";
  int num = 0, pos = 0;

  s21_sscanf(input, "%d %n", &num, &pos);

  ck_assert_int_eq(num, 123);
  ck_assert_int_eq(pos, 4);
}
END_TEST

/* Test for %n after parse failure */
START_TEST(test_s21_sscanf_n_after_error) {
  const char *input = "abc 123";
  int num = 0, pos = 0;

  s21_sscanf(input, "%d %n", &num, &pos);

  ck_assert_int_eq(num, 0);
  ck_assert_int_eq(pos, 0);
}
END_TEST

/* Test hex base detection */
START_TEST(test_s21_detect_base_hex) {
  ck_assert_int_eq(s21_detect_number_base("0x1F"), 16);
  ck_assert_int_eq(s21_detect_number_base("0XFF"), 16);
}
END_TEST

/* Test string reading with width */
START_TEST(test_s21_read_string_width) {
  char buf[10] = {0};
  char *input = "HelloWorld";
  struct FormatSpecifier spec = {.width = 5, .format = 's'};

  s21_read_string_or_char(&input, spec, buf, REGULAR_CHAR, true);

  ck_assert_str_eq(buf, "Hello");
  ck_assert_str_eq(input, "World");
}
END_TEST

/* Test negative long */
START_TEST(test_s21_string_to_long_negative) {
  const char *input = "-12345";
  char *end_ptr;
  long result = s21_string_to_long(input, &end_ptr, 10, 0);
  ck_assert_int_eq(result, -12345);
  ck_assert_ptr_eq(end_ptr, input + 6);
}
END_TEST

/* Test positive sign */
START_TEST(test_s21_string_to_long_positive_sign) {
  const char *input = "+12345";
  char *end_ptr;
  long result = s21_string_to_long(input, &end_ptr, 10, 0);
  ck_assert_int_eq(result, 12345);
  ck_assert_ptr_eq(end_ptr, input + 6);
}
END_TEST

/* Test sign only */
START_TEST(test_s21_string_to_long_sign_only) {
  const char *input = "-";
  char *end_ptr;
  long result = s21_string_to_long(input, &end_ptr, 10, 0);
  ck_assert_int_eq(result, 0);
  ck_assert_ptr_eq(end_ptr, input + 1);
}
END_TEST

// =========== ДОБАВЛЕННЫЕ ТЕСТЫ ===========

START_TEST(test_s21_sscanf_i_format) {
  int a, b, c;
  const char *input = "123 0123 0x12A";
  const char *format = "%i %i %i";
  int result = s21_sscanf(input, format, &a, &b, &c);
  ck_assert_int_eq(result, 3);
  ck_assert_int_eq(a, 123);
  ck_assert_int_eq(b, 83);
  ck_assert_int_eq(c, 298);
}
END_TEST

START_TEST(test_s21_sscanf_h_modifier) {
  short s;
  int result = s21_sscanf("123", "%hd", &s);
  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(s, 123);
}
END_TEST

START_TEST(test_s21_sscanf_L_modifier) {
  long double ld;
  int result = s21_sscanf("123.45", "%Lf", &ld);
  ck_assert_int_eq(result, 1);
  ck_assert_ldouble_eq_tol(ld, 123.45L, 1e-6);
}
END_TEST

START_TEST(test_s21_sscanf_c_with_width) {
  char c1, c2, c3;
  int result = s21_sscanf("abc", "%c%c%c", &c1, &c2, &c3);
  ck_assert_int_eq(result, 3);
  ck_assert_int_eq(c1, 'a');
  ck_assert_int_eq(c2, 'b');
  ck_assert_int_eq(c3, 'c');
}
END_TEST

START_TEST(test_s21_sscanf_e_format) {
  float f;
  int result = s21_sscanf("1.23e-4", "%e", &f);
  ck_assert_int_eq(result, 1);
  ck_assert_float_eq_tol(f, 1.23e-4f, 1e-6);
}
END_TEST

START_TEST(test_s21_sscanf_n_suppressed) {
  int pos = 3;
  s21_sscanf("hello", "hel%n", &pos);
  ck_assert_int_eq(pos, 3);

  s21_sscanf("hello", "hel%*n", &pos);
  ck_assert_int_eq(pos, 3);
}
END_TEST

// =========== / ДОБАВЛЕННЫЕ ТЕСТЫ ===========

Suite *tests_for_sscanf(void) {
  Suite *s = suite_create("sscanf_tests");
  TCase *tc_sscanf = tcase_create("sscanf_tc");

  tcase_add_test(tc_sscanf, s21_is_whitespace_test);
  tcase_add_test(tc_sscanf, s21_parse_format_specifier_test);
  tcase_add_test(tc_sscanf, s21_read_string_or_char_test);
  tcase_add_test(tc_sscanf, s21_string_to_long_test);
  tcase_add_test(tc_sscanf, s21_string_to_long_double_test);
  tcase_add_test(tc_sscanf, s21_read_pointer_value_test);
  tcase_add_test(tc_sscanf, s21_sscanf_read_integer_test);
  tcase_add_test(tc_sscanf, s21_sscanf_read_float_test);
  tcase_add_test(tc_sscanf, s21_sscanf_read_string_test);
  tcase_add_test(tc_sscanf, s21_sscanf_read_pointer_test);
  tcase_add_test(tc_sscanf, s21_sscanf_read_mixed_test);
  tcase_add_test(tc_sscanf, s21_sscanf_suppressed_assignment_test);
  tcase_add_test(tc_sscanf, s21_sscanf_width_specifier_test);
  tcase_add_test(tc_sscanf, s21_sscanf_invalid_format_test);
  tcase_add_test(tc_sscanf, s21_sscanf_empty_input_test);
  tcase_add_test(tc_sscanf, s21_sscanf_read_nan_test);
  tcase_add_test(tc_sscanf, s21_sscanf_read_inf_test);
  tcase_add_test(tc_sscanf, s21_sscanf_read_scientific_test);
  tcase_add_test(tc_sscanf, s21_sscanf_read_hex_test);
  tcase_add_test(tc_sscanf, s21_sscanf_read_octal_test);
  tcase_add_test(tc_sscanf, s21_sscanf_complex_format_test);
  tcase_add_test(tc_sscanf, s21_sscanf_read_max_int_test);
  tcase_add_test(tc_sscanf, s21_sscanf_read_min_int_test);
  tcase_add_test(tc_sscanf, s21_sscanf_read_max_unsigned_test);
  tcase_add_test(tc_sscanf, s21_sscanf_read_max_float_test);
  tcase_add_test(tc_sscanf, s21_sscanf_read_leading_zeros_test);
  tcase_add_test(tc_sscanf, s21_sscanf_read_spaces_test);
  tcase_add_test(tc_sscanf, s21_sscanf_read_invalid_characters_test);
  tcase_add_test(tc_sscanf, s21_sscanf_read_invalid_float_test);
  tcase_add_test(tc_sscanf, s21_sscanf_read_invalid_int_test);
  tcase_add_test(tc_sscanf, s21_sscanf_read_wide_char_test);
  tcase_add_test(tc_sscanf, s21_sscanf_read_wide_string_test);
  tcase_add_test(tc_sscanf, test_decimal_numbers);
  tcase_add_test(tc_sscanf, test_octal_numbers);
  tcase_add_test(tc_sscanf, test_hex_numbers);
  tcase_add_test(tc_sscanf, test_invalid_formats);
  tcase_add_test(tc_sscanf, test_s21_string_to_long_invalid);
  tcase_add_test(tc_sscanf, test_s21_sscanf_n_after_success);
  tcase_add_test(tc_sscanf, test_s21_sscanf_n_after_error);
  tcase_add_test(tc_sscanf, test_s21_detect_base_hex);
  tcase_add_test(tc_sscanf, test_s21_read_string_width);
  tcase_add_test(tc_sscanf, test_s21_string_to_long_negative);
  tcase_add_test(tc_sscanf, test_s21_string_to_long_positive_sign);
  tcase_add_test(tc_sscanf, test_s21_string_to_long_sign_only);

  tcase_add_test(tc_sscanf, test_s21_sscanf_i_format);
  tcase_add_test(tc_sscanf, test_s21_sscanf_h_modifier);
  tcase_add_test(tc_sscanf, test_s21_sscanf_L_modifier);
  tcase_add_test(tc_sscanf, test_s21_sscanf_c_with_width);
  tcase_add_test(tc_sscanf, test_s21_sscanf_e_format);
  tcase_add_test(tc_sscanf, test_s21_sscanf_n_suppressed);

  suite_add_tcase(s, tc_sscanf);
  return s;
}
