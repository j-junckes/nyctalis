#pragma once

#include <stdint.h>
#include <io.hpp>
//#include <stdlib.h>
 
#if UINT32_MAX == UINTPTR_MAX
#define STACK_CHK_GUARD 0xe2dee396
#else
#define STACK_CHK_GUARD 0x595e9fbd94fda766
#endif
 
uintptr_t __stack_chk_guard = STACK_CHK_GUARD;
 

extern "C" __attribute__((noreturn)) void __stack_chk_fail() {
#if defined(__is_stdk)
  //panic("Stack smashing detected");
  Print("Stack smashing detected\n");
  asm volatile("cli");
  asm volatile("hlt");
#else
	//abort();
  Print("Stack smashing detected\n");
  asm volatile("cli");
  asm volatile("hlt");
#endif
} 
