#pragma once
#include <vector>
#include <string>
#include "undefined.h"
#include "../enum.h"

namespace NJS::Class
{
	class Base : public Undefined
	{
	protected:
		inline bool isNull() const;
	public:
		const char *name = "object";
		const NJS::Enum::Type type = NJS::Enum::Type::OBJECT;
		Base();
		Base(std::nullptr_t _ptr);
		std::vector<std::pair<const char *, NJS::VAR>> *__OBJECT;
		explicit operator bool() const;
		explicit operator double() const;
		explicit operator int() const;
		explicit operator std::string() const;
		explicit operator long long() const;
		NJS::VAR const &operator[](std::string _index) const;
		NJS::VAR &operator[](std::string _index);
	};
} // namespace NJS::Class
