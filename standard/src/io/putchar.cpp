#include <io.hpp>

#if defined(__is_stdk)
#include <veil/tty.hpp>
#endif

int PutChar(int ic) {
#if defined(__is_stdk)
	char c = (char) ic;
	Terminal::PutChar(c);
#else
	// TODO: Implement stdio and the write system call.
#endif
	return ic;
}
