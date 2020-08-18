#pragma once
#include "baseobject.h"

namespace NJS::Class
{
	class Object : BaseObject
	{
	public:
		Object();
		std::vector<std::pair<const char *, NJS::VAR>> &__NJS_VALUE = __OBJECT;
		operator NJS::VAR() const;
		explicit operator bool() const;
		explicit operator double() const;
		explicit operator int() const;
		explicit operator std::string() const;
		explicit operator long long() const;
	};
} // namespace NJS::Class
