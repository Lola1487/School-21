# ======================
# Configuration Section
# ======================

# Use Bash as the shell for executing commands
SHELL := /bin/bash

# Compiler to use (GCC in this case)
CC = gcc

# Compiler flags:
# -std=c11: Use the C11 standard
# -Wall: Enable all warnings
# -Wextra: Enable extra warnings
# -Werror: Treat warnings as errors
CFLAGS = -g -std=c11 -Wall -Wextra -Werror

# Memory-related flags for sanitizers
# These flags enable advanced memory checks (e.g., for leaks, undefined behavior)
MEMFLAGS = -fsanitize=address -fsanitize=leak -fsanitize=undefined -fsanitize=unreachable

# Libraries to link against:
# -lm: Math library
# -lsubunit: Library for unit testing (used with Check)
LIBRARIES = -lm -lsubunit

# Directory containing test files
TEST_DIR = ./tests/

# Source files matching the pattern s21_*.c
SRC_FILES = s21_*.c

# All source and header files (including test files)
ALL_SRC_FILES = ./*.c ./*.h $(TEST_DIR)*.c $(TEST_DIR)*.h

# Header file for the project
HEADER_FILE = s21_string.h

# Object files derived from source files
OBJ_FILES = $(SRC_FILES:.c=.o)

# Clang-format tool for code formatting
CLANG_FORMAT = clang-format

# Clang-format style to use (Google style)
CLANG_FORMAT_STYLE = --style=google

# Cppcheck tool for static code analysis
CPPCHECK = cppcheck

# Cppcheck flags:
# --enable=all: Enable all checks
# --std=c11: Use the C11 standard
# --suppress=missingIncludeSystem: Ignore missing system includes
# --suppress=checkersReport: Suppress checker reports
CPPCHECK_FLAGS = --enable=all --std=c11 --suppress=missingIncludeSystem --suppress=checkersReport --suppress=unusedStructMember

# Main test runner file
TEST_RUNNER = tests/s21_test_runner.c

# All test files
TEST_SUITE = tests/*tests.c

# Flags for compiling tests:
# -lcheck: Link against the Check testing framework
# -coverage: Enable code coverage
# -lpthread -pthread: Support for threading
TEST_FLAGS = -lcheck -coverage -lpthread -pthread

# Valgrind log file
VALGRIND_LOG = valgrind_results.log

# ======================
# Targets Section
# ======================

# Define phony targets (targets that don't create files)
.PHONY: all test gcov_report valgrind sanitize check check_code_style run_static_analysis format_code clean help check_no_sanitize full_check

# Default target: clean, build the library, and run all checks
all: clean s21_string.a check_no_sanitize

# Target to build the standard library (without sanitizers)
s21_string.a: $(SRC_FILES)
	# Compile source files into object files (without sanitizers)
	$(CC) $(CFLAGS) -c $(SRC_FILES)
	# Create an archive (static library) from object files
	ar rc $@ $(OBJ_FILES)
	# Index the archive for faster linking
	ranlib $@
	# Remove object files after creating the library
	rm $(OBJ_FILES)

# Target to build library with sanitizers for testing
s21_string_asan.a: $(SRC_FILES)
	# Compile source files with sanitizers enabled
	$(CC) $(CFLAGS) $(MEMFLAGS) -c $(SRC_FILES)
	# Create an archive (static library) from object files
	ar rc $@ $(OBJ_FILES)
	# Index the archive for faster linking
	ranlib $@
	# Remove object files after creating the library
	rm $(OBJ_FILES)

# Target to run tests with standard library
test: clean s21_string.a
	# Compile and link the test runner with the standard library
	$(CC) $(CFLAGS) $(TEST_RUNNER) $(TEST_SUITE) $(TEST_FLAGS) s21_string.a -o test_suite $(LIBRARIES)
	# Run the test suite
	./test_suite

# Target to run tests with AddressSanitizer
sanitize: clean s21_string_asan.a
	@echo "############################################################"
	@echo "##### AddressSanitizer testing started #####################"
	@echo "############################################################"
	$(CC) $(CFLAGS) $(MEMFLAGS) $(TEST_RUNNER) $(TEST_SUITE) $(TEST_FLAGS) s21_string_asan.a -o sanitize_test $(LIBRARIES)
	./sanitize_test

# Target to generate a code coverage report
gcov_report: clean
	# Compile with coverage flags
	$(CC) $(CFLAGS) $(TEST_RUNNER) $(TEST_SUITE) $(TEST_FLAGS) $(SRC_FILES) -o gcov_report $(LIBRARIES)
	# Run the test suite to generate coverage data
	./gcov_report
	# Generate coverage information using lcov
	lcov -t "gcov_report" -o gcov_report.info -c -d .
	# Generate an HTML report from the coverage data
	genhtml -o report gcov_report.info
	# Clean up temporary files
	rm -rf *.gcda *.gcno gcov_report gcov_report.info
	# Open the HTML coverage report in the default browser
	@echo "############################################################"
	@echo "##### Gcov Report ##########################################"
	@echo "############################################################"
	open ./report/index.html || xdg-open ./report/index.html
	@echo "Report generated at ./report/index.html"

# Target to check for memory leaks using Valgrind
valgrind: test
	# Run the test suite with Valgrind to detect memory issues
	@echo "############################################################"
	@echo "##### Valgrind testing started #############################"
	@echo "############################################################"
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes -s --num-callers=20 --log-file="$(VALGRIND_LOG)" ./test_suite

# Target for running all checks except sanitize
check_no_sanitize: check_code_style run_static_analysis test valgrind

# Target for running all checks including sanitize
full_check: check_no_sanitize sanitize

# Target to run all checks (old name for backward compatibility)
check: full_check

# Target to check code style using clang-format
check_code_style:
	@echo "############################################################"
	@echo "##### ClangFormat checking #################################"
	@echo "############################################################"
	# Check code style without modifying files (-n flag)
	$(CLANG_FORMAT) $(CLANG_FORMAT_STYLE) -n $(ALL_SRC_FILES)

# Target to run static code analysis using cppcheck
run_static_analysis:
	@echo "############################################################"
	@echo "##### Cppcheck started #####################################"
	@echo "############################################################"
	# Run cppcheck with specified flags on all source files
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(ALL_SRC_FILES)

# Target to apply code style formatting using clang-format
format_code:
	@echo "############################################################"
	@echo "##### ClangFormat formatting ###############################"
	@echo "############################################################"
	# Apply code style formatting and modify files in place (-i flag)
	$(CLANG_FORMAT) $(CLANG_FORMAT_STYLE) -i $(ALL_SRC_FILES)

# Target to clean up build artifacts
clean:
	@echo "############################################################"
	@echo "##### Clean up started #####################################"
	@echo "############################################################"
	# Remove object files, libraries, test binaries, coverage files, and reports
	rm -f *.o *.a test_suite* gcov_report sanitize_test *.gcno *.gcda *.info *.log
	rm -rf report/

# Help target to show available options
help:
	@echo "Available targets:"
	@echo "  all           - Clean, build the library, run tests and Valgrind"
	@echo "  s21_string.a  - Build the standard static library (without sanitizers)"
	@echo "  s21_string_asan.a - Build the library with AddressSanitizer"
	@echo "  test          - Run unit tests with standard library"
	@echo "  sanitize      - Run tests with AddressSanitizer"
	@echo "  gcov_report   - Generate code coverage report"
	@echo "  valgrind      - Check for memory leaks using Valgrind"
	@echo "  check_no_sanitize - Run all checks except sanitize"
	@echo "  full_check    - Run all checks including sanitize"
	@echo "  check         - Alias for full_check"
	@echo "  check_code_style - Check code style using clang-format"
	@echo "  run_static_analysis - Run static code analysis using cppcheck"
	@echo "  format_code   - Format source code using clang-format"
	@echo "  clean         - Remove build artifacts"
	@echo "  help          - Show this help message"
