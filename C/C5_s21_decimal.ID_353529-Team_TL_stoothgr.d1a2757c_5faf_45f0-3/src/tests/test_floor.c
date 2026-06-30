#include "test_decimal.h"

/* Test 1: Positive number without fractional part should remain unchanged */
START_TEST(test_floor_positive_no_fraction) {
  // ARRANGE: Set up a positive decimal value that's already an integer
  s21_decimal value = {{1, 2, 3, 917504}};     // 553402.32229718589441
  s21_decimal expected = {{553402, 0, 0, 0}};  // 553402

  // ACT: Call the floor function
  s21_decimal result;
  int error_code = s21_floor(value, &result);

  // ASSERT: Verify function returns success and result matches expected value
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 2: Negative number without fractional part should remain unchanged */
START_TEST(test_floor_negative_no_fraction) {
  // ARRANGE: Set up a negative decimal value that's already an integer
  s21_decimal value = {{1, 2, 3, -2146566144}};  // -553402.32229718589441
  s21_decimal expected = {{553403, 0, 0, -2147483648}};  // -553403

  // ACT: Call the floor function
  s21_decimal result;
  int error_code = s21_floor(value, &result);

  // ASSERT: Verify function returns success and result matches expected value
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 3: Positive number with fractional part should truncate downward */
START_TEST(test_floor_positive_fraction) {
  // ARRANGE: Set up a positive decimal with fractional part
  s21_decimal value = {{25, 30, 0, 65536}};  // 12884901890.5
  s21_decimal expected = {{2, 3, 0, 0}};     // 12884901890

  // ACT: Call the floor function
  s21_decimal result;
  int error_code = s21_floor(value, &result);

  // ASSERT: Verify fractional part is removed and integer part remains
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 4: Positive number with small fractional part should truncate */
START_TEST(test_floor_positive_fraction_small) {
  // ARRANGE: Set up a positive decimal with small fractional part
  s21_decimal value = {{225, 300, 0, 131072}};  // 12884901890.25
  s21_decimal expected = {{2, 3, 0, 0}};        // 12884901890

  // ACT: Call the floor function
  s21_decimal result;
  int error_code = s21_floor(value, &result);

  // ASSERT: Verify even small fractional parts are properly handled
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 5: Negative number with fractional part should round down further */
START_TEST(test_floor_negative_fraction) {
  // ARRANGE: Set up a negative decimal with fractional part
  s21_decimal value = {
      {792095801, -1320247423, 6, -2147418112}};  // -12345678901234567890.5
  s21_decimal expected = {
      {-350287149, -1420514932, 0, -2147483648}};  // -12345678901234567891

  // ACT: Call the floor function
  s21_decimal result;
  int error_code = s21_floor(value, &result);

  // ASSERT: Verify negative numbers round down (more negative)
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 6: Decimal with value between 0 and 1 should floor to zero */
START_TEST(test_floor_zero) {
  // ARRANGE: Set up a decimal value between 0 and 1
  s21_decimal value = {{25, 0, 0, 131072}};  // 0.25
  s21_decimal expected = {{0, 0, 0, 0}};     // 0

  // ACT: Call the floor function
  s21_decimal result;
  int error_code = s21_floor(value, &result);

  // ASSERT: Verify positive fractions less than 1 floor to zero
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 7: Positive number with very small fractional part */
START_TEST(test_floor_small_fraction_positive) {
  // ARRANGE: Set up a positive decimal with very small fractional part
  s21_decimal value = {{10625, 10000, 0, 262144}};  // 4294967297.0625
  s21_decimal expected = {{1, 1, 0, 0}};            // 4294967297

  // ACT: Call the floor function
  s21_decimal result;
  int error_code = s21_floor(value, &result);

  // ASSERT: Verify tiny fractional parts are properly truncated
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 8: Negative number with very small fractional part */
START_TEST(test_floor_small_fraction_negative) {
  // ARRANGE: Set up a negative decimal with very small fractional part
  s21_decimal value = {{10625, 100000, 0, -2147221504}};  // -42949672961.0625
  s21_decimal expected = {{2, 10, 0, -2147483648}};       // -42949672962

  // ACT: Call the floor function
  s21_decimal result;
  int error_code = s21_floor(value, &result);

  // ASSERT: Verify negative numbers with tiny fractions round down
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 9: Negative numbers with exact half should round down correctly */
START_TEST(test_floor_negative_exact_half) {
  // ARRANGE: Set up negative decimals with exact .5 fractional parts
  s21_decimal value = {{15, 10, 0, -2147418112}};   // -4294967297.5
  s21_decimal expected = {{2, 1, 0, -2147483648}};  // -4294967298

  // ACT: Call the floor function
  s21_decimal result;
  int error_code = s21_floor(value, &result);

  // ASSERT: Verify negative .5 values round down (not towards zero)
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));

  // ARRANGE: Another negative decimal with fractional part
  s21_decimal value2 = {
      {33, 2, 3000, -2146107392}};  // -55.340232221137244782625
  s21_decimal expected2 = {{56, 0, 0, -2147483648}};  // -56

  // ACT: Call the floor function again
  s21_decimal result2;
  int error_code2 = s21_floor(value2, &result2);

  // ASSERT: Verify complex negative fractions round correctly
  ck_assert_int_eq(error_code2, 0);
  ck_assert_mem_eq(&result2, &expected2, sizeof(s21_decimal));
}
END_TEST

/* Test 10: Large positive integer should remain unchanged */
START_TEST(test_floor_positive_large_integer) {
  // ARRANGE: Set up a large positive integer value
  s21_decimal value = {{133456435, 0, 0, 0}};     // 133456435
  s21_decimal expected = {{133456435, 0, 0, 0}};  // 133456435

  // ACT: Call the floor function
  s21_decimal result;
  int error_code = s21_floor(value, &result);

  // ASSERT: Verify integers without fractions remain unchanged
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

Suite *test_floor(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\033[1;33ms21_floor\033[0m");

  tc_core = tcase_create("floor_tc");

  tcase_add_test(tc_core, test_floor_positive_no_fraction);
  tcase_add_test(tc_core, test_floor_negative_no_fraction);
  tcase_add_test(tc_core, test_floor_positive_fraction);
  tcase_add_test(tc_core, test_floor_positive_fraction_small);
  tcase_add_test(tc_core, test_floor_negative_fraction);
  tcase_add_test(tc_core, test_floor_zero);
  tcase_add_test(tc_core, test_floor_small_fraction_positive);
  tcase_add_test(tc_core, test_floor_small_fraction_negative);
  tcase_add_test(tc_core, test_floor_negative_exact_half);
  tcase_add_test(tc_core, test_floor_positive_large_integer);

  suite_add_tcase(s, tc_core);

  return s;
}
