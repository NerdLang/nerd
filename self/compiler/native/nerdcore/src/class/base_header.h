/*
	Copyright (c) 2021 NerdLang - Adrien THIERRY and contributors

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

*/

#pragma once
#include "_meta.h"

namespace NerdCore::Class
{
	class Base
	{
	public:
		#ifdef __NERD_ENV_ESP32
		virtual ~Base() { }
		#endif
		virtual void Delete() noexcept{};
		virtual void* Copy() noexcept{ return nullptr; };
		virtual explicit operator bool() const noexcept{ return true;};
		virtual explicit operator std::string() const noexcept{ return "";};
		virtual explicit operator int() const noexcept {return 0;};
		virtual explicit operator double() const noexcept {return 0.0;};
		virtual explicit operator long long() const noexcept {return 0;};
		virtual NerdCore::VAR &operator[](NerdCore::VAR key){ return NerdCore::Global::null; };
		virtual NerdCore::VAR &operator[](int key){ return NerdCore::Global::null; };
		virtual NerdCore::VAR &operator[](double key){ return NerdCore::Global::null; };
		virtual NerdCore::VAR &operator[](const char* key){ return NerdCore::Global::null; };
	};
}