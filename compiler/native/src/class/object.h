#pragma once
#include <vector>
#include <string>
#include "_base.h"
#include "../enum.h"

namespace NJS::Class
{
	class Object : public Base
	{
	public:
		Object();
		Object(std::vector<std::pair<const char *, NJS::VAR>> &obj);
		std::vector<std::pair<const char *, NJS::VAR>> &__NJS_VALUE = *__OBJECT;
		NJS::VAR valueOf() const;
		NJS::VAR toLocaleString() const;
		NJS::VAR toString() const;
	};
} // namespace NJS::Class
