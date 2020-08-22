#pragma once
#include "object.h"

namespace NJS::Class
{
	class Boolean : Object
	{
	public:
		const char *name = "boolean";
		const unsigned int type = NJS::Enum::Type::BOOLEAN;
		Boolean();
		Boolean(bool b);
		bool __NJS_VALUE;
		explicit operator bool() const;
		explicit operator double() const;
		explicit operator int() const;
		explicit operator std::string() const;
		explicit operator long long() const;
		Boolean operator=(const Boolean &_v);
		Boolean operator=(const bool &_v);
	};
} // namespace NJS::Class
