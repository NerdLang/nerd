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
	class FixedArray : public virtual Base
	{
	public:
		// Constructors
		FixedArray();
		FixedArray(NerdCore::VAR length);
		FixedArray(int length);
		FixedArray(NerdCore::VAR* value, int length);
		// Properties
		count_t counter = 0;
		NerdCore::VAR length;
		NerdCore::VAR* value;
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
		NerdCore::VAR const operator[](int key) const;
		NerdCore::VAR &operator[](NerdCore::VAR key);
		NerdCore::VAR &operator[](int key);
		NerdCore::VAR &operator[](double key);
		NerdCore::VAR &operator[](const char* key);

		// Comparation operators
		FixedArray operator!() const;
		
		template <typename t>
		bool operator==(const t &_v1) const { return false; }
		
		// === emulated with __NERD_EQUAL_VALUE_AND_TYPE
		// !== emulated with __NERD_NOT_EQUAL_VALUE_AND_TYPE
		
		template <typename t>
		bool operator!=(const t &_v1) const { return true; }
		
		template <typename t>
		bool operator<(const t &_v1) const { return (*this)[0] < _v1;}
		
		template <typename t>
		bool operator<=(const t &_v1) const { return (*this)[0] <= _v1; }
		
		template <typename t>
		bool operator>(const t &_v1) const { return (*this)[0] > _v1; }
		
		template <typename t>
		bool operator>=(const t &_v1) const { return (*this)[0] >= _v1; }
		
		// Numeric operators
		FixedArray operator+() const;
		FixedArray operator-() const;
		FixedArray operator++(const int _v1);
		FixedArray operator--(const int _v1);
		FixedArray operator+(const FixedArray &_v1) const;
		FixedArray operator+=(const FixedArray &_v1);
		FixedArray operator-(const FixedArray &_v1) const;
		FixedArray operator-=(const FixedArray &_v1);
		FixedArray operator*(const FixedArray &_v1) const;
		FixedArray operator*=(const FixedArray &_v1);
		// TODO: "**" and "**=" operators
		FixedArray operator/(const FixedArray &_v1) const;
		FixedArray operator/=(const FixedArray &_v1);
		FixedArray operator%(const FixedArray &_v1) const;
		FixedArray operator%=(const FixedArray &_v1);
		FixedArray operator&(const FixedArray &_v1) const;
		FixedArray operator|(const FixedArray &_v1) const;
		FixedArray operator^(const FixedArray &_v1) const;
		FixedArray operator~() const;
		FixedArray operator>>(const FixedArray &_v1) const;
		FixedArray operator<<(const FixedArray &_v1) const;
		FixedArray operator&=(const FixedArray &_v1);
		FixedArray operator|=(const FixedArray &_v1);
		FixedArray operator^=(const FixedArray &_v1);
		FixedArray operator>>=(const FixedArray &_v1);
		FixedArray operator<<=(const FixedArray &_v1);
		// TODO: ">>>" and ">>>=" operators
	};
} // namespace NerdCore::Class
