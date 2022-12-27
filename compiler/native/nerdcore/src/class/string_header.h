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
	class String : public virtual Base
	{
	public:
		// Constructors
		String();
		String(std::string val);
		String(const char* val);
		// Properties
		std::string value;
		NerdCore::Type::object_t object;
		NerdCore::VAR length;
		void* bind = nullptr;
		count_t counter = 1;
		// Methods
		inline void Delete() noexcept;
		inline void* Copy() noexcept;
		// Native cast
		explicit operator bool() const noexcept;
		explicit operator double() const noexcept;
		explicit operator int() const noexcept;
		explicit operator long long() const noexcept;
		explicit operator std::string() const noexcept;
		// Main operators
		inline NerdCore::VAR& GetSet(NerdCore::VAR keyVar);
		NerdCore::VAR const operator[](NerdCore::VAR key) const;
		NerdCore::VAR &operator[](NerdCore::VAR key);
		NerdCore::VAR &operator[](int key);
		NerdCore::VAR &operator[](double key);
		NerdCore::VAR &operator[](const char* key);
		
		// Comparation operators
		template <class... Args>
		NerdCore::VAR operator() (Args... args)
		{
			#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
			throw InvalidTypeException();
			#endif
			return NerdCore::Global::null;
		}
		String operator!() const;
		bool operator==(const String &_v1) const;
		// === emulated with __NERD_EQUAL_VALUE_AND_TYPE
		// !== emulated with __NERD_NOT_EQUAL_VALUE_AND_TYPE
		bool operator!=(const String &_v1) const;
		bool operator<(const String &_v1) const;
		bool operator<=(const String &_v1) const;
		bool operator>(const String &_v1) const;
		bool operator>=(const String &_v1) const;
		// Numeric operators
		String operator+() const;
		String operator-() const;
		String operator++(const int _v1);
		String operator--(const int _v1);
		String operator+(const String &_v1) const;
		String operator+=(const String &_v1);
		String operator-(const String &_v1) const;
		String operator-=(const String &_v1);
		String operator*(const String &_v1) const;
		String operator*=(const String &_v1);
		// TODO: "**" and "**=" operators
		String operator/(const String &_v1) const;
		String operator/=(const String &_v1);
		String operator%(const String &_v1) const;
		String operator%=(const String &_v1);
		String operator&(const String &_v1) const;
		String operator|(const String &_v1) const;
		String operator^(const String &_v1) const;
		String operator~() const;
		String operator>>(const String &_v1) const;
		String operator<<(const String &_v1) const;
		String operator&=(const String &_v1);
		String operator|=(const String &_v1);
		String operator^=(const String &_v1);
		String operator>>=(const String &_v1);
		String operator<<=(const String &_v1);
		// TODO: ">>>" and ">>>=" operators
		/*** STRING METHODS ***/
		NerdCore::VAR toString(NerdCore::VAR* _args, int _length) const;
		NerdCore::VAR split(NerdCore::VAR* _args, int _length) const;
		NerdCore::VAR indexOf(NerdCore::VAR* _args, int _length) const;
		NerdCore::VAR lastIndexOf(NerdCore::VAR* _args, int _length) const;
		NerdCore::VAR search(NerdCore::VAR* _args, int _length) const;
		NerdCore::VAR slice(NerdCore::VAR* _args, int _length) const;
		NerdCore::VAR substr(NerdCore::VAR* _args, int _length) const;
		NerdCore::VAR replace(NerdCore::VAR* _args, int _length) const;
		/* END STRING METHODS */
	};
} // namespace NerdCore::Class
