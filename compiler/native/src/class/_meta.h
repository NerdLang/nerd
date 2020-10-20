#pragma once
#include <exception>

namespace NJS::Class
{
#ifdef __NJS_ENV_ARDUINO
	typedef uint16_t count_t;
#else
	typedef int count_t;
#endif
	class InvalidTypeException : public std::exception
	{
	};
	#ifdef __NJS_ENV_ARDUINO
	const int SMI_MAX = 32767;
	const int SMI_MIN = -32768;
	#else
	const int SMI_MAX = 1073741823;
	const int SMI_MIN = -1073741824;
	#endif
} // namespace NJS::Class
