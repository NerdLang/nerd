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
	template<typename T>
	class NativeTPL : public virtual Base
	{
		
	private:
		inline void internalDelete()
		{
			if(is_ptr)
			{
				delete value;
			}
		}
	public:
		// Constructors
		bool is_ptr = true;
		int length = 0;
		std::string type;

		NativeTPL(T val)
		{
			is_ptr = true;
			value = val;

			type = "undef";
		}
		NativeTPL(T val, const char str[])
		{
			is_ptr = true;
			type = str;
			value = val;
		}
		NativeTPL(T val, bool isPtr)
		{
			is_ptr = isPtr;
			value = val;
			type = "undef";
		}
		NativeTPL(T val, const char str[], bool isPtr)
		{
			is_ptr = isPtr;
			value = val;
			type = str;
		}
		// Properties
		count_t counter = 1;
		T value;
		NerdCore::Type::object_t object;
		// Methods
		
		inline void Delete() noexcept
		{
			if (--counter == 0)
			{
				internalDelete();
				delete this;
			}
		}
		
		inline void* Copy() noexcept
		{
			counter++;
			return this;
		}
		
		template<typename Cast>
		const inline T operator()(Cast& c) const
		{
			static_assert(std::is_same<decltype(c), T>::value, "Casting must be same as NativeType");

			return value;
		}
		
		inline T operator()() const
		{
			return value;
		}
	
		operator bool() const noexcept { return true; }
		operator double() const noexcept
		{
			#ifdef __NERD_ENV_ARDUINO
			return 0;
			#else
			return std::numeric_limits<double>::quiet_NaN();
			#endif
		}
		operator int() const noexcept
		{
			#ifdef __NERD_ENV_ARDUINO
			return 0;
			#else
			return std::numeric_limits<int>::quiet_NaN();
			#endif
		}
		operator long long() const noexcept
		{
			#ifdef __NERD_ENV_ARDUINO
			return 0;
			#else
			return std::numeric_limits<long long>::quiet_NaN();
			#endif
		}
		operator std::string() const noexcept
		{
			return std::string("[native ") +  type +  std::string("]");
		}
		
		// Main operators
		NerdCore::VAR const operator[](NerdCore::VAR key) const
		{
			return NerdCore::Global::null;
		}
		NerdCore::VAR &operator[](NerdCore::VAR key)
		{
			return NerdCore::Global::null;
		}
		
		NerdCore::VAR &operator[](int key)
		{
			return NerdCore::Global::null;
		}
		
		NerdCore::VAR &operator[](double key)
		{
			return NerdCore::Global::null;
		}
		
		
		NerdCore::VAR &operator[](const char* key)
		{
			return NerdCore::Global::null;
		}
		
		// Comparation operators
		NativeTPL operator!() const 
		{
			#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		bool operator==(const NativeTPL<T> &_v1) const { return false; }
		// === emulated with __NERD_EQUAL_VALUE_AND_TYPE
		// !== emulated with __NERD_NOT_EQUAL_VALUE_AND_TYPE
		bool operator!=(const NativeTPL<T> &_v1) const { return true; }
		bool operator<(const NativeTPL<T> &_v1) const { return false; }
		bool operator<=(const NativeTPL<T> &_v1) const { return true; }
		bool operator>(const NativeTPL<T> &_v1) const { return false; }
		bool operator>=(const NativeTPL<T> &_v1) const { return true; }
		// Numeric operators
		NativeTPL operator+() const 
		{
			#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator-() const 
		{
			#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator++(const int _v1) 
		{
			#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator--(const int _v1) 
		{
			#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator+(const NativeTPL<T> &_v1) const 
		{
			#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator+=(const NativeTPL<T> &_v1) 
		{
			#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator-(const NativeTPL<T> &_v1) const 
		{
			#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator-=(const NativeTPL<T> &_v1) 
		{
			#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator*(const NativeTPL<T> &_v1) const 
		{
			#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator*=(const NativeTPL<T> &_v1) 
		{
			#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		// TODO: "**" and "**=" operators
		NativeTPL operator/(const NativeTPL<T> &_v1) const 
		{
			#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator/=(const NativeTPL<T> &_v1) 
		{
			#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator%(const NativeTPL<T> &_v1) const 
		{
			#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator%=(const NativeTPL<T> &_v1) 
		{
			#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator&(const NativeTPL<T> &_v1) const 
		{
			#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator|(const NativeTPL<T> &_v1) const 
		{
			#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator^(const NativeTPL<T> &_v1) const 
		{
			#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator~() const 
		{
			#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator>>(const NativeTPL<T> &_v1) const 
		{
			#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator<<(const NativeTPL<T> &_v1) const 
		{
			#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator&=(const NativeTPL<T> &_v1) 
		{
			#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator|=(const NativeTPL<T> &_v1) 
		{
			#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator^=(const NativeTPL<T> &_v1) 
		{
			#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator>>=(const NativeTPL<T> &_v1) 
		{
			#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		NativeTPL operator<<=(const NativeTPL<T> &_v1) 
		{
			#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NativeTPL();
		}
		// TODO: ">>>" and ">>>=" operators
		
	};
} // namespace NerdCore::Class
