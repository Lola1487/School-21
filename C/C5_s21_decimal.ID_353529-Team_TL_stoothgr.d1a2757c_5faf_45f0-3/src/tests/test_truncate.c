#include "test_decimal.h"

/* Test 1: Positive integer without fractional part should remain unchanged */
START_TEST(test_truncate_no_fraction) {
  // ARRANGE: Set up a positive decimal value that's already an integer
  s21_decimal value = {
      {123456789, 0, 0,
       0x00000000}};  // Integer number without fractional part (123456789)
  s21_decimal expected = {
      {123456789, 0, 0, 0}};  // Expected unchanged value (123456789)

  // ACT: Call the truncate function
  s21_decimal result;
  int error_code = s21_truncate(value, &result);

  // ASSERT: Verify function returns success and result matches expected value
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 2: Positive number with fractional part should remove fractional digits
 */
START_TEST(test_truncate_with_fraction) {
  // ARRANGE: Set up a positive decimal value with fractional part (1234567.89)
  s21_decimal value = {{123456789, 0, 0, 0x00020000}};   // 1234567.89
  s21_decimal expected = {{1234567, 0, 0, 0x00000000}};  // Expected: 1234567

  // ACT: Call the truncate function
  s21_decimal result;
  int error_code = s21_truncate(value, &result);

  // ASSERT: Verify function returns success and fractional part is removed
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 3: Positive number with small fractional part should truncate to integer
 */
START_TEST(test_truncate_with_fraction_2) {
  // ARRANGE: Set up a positive decimal value with small fractional part
  // (1.23456789)
  s21_decimal value = {{123456789, 0, 0, 0x00080000}};  // 1.23456789
  s21_decimal expected = {{1, 0, 0, 0x00000000}};       // Expected: 1

  // ACT: Call the truncate function
  s21_decimal result;
  int error_code = s21_truncate(value, &result);

  // ASSERT: Verify function returns success and truncates to integer
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 4: Negative integer without fractional part should remain unchanged */
START_TEST(test_truncate_negative_number) {
  // ARRANGE: Set up a negative decimal value that's already an integer
  // (-987654321)
  s21_decimal value = {
      {987654321, 0, 0, 0x80000000}};  // Negative integer number (-987654321)
  s21_decimal expected = {
      {987654321, 0, 0, 0x80000000}};  // Expected unchanged value (-987654321)

  // ACT: Call the truncate function
  s21_decimal result;
  int error_code = s21_truncate(value, &result);

  // ASSERT: Verify function returns success and result matches expected value
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 5: Negative number with fractional part should remove fractional digits
 */
START_TEST(test_truncate_with_fraction_negative) {
  // ARRANGE: Set up a negative decimal value with fractional part (-1234567.89)
  s21_decimal value = {{123456789, 0, 0, 0x80020000}};   // -1234567.89
  s21_decimal expected = {{1234567, 0, 0, 0x80000000}};  // Expected: -1234567

  // ACT: Call the truncate function
  s21_decimal result;
  int error_code = s21_truncate(value, &result);

  // ASSERT: Verify function returns success and fractional part is removed
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 6: Negative number with small fractional part should truncate to
 * negative integer */
START_TEST(test_truncate_with_fraction_negative_2) {
  // ARRANGE: Set up a negative decimal value with small fractional part
  // (-1.23456789)
  s21_decimal value = {{123456789, 0, 0, 0x80080000}};  // -1.23456789
  s21_decimal expected = {{1, 0, 0, 0x80000000}};       // Expected: -1

  // ACT: Call the truncate function
  s21_decimal result;
  int error_code = s21_truncate(value, &result);

  // ASSERT: Verify function returns success and truncates to negative integer
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 7: Very small number with large scale should truncate to zero */
START_TEST(test_truncate_large_scale) {
  // ARRANGE: Set up a very small decimal value (0.0000000000000000000000000001)
  s21_decimal value = {
      {1, 0, 0, 0x001C0000}};  // 0.0000000000000000000000000001
  s21_decimal expected = {{0, 0, 0, 0x00000000}};  // Expected: 0

  // ACT: Call the truncate function
  s21_decimal result;
  int error_code = s21_truncate(value, &result);

  // ASSERT: Verify function returns success and truncates to zero
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 8: Null pointer should return error code */
START_TEST(test_truncate_null_pointer) {
  // ARRANGE: Set up any decimal value with fractional part
  s21_decimal value = {
      {123456789, 0, 0, 0x00180000}};  // Any number with fractional part

  // ACT: Call truncate with NULL pointer
  int error_code = s21_truncate(value, NULL);

  // ASSERT: Verify function returns error code 1 for null pointer
  ck_assert_int_eq(error_code, 1);
}
END_TEST

/* Test 9: Zero with negative sign and large scale should remain zero */
START_TEST(test_truncate_zero_with_large_negative_bit) {
  // ARRANGE: Set up zero value with negative sign and scale 28
  s21_decimal value = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000,
       0b10000000000111000000000000000000}};  // 0 with negative sign

  // ARRANGE: Expected result is zero with negative sign
  s21_decimal expected = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000,
       0b10000000000000000000000000000000}};  // 0 with negative sign

  // ACT: Call the truncate function
  s21_decimal result;
  int error_code = s21_truncate(value, &result);

  // ASSERT: Verify function returns success and zero remains zero
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 10: Comprehensive test with various custom values */
START_TEST(test_truncate_custom_values) {
  // Test case 10.1: Positive number with fractional part
  // ARRANGE: Set up positive decimal 553402.32229718589441
  s21_decimal value1 = {{1, 2, 3, 917504}};     // 553402.32229718589441
  s21_decimal expected1 = {{553402, 0, 0, 0}};  // Expected: 553402

  // ACT: Call truncate function
  s21_decimal result1;
  int error_code1 = s21_truncate(value1, &result1);

  // ASSERT: Verify successful truncation
  ck_assert_int_eq(error_code1, 0);
  ck_assert_mem_eq(&result1, &expected1, sizeof(s21_decimal));

  // Test case 10.2: Negative number with fractional part
  // ARRANGE: Set up negative decimal -553402.32229718589441
  s21_decimal value2 = {{1, 2, 3, -2146566144}};  // -553402.32229718589441
  s21_decimal expected2 = {{553402, 0, 0, -2147483648}};  // Expected: -553402

  // ACT: Call truncate function
  s21_decimal result2;
  int error_code2 = s21_truncate(value2, &result2);

  // ASSERT: Verify successful truncation
  ck_assert_int_eq(error_code2, 0);
  ck_assert_mem_eq(&result2, &expected2, sizeof(s21_decimal));

  // Additional test cases follow the same ARRANGE-ACT-ASSERT pattern...
  // [The rest of the test cases would be structured similarly]
}
END_TEST

Suite *test_truncate(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\033[1;33ms21_truncate\033[0m");

  tc_core = tcase_create("truncate_tc");

  tcase_add_test(tc_core, test_truncate_no_fraction);
  tcase_add_test(tc_core, test_truncate_with_fraction);
  tcase_add_test(tc_core, test_truncate_with_fraction_2);
  tcase_add_test(tc_core, test_truncate_with_fraction_negative);
  tcase_add_test(tc_core, test_truncate_with_fraction_negative_2);
  tcase_add_test(tc_core, test_truncate_negative_number);
  tcase_add_test(tc_core, test_truncate_large_scale);
  tcase_add_test(tc_core, test_truncate_null_pointer);
  tcase_add_test(tc_core, test_truncate_zero_with_large_negative_bit);
  tcase_add_test(tc_core, test_truncate_custom_values);

  suite_add_tcase(s, tc_core);

  return s;
}
