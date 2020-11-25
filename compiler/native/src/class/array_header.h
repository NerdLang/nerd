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

namespace Nectar::Class
{
	class Array : public virtual Base
	{
	public:
		// Constructors
		Array();
		Array(Nectar::Type::vector_t vec);
		// Properties
		count_t counter = 0;
		Nectar::VAR length;
		Nectar::Type::vector_t value;
		Nectar::Type::object_t object;
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
		Nectar::VAR const operator[](Nectar::VAR key) const;
		Nectar::VAR const operator[](int key) const;
		Nectar::VAR &operator[](Nectar::VAR key);
		Nectar::VAR &operator[](int key);
		Nectar::VAR &operator[](double key);
		Nectar::VAR &operator[](const char* key);

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
		
		Nectar::VAR __iterator(Nectar::VAR* args, int _length) const;
		Nectar::VAR __unscopables(Nectar::VAR* args, int _length) const;
		Nectar::VAR concat(Nectar::VAR* args, int _length) const;
		Nectar::VAR copyWithin(Nectar::VAR* args, int _length);
		Nectar::VAR entries(Nectar::VAR* args, int _length) const;
		Nectar::VAR every(Nectar::VAR* args, int _length) const;
		Nectar::VAR fill(Nectar::VAR* args, int _length) const;
		Nectar::VAR filter(Nectar::VAR* args, int _length) const;
		Nectar::VAR find(Nectar::VAR* args, int _length) const;
		Nectar::VAR findIndex(Nectar::VAR* args, int _length) const;
		Nectar::VAR flat(Nectar::VAR* args, int _length) const;
		Nectar::VAR flatMap(Nectar::VAR* args, int _length) const;
		Nectar::VAR forEach(Nectar::VAR* args, int _length) const;
		Nectar::VAR includes(Nectar::VAR* args, int _length) const;
		Nectar::VAR indexOf(Nectar::VAR* args, int _length) const;
		Nectar::VAR join(Nectar::VAR* args, int _length) const;
		Nectar::VAR keys(Nectar::VAR* args, int _length) const;
		Nectar::VAR lastIndexOf(Nectar::VAR* args, int _length) const;
		Nectar::VAR map(Nectar::VAR* args, int _length) const;
		Nectar::VAR pop(Nectar::VAR* args, int _length);
		Nectar::VAR push(Nectar::VAR* args, int _length);
		Nectar::VAR reduce(Nectar::VAR* args, int _length) const;
		Nectar::VAR reduceRight(Nectar::VAR* args, int _length) const;
		Nectar::VAR reverse(Nectar::VAR* args, int _length);
		Nectar::VAR shift(Nectar::VAR* args, int _length);
		Nectar::VAR slice(Nectar::VAR* args, int _length) const;
		Nectar::VAR some(Nectar::VAR* args, int _length) const;
		Nectar::VAR sort(Nectar::VAR* args, int _length) const;
		Nectar::VAR splice(Nectar::VAR* args, int _length);
		Nectar::VAR toLocaleString(Nectar::VAR* args, int _length) const;
		Nectar::VAR toString(Nectar::VAR* args, int _length) const;
		Nectar::VAR unshift(Nectar::VAR* args, int _length);
		Nectar::VAR values(Nectar::VAR* args, int _length) const;
	};
} // namespace Nectar::Class
