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
#include "undefined_header.h"
#include <limits>

namespace NectarCore::Class
{
	// Constructors
	Undefined::Undefined() { }
	// Methods
	inline void Undefined::Delete() noexcept
	{
	}
	inline void* Undefined::Copy() noexcept
	{
		return this;
	}
	// Native cast
	Undefined::operator bool() const noexcept { return false; }
	Undefined::operator double() const noexcept { return std::numeric_limits<double>::quiet_NaN(); }
	Undefined::operator int() const noexcept { return std::numeric_limits<int>::quiet_NaN(); }
	Undefined::operator long long() const noexcept { return std::numeric_limits<long long>::quiet_NaN(); }
	Undefined::operator std::string() const noexcept { return "undefined"; }
	// Main operators
	NectarCore::VAR const Undefined::operator[](NectarCore::VAR key) const
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw NectarCore::VAR("TypeError: Cannot read property '" + (std::string)key + "' of undefined ");
		#endif
		return NectarCore::Global::undefined;
	}
	NectarCore::VAR &Undefined::operator[](NectarCore::VAR key)
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw NectarCore::VAR("TypeError: Cannot read property '" + (std::string)key + "' of undefined ");
		#endif
		return NectarCore::Global::undefined;
	}
	NectarCore::VAR &Undefined::operator[](int key)
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw NectarCore::VAR("TypeError: Cannot read property " + std::to_string(key) + " of undefined ");
		#endif
		return NectarCore::Global::undefined;
	}
	NectarCore::VAR &Undefined::operator[](double key)
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw NectarCore::VAR("TypeError: Cannot read property " + std::to_string(key) + " of undefined ");
		#endif
		return NectarCore::Global::undefined;
	}
	NectarCore::VAR &Undefined::operator[](const char* key)
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw NectarCore::VAR("TypeError: Cannot read property '" + (std::string)key + "' of undefined ");
		#endif
		return NectarCore::Global::undefined;
	}
	
	// Comparation operators
	Undefined Undefined::operator!() const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	bool Undefined::operator==(const Undefined &_v1) const { return true; }
	// === emulated with __Nectar_EQUAL_VALUE_AND_TYPE
	// !== emulated with __Nectar_NOT_EQUAL_VALUE_AND_TYPE
	bool Undefined::operator!=(const Undefined &_v1) const { return false; }
	bool Undefined::operator<(const Undefined &_v1) const { return false; }
	bool Undefined::operator<=(const Undefined &_v1) const { return false; }
	bool Undefined::operator>(const Undefined &_v1) const { return false; }
	bool Undefined::operator>=(const Undefined &_v1) const { return false; }
	// Numeric operators
	Undefined Undefined::operator+() const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator-() const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator++(const int _v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator--(const int _v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator+(const Undefined &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator+=(const Undefined &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator-(const Undefined &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator-=(const Undefined &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator*(const Undefined &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator*=(const Undefined &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	// TODO: "**" and "**=" operators
	Undefined Undefined::operator/(const Undefined &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator/=(const Undefined &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator%(const Undefined &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator%=(const Undefined &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator&(const Undefined &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator|(const Undefined &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator^(const Undefined &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator~() const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator>>(const Undefined &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator<<(const Undefined &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator&=(const Undefined &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator|=(const Undefined &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator^=(const Undefined &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator>>=(const Undefined &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator<<=(const Undefined &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	// TODO: ">>>" and ">>>=" operators
} // namespace NectarCore::Class
