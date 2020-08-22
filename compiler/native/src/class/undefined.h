#pragma once
#include "../var.h"
#include "../enum.h"

namespace NJS::Class
{
	class Undefined
	{
	public:
		const char *name = "undefined";
		const unsigned int type = NJS::Enum::Type::UNDEFINED;
		unsigned int cnt = 0;
		Undefined();
		void Delete();
		explicit operator bool() const;
		explicit operator double() const;
		explicit operator int() const;
		explicit operator std::string() const;
		explicit operator long long() const;
		NJS::VAR const &operator[](std::string _index) const;
		NJS::VAR &operator[](std::string _index);
		template <class... Args>
		NJS::VAR operator()(Args... args) const;
	};
} // namespace NJS::Class
