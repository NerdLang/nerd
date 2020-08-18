#pragma once
#include <vector>
#include <string>
#include "base.h"
#include "../values.h"

namespace NJS::Class
{
	class BaseObject : Base
	{
	public:
		BaseObject();
		std::vector<std::pair<const char *, NJS::VAR>> __OBJECT;
		NJS::VAR const &operator[](NJS::VAR _index) const;
		NJS::VAR &operator[](NJS::VAR _index);
		NJS::VAR valueOf() const;
		NJS::VAR toLocaleString() const;
		NJS::VAR toString() const;
	};
} // namespace NJS::Class
