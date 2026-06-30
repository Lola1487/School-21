#include "s21_test_runner.h"

START_TEST(s21_wcstombs_0) {
  // ARRANGE
  char got[100] = {0};
  char expected[100] = {0};
  const s21_wchar_t *str1 = L"HELL";
  const wchar_t *str2 = L"HELL";

  setlocale(LC_ALL, "en_US.UTF-8");

  // ACT - Convert wide strings to multibyte using standard and custom functions
  s21_size_t result = wcstombs(expected, str2, sizeof(expected));
  s21_size_t result2 = s21_wcstombs(got, str1, sizeof(got));

  // ASSERT - Verify both strings and return values match
  ck_assert_str_eq(got, expected);
  ck_assert_int_eq(result, result2);
}
END_TEST

/**
 * @brief Test case for empty wide character string conversion
 */
START_TEST(s21_wcstombs_1) {
  // ARRANGE
  char got[100] = {0};
  char expected[100] = {0};
  const s21_wchar_t *str1 = L"";
  const wchar_t *str2 = L"";

  setlocale(LC_ALL, "en_US.UTF-8");

  // ACT
  s21_size_t result = wcstombs(expected, str2, sizeof(expected));
  s21_size_t result2 = s21_wcstombs(got, str1, sizeof(got));

  // ASSERT
  ck_assert_str_eq(got, expected);
  ck_assert_int_eq(result, result2);
}
END_TEST

/**
 * @brief Test case for Japanese wide character string conversion
 */
START_TEST(s21_wcstombs_2) {
  // ARRANGE
  char got[100] = {0};
  char expected[100] = {0};
  const s21_wchar_t str1[] = {0x3053, 0x306b, 0x3093, 0x306b,
                              0x3061, 0x306f, 0};
  const wchar_t str2[] = {0x3053, 0x306b, 0x3093, 0x306b, 0x3061, 0x306f, 0};

  setlocale(LC_ALL, "en_US.UTF-8");

  // ACT
  s21_size_t result = wcstombs(expected, str2, sizeof(expected));
  s21_size_t result2 = s21_wcstombs(got, str1, sizeof(got));

  // ASSERT
  ck_assert_str_eq(got, expected);
  ck_assert_int_eq(result, result2);
}
END_TEST

/**
 * @brief Test case for NULL wide character string input
 */
START_TEST(s21_wcstombs_3) {
  // ARRANGE
  char got[100] = {0};
  const s21_wchar_t *wcstr = s21_NULL;

  // ACT
  s21_size_t result = s21_wcstombs(got, wcstr, sizeof(got));

  // ASSERT - Should return empty string and 0 for NULL input
  ck_assert_str_eq(got, "");
  ck_assert_int_eq(result, 0);
}
END_TEST

/**
 * @brief Test case for Arabic wide character string conversion
 */
START_TEST(s21_wcstombs_4) {
  // ARRANGE
  char got[100] = {0};
  char expected[100] = {0};
  const s21_wchar_t str1[] = {0x0771, 0x0772, 0};
  const wchar_t str2[] = {0x0771, 0x0772, 0};

  setlocale(LC_ALL, "en_US.UTF-8");

  // ACT
  s21_size_t result = wcstombs(expected, str2, sizeof(expected));
  s21_size_t result2 = s21_wcstombs(got, str1, sizeof(got));

  // ASSERT
  ck_assert_str_eq(got, expected);
  ck_assert_int_eq(result, result2);
}
END_TEST

/**
 * @brief Test case for emoji wide character conversion
 */
START_TEST(s21_wcstombs_5) {
  // ARRANGE
  char got[100] = {0};
  char expected[100] = {0};
  const s21_wchar_t str1[] = {0x1F600, 0};
  const wchar_t str2[] = {0x1F600, 0};

  setlocale(LC_ALL, "en_US.UTF-8");

  // ACT
  s21_size_t result = wcstombs(expected, str2, sizeof(expected));
  s21_size_t result2 = s21_wcstombs(got, str1, sizeof(got));

  // ASSERT
  ck_assert_str_eq(got, expected);
  ck_assert_int_eq(result, result2);
}
END_TEST

/**
 * @brief Test case for exact buffer size matching string length
 */
START_TEST(s21_wcstombs_6) {
  // ARRANGE
  char got[6] = {0};
  const s21_wchar_t *str1 = L"HELLO";

  // ACT
  s21_size_t result = s21_wcstombs(got, str1, sizeof(got));

  // ASSERT - Should convert full string when buffer is exactly sized
  ck_assert_str_eq(got, "HELLO");
  ck_assert_int_eq(result, 5);
}
END_TEST

/**
 * @brief Test case for buffer size one less than string length
 */
START_TEST(s21_wcstombs_7) {
  // ARRANGE
  char got[5] = {0};
  const s21_wchar_t *str1 = L"HELLO";

  // ACT
  s21_size_t result = s21_wcstombs(got, str1, sizeof(got));

  // ASSERT - Should truncate when buffer is too small
  ck_assert_str_eq(got, "HELL");
  ck_assert_int_eq(result, 4);
}
END_TEST

/**
 * @brief Test case for buffer size significantly smaller than string length
 */
START_TEST(s21_wcstombs_8) {
  // ARRANGE
  char got[4] = {0};
  const s21_wchar_t *str1 = L"HELLO";

  // ACT
  s21_size_t result = s21_wcstombs(got, str1, sizeof(got));

  // ASSERT - Should truncate to buffer size - 1
  ck_assert_str_eq(got, "HEL");
  ck_assert_int_eq(result, 3);
}
END_TEST

/**
 * @brief Test case for both NULL parameters (covers line 10)
 */
START_TEST(s21_wcstombs_9) {
  // ACT - Both parameters are NULL
  s21_size_t result = s21_wcstombs(s21_NULL, s21_NULL, 10);

  // ASSERT - Should return 0 when both pointers are NULL
  ck_assert_int_eq(result, 0);
}
END_TEST

/**
 * @brief Test case for invalid Unicode characters (covers line 39)
 */
START_TEST(s21_wcstombs_10) {
  // ARRANGE - Invalid Unicode characters beyond 0x10FFFF
  const s21_wchar_t invalid_chars[] = {0x110000, 0xFFFFFF, 0xFFFFFFFF, 0};
  char buffer[100];

  // ACT
  s21_size_t result = s21_wcstombs(buffer, invalid_chars, sizeof(buffer));

  // ASSERT - Should return (s21_size_t)-1 for invalid characters
  ck_assert_int_eq(result, (s21_size_t)-1);
}
END_TEST

/**
 * @brief Test case for single invalid Unicode character
 */
START_TEST(s21_wcstombs_11) {
  // ARRANGE - Single invalid character
  const s21_wchar_t invalid_char = 0x110000;
  char buffer[100];

  // ACT
  s21_size_t result = s21_wcstombs(buffer, &invalid_char, sizeof(buffer));

  // ASSERT
  ck_assert_int_eq(result, (s21_size_t)-1);
}
END_TEST

/**
 * @brief Test case for testing all Unicode ranges
 */
START_TEST(s21_wcstombs_12) {
  // ARRANGE - Test boundary values for different UTF-8 ranges
  const s21_wchar_t test_chars[] = {0x7F,      // Last 1-byte character
                                    0x80,      // First 2-byte character
                                    0x7FF,     // Last 2-byte character
                                    0x800,     // First 3-byte character
                                    0xFFFF,    // Last 3-byte character
                                    0x10000,   // First 4-byte character
                                    0x10FFFF,  // Last valid Unicode character
                                    0};
  char buffer[100];

  // ACT
  s21_size_t result = s21_wcstombs(buffer, test_chars, sizeof(buffer));

  // ASSERT - Should successfully convert all valid characters
  ck_assert_int_ne(result, (s21_size_t)-1);
  ck_assert_int_gt(result, 0);
}
END_TEST

/**
 * @brief Test case for insufficient buffer for 4-byte character
 */
START_TEST(s21_wcstombs_13) {
  // ARRANGE - 4-byte character with insufficient buffer
  const s21_wchar_t wide_str[] = {0x10345, 0};
  char buffer[3];  // Only enough for 2 bytes + null

  // ACT
  s21_size_t result = s21_wcstombs(buffer, wide_str, sizeof(buffer));

  // ASSERT - Should return 0 (nothing converted due to insufficient space)
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(buffer[0], '\0');
}
END_TEST

/**
 * @brief Creates test suite for wcstombs functionality
 * @return Pointer to the test suite
 */
Suite *tests_for_wchar_wcstombs(void) {
  Suite *s = suite_create("wcstombs_tests");
  TCase *tc_wcstombs = tcase_create("wcstombs_tc");

  tcase_add_test(tc_wcstombs, s21_wcstombs_0);
  tcase_add_test(tc_wcstombs, s21_wcstombs_1);
  tcase_add_test(tc_wcstombs, s21_wcstombs_2);
  tcase_add_test(tc_wcstombs, s21_wcstombs_3);
  tcase_add_test(tc_wcstombs, s21_wcstombs_4);
  tcase_add_test(tc_wcstombs, s21_wcstombs_5);
  tcase_add_test(tc_wcstombs, s21_wcstombs_6);
  tcase_add_test(tc_wcstombs, s21_wcstombs_7);
  tcase_add_test(tc_wcstombs, s21_wcstombs_8);
  tcase_add_test(tc_wcstombs, s21_wcstombs_9);
  tcase_add_test(tc_wcstombs, s21_wcstombs_10);
  tcase_add_test(tc_wcstombs, s21_wcstombs_11);
  tcase_add_test(tc_wcstombs, s21_wcstombs_12);
  tcase_add_test(tc_wcstombs, s21_wcstombs_13);

  suite_add_tcase(s, tc_wcstombs);
  return s;
}
