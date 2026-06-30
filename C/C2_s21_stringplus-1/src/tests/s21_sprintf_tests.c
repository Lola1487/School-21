#include <wchar.h>

#include "s21_test_runner.h"

START_TEST(s21_sprintf_c_basic) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%c", 'A'), sprintf(expected, "%c", 'A'));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_c_width) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%5c", 'A'), sprintf(expected, "%5c", 'A'));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_c_left_align) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%-5c", 'A'),
                   sprintf(expected, "%-5c", 'A'));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_c_special_chars) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%c", '\n'), sprintf(expected, "%c", '\n'));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_wide_c_basic) {
  char got[100], expected[100];
  setlocale(LC_ALL, "en_US.UTF-8");
  ck_assert_int_eq(s21_sprintf(got, "%lc", L'Б'),
                   sprintf(expected, "%lc", (wint_t)L'Б'));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_wide_c_width) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%5lc", L'的'),
                   sprintf(expected, "%5lc", (wint_t)L'的'));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_wide_c_left_align) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%-5lc", L'𒆩'),
                   sprintf(expected, "%-5lc", (wint_t)L'𒆩'));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_d_basic) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%d", 123), sprintf(expected, "%d", 123));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_d_negative) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%d", -123), sprintf(expected, "%d", -123));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_d_width) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%5d", 123), sprintf(expected, "%5d", 123));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_d_precision) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%.5d", 123),
                   sprintf(expected, "%.5d", 123));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_d_zero_pad) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%05d", 123),
                   sprintf(expected, "%05d", 123));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_d_plus_flag) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%+d", 123), sprintf(expected, "%+d", 123));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_d_space_flag) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "% d", 123), sprintf(expected, "% d", 123));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_d_long) {
  char got[100], expected[100];
  long num = 123456789L;
  ck_assert_int_eq(s21_sprintf(got, "%ld", num), sprintf(expected, "%ld", num));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_d_short) {
  char got[100], expected[100];
  short num = 123;
  ck_assert_int_eq(s21_sprintf(got, "%hd", num), sprintf(expected, "%hd", num));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_u_basic) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%u", 123U), sprintf(expected, "%u", 123U));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_u_width) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%10u", (unsigned int)123),
                   sprintf(expected, "%10u", (unsigned int)123));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_u_precision) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%.5u", (unsigned int)123),
                   sprintf(expected, "%.5u", (unsigned int)123));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_u_long) {
  char got[100], expected[100];
  unsigned long num = 123456789UL;
  ck_assert_int_eq(s21_sprintf(got, "%lu", num), sprintf(expected, "%lu", num));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_u_short) {
  char got[100], expected[100];
  unsigned short num = 123;
  ck_assert_int_eq(s21_sprintf(got, "%hu", num), sprintf(expected, "%hu", num));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_o_basic) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%o", 123), sprintf(expected, "%o", 123));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_o_hash) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%#o", 123), sprintf(expected, "%#o", 123));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_o_long) {
  char got[100], expected[100];
  unsigned long num = 123456789UL;
  ck_assert_int_eq(s21_sprintf(got, "%lo", num), sprintf(expected, "%lo", num));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_x_basic) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%x", 123), sprintf(expected, "%x", 123));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_X_basic) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%X", 123), sprintf(expected, "%X", 123));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_x_hash) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%#x", 123), sprintf(expected, "%#x", 123));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_X_hash) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%#X", 123), sprintf(expected, "%#X", 123));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_x_long) {
  char got[100], expected[100];
  unsigned long num = 123456789UL;
  ck_assert_int_eq(s21_sprintf(got, "%lx", num), sprintf(expected, "%lx", num));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_X_long) {
  char got[100], expected[100];
  unsigned long num = 123456789UL;
  ck_assert_int_eq(s21_sprintf(got, "%lX", num), sprintf(expected, "%lX", num));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_f_basic) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%f", 0.123),
                   sprintf(expected, "%f", 0.123));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_f_precision) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%.2f", 123.456),
                   sprintf(expected, "%.2f", 123.456));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_f_precision_zero) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%.2f", 123.),
                   sprintf(expected, "%.2f", 123.));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_f_width) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%10f", 123.456),
                   sprintf(expected, "%10f", 123.456));
  ck_assert_str_eq(got, expected);
}
END_TEST

END_TEST

START_TEST(s21_sprintf_f_long_double) {
  char got[100], expected[100];
  long double num = 123.456L;
  ck_assert_int_eq(s21_sprintf(got, "%Lf", num), sprintf(expected, "%Lf", num));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_f_negative) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%f", -123.456),
                   sprintf(expected, "%f", -123.456));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_f_plus_flag) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%+f", 123.456),
                   sprintf(expected, "%+f", 123.456));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_f_space_flag) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "% f", 123.456),
                   sprintf(expected, "% f", 123.456));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_f_nan) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%f", NAN), sprintf(expected, "%f", NAN));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_f_minus_nan) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%f", -NAN), sprintf(expected, "%f", -NAN));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_f_plus_nan) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%+f", NAN), sprintf(expected, "%+f", NAN));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_f_space_nan) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "% f", NAN), sprintf(expected, "% f", NAN));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_F_upper_nan) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%F", NAN), sprintf(expected, "%F", NAN));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_e_basic) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%e", 0.123),
                   sprintf(expected, "%e", 0.123));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_E_basic) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%E", 123.456),
                   sprintf(expected, "%E", 123.456));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_e_precision) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%.2e", 123.456),
                   sprintf(expected, "%.2e", 123.456));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_e_hash) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%#e", 123.),
                   sprintf(expected, "%#e", 123.));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_e_long_double) {
  char got[100], expected[100];
  long double num = 123.456L;
  ck_assert_int_eq(s21_sprintf(got, "%Le", num), sprintf(expected, "%Le", num));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_e_nan) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%e", NAN), sprintf(expected, "%e", NAN));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_E_upper_nan) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%E", NAN), sprintf(expected, "%E", NAN));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_g_basic) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%g", 123.456),
                   sprintf(expected, "%g", 123.456));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_g_hash) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%#g", 0.), sprintf(expected, "%#g", 0.));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_g_hash_precision) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%#.1g", 0.),
                   sprintf(expected, "%#.1g", 0.));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_G_basic) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%G", 123.456),
                   sprintf(expected, "%G", 123.456));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_g_long_double) {
  char got[100], expected[100];
  long double num = 123.456L;
  ck_assert_int_eq(s21_sprintf(got, "%Lg", num), sprintf(expected, "%Lg", num));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_g_nan) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%g", NAN), sprintf(expected, "%g", NAN));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_G_upper_nan) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%G", NAN), sprintf(expected, "%G", NAN));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_g_scientific) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%g", 0.00009),
                   sprintf(expected, "%g", 0.00009));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_g_scientific_precision) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%.2g", 123.456),
                   sprintf(expected, "%.2g", 123.456));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_s_basic) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%s", "test"),
                   sprintf(expected, "%s", "test"));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_s_width) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%10s", "test"),
                   sprintf(expected, "%10s", "test"));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_s_precision) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%.2s", "test"),
                   sprintf(expected, "%.2s", "test"));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_wide_s_basic) {
  char got[100], expected[100];

  setlocale(LC_ALL, "en_US.UTF-8");

  ck_assert_int_eq(s21_sprintf(got, "%ls", L"тест test"),
                   sprintf(expected, "%ls", L"тест test"));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_wide_s_very_long_string) {
  char got[1000], expected[1000];

  setlocale(LC_ALL, "en_US.UTF-8");

  ck_assert_int_eq(s21_sprintf(got, "%ls",
                               L"Все люди рождаются свободными и равными в "
                               L"своём достоинстве и правах."),
                   sprintf(expected, "%ls",
                           L"Все люди рождаются свободными и равными в своём "
                           L"достоинстве и правах."));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_wide_s_width) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%10ls", L"тест"),
                   sprintf(expected, "%10ls", L"тест"));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_wide_s_precision) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%.2ls", L"тест"),
                   sprintf(expected, "%.2ls", L"тест"));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_p_basic) {
  char got[100], expected[100];
  int x = 5;
  ck_assert_int_eq(s21_sprintf(got, "%p", &x), sprintf(expected, "%p", &x));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_p_null) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%p", (void *)NULL),
                   sprintf(expected, "%p", (void *)NULL));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_n_basic) {
  char got[100];
  int count1 = 0, count2 = 0;
  s21_sprintf(got, "test%n", &count1);
  sprintf(got, "test%n", &count2);
  ck_assert_int_eq(count1, count2);
}
END_TEST

START_TEST(s21_sprintf_n_short) {
  char got[100];
  short int count1 = 0, count2 = 0;
  s21_sprintf(got, "test%hn", &count1);
  sprintf(got, "test%hn", &count2);
  ck_assert_int_eq(count1, count2);
}
END_TEST

START_TEST(s21_sprintf_n_long) {
  char got[100];
  long int count1 = 0, count2 = 0;
  s21_sprintf(got, "test%ln", &count1);
  sprintf(got, "test%ln", &count2);
  ck_assert_int_eq(count1, count2);
}
END_TEST

START_TEST(s21_sprintf_percent) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%%"), sprintf(expected, "%%"));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_combined) {
  char got[100], expected[100];
  ck_assert_int_eq(
      s21_sprintf(got, "Char: %c, Int: %d, Str: %s", 'A', 123, "test"),
      sprintf(expected, "Char: %c, Int: %d, Str: %s", 'A', 123, "test"));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_combined_flags) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%+10.2f %#x %-5s", 123.456, 255, "test"),
                   sprintf(expected, "%+10.2f %#x %-5s", 123.456, 255, "test"));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_length_h) {
  char got[100], expected[100];
  short x = 123;
  ck_assert_int_eq(s21_sprintf(got, "%hd", x), sprintf(expected, "%hd", x));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_length_l) {
  char got[100], expected[100];
  long x = 123456789;
  ck_assert_int_eq(s21_sprintf(got, "%ld", x), sprintf(expected, "%ld", x));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_length_L) {
  char got[100], expected[100];
  long double x = 123.456;
  ck_assert_int_eq(s21_sprintf(got, "%Lf", x), sprintf(expected, "%Lf", x));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_empty_format) {
  char got[100] = {0};
  ck_assert_int_eq(s21_sprintf(got, ""), 0);
}
END_TEST

START_TEST(s21_sprintf_null_buffer) {
  ck_assert_int_eq(s21_sprintf(NULL, "test"), -1);
}
END_TEST

START_TEST(s21_sprintf_null_format) {
  char buffer[100];
  ck_assert_int_eq(s21_sprintf(buffer, NULL), -1);
}
END_TEST

START_TEST(s21_sprintf_asterisk_width) {
  char got[100], expected[100];
  int width = 10;
  ck_assert_int_eq(s21_sprintf(got, "%*d", width, 123),
                   sprintf(expected, "%*d", width, 123));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_asterisk_precision) {
  char got[100], expected[100];
  int precision = 5;
  ck_assert_int_eq(s21_sprintf(got, "%.*f", precision, 123.456),
                   sprintf(expected, "%.*f", precision, 123.456));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_Lf_long_double) {
  char got[100], expected[100];
  long double ld = 123456789.123456789L;
  ck_assert_int_eq(s21_sprintf(got, "%Lf", ld), sprintf(expected, "%Lf", ld));
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(s21_sprintf_s_empty_precision) {
  char got[100], expected[100];
  ck_assert_int_eq(s21_sprintf(got, "%.5s", ""), sprintf(expected, "%.5s", ""));
  ck_assert_str_eq(got, expected);
}
END_TEST

Suite *tests_for_sprintf(void) {
  Suite *s = suite_create("s21_sprintf");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, s21_sprintf_c_basic);
  tcase_add_test(tc, s21_sprintf_c_width);
  tcase_add_test(tc, s21_sprintf_c_left_align);
  tcase_add_test(tc, s21_sprintf_c_special_chars);

  tcase_add_test(tc, s21_sprintf_wide_c_basic);
  tcase_add_test(tc, s21_sprintf_wide_c_width);
  tcase_add_test(tc, s21_sprintf_wide_c_left_align);

  tcase_add_test(tc, s21_sprintf_d_basic);
  tcase_add_test(tc, s21_sprintf_d_negative);
  tcase_add_test(tc, s21_sprintf_d_width);
  tcase_add_test(tc, s21_sprintf_d_precision);
  tcase_add_test(tc, s21_sprintf_d_zero_pad);
  tcase_add_test(tc, s21_sprintf_d_plus_flag);
  tcase_add_test(tc, s21_sprintf_d_space_flag);

  tcase_add_test(tc, s21_sprintf_d_long);
  tcase_add_test(tc, s21_sprintf_d_short);

  tcase_add_test(tc, s21_sprintf_u_basic);
  tcase_add_test(tc, s21_sprintf_u_width);
  tcase_add_test(tc, s21_sprintf_u_precision);

  tcase_add_test(tc, s21_sprintf_u_long);
  tcase_add_test(tc, s21_sprintf_u_short);

  tcase_add_test(tc, s21_sprintf_o_basic);
  tcase_add_test(tc, s21_sprintf_o_hash);
  tcase_add_test(tc, s21_sprintf_o_long);

  tcase_add_test(tc, s21_sprintf_x_basic);
  tcase_add_test(tc, s21_sprintf_X_basic);
  tcase_add_test(tc, s21_sprintf_x_hash);
  tcase_add_test(tc, s21_sprintf_X_hash);

  tcase_add_test(tc, s21_sprintf_x_long);
  tcase_add_test(tc, s21_sprintf_X_long);

  tcase_add_test(tc, s21_sprintf_f_basic);
  tcase_add_test(tc, s21_sprintf_f_precision);
  tcase_add_test(tc, s21_sprintf_f_precision_zero);
  tcase_add_test(tc, s21_sprintf_f_width);

  tcase_add_test(tc, s21_sprintf_f_long_double);
  tcase_add_test(tc, s21_sprintf_f_negative);
  tcase_add_test(tc, s21_sprintf_f_plus_flag);
  tcase_add_test(tc, s21_sprintf_f_space_flag);

  tcase_add_test(tc, s21_sprintf_f_nan);
  tcase_add_test(tc, s21_sprintf_f_minus_nan);
  tcase_add_test(tc, s21_sprintf_f_plus_nan);
  tcase_add_test(tc, s21_sprintf_f_space_nan);
  tcase_add_test(tc, s21_sprintf_F_upper_nan);

  tcase_add_test(tc, s21_sprintf_e_basic);
  tcase_add_test(tc, s21_sprintf_E_basic);
  tcase_add_test(tc, s21_sprintf_e_precision);
  tcase_add_test(tc, s21_sprintf_e_hash);
  tcase_add_test(tc, s21_sprintf_e_long_double);
  tcase_add_test(tc, s21_sprintf_e_nan);
  tcase_add_test(tc, s21_sprintf_E_upper_nan);

  tcase_add_test(tc, s21_sprintf_g_basic);
  tcase_add_test(tc, s21_sprintf_g_hash);
  tcase_add_test(tc, s21_sprintf_g_hash_precision);
  tcase_add_test(tc, s21_sprintf_G_basic);
  tcase_add_test(tc, s21_sprintf_g_long_double);
  tcase_add_test(tc, s21_sprintf_g_nan);
  tcase_add_test(tc, s21_sprintf_G_upper_nan);

  tcase_add_test(tc, s21_sprintf_g_scientific);
  tcase_add_test(tc, s21_sprintf_g_scientific_precision);

  tcase_add_test(tc, s21_sprintf_s_basic);
  tcase_add_test(tc, s21_sprintf_s_width);
  tcase_add_test(tc, s21_sprintf_s_precision);

  tcase_add_test(tc, s21_sprintf_wide_s_basic);
  tcase_add_test(tc, s21_sprintf_wide_s_very_long_string);
  tcase_add_test(tc, s21_sprintf_wide_s_width);
  tcase_add_test(tc, s21_sprintf_wide_s_precision);

  tcase_add_test(tc, s21_sprintf_p_basic);
  tcase_add_test(tc, s21_sprintf_p_null);

  tcase_add_test(tc, s21_sprintf_n_basic);
  tcase_add_test(tc, s21_sprintf_n_short);
  tcase_add_test(tc, s21_sprintf_n_long);

  tcase_add_test(tc, s21_sprintf_percent);

  tcase_add_test(tc, s21_sprintf_combined);
  tcase_add_test(tc, s21_sprintf_combined_flags);

  tcase_add_test(tc, s21_sprintf_length_h);
  tcase_add_test(tc, s21_sprintf_length_l);
  tcase_add_test(tc, s21_sprintf_length_L);

  tcase_add_test(tc, s21_sprintf_empty_format);
  tcase_add_test(tc, s21_sprintf_null_buffer);
  tcase_add_test(tc, s21_sprintf_null_format);
  tcase_add_test(tc, s21_sprintf_asterisk_width);
  tcase_add_test(tc, s21_sprintf_asterisk_precision);

  tcase_add_test(tc, s21_sprintf_Lf_long_double);
  tcase_add_test(tc, s21_sprintf_s_empty_precision);

  suite_add_tcase(s, tc);
  return s;
}
