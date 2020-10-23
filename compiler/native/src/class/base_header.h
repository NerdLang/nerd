#pragma once
#include "_meta.h"

namespace NJS::Class
{
	class Base
	{
	public:
		#ifdef __NJS_ENV_ESP32
		virtual ~Base() { }
		#endif
		virtual void Delete() noexcept{};
		virtual void* Copy() noexcept{ return nullptr; };
		virtual explicit operator bool() const noexcept{ return false;};
		virtual explicit operator std::string() const noexcept{ return "";};
		virtual explicit operator int() const noexcept {return 0;};
		virtual explicit operator double() const noexcept {return 0.0;};
		virtual explicit operator long long() const noexcept {return 0;};
		virtual NJS::VAR &operator[](NJS::VAR key){static var _ret = NJS::VAR(); return _ret;};
	};
}