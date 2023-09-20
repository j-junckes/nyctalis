#pragma once
#include <stddef.h>
#include <stdint.h>

struct SourceLocation {
  static constexpr SourceLocation
  current(const char* __file = __builtin_FILE(),
    const char* __func = __builtin_FUNCTION(),
    int __line = __builtin_LINE(),
    int __col = 0) noexcept {
    SourceLocation __loc;
    __loc._file = __file;
    __loc._function = __func;
    __loc._line = __line;
    __loc._column = __col;
    return __loc;
  }

  constexpr SourceLocation() noexcept
  : _file("unknown"), _function(_file), _line(0), _column(0) { }

  constexpr uint_least32_t Line() const noexcept { return _line; }
  constexpr uint_least32_t Column() const noexcept { return _column; }
  constexpr const char* FileName() const noexcept { return _file; }
  constexpr const char* FunctionName() const noexcept { return _function; }

private:
  const char* _file;
  const char* _function;
  uint_least32_t _line;
  uint_least32_t _column;
};

enum class LogLevel {
  Debug,
  Info,
  Warning,
  Error,
  Fatal,
};

void Log(LogLevel level, const char* msg, const SourceLocation loc = SourceLocation::current());
