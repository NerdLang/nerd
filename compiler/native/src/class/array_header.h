/*
 * This file is part of NectarCPP
 * Copyright (c) 2020 - 2020 Adrien THIERRY
 * https://nectar-lang.org - https://seraum.com/
 *
 * sources : https://github.com/nectar-lang/NectarCPP
 * 
 * NectarCPP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NectarCPP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NectarCPP.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
 
#pragma once
#include "_meta.h"

namespace NectarCore::Class
{
	class Array : public virtual Base
	{
	public:
		// Constructors
		Array();
		Array(NectarCore::Type::vector_t vec);
		// Properties
		count_t counter = 0;
		NectarCore::VAR length;
		NectarCore::Type::vector_t value;
		NectarCore::Type::object_t object;
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
		NectarCore::VAR const operator[](NectarCore::VAR key) const;
		NectarCore::VAR const operator[](int key) const;
		NectarCore::VAR &operator[](NectarCore::VAR key);
		NectarCore::VAR &operator[](int key);
		NectarCore::VAR &operator[](double key);
		NectarCore::VAR &operator[](const char* key);

		// Comparation operators
		Array operator!() const;
		
		template <typename t>
		bool operator==(const t &_v1) const { return false; }
		
		// === emulated with __Nectar_EQUAL_VALUE_AND_TYPE
		// !== emulated with __Nectar_NOT_EQUAL_VALUE_AND_TYPE
		
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
		
		NectarCore::VAR __iterator(NectarCore::VAR* args, int _length) const;
		NectarCore::VAR __unscopables(NectarCore::VAR* args, int _length) const;
		NectarCore::VAR concat(NectarCore::VAR* args, int _length) const;
		NectarCore::VAR copyWithin(NectarCore::VAR* args, int _length);
		NectarCore::VAR entries(NectarCore::VAR* args, int _length) const;
		NectarCore::VAR every(NectarCore::VAR* args, int _length) const;
		NectarCore::VAR fill(NectarCore::VAR* args, int _length) const;
		NectarCore::VAR filter(NectarCore::VAR* args, int _length) const;
		NectarCore::VAR find(NectarCore::VAR* args, int _length) const;
		NectarCore::VAR findIndex(NectarCore::VAR* args, int _length) const;
		NectarCore::VAR flat(NectarCore::VAR* args, int _length) const;
		NectarCore::VAR flatMap(NectarCore::VAR* args, int _length) const;
		NectarCore::VAR forEach(NectarCore::VAR* args, int _length) const;
		NectarCore::VAR includes(NectarCore::VAR* args, int _length) const;
		NectarCore::VAR indexOf(NectarCore::VAR* args, int _length) const;
		NectarCore::VAR join(NectarCore::VAR* args, int _length) const;
		NectarCore::VAR keys(NectarCore::VAR* args, int _length) const;
		NectarCore::VAR lastIndexOf(NectarCore::VAR* args, int _length) const;
		NectarCore::VAR map(NectarCore::VAR* args, int _length) const;
		NectarCore::VAR pop(NectarCore::VAR* args, int _length);
		NectarCore::VAR push(NectarCore::VAR* args, int _length);
		NectarCore::VAR reduce(NectarCore::VAR* args, int _length) const;
		NectarCore::VAR reduceRight(NectarCore::VAR* args, int _length) const;
		NectarCore::VAR reverse(NectarCore::VAR* args, int _length);
		NectarCore::VAR shift(NectarCore::VAR* args, int _length);
		NectarCore::VAR slice(NectarCore::VAR* args, int _length) const;
		NectarCore::VAR some(NectarCore::VAR* args, int _length) const;
		NectarCore::VAR sort(NectarCore::VAR* args, int _length) const;
		NectarCore::VAR splice(NectarCore::VAR* args, int _length);
		NectarCore::VAR toLocaleString(NectarCore::VAR* args, int _length) const;
		NectarCore::VAR toString(NectarCore::VAR* args, int _length) const;
		NectarCore::VAR unshift(NectarCore::VAR* args, int _length);
		NectarCore::VAR values(NectarCore::VAR* args, int _length) const;
	};
} // namespace NectarCore::Class
