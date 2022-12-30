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
#include "native_header.h"
#include <functional>
#include <limits>

namespace NerdCore::Class
{
	// Constructors
	Native::Native() {}
	Native::Native(void *val)
	{
		value = val;
	}
	// Methods
	inline void Native::Delete() noexcept
	{
		if (--counter < 1)
		{
			if((*this)["__NERD_On_Destroy"]) (*this)["__NERD_On_Destroy"](NerdCore::Global::null);
			delete this;
		}
	}
	inline void* Native::Copy() noexcept
	{
		counter++;
		return this;
	}
	// Native cast
	Native::operator bool() const noexcept { return true; }
	Native::operator double() const noexcept
	{
		#ifdef __NERD_ENV_ARDUINO
		return 0;
		#else
		return std::numeric_limits<double>::quiet_NaN();
		#endif
	}
	Native::operator int() const noexcept
	{
		#ifdef __NERD_ENV_ARDUINO
		return 0;
		#else
		return std::numeric_limits<int>::quiet_NaN();
		#endif
	}
	Native::operator long long() const noexcept
	{
		#ifdef __NERD_ENV_ARDUINO
		return 0;
		#else
		return std::numeric_limits<long long>::quiet_NaN();
		#endif
	}
	Native::operator std::string() const noexcept
	{
		return "[native code]";
	}
	// Main operators
	NerdCore::VAR const Native::operator[](NerdCore::VAR key) const
	{
		return NerdCore::Global::null;
	}
	NerdCore::VAR &Native::operator[](NerdCore::VAR key)
	{
		return NerdCore::Global::null;
	}
	
	NerdCore::VAR &Native::operator[](int key)
	{
		return NerdCore::Global::null;
	}
	
	NerdCore::VAR &Native::operator[](double key)
	{
		return NerdCore::Global::null;
	}
	
	
	NerdCore::VAR &Native::operator[](const char* key)
	{
		return NerdCore::Global::null;
	}
	
	// Comparation operators
	Native Native::operator!() const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	bool Native::operator==(const Native &_v1) const { return false; }
	// === emulated with __NERD_EQUAL_VALUE_AND_TYPE
	// !== emulated with __NERD_NOT_EQUAL_VALUE_AND_TYPE
	bool Native::operator!=(const Native &_v1) const { return true; }
	bool Native::operator<(const Native &_v1) const { return false; }
	bool Native::operator<=(const Native &_v1) const { return true; }
	bool Native::operator>(const Native &_v1) const { return false; }
	bool Native::operator>=(const Native &_v1) const { return true; }
	// Numeric operators
	Native Native::operator+() const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator-() const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator++(const int _v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator--(const int _v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator+(const Native &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator+=(const Native &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator-(const Native &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator-=(const Native &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator*(const Native &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator*=(const Native &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	// TODO: "**" and "**=" operators
	Native Native::operator/(const Native &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator/=(const Native &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator%(const Native &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator%=(const Native &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator&(const Native &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator|(const Native &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator^(const Native &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator~() const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator>>(const Native &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator<<(const Native &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator&=(const Native &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator|=(const Native &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator^=(const Native &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator>>=(const Native &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator<<=(const Native &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	// TODO: ">>>" and ">>>=" operators
} // namespace NerdCore::Class
