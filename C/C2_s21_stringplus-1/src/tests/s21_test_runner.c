#include "s21_test_runner.h"

int main(void) {
  int total_fail_count = 0;  // Total number of failed tests
  int total_pass_count = 0;  // Total number of passed tests

  // Array of test suites to be executed
  Suite *test_list[] = {
      tests_for_memchr(),   tests_for_memcmp(),   tests_for_memcpy(),
      tests_for_memset(),   tests_for_strncat(),  tests_for_strchr(),
      tests_for_strncmp(),  tests_for_strncpy(),  tests_for_strcspn(),
      tests_for_strerror(), tests_for_strpbrk(),  tests_for_strrchr(),
      tests_for_strstr(),   tests_for_strtok(),   tests_for_strlen(),
      tests_for_to_upper(), tests_for_to_lower(), tests_for_insert(),
      tests_for_trim(),     tests_for_sprintf(),  tests_for_wchar_wcstombs(),
      tests_for_sscanf(),
  };

  // Calculate the number of test suites in the array
  size_t num_tests = sizeof(test_list) / sizeof(test_list[0]);

  // Loop through each test suite and execute it
  for (size_t i = 0; i < num_tests; i++) {
    Suite *s;
    SRunner *runner;

    // Create a test suite runner
    s = test_list[i];
    runner = srunner_create(s);

    // Set the fork status to avoid forking (useful for debugging)
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

    // Free the runner after execution
    srunner_free(runner);
  }

  // Print the final summary
  printf("\n=== Final Test Results ===\n");
  printf("Total tests passed: \033[32m%d\033[0m\n", total_pass_count);
  printf("Total tests failed: \033[31m%d\033[0m\n", total_fail_count);
  printf("=========================\n");

  // Return the total number of failed tests
  return total_fail_count;
}
