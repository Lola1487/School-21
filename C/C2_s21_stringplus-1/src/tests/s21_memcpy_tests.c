#include "s21_test_runner.h"

/*!
 * @test Test basic functionality of s21_memcpy with simple string copying.
 */
START_TEST(s21_memcpy_basic_functionality) {
  /* ARRANGE */
  const char* source_str = "Hello World!";
  char* destination_str;
  char* expected_result;
  size_t length = strlen(source_str) + 1;  // Including null terminator

  destination_str = malloc(length);
  expected_result = malloc(length);
  memset(destination_str, '!',
         length);  // Fill destination buffer with some value
  memset(expected_result, '!', length);

  /* ACT */
  memcpy(expected_result, source_str, length);
  const void* actual_result = s21_memcpy(destination_str, source_str, length);

  /* ASSERT */
  ck_assert_msg(actual_result == destination_str,
                "Return value should be equal to destination pointer.");
  ck_assert_mem_eq(destination_str, expected_result, length);

  /* Clean up allocated memory */
  free(destination_str);
  free(expected_result);
}
END_TEST

/*!
 * @test Test s21_memcpy when copying partial strings.
 */
START_TEST(s21_memcpy_partial_copy) {
  /* ARRANGE */
  const char* source_str = "This is a longer string.";
  char* destination_str;
  char* expected_result;
  size_t length = 10;  // Copy only first 10 characters

  destination_str = malloc(strlen(source_str) + 1);
  expected_result = malloc(strlen(source_str) + 1);
  memset(destination_str, '#', strlen(source_str) + 1);
  memset(expected_result, '#', strlen(source_str) + 1);

  /* ACT */
  memcpy(expected_result, source_str, length);
  const void* actual_result = s21_memcpy(destination_str, source_str, length);

  /* ASSERT */
  ck_assert_msg(actual_result == destination_str,
                "Return value should be equal to destination pointer.");
  ck_assert_mem_eq(destination_str, expected_result, length);

  /* Clean up allocated memory */
  free(destination_str);
  free(expected_result);
}
END_TEST

/*!
 * @test Test s21_memcpy when copying zero bytes.
 */
START_TEST(s21_memcpy_zero_bytes) {
  /* ARRANGE */
  const char* source_str = "";
  char* destination_str;
  char* expected_result;
  size_t length = 0;  // No bytes to copy

  destination_str = malloc(1);
  expected_result = malloc(1);
  memset(destination_str, '@', 1);
  memset(expected_result, '@', 1);

  /* ACT */
  memcpy(expected_result, source_str, length);
  const void* actual_result = s21_memcpy(destination_str, source_str, length);

  /* ASSERT */
  ck_assert_msg(actual_result == destination_str,
                "Return value should be equal to destination pointer.");
  ck_assert_mem_eq(destination_str, expected_result, 1);

  /* Clean up allocated memory */
  free(destination_str);
  free(expected_result);
}
END_TEST

/*!
 * @test Test s21_memcpy when source and destination pointers are the same.
 */
START_TEST(s21_memcpy_same_pointers) {
  /* ARRANGE */
  const char* source_str = "Duplicate data";
  char* destination_str;
  size_t length = strlen(source_str) + 1;

  destination_str = malloc(length);
  strcpy(destination_str, source_str);

  /* ACT */
  const void* actual_result =
      s21_memcpy(destination_str, destination_str, length);

  /* ASSERT */
  ck_assert_msg(actual_result == destination_str,
                "Return value should be equal to destination pointer.");
  ck_assert_str_eq(destination_str, source_str);

  /* Clean up allocated memory */
  free(destination_str);
}
END_TEST

/*!
 * @brief Creates a test suite for testing s21_memcpy function.
 *
 * @return A pointer to the created test suite.
 */
Suite* tests_for_memcpy() {
  Suite* s;
  TCase* tc_memcpy;

  s = suite_create("memcpy_tests");
  tc_memcpy = tcase_create("memcpy_tc");

  tcase_add_test(tc_memcpy, s21_memcpy_basic_functionality);
  tcase_add_test(tc_memcpy, s21_memcpy_partial_copy);
  tcase_add_test(tc_memcpy, s21_memcpy_zero_bytes);
  tcase_add_test(tc_memcpy, s21_memcpy_same_pointers);

  suite_add_tcase(s, tc_memcpy);

  return s;
}
