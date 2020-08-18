#pragma once
#include "../njs.h"
#include "../enum.h"

namespace NJS::Class
{
	class Base
	{
	public:
		int cnt = 0;
		Base();
		void Delete();
		operator NJS::VAR() const;
		explicit operator bool() const;
		explicit operator double() const;
		explicit operator int() const;
		explicit operator std::string() const;
		explicit operator long long() const;
		NJS::VAR operator()() const;
	};
} // namespace NJS::Class
