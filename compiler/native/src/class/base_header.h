#pragma once
#include "_meta.h"

namespace NJS::Class
{
	class Base
	{
	public:
		virtual void Delete() noexcept;
		virtual explicit operator bool() const noexcept;
		virtual explicit operator string() const noexcept;
		virtual explicit operator int() const noexcept;
		virtual explicit operator double() const noexcept;
		virtual NJS::VAR &operator[](NJS::VAR key);
	};
}