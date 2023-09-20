#include <debug.hpp>
#if defined(__is_stdk)
#include <veil/serial.hpp>
#endif
#include <string.hpp>

// split a string and return the last match
const char* strrchr(const char* str, int ch) {
  const char* last = nullptr;
  do {
    if (*str == ch)
      last = str;
  } while (*str++);
  return ++last;
} 

void Log(LogLevel level, const char* msg, const SourceLocation loc) {
  auto logLevel = "UNK";
  switch (level)
  {
  case LogLevel::Debug:
    logLevel = "DBG";
    break;
  case LogLevel::Info:
    logLevel = "INF";
    break;
  case LogLevel::Warning:
    logLevel = "WRN";
    break;
  case LogLevel::Error:
    logLevel = "ERR";
    break;
  case LogLevel::Fatal:
    logLevel = "FTL";
    break;
  
  default:
    break;
  }
  //Print("[%s:%d:%d %s]: %s\n", strrchr(loc.file_name(), '/'), loc.line(), logLevel, msg);
  #if defined(__is_stdk)
  if (!Serial::HasBeenInitialized()) {
    return;
  }
  Serial::Write("[");
  Serial::Write((char*) strrchr(loc.FileName(), '/'));
  Serial::Write(":");
  char buf[6];
  IntToString(loc.Line(), buf, 10);
  Serial::Write(buf);
  Serial::Write(": ");
  Serial::Write((char*) logLevel);
  Serial::Write("]: ");
  Serial::Write((char*) msg);
  Serial::Write("\n");
  #else
  // TODO: implement
  #endif
}
