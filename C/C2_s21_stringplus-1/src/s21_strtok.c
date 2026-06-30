#include <stdbool.h>

#include "s21_string.h"

// Checks if a character is one of the delimiter characters
static bool s21_is_delimiter(const char *character, const char *delimiters) {
  bool is_delimiter = false;

  // Check if the character matches any of the delimiters
  for (s21_size_t i = 0; i < s21_strlen(delimiters); i++) {
    if (*character == delimiters[i]) {
      is_delimiter = true;
      break;
    }
  }

  return is_delimiter;
}

// Breaks a string into a series of tokens based on delimiter characters
char *s21_strtok(char *str, const char *delimiters) {
  // Check if delimiters is valid
  if (!delimiters) {
    return s21_NULL;
  }

  // Static variable to keep track of the current position between calls
  static char *next_token_position = s21_NULL;

  // Pointer that will point to the beginning of the found token
  char *token_start = s21_NULL;

  // If str is provided, update next_token_position to start from str
  if (str) {
    next_token_position = str;
  }

  // If we have a valid position to continue from
  if (next_token_position != s21_NULL) {
    // Skip any leading delimiters
    while (*next_token_position &&
           s21_is_delimiter(next_token_position, delimiters)) {
      next_token_position++;
    }

    // If we haven't reached the end of the string, we found the start of a
    // token
    if (*next_token_position != '\0') {
      token_start = next_token_position;
    }

    // Find the end of the current token
    while (*next_token_position &&
           !s21_is_delimiter(next_token_position, delimiters)) {
      next_token_position++;
    }

    // If we haven't reached the end of the string, replace the delimiter with
    // '\0' and move the position pointer one character forward
    if (*next_token_position) {
      *next_token_position = '\0';
      next_token_position++;
    } else {
      // If we've reached the end of the string, set the position to NULL
      // for the next call to indicate no more tokens
      next_token_position = s21_NULL;
    }
  }

  return token_start;
}
