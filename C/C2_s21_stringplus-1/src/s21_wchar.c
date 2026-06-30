#include "s21_wchar.h"

#include <stdbool.h>

// Converts a wide character string to a multibyte string (UTF-8 encoding)
s21_size_t s21_wcstombs(char* mbstr, const s21_wchar_t* wcstr,
                        s21_size_t count) {
  // Handle case when both pointers are NULL
  if (mbstr == s21_NULL && wcstr == s21_NULL) {
    return 0;
  }

  s21_size_t converted = 0;  // Counter for successfully converted bytes

  // Handle case when wide string pointer is NULL
  if (wcstr == s21_NULL) {
    // If destination buffer exists and has space, null-terminate it
    if (mbstr != s21_NULL && count > 0) {
      *mbstr = '\0';
    }
    return 0;
  }

  // Process each wide character until null terminator is found
  while (*wcstr != L'\0') {
    s21_wchar_t wc = *wcstr;  // Current wide character
    int bytes_needed = 0;     // Bytes needed for UTF-8 encoding

    // Determine number of bytes needed for UTF-8 encoding
    if (wc < 0x80) {
      bytes_needed = 1;  // ASCII character (1 byte)
    } else if (wc < 0x800) {
      bytes_needed = 2;  // 2-byte UTF-8 sequence
    } else if (wc < 0x10000) {
      bytes_needed = 3;  // 3-byte UTF-8 sequence
    } else if (wc < 0x110000) {
      bytes_needed = 4;  // 4-byte UTF-8 sequence
    } else {
      return (s21_size_t)-1;  // Invalid wide character (out of Unicode range)
    }

    // Check if there's enough space in buffer (including null terminator)
    if (converted + bytes_needed + 1 > count) {
      break;  // Not enough space - stop conversion
    }

    // Encode wide character to UTF-8 multibyte sequence
    switch (bytes_needed) {
      case 4:  // 4-byte sequence (U+10000 to U+10FFFF)
        mbstr[converted++] = (char)((wc >> 18) | 0xF0);  // Leading byte
        mbstr[converted++] =
            (char)(((wc >> 12) & 0x3F) | 0x80);                  // Continuation
        mbstr[converted++] = (char)(((wc >> 6) & 0x3F) | 0x80);  // Continuation
        mbstr[converted++] = (char)((wc & 0x3F) | 0x80);         // Continuation
        break;
      case 3:  // 3-byte sequence (U+0800 to U+FFFF)
        mbstr[converted++] = (char)((wc >> 12) | 0xE0);          // Leading byte
        mbstr[converted++] = (char)(((wc >> 6) & 0x3F) | 0x80);  // Continuation
        mbstr[converted++] = (char)((wc & 0x3F) | 0x80);         // Continuation
        break;
      case 2:  // 2-byte sequence (U+0080 to U+07FF)
        mbstr[converted++] = (char)((wc >> 6) | 0xC0);    // Leading byte
        mbstr[converted++] = (char)((wc & 0x3F) | 0x80);  // Continuation
        break;
      case 1:                           // 1-byte sequence (ASCII)
        mbstr[converted++] = (char)wc;  // Single byte
        break;
    }

    wcstr++;  // Move to next wide character
  }

  // Add null terminator if buffer exists and has space
  if (mbstr != s21_NULL && converted < count) {
    mbstr[converted] = '\0';
  }

  return converted;  // Return number of bytes converted (excluding null)
}
