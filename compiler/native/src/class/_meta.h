#pragma once
#include <exception>

namespace NJS::Class
{
#ifdef __NJS_ARDUINO
	typedef uint16_t count_t;
#else
	typedef uint32_t count_t;
#endif
	class InvalidTypeException : public std::exception
	{
	};
	typedef std::vector<NJS::VAR> vector_t;
	typedef std::pair<const char *, NJS::VAR> pair_t;
	typedef std::vector<pair_t> object_t;
} // namespace NJS::Class
