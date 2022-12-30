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
	class Native : public virtual Base
	{
	public:
		// Constructors
		Native();
		Native(void* val);
		// Properties
		count_t counter = 1;
		int length = 0;
		void* value = nullptr;
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
		NerdCore::VAR const operator[](NerdCore::VAR key) const;
		NerdCore::VAR &operator[](NerdCore::VAR key);
		NerdCore::VAR &operator[](int key);
		NerdCore::VAR &operator[](double key);
		NerdCore::VAR &operator[](const char* key);
		
		// Comparation operators
		Native operator!() const;
		bool operator==(const Native &_v1) const;
		// === emulated with __NERD_EQUAL_VALUE_AND_TYPE
		// !== emulated with __NERD_NOT_EQUAL_VALUE_AND_TYPE
		bool operator!=(const Native &_v1) const;
		bool operator<(const Native &_v1) const;
		bool operator<=(const Native &_v1) const;
		bool operator>(const Native &_v1) const;
		bool operator>=(const Native &_v1) const;
		// Numeric operators
		Native operator+() const;
		Native operator-() const;
		Native operator++(const int _v1);
		Native operator--(const int _v1);
		Native operator+(const Native &_v1) const;
		Native operator+=(const Native &_v1);
		Native operator-(const Native &_v1) const;
		Native operator-=(const Native &_v1);
		Native operator*(const Native &_v1) const;
		Native operator*=(const Native &_v1);
		// TODO: "**" and "**=" operators
		Native operator/(const Native &_v1) const;
		Native operator/=(const Native &_v1);
		Native operator%(const Native &_v1) const;
		Native operator%=(const Native &_v1);
		Native operator&(const Native &_v1) const;
		Native operator|(const Native &_v1) const;
		Native operator^(const Native &_v1) const;
		Native operator~() const;
		Native operator>>(const Native &_v1) const;
		Native operator<<(const Native &_v1) const;
		Native operator&=(const Native &_v1);
		Native operator|=(const Native &_v1);
		Native operator^=(const Native &_v1);
		Native operator>>=(const Native &_v1);
		Native operator<<=(const Native &_v1);
		// TODO: ">>>" and ">>>=" operators
	};
} // namespace NerdCore::Class
