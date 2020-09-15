#pragma once
#include "_meta.h"

namespace NJS::Class
{
	class Base
	{
	public:
		virtual void Delete() noexcept{};
		virtual explicit operator bool() const noexcept{ return 1;};
		virtual explicit operator std::string() const noexcept{ return "";};
		virtual explicit operator int() const noexcept {return 0;};
		virtual explicit operator double() const noexcept {return 0.0;};
		virtual explicit operator long long() const noexcept {return 0;};
		virtual NJS::VAR &operator[](NJS::VAR key){static NJS::VAR _ret; return _ret;};
	};
}