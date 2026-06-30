#include "s21_sscanf.h"

/* ====================== Main Function ====================== */

// Reads formatted input from the string `str`.
int s21_sscanf(const char* input_string, const char* format_string, ...) {
  int arguments_successfully_read = 0;
  va_list argument_list;
  va_start(argument_list, format_string);

  int parsing_failed = 0;
  char* current_input_position = (char*)input_string;
  char* current_format_position = (char*)format_string;

  // Strict empty input check (after whitespace skipping)
  bool is_empty_input = true;
  for (const char* scan_position = input_string; *scan_position;
       scan_position++) {
    if (!s21_is_whitespace(*scan_position)) {
      is_empty_input = false;
      break;
    }
  }
  if (is_empty_input) {
    va_end(argument_list);
    return -1;
  }

  while ((*current_input_position || *current_format_position) &&
         !parsing_failed) {
    if (*current_format_position != '%') {
      if (s21_is_whitespace(*current_format_position)) {
        s21_skip_whitespace_characters(&current_input_position);
        current_format_position++;
      } else if (*current_input_position != *current_format_position) {
        parsing_failed = 1;
      } else {
        current_input_position++;
        current_format_position++;
      }
    } else {
      struct FormatSpecifier spec_info;
      int parsing_result =
          s21_parse_format_specifier(&spec_info, &current_format_position);

      if (parsing_result != 0) {
        parsing_failed = 1;
      } else if (spec_info.format == 'n') {
        int* position_ptr = va_arg(argument_list, int*);
        *position_ptr = (current_input_position - input_string);
      } else {
        int result = s21_assign_parsed_value(&current_input_position, spec_info,
                                             argument_list,
                                             &arguments_successfully_read);
        if (result == -1 && spec_info.format != '%') {
          parsing_failed = 1;
        }
      }
    }
  }

  va_end(argument_list);
  return arguments_successfully_read;
}

/* ================== Character Type Checking Functions ================== */

int s21_is_whitespace(int character) {
  return s21_char_is_in_set(character, " \f\n\r\v\t");
}

int s21_is_hex_digit(int character) {
  return s21_char_is_in_set(character, "0123456789abcdefABCDEF");
}

int s21_is_decimal_digit(int character) {
  return s21_char_is_in_set(character, "0123456789");
}

int s21_is_octal_digit(int character) {
  return s21_char_is_in_set(character, "01234567");
}

int s21_char_is_in_set(int character, char* character_set) {
  unsigned char char_to_check = (unsigned char)character;
  int is_found = 0;

  // Check if the character is in the set
  while (*character_set) {
    if (char_to_check == *character_set) {
      is_found = 1;
      break;
    }
    character_set++;
  }

  return is_found;
}

/* ========== String and Format Specifier Processing Functions * ========== */

void s21_skip_whitespace_characters(char** string_position) {
  while (s21_is_whitespace(**string_position)) {
    (*string_position)++;
  }
}

int s21_assign_parsed_value(char** string_position,
                            struct FormatSpecifier spec_info, va_list args,
                            int* arguments_read) {
  int operation_result = 0;

  // Handle literal %
  if (spec_info.format == '%') {
    if (**string_position == '%') {
      (*string_position)++;
    } else {
      operation_result = -1;
    }
    return operation_result;
  }

  // Handle pointer
  if (spec_info.format == 'p') {
    void** output_pointer = s21_NULL;
    if (!spec_info.suppress_assignment) {
      output_pointer = va_arg(args, void**);
    }

    operation_result =
        s21_read_pointer_value(string_position, spec_info, output_pointer);

    if (output_pointer && !operation_result) {
      (*arguments_read)++;
    }
    return operation_result;
  }

  // Skip whitespace for numeric and string formats
  if (s21_char_is_in_set(spec_info.format, "diouxXfFeEgGsc")) {
    s21_skip_whitespace_characters(string_position);
  }

  // Handle strings and characters
  if (s21_char_is_in_set(spec_info.format, "sc")) {
    s21_process_string_or_char_format(string_position, spec_info, args,
                                      arguments_read);
    return operation_result;
  }

  // Handle integers
  if (s21_char_is_in_set(spec_info.format, "diouxX")) {
    return s21_parse_and_store_number(string_position, spec_info, args,
                                      arguments_read, INTEGER_NUMBER);
  }

  // Handle floating-point numbers
  if (s21_char_is_in_set(spec_info.format, "fFeEgG")) {
    return s21_parse_and_store_number(string_position, spec_info, args,
                                      arguments_read, FLOATING_POINT_NUMBER);
  }

  return operation_result;
}

/* Parses format string and extracts specifier information */
int s21_parse_format_specifier(struct FormatSpecifier* spec_info,
                               char** format_string) {
  (*format_string)++;  // Skip the % character
  int parsing_result = 0;

  // Check for assignment suppression flag
  if (**format_string == '*') {
    spec_info->suppress_assignment = true;
    (*format_string)++;
  } else {
    spec_info->suppress_assignment = false;
  }

  // Read field width
  if (s21_is_decimal_digit(**format_string)) {
    spec_info->width = s21_string_to_long(*format_string, format_string, 10, 0);
  } else {
    spec_info->width = 0;
  }

  // Read length modifier
  if (s21_char_is_in_set(**format_string, "hLl")) {
    spec_info->length = **format_string;
    (*format_string)++;
  } else {
    spec_info->length = '\0';
  }

  // Read format specifier character
  if (s21_char_is_in_set(**format_string, "%csdiuoxXneEfgGp")) {
    spec_info->format = **format_string;
    (*format_string)++;
  } else {
    spec_info->format = '\0';
    parsing_result = -1;  // Invalid format
  }

  return parsing_result;
}

/* =============== String-to-Number Conversion Functions =============== */

/* Converts string to long integer with specified base */
long s21_string_to_long(const char* string_value, char** end_position,
                        int number_base, int max_width) {
  bool no_valid_number = false;
  bool overflow_detected = false;
  long result_value = 0;
  char* original_string = (char*)string_value;
  int chars_read = 0;

  // Skip whitespace characters
  s21_skip_whitespace_characters((char**)&string_value);

  if (*string_value == '\0') {
    no_valid_number = true;
  }

  // Determine the sign of the number
  int sign_multiplier = 1;
  if (!no_valid_number) {
    if (*string_value == '-') {
      sign_multiplier = -1;
      string_value++;
      chars_read++;
    } else if (*string_value == '+') {
      sign_multiplier = 1;
      string_value++;
      chars_read++;
    }
  }

  // Determine the number base if not specified
  if (number_base == 0 && !no_valid_number) {
    number_base = s21_detect_number_base(string_value);
    if (number_base == 8) {
      string_value++;  // Skip the leading 0 for octal numbers
      chars_read++;
    }
    if (number_base == -1) {
      no_valid_number = true;
    }
  }

  if (no_valid_number) {
    if (end_position) {
      *end_position = original_string;
    }
    result_value = 0;
  } else {
    // Skip the prefix for hexadecimal numbers
    if (number_base == 16 && s21_is_hex_digit(*(string_value + 2)) &&
        (s21_strncmp(string_value, "0x", 2) == 0 ||
         s21_strncmp(string_value, "0X", 2) == 0)) {
      string_value += 2;
      chars_read += 2;
    }

    // Read the digits of the number
    bool end_of_number = false;
    while (!end_of_number && *string_value &&
           (max_width == 0 || chars_read < max_width)) {
      bool is_valid_digit_for_base =
          (number_base == 16 && s21_is_hex_digit(*string_value)) ||
          (number_base == 10 && s21_is_decimal_digit(*string_value)) ||
          (number_base == 8 && s21_is_octal_digit(*string_value));

      if (is_valid_digit_for_base) {
        if (result_value > LONG_MAX / number_base) {
          overflow_detected = true;
        }
        result_value = result_value * number_base +
                       s21_convert_char_to_digit(*string_value);
        string_value++;
        chars_read++;
      } else {
        end_of_number = true;
      }
    }

    if (end_position) {
      *end_position = (char*)string_value;
    }
  }

  // Handle overflow
  if (overflow_detected) {
    result_value = (sign_multiplier == 1) ? LONG_MAX : LONG_MIN;
    sign_multiplier = 1;
  }

  return result_value * sign_multiplier;
}

int s21_convert_char_to_digit(char character) {
  int digit_value;

  if (character <= '9') {
    digit_value = character - '0';
  } else if (character >= 'a') {
    digit_value = character - 'a' + 10;
  } else {
    digit_value = character - 'A' + 10;
  }

  return digit_value;
}

/* Converts string to long double floating-point number */
long double s21_string_to_long_double(const char* string_value,
                                      char** end_position) {
  bool number_found = false;
  long double result_value = 0;
  const char* current_position = string_value;
  int sign_multiplier = 1;

  // Skip whitespace characters
  s21_skip_whitespace_characters((char**)&current_position);

  // Handle sign
  if (*current_position == '-') {
    sign_multiplier = -1;
    current_position++;
  } else if (*current_position == '+') {
    sign_multiplier = 1;
    current_position++;
  }

  // Check for special values (NaN, Infinity)
  if (s21_string_is_special_value(current_position, NOT_A_NUMBER_VALUE)) {
    if (end_position) {
      *end_position = (char*)current_position + 3;  // Skip "nan"
    }
    return (long double)NAN;
  }

  if (s21_string_is_special_value(current_position, INFINITY_VALUE)) {
    if (end_position) {
      *end_position = (char*)current_position + 3;  // Skip "inf"
    }
    return (long double)INFINITY * sign_multiplier;
  }

  // Parse integer part
  char* digit_end_position = (char*)current_position;
  while (s21_is_decimal_digit(*digit_end_position)) {
    result_value *= 10.0L;
    result_value += *digit_end_position++ - '0';
    number_found = true;
  }
  current_position = digit_end_position;

  // Parse fractional part
  if (*current_position == '.') {
    current_position++;
    long double fractional_value = 0.0L;
    long double divisor = 10.0L;

    while (s21_is_decimal_digit(*current_position)) {
      fractional_value += (*current_position - '0') / divisor;
      divisor *= 10.0L;
      current_position++;
      number_found = true;
    }
    result_value += fractional_value;
  }

  // Parse exponent part
  if (number_found && (*current_position == 'e' || *current_position == 'E')) {
    current_position++;
    int exponent_sign = 1;

    if (*current_position == '-') {
      exponent_sign = -1;
      current_position++;
    } else if (*current_position == '+') {
      current_position++;
    }

    long exponent_value = 0;
    while (s21_is_decimal_digit(*current_position)) {
      exponent_value = exponent_value * 10 + (*current_position - '0');
      current_position++;
    }
    result_value *= powl(10.0L, exponent_sign * exponent_value);
  }

  // Set end position
  if (end_position) {
    *end_position = (char*)current_position;
  }

  // Check if any number was actually parsed
  if (!number_found) {
    if (end_position) {
      *end_position = (char*)string_value;  // Reset position if no valid number
    }
    return 0.0L;
  }

  return result_value * sign_multiplier;
}

/* ====================== Data Reading Functions ====================== */

/* Reads string or character data according to format specifier */
int s21_read_string_or_char(char** string_position,
                            struct FormatSpecifier spec_info,
                            void* output_buffer, enum DataType data_type,
                            bool is_string_format) {
  int max_characters_to_read;
  int position = 0;

  // Determine the width based on the reading type
  if (is_string_format) {
    max_characters_to_read = (spec_info.width > 0) ? spec_info.width : INT_MAX;
    s21_skip_whitespace_characters(string_position);

    // Read until a whitespace character or the width is reached
    while (position < max_characters_to_read && **string_position &&
           !s21_is_whitespace(**string_position)) {
      if (output_buffer) {
        if (data_type == REGULAR_CHAR) {
          *((char*)output_buffer + position) = **string_position;
        } else if (data_type == WIDE_CHAR) {
          *((s21_wchar_t*)output_buffer + position) = **string_position;
        }
      }
      (*string_position)++;
      position++;
    }

    // Add the null terminator for strings
    if (output_buffer) {
      if (data_type == REGULAR_CHAR) {
        *((char*)output_buffer + position) = '\0';
      } else if (data_type == WIDE_CHAR) {
        *((s21_wchar_t*)output_buffer + position) = '\0';
      }
    }
  } else {
    // For characters - read a fixed number of characters
    max_characters_to_read = (spec_info.width > 0) ? spec_info.width : 1;

    while (position < max_characters_to_read && **string_position) {
      if (output_buffer) {
        if (data_type == REGULAR_CHAR) {
          *((char*)output_buffer + position) = **string_position;
        } else if (data_type == WIDE_CHAR) {
          *((s21_wchar_t*)output_buffer + position) = **string_position;
        }
      }
      (*string_position)++;
      position++;
    }
  }

  return 0;
}

/* Processes pointer value conversion (%p format specifier) */
int s21_read_pointer_value(char** string_position,
                           struct FormatSpecifier spec_info,
                           void** output_pointer) {
  int operation_result = 0;
  char buffer[256];
  int max_chars_to_read = 255;

  if ((spec_info.width > 0) && (spec_info.width < 256)) {
    max_chars_to_read = spec_info.width;
  }

  s21_strncpy(buffer, *string_position, max_chars_to_read);
  buffer[max_chars_to_read] = '\0';

  // Check for special value (nil)
  if (s21_strncmp(buffer, "(nil)", 5) == 0) {
    if (output_pointer) {
      *output_pointer = s21_NULL;
    }
    *string_position += 5;
  } else {
    // Try to read a hexadecimal number
    char* end_of_number = buffer;

    long pointer_value = s21_string_to_long(buffer, &end_of_number, 16, 0);

    if (end_of_number == buffer) {
      operation_result = -1;  // Failed to read the number
    } else {
      if (output_pointer) {
        *output_pointer = (void*)pointer_value;
      }
      *string_position += end_of_number - buffer;
    }
  }

  return operation_result;
}

/* ================ Special Number Checking Functions ================ */

/* Checks if string represents special floating-point value (inf/nan) */
bool s21_string_is_special_value(const char* string_value,
                                 enum SpecialNumber special_type) {
  // Early exit for NULL input
  if (!string_value) {
    return false;
  }

  bool result = false;
  char* lowercase_string = s21_to_lower(string_value);  // Allocates memory

  // Check if allocation succeeded
  if (!lowercase_string) {
    return false;  // Memory error → treat as non-match
  }

  // Case-insensitive comparison for "nan" or "inf"
  if (special_type == NOT_A_NUMBER_VALUE &&
      s21_strncmp("nan", lowercase_string, 3) == 0) {
    result = true;
  } else if (special_type == INFINITY_VALUE &&
             s21_strncmp("inf", lowercase_string, 3) == 0) {
    result = true;
  }

  free(lowercase_string);  // Critical: Always free allocated memory
  return result;
}

/* =============== Format Specifier Processing Functions =============== */

/* Handles string/char format specifiers (%s, %c, %lc, %ls) */
void s21_process_string_or_char_format(char** string_position,
                                       struct FormatSpecifier spec_info,
                                       va_list args, int* arguments_read) {
  void* output_buffer = s21_NULL;
  // Initialize the type with the default value
  enum DataType data_type = REGULAR_CHAR;

  // Determine the data type and get the argument if assignment is not
  // suppressed
  if (spec_info.length == '\0') {
    data_type = REGULAR_CHAR;
    if (!spec_info.suppress_assignment) {
      output_buffer = va_arg(args, char*);
      (*arguments_read)++;
    }
  } else if (spec_info.length == 'l') {
    data_type = WIDE_CHAR;
    if (!spec_info.suppress_assignment) {
      output_buffer = va_arg(args, s21_wchar_t*);
      (*arguments_read)++;
    }
  } else {
    // Unexpected length modifier, use the default type
  }

  // Call the general data reading function
  s21_read_string_or_char(string_position, spec_info, output_buffer, data_type,
                          spec_info.format == 's');
}

/* Parses and stores numeric value based on format specifier */
int s21_parse_and_store_number(char** string_position,
                               struct FormatSpecifier spec_info, va_list args,
                               int* arguments_read,
                               enum NumberFormat number_type) {
  int operation_result = 0;
  char buffer[256] = {0};
  char* end_of_number = buffer;
  int max_chars_to_read = 255;

  if ((spec_info.width > 0) && (spec_info.width < 256)) {
    max_chars_to_read = spec_info.width;
  }

  // Copy relevant portion of input
  int i = 0;
  while (i < max_chars_to_read && (*string_position)[i] != '\0') {
    buffer[i] = (*string_position)[i];
    i++;
  }
  buffer[i] = '\0';

  if (number_type == INTEGER_NUMBER) {
    int number_base = s21_get_base_for_integer_format(spec_info.format);
    long value = s21_string_to_long(buffer, &end_of_number, number_base,
                                    spec_info.width);

    if (end_of_number == buffer) {
      operation_result = -1;
    } else if (!spec_info.suppress_assignment) {
      s21_store_integer_value(value, spec_info.length, args);
      (*arguments_read)++;
    }
  } else {
    long double value = s21_string_to_long_double(buffer, &end_of_number);

    if (end_of_number == buffer) {
      operation_result = -1;
    } else if (!spec_info.suppress_assignment) {
      s21_store_float_value(value, spec_info.length, args);
      (*arguments_read)++;
    }
  }

  if (operation_result == 0) {
    (*string_position) += end_of_number - buffer;
  }

  return operation_result;
}

// Helper function to determine +the base based on the format

/* Returns numeric base corresponding to integer format specifier */
int s21_get_base_for_integer_format(char format) {
  int number_base = 0;

  switch (format) {
    case 'd':
      number_base = 10;
      break;
    case 'i':
      number_base = 0;
      break;  // Auto-detect
    case 'o':
      number_base = 8;
      break;
    case 'u':
      number_base = 10;
      break;
    case 'x':
    case 'X':
      number_base = 16;
      break;
  }

  return number_base;
}

// Helper function to store an integer value considering the length modifier

/* Stores integer value considering length modifier (h, l, default) */
void s21_store_integer_value(long value, char length_modifier, va_list args) {
  if (length_modifier == 'l') {
    *va_arg(args, long*) = value;
  } else if (length_modifier == '\0') {
    *va_arg(args, int*) = (int)value;
  } else if (length_modifier == 'h') {
    *va_arg(args, short int*) = (short int)value;
  }
}

// Helper function to store a floating-point value considering the length
// modifier

/* Stores floating-point value considering length modifier (l, L, default) */
void s21_store_float_value(long double value, char length_modifier,
                           va_list args) {
  if (length_modifier == 'L') {
    *va_arg(args, long double*) = value;
  } else if (length_modifier == 'l') {
    *va_arg(args, double*) = (double)value;
  } else if (length_modifier == '\0') {
    *va_arg(args, float*) = (float)value;
  }
}

/* Detects numeric base for 'i' format specifier (auto-detection) */
int s21_detect_number_base(const char* string_value) {
  if (!string_value || !*string_value) return -1;  // Handle NULL/empty input

  // Skip optional sign
  const char* ptr = string_value;
  if (*ptr == '+' || *ptr == '-') ptr++;

  // Check for hex prefix (0x or 0X)
  if (*ptr == '0' && (*(ptr + 1) == 'x' || *(ptr + 1) == 'X')) {
    return 16;
  }

  // Explicitly reject binary (0b or 0B)
  if (*ptr == '0' && (*(ptr + 1) == 'b' || *(ptr + 1) == 'B')) {
    return -1;
  }

  // Numbers starting with 0 are octal
  if (*ptr == '0') {
    return 8;
  }

  // Numbers starting with 1-9 are decimal
  if (*ptr >= '1' && *ptr <= '9') {
    return 10;
  }

  // All other cases are invalid
  return -1;
}
