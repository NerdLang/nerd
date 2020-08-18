#pragma once
#include "baseobject.h"

namespace NJS::Class
{
	class Function : BaseObject
	{
	public:
		Function(void *_f);
		void *__NJS_VALUE;
		operator NJS::VAR() const;
		explicit operator bool() const;
		explicit operator double() const;
		explicit operator int() const;
		explicit operator std::string() const;
		explicit operator long long() const;
		NJS::VAR operator()() const;
	};
} // namespace NJS::Class
