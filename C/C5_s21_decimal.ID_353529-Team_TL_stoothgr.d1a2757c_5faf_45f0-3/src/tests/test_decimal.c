#include "test_decimal.h"

int main(void) {
  int total_fail_count = 0;  // Total number of failed tests
  int total_pass_count = 0;  // Total number of passed tests

  // Array of test suites to be executed
  Suite *s21_decimal_test[] = {test_add(),
                               test_sub(),
                               test_div(),
                               test_mul(),
                               test_is_greater(),
                               test_is_greater_or_equal(),
                               test_is_less(),
                               test_is_less_or_equal(),
                               test_is_equal(),
                               test_is_not_equal(),
                               test_negate(),
                               test_truncate(),
                               test_floor(),
                               test_round(),
                               test_from_int_to_decimal(),
                               test_from_decimal_to_int(),
                               test_from_float_to_decimal(),
                               test_from_decimal_to_float(),
                               NULL};

  // Array with test suite names
  const char *suite_names[] = {"Addition",
                               "Subtraction",
                               "Division",
                               "Multiplication",
                               "Is Greater",
                               "Is Greater or Equal",
                               "Is Less",
                               "Is Less or Equal",
                               "Is Equal",
                               "Is Not Equal",
                               "Negate",
                               "Truncate",
                               "Floor",
                               "Round",
                               "From Int to Decimal",
                               "From Decimal to Int",
                               "From Float to Decimal",
                               "From Decimal to Float"};

  // Calculate the number of test suites
  int num_suites = 0;
  while (s21_decimal_test[num_suites] != NULL) {
    num_suites++;
  }

  printf("\033[36mRunning s21_decimal tests:\033[0m\n");
  printf("\033[36m==========================\033[0m\n\n");

  // Loop through each test suite and execute it
  for (int i = 0; i < num_suites; i++) {
    SRunner *runner = srunner_create(s21_decimal_test[i]);

    // Set the fork status (using CK_NOFORK like in your sample)
    srunner_set_fork_status(runner, CK_NOFORK);

    // Run all tests in the suite
    srunner_run_all(runner, CK_NORMAL);

    // Get the number of failed tests in the current suite
    int fail_count = srunner_ntests_failed(runner);
    // Get the total number of tests in the current suite
    int total_tests = srunner_ntests_run(runner);
    // Calculate the number of passed tests
    int pass_count = total_tests - fail_count;

    // Update the total number of passed and failed tests
    total_fail_count += fail_count;
    total_pass_count += pass_count;

    // Print the result of the current test suite with colored name
    printf("\033[93m%-25s\033[0m: ",
           suite_names[i]);  // Bright yellow for test names
    if (fail_count > 0) {
      printf("\033[31m❌ FAILED (%d/%d passed)\033[0m\n", pass_count,
             total_tests);
    } else {
      printf("\033[32m✅ PASSED (%d/%d)\033[0m\n", pass_count, total_tests);
    }

    // Free the runner after execution
    srunner_free(runner);
  }

  // Print the final summary
  printf("\n\033[36m=== Final Test Results ===\033[0m\n");
  printf("Total suites: %d\n", num_suites);
  printf("Total tests passed: \033[32m%d\033[0m\n", total_pass_count);
  printf("Total tests failed: \033[31m%d\033[0m\n", total_fail_count);
  printf("Total tests run: %d\n", total_pass_count + total_fail_count);

  if (total_fail_count == 0) {
    printf("\033[32m🎉 ALL TESTS PASSED!\033[0m\n");
  } else {
    printf("\033[31m❌ SOME TESTS FAILED!\033[0m\n");
  }
  printf("\033[36m===========================\033[0m\n");

  // Return the total number of failed tests (non-zero if any tests failed)
  return total_fail_count;
}
