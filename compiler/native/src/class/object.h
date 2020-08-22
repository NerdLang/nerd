#pragma once
#include <vector>
#include <string>
#include "undefined.h"
#include "../enum.h"

namespace NJS::Class
{
	class Object : Undefined
	{
	public:
		const char *name = "object";
		const unsigned int type = NJS::Enum::Type::OBJECT;
		Object();
		std::vector<std::pair<const char *, NJS::VAR>> __OBJECT;
		std::vector<std::pair<const char *, NJS::VAR>> &__NJS_VALUE = __OBJECT;
		explicit operator bool() const;
		explicit operator double() const;
		explicit operator int() const;
		explicit operator std::string() const;
		explicit operator long long() const;
		NJS::VAR const &operator[](NJS::VAR _index) const;
		NJS::VAR &operator[](NJS::VAR _index);
		NJS::VAR valueOf() const;
		NJS::VAR toLocaleString() const;
		NJS::VAR toString() const;
	};
} // namespace NJS::Class
