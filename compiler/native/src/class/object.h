#pragma once
#include <vector>
#include <string>
#include "undefined.h"
#include "../enum.h"

namespace NJS::Class
{
	class Object : public Undefined
	{
	private:
		inline bool isNull() const;
	public:
		const char *name = "object";
		const NJS::Enum::Type type = NJS::Enum::Type::OBJECT;
		Object();
		Object(std::nullptr_t _ptr);
		Object(std::vector<std::pair<const char *, NJS::VAR>> obj);
		std::vector<std::pair<const char *, NJS::VAR>> *__OBJECT;
		std::vector<std::pair<const char *, NJS::VAR>> &__NJS_VALUE = *__OBJECT;
		explicit operator bool() const;
		explicit operator double() const;
		explicit operator int() const;
		explicit operator std::string() const;
		explicit operator long long() const;
		NJS::VAR const &operator[](std::string _index) const;
		NJS::VAR &operator[](std::string _index);
		NJS::VAR valueOf() const;
		NJS::VAR toLocaleString() const;
		NJS::VAR toString() const;
	};
} // namespace NJS::Class
