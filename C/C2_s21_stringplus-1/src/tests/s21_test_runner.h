#ifndef S21_TEST_RUNNER_H
#define S21_TEST_RUNNER_H

#include <check.h>  // Include the Check unit testing framework
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"  // Include custom string library
#include "../s21_wchar.h"   // Include custom wide character library

/**
 * @file s21_test_runner.h
 * @brief Header file for the test runner of the custom string library.
 *
 * This file declares the test suites for various functions in the custom string
 * library.
 */

// Declare test suites for each function in the custom string library
Suite *tests_for_memchr();
Suite *tests_for_memcmp();
Suite *tests_for_memcpy();
Suite *tests_for_memset();
Suite *tests_for_strncat();
Suite *tests_for_strchr();
Suite *tests_for_strncmp();
Suite *tests_for_strncpy();
Suite *tests_for_strcspn();
Suite *tests_for_strerror();
Suite *tests_for_strlen();
Suite *tests_for_strpbrk();
Suite *tests_for_strrchr();
Suite *tests_for_strstr();
Suite *tests_for_strtok();
Suite *tests_for_sprintf();
Suite *tests_for_sscanf();

// Test suites for additional functions
Suite *tests_for_to_upper();
Suite *tests_for_to_lower();
Suite *tests_for_insert();
Suite *tests_for_trim();

// Test suites for other functions
Suite *tests_for_wchar_wcstombs();

#endif  // S21_TEST_RUNNER_H
