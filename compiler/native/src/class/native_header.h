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
	class Native : public virtual Base
	{
	public:
		// Constructors
		Native();
		Native(void* val);
		// Properties
		count_t counter = 1;
		void* value = nullptr;
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
		Nectar::VAR &operator[](Nectar::VAR key);
		Nectar::VAR &operator[](int key);
		Nectar::VAR &operator[](double key);
		Nectar::VAR &operator[](const char* key);
		template <class... Args>
		Nectar::VAR operator()(Args... args) const
		{
			auto _args = Nectar::Type::vector_t{(Nectar::VAR)args...};
			return (*static_cast<std::function<Nectar::VAR(Nectar::Type::vector_t)> *>(value))(_args);
		}
	
		// Comparation operators
		Native operator!() const;
		bool operator==(const Native &_v1) const;
		// === emulated with __Nectar_EQUAL_VALUE_AND_TYPE
		// !== emulated with __Nectar_NOT_EQUAL_VALUE_AND_TYPE
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
} // namespace Nectar::Class
