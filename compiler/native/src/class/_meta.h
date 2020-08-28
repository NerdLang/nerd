#pragma once
#include <exception>

namespace NJS::Class
{
	typedef uint32_t count_t;
	class InvalidTypeException : public std::exception
	{
	};
	typedef std::vector<NJS::VAR> vector_t;
	typedef std::pair<const char *, NJS::VAR> pair_t;
	typedef std::vector<pair_t> object_t;
} // namespace NJS::Class
