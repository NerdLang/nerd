#pragma once
#include "../var.h"
#include "../enum.h"

class Empty {};

namespace NJS::Class
{
	class Undefined
	{
	public:
		const char *name = "undefined";
		const NJS::Enum::Type type = NJS::Enum::Type::UNDEFINED;
		unsigned int cnt = 0;
		Empty __NJS_VALUE;
		Undefined();
		void Delete();
		explicit operator bool() const;
		explicit operator double() const;
		explicit operator int() const;
		explicit operator std::string() const;
		explicit operator long long() const;
		template<typename T> NJS::VAR operator=(T &_v);
		NJS::VAR const &operator[](std::string _index) const;
		NJS::VAR &operator[](std::string _index);
		template <class... Args>
		NJS::VAR operator()(Args... args) const;
	};
} // namespace NJS::Class
