# Colors for statuses:
RED = \033[0;31m    # Error
GREEN = \033[0;32m  # Success
YELLOW = \033[0;33m # Warnings/Waiting
BLUE = \033[0;34m   # Informational messages
NC = \033[0m        # No Color

# Compiler to use (GCC in this case)
CC = gcc

CFLAGS = -std=c11 -Wall -Wextra -Werror

MEMFLAGS = -fsanitize=address -fsanitize=leak -fsanitize=undefined -fsanitize=unreachable


LDFLAGS = -lcheck -lsubunit -lm

GCOV_FLAGS = -fprofile-arcs -ftest-coverage

ARITH_DIR = arithmetic
CMP_DIR = comparison
CONV_DIR = conversion
OTHER_DIR = other
COMMON_DIR = common
TESTS_DIR = tests
SRC_ARITH   = $(wildcard $(ARITH_DIR)/*.c)
SRC_CMP     = $(wildcard $(CMP_DIR)/*.c)
SRC_CONV    = $(wildcard $(CONV_DIR)/*.c)
SRC_OTHER   = $(wildcard $(OTHER_DIR)/*.c)
SRC_COMMON  = $(wildcard $(COMMON_DIR)/*.c)
SRC_TESTS   = $(wildcard $(TESTS_DIR)/*.c)

OBJ_ARITH   = $(patsubst $(ARITH_DIR)/%.c,%.o, $(SRC_ARITH))
OBJ_CMP     = $(patsubst $(CMP_DIR)/%.c,%.o, $(SRC_CMP))
OBJ_CONV    = $(patsubst $(CONV_DIR)/%.c,%.o, $(SRC_CONV))
OBJ_OTHER   = $(patsubst $(OTHER_DIR)/%.c,%.o, $(SRC_OTHER))
OBJ_COMMON  = $(patsubst $(COMMON_DIR)/%.c,%.o, $(SRC_COMMON))


ALL_SRC_FILES := $(shell find . -type f \( -name "*.c" -o -name "*.h" \))

CLANG_FORMAT = clang-format


CLANG_FORMAT_STYLE = --style=google

# Cppcheck tool for static code analysis
CPPCHECK = cppcheck

# Cppcheck flags:
# --enable=all: Enable all checks
# --inconclusive: show inconclusive results
# --std=c11: Use the C11 standard
# --suppress=missingIncludeSystem: Ignore missing system includes
# --suppress=checkersReport: Suppress checker reports
CPPCHECK_FLAGS = --enable=all --inconclusive --std=c11 \
                 --suppress=missingIncludeSystem --suppress=checkersReport \
                 --suppress=unusedStructMember

# Valgrind log file
VALGRIND_LOG = valgrind_results.log

# ======================
# Targets Section
# ======================

# Define phony targets (targets that don't create files)
.PHONY: all clean rebuild gcov_report valgrind valgrind_run valgrind_log test \
        check_code_style format_code run_static_analysis help check_no_sanitize sanitize

# Build Targets
# ============================================================
# These targets handle compiling source code and building libraries

# Default target when you just run 'make'
# It depends on the 'all' target which builds the main library
all: clean s21_decimal.a check_no_sanitize

# Build the main static library
# This target depends on all arithmetic, comparison, conversion, other, and common sources
s21_decimal.a: $(SRC_ARITH) $(SRC_CMP) $(SRC_CONV) $(SRC_OTHER) $(SRC_COMMON)
	@echo "$(BLUE)############################################################$(NC)"
	@echo "$(BLUE)##### Building s21_decimal library #########################$(NC)"
	@echo "$(BLUE)############################################################$(NC)"

	@echo "$(BLUE)Find files... $(NC)"
	@echo "$(BLUE)All found source files for compilation:$(NC)"

    # Show files grouped by categories
	@echo "$(BLUE)Arithmetic files:$(NC)"
	@for file in $(SRC_ARITH); do \
		echo "$(BLUE)  $$(basename $$file)$(NC)"; \
	done

	@echo "$(BLUE)Comparison files:$(NC)"
	@for file in $(SRC_CMP); do \
		echo "$(BLUE)  $$(basename $$file)$(NC)"; \
	done

	@echo "$(BLUE)Conversion files:$(NC)"
	@for file in $(SRC_CONV); do \
		echo "$(BLUE)  $$(basename $$file)$(NC)"; \
	done

	@echo "$(BLUE)Other files:$(NC)"
	@for file in $(SRC_OTHER); do \
		echo "$(BLUE)  $$(basename $$file)$(NC)"; \
	done

	@echo "$(BLUE)Common files:$(NC)"
	@for file in $(SRC_COMMON); do \
		echo "$(BLUE)  $$(basename $$file)$(NC)"; \
	done

    # Compile all source files to object files
    # -c flag: compile only (don't link)
    # $^: automatic variable that expands to all dependencies
	@echo "$(BLUE)Compiling all source files to object files...$(NC)"
	@$(CC) -c $(CFLAGS) $^

    # Create static library using 'ar' (archive utility)
    # r: replace existing files
    # c: create archive if not exists
    # s: write index for faster linking
    # $@: automatic variable for target name (s21_decimal.a)
	@echo "$(BLUE)Creating static library using 'ar' (archive utility)...$(NC)"
	@ar rcs $@ $(OBJ_ARITH) $(OBJ_CMP) $(OBJ_CONV) $(OBJ_OTHER) $(OBJ_COMMON)
    # Index the archive for faster linking
	@ranlib $@
    # Remove object files after creating the library
	@rm $(OBJ_ARITH) $(OBJ_CMP) $(OBJ_CONV) $(OBJ_OTHER) $(OBJ_COMMON)

	@echo "$(GREEN)Library built: s21_decimal.a$(NC)"

# Target to build library with sanitizers for testing
# This target depends on all arithmetic, comparison, conversion, other, and common sources
s21_decimal_asan.a: $(SRC_ARITH) $(SRC_CMP) $(SRC_CONV) $(SRC_OTHER) $(SRC_COMMON)
	@echo "$(BLUE)############################################################$(NC)"
	@echo "$(BLUE)# Building s21_decimal library with sanitizers for testing #$(NC)"
	@echo "$(BLUE)############################################################$(NC)"

	@echo "$(BLUE)Find files... $(NC)"
	@echo "$(BLUE)All found source files for compilation:$(NC)"

    # Show files grouped by categories
	@echo "$(BLUE)Arithmetic files:$(NC)"
	@for file in $(SRC_ARITH); do \
		echo "$(BLUE)  $$(basename $$file)$(NC)"; \
	done

	@echo "$(BLUE)Comparison files:$(NC)"
	@for file in $(SRC_CMP); do \
		echo "$(BLUE)  $$(basename $$file)$(NC)"; \
	done

	@echo "$(BLUE)Conversion files:$(NC)"
	@for file in $(SRC_CONV); do \
		echo "$(BLUE)  $$(basename $$file)$(NC)"; \
	done

	@echo "$(BLUE)Other files:$(NC)"
	@for file in $(SRC_OTHER); do \
		echo "$(BLUE)  $$(basename $$file)$(NC)"; \
	done

	@echo "$(BLUE)Common files:$(NC)"
	@for file in $(SRC_COMMON); do \
		echo "$(BLUE)  $$(basename $$file)$(NC)"; \
	done

    # Compile source files with sanitizers enabled
    # Compile all source files to object files
    # -c flag: compile only (don't link)
    # $^: automatic variable that expands to all dependencies
	@echo "$(BLUE)Compiling all source files to object files...$(NC)"
	@$(CC) -c $(CFLAGS) $(MEMFLAGS) $^

    # Create static library using 'ar' (archive utility)
    # r: replace existing files
    # c: create archive if not exists
    # s: write index for faster linking
    # $@: automatic variable for target name (s21_decimal.a)
	@echo "$(BLUE)Creating static library using 'ar' (archive utility)...$(NC)"
	@ar rcs $@ $(OBJ_ARITH) $(OBJ_CMP) $(OBJ_CONV) $(OBJ_OTHER) $(OBJ_COMMON)
# Index the archive for faster linking
	@ranlib $@
    # Remove object files after creating the library
	@rm $(OBJ_ARITH) $(OBJ_CMP) $(OBJ_CONV) $(OBJ_OTHER) $(OBJ_COMMON)

	@echo "$(GREEN)Library built: s21_decimal_asan.a$(NC)"

# Test Targets
# ============================================================
# These targets handle testing, coverage analysis, and quality checks

# Target to run unit tests with standard library
test: clean s21_decimal.a
	@echo "$(BLUE)############################################################$(NC)"
	@echo "$(BLUE)##### Running unit tests ###################################$(NC)"
	@echo "$(BLUE)############################################################$(NC)"

    # Compile test files with the library
	@$(CC) $(CFLAGS) $(SRC_TESTS) s21_decimal.a -o unit_test $(LDFLAGS)

    # Execute the test program
	./unit_test

# Build library with coverage instrumentation
gcov_s21_decimal.a: clean
	@echo "$(BLUE)############################################################$(NC)"
	@echo "$(BLUE)##### Building library for coverage analysis ###############$(NC)"
	@echo "$(BLUE)############################################################$(NC)"

	@echo "$(BLUE)Find files... $(NC)"
	@echo "$(BLUE)All found source files for compilation:$(NC)"

    # Show files grouped by categories
	@echo "$(BLUE)Arithmetic files:$(NC)"
	@for file in $(SRC_ARITH); do \
		echo "$(BLUE)  $$(basename $$file)$(NC)"; \
	done

	@echo "$(BLUE)Comparison files:$(NC)"
	@for file in $(SRC_CMP); do \
		echo "$(BLUE)  $$(basename $$file)$(NC)"; \
	done

	@echo "$(BLUE)Conversion files:$(NC)"
	@for file in $(SRC_CONV); do \
		echo "$(BLUE)  $$(basename $$file)$(NC)"; \
	done

	@echo "$(BLUE)Other files:$(NC)"
	@for file in $(SRC_OTHER); do \
		echo "$(BLUE)  $$(basename $$file)$(NC)"; \
	done

	@echo "$(BLUE)Common files:$(NC)"
	@for file in $(SRC_COMMON); do \
		echo "$(BLUE)  $$(basename $$file)$(NC)"; \
	done

    # Compile source files with coverage flags
    # -c flag: compile only (don't link)
	@$(CC) -c $(CFLAGS) $(GCOV_FLAGS) $(SRC_ARITH) $(SRC_CMP) $(SRC_CONV) $(SRC_OTHER) $(SRC_COMMON)

    # Create instrumented library using 'ar' (archive utility)
    # r: replace existing files
    # c: create archive if not exists
    # s: write index for faster linking
	@echo "$(BLUE)Creating instrumented library using 'ar' (archive utility)...$(NC)"
	@ar rcs s21_decimal.a $(OBJ_ARITH) $(OBJ_CMP) $(OBJ_CONV) $(OBJ_OTHER) $(OBJ_COMMON)
    # Remove object files after creating the library
	@rm $(OBJ_ARITH) $(OBJ_CMP) $(OBJ_CONV) $(OBJ_OTHER) $(OBJ_COMMON)

	@echo "$(GREEN)Instrumented library built: s21_decimal.a$(NC)"

# Generate code coverage report
gcov_report: gcov_s21_decimal.a
	@echo "$(BLUE)############################################################$(NC)"
	@echo "$(BLUE)##### Generating coverage report ###########################$(NC)"
	@echo "$(BLUE)############################################################$(NC)"

    # Compile test runner with coverage support
	@$(CC) $(CFLAGS) $(GCOV_FLAGS) $(SRC_TESTS) s21_decimal.a -o gcov_unit_test $(LDFLAGS)

	@echo "$(BLUE)Run tests to generate coverage data...$(NC)"
	./gcov_unit_test

	@echo "$(BLUE)Generate coverage information for each source file...$(NC)"
	@gcov $(OBJ_ARITH) $(OBJ_CMP) $(OBJ_CONV) $(OBJ_OTHER) $(OBJ_COMMON)


	@echo "$(BLUE)Create LCOV info file...$(NC)"
	lcov -t "gcov_report" -o s21_decimal_coverage.info -c -d .


	@echo "$(BLUE)Generate HTML report from LCOV data...$(NC)"
	genhtml -o report s21_decimal_coverage.info
	@echo "$(GREEN)Report generated at ./report/index.html$(NC)"

	@echo "$(BLUE)Clean up temporary files$(NC)"
	rm -rf *.gcda *.gcno gcov_report gcov_report.info s21_decimal.a *.gcov

	@echo "$(BLUE)Open the HTML coverage report in the default browser$(NC)"
	open ./report/index.html 2>/dev/null || xdg-open ./report/index.html 2>/dev/null

valgrind: valgrind_run valgrind_log


# Target to check for memory leaks using Valgrind and save results to log file
valgrind_run: test
	@echo "$(BLUE)############################################################$(NC)"
	@echo "$(BLUE)##### Valgrind testing started #############################$(NC)"
	@echo "$(BLUE)############################################################$(NC)"

    # Run with Valgrind
    # --tool=memcheck: use memory error detector
    # --leak-check=yes: show details of leaks
	valgrind --tool=memcheck --leak-check=yes \
	--log-file="$(VALGRIND_LOG)" ./unit_test

	@echo "$(GREEN)Results saved to "$(VALGRIND_LOG)"$(NC)"

valgrind_log:
	@echo "$(BLUE)############################################################$(NC)"
	@echo "$(BLUE)############ Valgrind log ##################################$(NC)"
	@echo "$(BLUE)############################################################$(NC)"

	@echo "$(BLUE)Find errors in "$(VALGRIND_LOG)"...$(NC)"

	@if [ ! -f "$(VALGRIND_LOG)" ]; then \
		echo "$(YELLOW)==== Valgrind log file not found! ====$(NC)"; \
		echo "$(YELLOW)Run valgrind_run target first$(NC)"; \
	elif ! grep -q "ERROR SUMMARY: [1-9]" "$(VALGRIND_LOG)"; then \
		echo "$(GREEN)==== Valgrind: No memory leaks or errors found. ====$(NC)"; \
	else \
		echo "$(RED)==== Valgrind: Errors detected! ====\nPlease check $(VALGRIND_LOG) for details.$(NC)"; \
		grep -A 2 "ERROR SUMMARY" "$(VALGRIND_LOG)" | tail -n 1; \
	fi

# Target to run unit tests with AddressSanitizer
sanitize: clean s21_decimal_asan.a
	@echo "$(BLUE)############################################################$(NC)"
	@echo "$(BLUE)##### AddressSanitizer testing started #####################$(NC)"
	@echo "$(BLUE)############################################################$(NC)"

    # Compile test files with the library
	@$(CC) $(CFLAGS) $(MEMFLAGS) $(SRC_TESTS) s21_decimal_asan.a -o sanitize_test $(LDFLAGS)

    # Execute the test program
	./sanitize_test

# Code Quality Targets
# ============================================================
# These targets help maintain code quality and style

# Target to check code style using clang-format
check_code_style:
	@echo "$(BLUE)############################################################$(NC)"
	@echo "$(BLUE)##### ClangFormat checking #################################$(NC)"
	@echo "$(BLUE)############################################################$(NC)"
    # Check code style without modifying files (-n flag)
	@$(CLANG_FORMAT) $(CLANG_FORMAT_STYLE) -n $(ALL_SRC_FILES)
	@echo "$(GREEN)Check code style complete$(NC)"

# Target to apply code style formatting using clang-format
format_code:
	@echo "$(BLUE)############################################################$(NC)"
	@echo "$(BLUE)##### ClangFormat formatting ###############################$(NC)"
	@echo "$(BLUE)############################################################$(NC)"
    # Apply code style formatting and modify files in place (-i flag)
	$(CLANG_FORMAT) $(CLANG_FORMAT_STYLE) -i $(ALL_SRC_FILES)
	@echo "$(GREEN)Formatting applied to all source files$(NC)"

# Target to run static code analysis using cppcheck
run_static_analysis:
	@echo "$(BLUE)############################################################$(NC)"
	@echo "$(BLUE)##### Cppcheck started #####################################$(NC)"
	@echo "$(BLUE)############################################################$(NC)"
    # Run cppcheck with specified flags on all source files
	@$(CPPCHECK) $(CPPCHECK_FLAGS) $(ALL_SRC_FILES)

# Target for running all checks except sanitize
check_no_sanitize: check_code_style run_static_analysis test valgrind

# Target for running all checks including sanitize
check: check_no_sanitize sanitize

# Clean and Utility Targets
# ============================================================
# These targets manage build artifacts and provide help

# Remove all generated files:
# object files, libraries, test binaries, coverage files, and reports
clean:
	@echo "$(BLUE)############################################################$(NC)"
	@echo "$(BLUE)##### Clean up started #####################################$(NC)"
	@echo "$(BLUE)############################################################$(NC)"
	@echo "$(YELLOW)Remove library file$(NC)"
	rm -f s21_decimal.a
	rm -f s21_decimal_asan.a
	@echo "$(YELLOW)Remove object files$(NC)"
	rm -f *.o
	@echo "$(YELLOW)Remove precompiled headers$(NC)"
	rm -f *.h.gch
	@echo "$(YELLOW)Remove test executables$(NC)"
	rm -f unit_test
	rm -f sanitize_test
	@echo "$(YELLOW)Remove coverage artifacts$(NC)"
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f gcov_unit_test
	@echo "$(YELLOW)Remove report directories$(NC)"
	rm -rf report
	@echo "$(YELLOW)Remove info files$(NC)"
	rm -f *.info
	@echo "$(YELLOW)Remove log files$(NC)"
	rm -f $(VALGRIND_LOG)
	@echo "$(GREEN)All build artifacts removed$(NC)"

# Clean and rebuild standard static library
rebuild: clean s21_decimal.a

# Help target to show available options
help:
	@echo "$(BLUE)############################################################$(NC)"
	@echo "$(BLUE)##### s21_decimal Makefile Help ############################$(NC)"
	@echo "$(BLUE)############################################################$(NC)"
	@echo "$(BLUE)Available targets:$(NC)"
	@echo ""
	@echo "$(BLUE)  BUILD TARGETS:$(NC)"
	@echo "$(BLUE)    all               - Clean, build library and run basic checks$(NC)"
	@echo "$(BLUE)                         (clean + s21_decimal.a + check_no_sanitize)$(NC)"
	@echo "$(BLUE)    s21_decimal.a     - Build standard static library$(NC)"
	@echo "$(BLUE)    s21_decimal_asan.a - Build library with memory sanitizers$(NC)"
	@echo "$(BLUE)    rebuild           - Clean and rebuild standard static library$(NC)"
	@echo "$(BLUE)                         (clean + s21_decimal.a)$(NC)"
	@echo ""
	@echo "$(BLUE)  TESTING TARGETS:$(NC)"
	@echo "$(BLUE)    test              - Build and run unit tests (standard)$(NC)"
	@echo "$(BLUE)    sanitize          - Build and run tests with AddressSanitizer$(NC)"
	@echo "$(BLUE)    gcov_report       - Generate code coverage report$(NC)"
	@echo "$(BLUE)    valgrind          - Run full Valgrind check$(NC)"
	@echo "$(BLUE)                         (memcheck + log analysis)$(NC)"
	@echo "$(BLUE)    valgrind_run      - Run Valgrind and save results to log$(NC)"
	@echo "$(BLUE)    valgrind_log      - Analyze Valgrind log file$(NC)"
	@echo ""
	@echo "$(BLUE)  CODE QUALITY TARGETS:$(NC)"
	@echo "$(BLUE)    check_code_style     - Check code style using clang-format$(NC)"
	@echo "$(BLUE)    format_code          - Format all source code using clang-format$(NC)"
	@echo "$(BLUE)    run_static_analysis  - Run static code analysis using cppcheck$(NC)"
	@echo ""
	@echo "$(BLUE)  COMPREHENSIVE CHECK TARGETS:$(NC)"
	@echo "$(BLUE)    check_no_sanitize    - Run comprehensive checks WITHOUT sanitizers$(NC)"
	@echo "$(BLUE)                         (style + static analysis + tests + valgrind)$(NC)"
	@echo "$(BLUE)    check               - Run ALL comprehensive checks WITH sanitizers$(NC)"
	@echo "$(BLUE)                         (check_no_sanitize + sanitize)$(NC)"
	@echo ""
	@echo "$(BLUE)  MAINTENANCE TARGETS:$(NC)"
	@echo "$(BLUE)    clean             - Remove all build artifacts and reports$(NC)"
	@echo "$(BLUE)    help              - Show this help message$(NC)"
	@echo ""
	@echo "$(BLUE)  PROJECT STRUCTURE:$(NC)"
	@echo "$(BLUE)    Source files are organized in these directories:$(NC)"
	@echo "$(BLUE)      arithmetic/    - Arithmetic operations implementation$(NC)"
	@echo "$(BLUE)      comparison/    - Comparison operations implementation$(NC)"
	@echo "$(BLUE)      conversion/    - Conversion operations implementation$(NC)"
	@echo "$(BLUE)      other/         - Other operations implementation$(NC)"
	@echo "$(BLUE)      common/        - Common utilities and helpers$(NC)"
	@echo "$(BLUE)      tests/         - Unit test files$(NC)"
	@echo ""
	@echo "$(BLUE)  CODE QUALITY TOOLS:$(NC)"
	@echo "$(BLUE)    clang-format     - Code formatting (Google style)$(NC)"
	@echo "$(BLUE)    cppcheck         - Static code analysis$(NC)"
	@echo "$(BLUE)    gcov/lcov        - Code coverage reporting$(NC)"
	@echo "$(BLUE)    valgrind         - Memory leak detection$(NC)"
	@echo "$(BLUE)    AddressSanitizer - Runtime memory error detector$(NC)"
	@echo ""
	@echo "$(BLUE)############################################################$(NC)"
