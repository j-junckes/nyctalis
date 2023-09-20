#include <io.hpp>
#include <string.hpp>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#include <stdarg.h>

static bool PrintSimple(const char* data, size_t length) {
  const unsigned char* bytes = (const unsigned char*) data;
  for (size_t i = 0; i < length; i++)
    if (PutChar(bytes[i]) == (-1))
      return false;
  return true;
}

int Print(const char* __restrict format, ...) {
  va_list parameters;
  va_start(parameters, format);

  int written = 0;

  while (*format != '\0') {
    size_t maxrem = INT_MAX - written;

    if (format[0] != '%' || format[1] == '%') {
      if (format[0] == '%')
        format++;
      size_t amount = 1;
      while (format[amount] && format[amount] != '%')
        amount++;
      if (maxrem < amount) {
        // TODO: Set errno to EOVERFLOW.
        va_end(parameters);
        return -1;
      }
      if (!PrintSimple(format, amount)) {
        va_end(parameters);
        return -1;
      }
      format += amount;
      written += amount;
      continue;
    }

    const char* format_begun_at = format++;

    if (*format == 'c') {
      format++;
      char c = (char) va_arg(parameters, int /* char promotes to int */);
      if (!maxrem) {
        // TODO: Set errno to EOVERFLOW.
        va_end(parameters);
        return -1;
      }
      if (!PrintSimple(&c, sizeof(c))) {
        va_end(parameters);
        return -1;
      }
      written++;
    } else if (*format == 's') {
      format++; 
      const char* str = va_arg(parameters, const char*);
      size_t len = StrLength(str);
      if (maxrem < len) {
        // TODO: Set errno to EOVERFLOW.
        va_end(parameters);
        return -1;
      }
      if (!PrintSimple(str, len)) {
        va_end(parameters);
        return -1;
      }
      written += len;
    } else if (*format == 'd') {
      format++;
      int d = va_arg(parameters, int);
      char str[32];
      IntToString(d, str, 10);
      size_t len = StrLength(str);
      if (maxrem < len) {
        // TODO: Set errno to EOVERFLOW.
        va_end(parameters);
        return -1;
      }
      if (!PrintSimple(str, len)) {
        va_end(parameters);
        return -1;
      }
      written += len;
    } else {
      format = format_begun_at;
      size_t len = StrLength(format);
      if (maxrem < len) {
        // TODO: Set errno to EOVERFLOW.
        va_end(parameters);
        return -1;
      }
      if (!PrintSimple(format, len)) {
        va_end(parameters);
        return -1;
      }
      written += len;
      format += len;
    }
  }

  va_end(parameters);
  return written;
}

