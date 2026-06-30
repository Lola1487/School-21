#ifndef S21_TEST_DECIMAL_H
#define S21_TEST_DECIMAL_H

#include <check.h>   // Check unit testing framework
#include <limits.h>  // For integer limits
#include <stdio.h>   // Standard I/O functions

#include "../s21_decimal.h"  // Main decimal library header

// Arithmetic operation test suites
Suite *test_add(void);  ///< Test suite for addition operation
Suite *test_sub(void);  ///< Test suite for subtraction operation
Suite *test_div(void);  ///< Test suite for division operation
Suite *test_mul(void);  ///< Test suite for multiplication operation

// Comparison operation test suites
Suite *test_is_greater(void);  ///< Test suite for greater than comparison
Suite *test_is_greater_or_equal(
    void);                  ///< Test suite for greater than or equal comparison
Suite *test_is_less(void);  ///< Test suite for less than comparison
Suite *test_is_less_or_equal(
    void);                   ///< Test suite for less than or equal comparison
Suite *test_is_equal(void);  ///< Test suite for equality comparison
Suite *test_is_not_equal(void);  ///< Test suite for inequality comparison

// Conversion and utility function test suites
Suite *test_negate(void);    ///< Test suite for negation operation
Suite *test_truncate(void);  ///< Test suite for truncate operation
Suite *test_round(void);     ///< Test suite for rounding operation
Suite *test_floor(void);     ///< Test suite for floor operation

// Type conversion test suites
Suite *test_from_int_to_decimal(
    void);  ///< Test suite for integer to decimal conversion
Suite *test_from_decimal_to_int(
    void);  ///< Test suite for decimal to integer conversion
Suite *test_from_float_to_decimal(
    void);  ///< Test suite for float to decimal conversion
Suite *test_from_decimal_to_float(
    void);  ///< Test suite for decimal to float conversion

#endif  // S21_TEST_DECIMAL_H
