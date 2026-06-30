#include "test_decimal.h"

/* Test 1: Convert positive number to negative - basic functionality test */
START_TEST(test_negate_positive_to_negative) {
  // ARRANGE: Set up a positive decimal value
  s21_decimal value = {{123, 0, 0, 0x00000000}};  // Positive number 123
  s21_decimal expected = {
      {123, 0, 0, 0x80000000}};  // Expected negative number -123

  // ACT: Call the negate function
  s21_decimal result;
  int error_code = s21_negate(value, &result);

  // ASSERT: Verify function returns success and sign bit is flipped
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));

  // ARRANGE: Set up another positive decimal with complex structure
  s21_decimal value2 = {{1, 1, 1, 917504}};  // 184467.44078004518913
  s21_decimal expected2 = {
      {1, 1, 1, -2146566144}};  // Expected -184467.44078004518913

  // ACT: Call the negate function again
  s21_decimal result2;
  int error_code2 = s21_negate(value2, &result2);

  // ASSERT: Verify function returns success and complex value sign is flipped
  ck_assert_int_eq(error_code2, 0);
  ck_assert_mem_eq(&result2, &expected2, sizeof(s21_decimal));
}
END_TEST

/* Test 2: Convert negative number to positive - inverse functionality test */
START_TEST(test_negate_negative_to_positive) {
  // ARRANGE: Set up a negative decimal value
  s21_decimal value = {{123, 0, 0, 0x80000000}};  // Negative number -123
  s21_decimal expected = {
      {123, 0, 0, 0x00000000}};  // Expected positive number 123

  // ACT: Call the negate function
  s21_decimal result;
  int error_code = s21_negate(value, &result);

  // ASSERT: Verify function returns success and sign bit is flipped
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));

  // ARRANGE: Set up another negative decimal with complex structure
  s21_decimal value2 = {
      {32444, 100, 343253, -2145976320}};  // -63.31900243533454217608892
  s21_decimal expected2 = {
      {32444, 100, 343253, 1507328}};  // Expected 63.31900243533454217608892

  // ACT: Call the negate function again
  s21_decimal result2;
  int error_code2 = s21_negate(value2, &result2);

  // ASSERT: Verify function returns success and complex value sign is flipped
  ck_assert_int_eq(error_code2, 0);
  ck_assert_mem_eq(&result2, &expected2, sizeof(s21_decimal));
}
END_TEST

/* Test 3: Convert positive zero to negative zero - edge case test */
START_TEST(test_negate_zero_positive) {
  // ARRANGE: Set up a positive zero value
  s21_decimal value = {{0, 0, 0, 917504}};          // Positive zero
  s21_decimal expected = {{0, 0, 0, -2146566144}};  // Expected negative zero

  // ACT: Call the negate function
  s21_decimal result;
  int error_code = s21_negate(value, &result);

  // ASSERT: Verify function returns success and zero sign is flipped
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 4: Convert negative zero to positive zero - edge case test */
START_TEST(test_negate_zero_negative) {
  // ARRANGE: Set up a negative zero value
  s21_decimal value = {{0, 0, 0, 0x80000000}};     // Negative zero
  s21_decimal expected = {{0, 0, 0, 0x00000000}};  // Expected positive zero

  // ACT: Call the negate function
  s21_decimal result;
  int error_code = s21_negate(value, &result);

  // ASSERT: Verify function returns success and zero sign is flipped
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 5: Handle null pointer parameter - error condition test */
START_TEST(test_negate_null_pointer) {
  // ARRANGE: Set up any decimal value
  s21_decimal value = {{123, 0, 0, 0x00000000}};  // Any number

  // ACT: Call the negate function with NULL result pointer
  int error_code = s21_negate(value, NULL);

  // ASSERT: Verify function returns error code for null pointer
  ck_assert_int_eq(error_code, 1);
}
END_TEST

Suite *test_negate(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\033[1;33ms21_negate\033[0m");

  tc_core = tcase_create("negate_tc");

  tcase_add_test(tc_core, test_negate_positive_to_negative);
  tcase_add_test(tc_core, test_negate_negative_to_positive);
  tcase_add_test(tc_core, test_negate_zero_positive);
  tcase_add_test(tc_core, test_negate_zero_negative);
  tcase_add_test(tc_core, test_negate_null_pointer);

  suite_add_tcase(s, tc_core);

  return s;
}
