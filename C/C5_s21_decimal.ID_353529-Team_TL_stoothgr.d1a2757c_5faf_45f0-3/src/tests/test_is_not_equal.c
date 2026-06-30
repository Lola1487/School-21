#include "test_decimal.h"

/* Test 1: Two zero decimals should be equal (return 0 for not_equal) */
START_TEST(test_is_not_equal_zero_values) {
  // ARRANGE: Set up two zero decimal values
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  // ACT: Call the is_not_equal function
  int result = s21_is_not_equal(val1, val2);

  // ASSERT: Verify that zeros are considered equal (not not_equal)
  ck_assert_int_eq(0, result);
}
END_TEST

/* Test 2: Different values with different signs should not be equal */
START_TEST(test_is_not_equal_different_values_and_signs) {
  // ARRANGE: Set up two different decimal values with opposite signs
  s21_decimal val1 = {{1, 2, 3, 655360}};       // Positive value
  s21_decimal val2 = {{3, 2, 1, -2146828288}};  // Negative value

  // ACT: Call the is_not_equal function
  int result = s21_is_not_equal(val1, val2);

  // ASSERT: Verify that different values are considered not equal
  ck_assert_int_eq(1, result);
}
END_TEST

/* Test 3: Different values with same sign should not be equal */
START_TEST(test_is_not_equal_different_values_same_sign) {
  // ARRANGE: Set up two different negative decimal values
  s21_decimal val1 = {{1, 2, 3, -2146828288}};  // Negative value 1
  s21_decimal val2 = {{3, 2, 1, -2146828288}};  // Negative value 2

  // ACT: Call the is_not_equal function
  int result = s21_is_not_equal(val1, val2);

  // ASSERT: Verify that different values are considered not equal
  ck_assert_int_eq(1, result);
}
END_TEST

/* Test 4: Different values with different scales should not be equal */
START_TEST(test_is_not_equal_different_scales) {
  // ARRANGE: Set up values with different scales but same sign
  s21_decimal val1 = {{1, 2, 3, -2146566144}};  // Scale 2, negative
  s21_decimal val2 = {{3, 2, 1, -2146959360}};  // Scale 5, negative

  // ACT: Call the is_not_equal function
  int result = s21_is_not_equal(val1, val2);

  // ASSERT: Verify that values with different scales are considered not equal
  ck_assert_int_eq(1, result);
}
END_TEST

/* Test 5: Different values with opposite signs and different scales should not
 * be equal */
START_TEST(test_is_not_equal_mixed_signs_and_scales) {
  // ARRANGE: Set up values with different signs and different scales
  s21_decimal val1 = {{10, 2, 3, -2146566144}};  // Negative, scale 2
  s21_decimal val2 = {{3, 2, 1, 524288}};        // Positive, scale 1

  // ACT: Call the is_not_equal function
  int result = s21_is_not_equal(val1, val2);

  // ASSERT: Verify that completely different values are considered not equal
  ck_assert_int_eq(1, result);
}
END_TEST

/* Test 6: Identical values with same scale should be equal */
START_TEST(test_is_not_equal_identical_values) {
  // ARRANGE: Set up two identical decimal values
  s21_decimal val1 = {{1, 2, 3, 917504}};  // Value with specific scale
  s21_decimal val2 = {{1, 2, 3, 917504}};  // Same value and scale

  // ACT: Call the is_not_equal function
  int result = s21_is_not_equal(val1, val2);

  // ASSERT: Verify that identical values are considered equal (not not_equal)
  ck_assert_int_eq(0, result);
}
END_TEST

Suite *test_is_not_equal(void) {
  Suite *s = suite_create("\033[1;34ms21_is_not_equal\033[0m");
  TCase *tc = tcase_create("is_not_equal_tc");

  tcase_add_test(tc, test_is_not_equal_zero_values);
  tcase_add_test(tc, test_is_not_equal_different_values_and_signs);
  tcase_add_test(tc, test_is_not_equal_different_values_same_sign);
  tcase_add_test(tc, test_is_not_equal_different_scales);
  tcase_add_test(tc, test_is_not_equal_mixed_signs_and_scales);
  tcase_add_test(tc, test_is_not_equal_identical_values);

  suite_add_tcase(s, tc);
  return s;
}
