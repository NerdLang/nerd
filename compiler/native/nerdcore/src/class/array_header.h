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
	class Array : public virtual Base
	{
	public:
		// Constructors
		Array();
		Array(NerdCore::Type::vector_t vec);
		
		template<typename ...Args>
		Array(Args ... args)
		{
			NerdCore::Type::vector_t _vec = {args...};
			value = _vec;
		}
		
		Array(std::initializer_list<NerdCore::VAR> l);
		
		// Properties
		count_t counter = 0;
		NerdCore::Type::vector_t value;
		NerdCore::Type::object_t object;
		NerdCore::VAR length;
		// Methods
		double Size();
		inline void Delete() noexcept;
		inline void jsDelete(const NerdCore::VAR _key) noexcept;
		inline void* Copy() noexcept;
		// Native cast
		explicit operator bool() const noexcept;
		explicit operator double() const noexcept;
		explicit operator int() const noexcept;
		explicit operator long long() const noexcept;
		explicit operator std::string() const noexcept;
		// Main operators
		NerdCore::VAR &GetSet(std::string key);
		NerdCore::VAR const operator[](int key) const;
		NerdCore::VAR &operator[](NerdCore::VAR key);
		NerdCore::VAR &operator[](int key);
		NerdCore::VAR &operator[](double key);
		NerdCore::VAR &operator[](const char* key);

		// Comparation operators
		Array operator!() const;
		
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
		Array operator+() const;
		Array operator-() const;
		Array operator++(const int _v1);
		Array operator--(const int _v1);
		Array operator+(const Array &_v1) const;
		Array operator+=(const Array &_v1);
		Array operator-(const Array &_v1) const;
		Array operator-=(const Array &_v1);
		Array operator*(const Array &_v1) const;
		Array operator*=(const Array &_v1);
		// TODO: "**" and "**=" operators
		Array operator/(const Array &_v1) const;
		Array operator/=(const Array &_v1);
		Array operator%(const Array &_v1) const;
		Array operator%=(const Array &_v1);
		Array operator&(const Array &_v1) const;
		Array operator|(const Array &_v1) const;
		Array operator^(const Array &_v1) const;
		Array operator~() const;
		Array operator>>(const Array &_v1) const;
		Array operator<<(const Array &_v1) const;
		Array operator&=(const Array &_v1);
		Array operator|=(const Array &_v1);
		Array operator^=(const Array &_v1);
		Array operator>>=(const Array &_v1);
		Array operator<<=(const Array &_v1);
		// TODO: ">>>" and ">>>=" operators
		
		NerdCore::VAR __iterator(NerdCore::VAR* args, int _length) const;
		NerdCore::VAR __unscopables(NerdCore::VAR* args, int _length) const;
		NerdCore::VAR concat(NerdCore::VAR* args, int _length) const;
		NerdCore::VAR copyWithin(NerdCore::VAR* args, int _length);
		NerdCore::VAR entries(NerdCore::VAR* args, int _length) const;
		NerdCore::VAR every(NerdCore::VAR* args, int _length) const;
		NerdCore::VAR fill(NerdCore::VAR* args, int _length) const;
		NerdCore::VAR filter(NerdCore::VAR* args, int _length) const;
		NerdCore::VAR find(NerdCore::VAR* args, int _length) const;
		NerdCore::VAR findIndex(NerdCore::VAR* args, int _length) const;
		NerdCore::VAR flat(NerdCore::VAR* args, int _length) const;
		NerdCore::VAR flatMap(NerdCore::VAR* args, int _length) const;
		NerdCore::VAR forEach(NerdCore::VAR* args, int _length) const;
		NerdCore::VAR includes(NerdCore::VAR* args, int _length) const;
		NerdCore::VAR indexOf(NerdCore::VAR* args, int _length) const;
		NerdCore::VAR join(NerdCore::VAR* args, int _length) const;
		NerdCore::VAR keys(NerdCore::VAR* args, int _length) const;
		NerdCore::VAR lastIndexOf(NerdCore::VAR* args, int _length) const;
		NerdCore::VAR map(NerdCore::VAR* args, int _length) const;
		NerdCore::VAR pop(NerdCore::VAR* args, int _length);
		NerdCore::VAR push(NerdCore::VAR* args, int _length);
		NerdCore::VAR reduce(NerdCore::VAR* args, int _length) const;
		NerdCore::VAR reduceRight(NerdCore::VAR* args, int _length) const;
		NerdCore::VAR reverse(NerdCore::VAR* args, int _length);
		NerdCore::VAR shift(NerdCore::VAR* args, int _length);
		NerdCore::VAR slice(NerdCore::VAR* args, int _length) const;
		NerdCore::VAR some(NerdCore::VAR* args, int _length) const;
		NerdCore::VAR sort(NerdCore::VAR* args, int _length) const;
		NerdCore::VAR splice(NerdCore::VAR* args, int _length);
		NerdCore::VAR toLocaleString(NerdCore::VAR* args, int _length) const;
		NerdCore::VAR toString(NerdCore::VAR* args, int _length) const;
		NerdCore::VAR unshift(NerdCore::VAR* args, int _length);
		NerdCore::VAR values(NerdCore::VAR* args, int _length) const;
	};
} // namespace NerdCore::Class
