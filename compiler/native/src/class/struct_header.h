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
	class Struct : public virtual Base
	{
	public:
		// Constructors
		Struct();
		Struct(void* val);
		Struct(void* val, void* fn);
		// Properties
		count_t counter = 1;
		void* value = nullptr;
		NectarCore::Type::object_t object;
		NectarCore::Type::clean_struct* Clean;
		// Methods
		inline void Delete() noexcept;
		inline void StructDelete() noexcept;
		inline void* Copy() noexcept;
		// Struct cast
		explicit operator bool() const noexcept;
		explicit operator double() const noexcept;
		explicit operator int() const noexcept;
		explicit operator long long() const noexcept;
		explicit operator std::string() const noexcept;
		// Main operators
		NectarCore::VAR const operator[](NectarCore::VAR key) const;
		NectarCore::VAR &operator[](NectarCore::VAR key);
		NectarCore::VAR &operator[](int key);
		NectarCore::VAR &operator[](double key);
		NectarCore::VAR &operator[](const char* key);
		
		template <class... Args>
		NectarCore::VAR operator()(Args... args) const
		{
			auto _args = NectarCore::Type::vector_t{(NectarCore::VAR)args...};
			return (*static_cast<std::function<NectarCore::VAR(NectarCore::Type::vector_t)> *>(value))(_args);
		}
		
		// Comparation operators
		NectarCore::VAR operator!() const;
		bool operator==(const NectarCore::VAR &_v1) const;
		// === emulated with __Nectar_EQUAL_VALUE_AND_TYPE
		// !== emulated with __Nectar_NOT_EQUAL_VALUE_AND_TYPE
		bool operator!=(const NectarCore::VAR &_v1) const;
		bool operator<(const NectarCore::VAR &_v1) const;
		bool operator<=(const NectarCore::VAR &_v1) const;
		bool operator>(const NectarCore::VAR &_v1) const;
		bool operator>=(const NectarCore::VAR &_v1) const;
		// Numeric operators
		NectarCore::VAR operator+() const;
		NectarCore::VAR operator-() const;
		NectarCore::VAR operator++(const int _v1);
		NectarCore::VAR operator--(const int _v1);
		NectarCore::VAR operator+(const NectarCore::VAR &_v1) const;
		NectarCore::VAR operator+=(const NectarCore::VAR &_v1);
		NectarCore::VAR operator-(const NectarCore::VAR &_v1) const;
		NectarCore::VAR operator-=(const NectarCore::VAR &_v1);
		NectarCore::VAR operator*(const NectarCore::VAR &_v1) const;
		NectarCore::VAR operator*=(const NectarCore::VAR &_v1);
		// TODO: "**" and "**=" operators
		NectarCore::VAR operator/(const NectarCore::VAR &_v1) const;
		NectarCore::VAR operator/=(const NectarCore::VAR &_v1);
		NectarCore::VAR operator%(const NectarCore::VAR &_v1) const;
		NectarCore::VAR operator%=(const NectarCore::VAR &_v1);
		NectarCore::VAR operator&(const NectarCore::VAR &_v1) const;
		NectarCore::VAR operator|(const NectarCore::VAR &_v1) const;
		NectarCore::VAR operator^(const NectarCore::VAR &_v1) const;
		NectarCore::VAR operator~() const;
		NectarCore::VAR operator>>(const NectarCore::VAR &_v1) const;
		NectarCore::VAR operator<<(const NectarCore::VAR &_v1) const;
		NectarCore::VAR operator&=(const NectarCore::VAR &_v1);
		NectarCore::VAR operator|=(const NectarCore::VAR &_v1);
		NectarCore::VAR operator^=(const NectarCore::VAR &_v1);
		NectarCore::VAR operator>>=(const NectarCore::VAR &_v1);
		NectarCore::VAR operator<<=(const NectarCore::VAR &_v1);
		// TODO: ">>>" and ">>>=" operators
	};
} // namespace NectarCore::Class
