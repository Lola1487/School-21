#include "s21_test_runner.h"

#include <stdio.h>

int main(void) {
  int total_fail_count = 0;
  int total_pass_count = 0;

  // Array of all test suites to be executed, NULL-terminated
  Suite *suites[] = {
      create_matrix_suite(),    remove_matrix_suite(),  eq_matrix_suite(),
      sum_matrix_suite(),       sub_matrix_suite(),     mult_number_suite(),
      mult_matrix_suite(),      transpose_suite(),      determinant_suite(),
      calc_complements_suite(), inverse_matrix_suite(), NULL};

  // Run each test suite individually
  for (int i = 0; suites[i] != NULL; i++) {
    SRunner *runner = srunner_create(suites[i]);

    // Disable forking for cleaner output and easier debugging
    srunner_set_fork_status(runner, CK_NOFORK);

    // Run all tests in the suite
    srunner_run_all(runner, CK_NORMAL);

    // Get test statistics for current suite
    int fail_count = srunner_ntests_failed(runner);
    int total_tests = srunner_ntests_run(runner);

    // Update global counters
    total_fail_count += fail_count;
    total_pass_count += (total_tests - fail_count);

    // Print colored result for current suite
    if (fail_count > 0) {
      printf("\033[31m❌ Tests failed: %d errors detected.\033[0m\n",
             fail_count);
    } else {
      printf("\033[32m✅ All tests passed successfully!\033[0m\n");
    }

    // Free runner resources
    srunner_free(runner);
  }

  // Print final summary with colored statistics
  printf("\n=== Final Test Results ===\n");
  printf("Total tests passed: \033[32m%d\033[0m\n", total_pass_count);
  printf("Total tests failed: \033[31m%d\033[0m\n", total_fail_count);
  printf("=========================\n");

  return total_fail_count;
}

// Helper function to initialize matrix with values from a flat array
void init_matrix(s21_matrix *A, int rows, int columns, const double values[]) {
  // Safety check: if creation fails, we avoid writing to invalid memory
  if (s21_create_matrix(rows, columns, A) != OK) {
    return;
  }

  int idx = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A->matrix[i][j] = values[idx++];
    }
  }
}
