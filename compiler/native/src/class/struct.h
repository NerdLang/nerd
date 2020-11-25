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
#include "struct_header.h"
#include <functional>
#include <limits>

namespace NectarCore::Class
{
	// Constructors
	Struct::Struct() {}
	Struct::Struct(void *val)
	{
		value = val;
	}
	Struct::Struct(void *val, void* fn)
	{
		value = val;
		Clean = (NectarCore::Type::clean_struct*)fn;
	}
	// Methods
	inline void Struct::Delete() noexcept
	{
		if (--counter == 0)
		{
			(*static_cast<NectarCore::Type::clean_struct *>(Clean))(value);
			delete Clean;
			delete this;
		}
	}
	
	inline void* Struct::Copy() noexcept
	{
		counter++;
		return this;
	}
	// Native cast
	Struct::operator bool() const noexcept { return true; }
	Struct::operator double() const noexcept
	{
		return std::numeric_limits<double>::quiet_NaN();
	}
	Struct::operator int() const noexcept
	{
		return std::numeric_limits<int>::quiet_NaN();
	}
	Struct::operator long long() const noexcept
	{
		return std::numeric_limits<long long>::quiet_NaN();
	}
	Struct::operator std::string() const noexcept
	{
		return "[native struct]";
	}
	// Main operators
	NectarCore::VAR const Struct::operator[](NectarCore::VAR key) const
	{
		return NectarCore::Global::undefined;
	}
	NectarCore::VAR &Struct::operator[](NectarCore::VAR key)
	{
		#ifndef __Nectar__OBJECT_VECTOR
		return object[(std::string)key];
		#else
		for (auto & search : object)
		{
			if (((std::string)key).compare(search.first) == 0)
			{
				return search.second;
			}
		}

		object.push_back(NectarCore::Type::pair_t((std::string)key, NectarCore::VAR()));
		return object[object.size() - 1].second;
		#endif
	}
	
	NectarCore::VAR &Struct::operator[](int key)
	{
		#ifndef __Nectar__OBJECT_VECTOR
		return object[std::to_string(key)];
		#else
		std::string _str = std::to_string(key);
		for (auto & search : object)
		{
			if (_str.compare(search.first) == 0)
			{
				return search.second;
			}
		}

		object.push_back(NectarCore::Type::pair_t(_str, NectarCore::VAR()));
		return object[object.size() - 1].second;
		#endif
	}
	
	NectarCore::VAR &Struct::operator[](double key)
	{
		#ifndef __Nectar__OBJECT_VECTOR
		return object[std::to_string(key)];
		#else
		std::string _str = std::to_string(key);
		for (auto & search : object)
		{
			if (_str.compare(search.first) == 0)
			{
				return search.second;
			}
		}

		object.push_back(NectarCore::Type::pair_t(_str, NectarCore::VAR()));
		return object[object.size() - 1].second;
		#endif
	}
	
	
	NectarCore::VAR &Struct::operator[](const char* key)
	{
		std::string str = key;
		#ifndef __Nectar__OBJECT_VECTOR
		return object[str];
		#else
		for (auto & search : object)
		{
			if (str.compare(search.first) == 0)
			{
				return search.second;
			}
		}

		object.push_back(NectarCore::Type::pair_t(str, NectarCore::VAR()));
		return object[object.size() - 1].second;
		#endif
	}
	
	// Comparation operators
	NectarCore::VAR Struct::operator!() const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NectarCore::VAR();
	}
	bool Struct::operator==(const NectarCore::VAR &_v1) const { return false; }
	// === emulated with __Nectar_EQUAL_VALUE_AND_TYPE
	// !== emulated with __Nectar_NOT_EQUAL_VALUE_AND_TYPE
	bool Struct::operator!=(const NectarCore::VAR &_v1) const { return true; }
	bool Struct::operator<(const NectarCore::VAR &_v1) const { return false; }
	bool Struct::operator<=(const NectarCore::VAR &_v1) const { return true; }
	bool Struct::operator>(const NectarCore::VAR &_v1) const { return false; }
	bool Struct::operator>=(const NectarCore::VAR &_v1) const { return true; }
	// Numeric operators
	NectarCore::VAR Struct::operator+() const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NectarCore::VAR();
	}
	NectarCore::VAR Struct::operator-() const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NectarCore::VAR();
	}
	NectarCore::VAR Struct::operator++(const int _v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NectarCore::VAR();
	}
	NectarCore::VAR Struct::operator--(const int _v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NectarCore::VAR();
	}
	NectarCore::VAR Struct::operator+(const NectarCore::VAR &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NectarCore::VAR();
	}
	NectarCore::VAR Struct::operator+=(const NectarCore::VAR &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NectarCore::VAR();
	}
	NectarCore::VAR Struct::operator-(const NectarCore::VAR &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NectarCore::VAR();
	}
	NectarCore::VAR Struct::operator-=(const NectarCore::VAR &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NectarCore::VAR();
	}
	NectarCore::VAR Struct::operator*(const NectarCore::VAR &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NectarCore::VAR();
	}
	NectarCore::VAR Struct::operator*=(const NectarCore::VAR &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NectarCore::VAR();
	}
	// TODO: "**" and "**=" operators
	NectarCore::VAR Struct::operator/(const NectarCore::VAR &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NectarCore::VAR();
	}
	NectarCore::VAR Struct::operator/=(const NectarCore::VAR &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NectarCore::VAR();
	}
	NectarCore::VAR Struct::operator%(const NectarCore::VAR &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NectarCore::VAR();
	}
	NectarCore::VAR Struct::operator%=(const NectarCore::VAR &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NectarCore::VAR();
	}
	NectarCore::VAR Struct::operator&(const NectarCore::VAR &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NectarCore::VAR();
	}
	NectarCore::VAR Struct::operator|(const NectarCore::VAR &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NectarCore::VAR();
	}
	NectarCore::VAR Struct::operator^(const NectarCore::VAR &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NectarCore::VAR();
	}
	NectarCore::VAR Struct::operator~() const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NectarCore::VAR();
	}
	NectarCore::VAR Struct::operator>>(const NectarCore::VAR &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NectarCore::VAR();
	}
	NectarCore::VAR Struct::operator<<(const NectarCore::VAR &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NectarCore::VAR();
	}
	NectarCore::VAR Struct::operator&=(const NectarCore::VAR &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NectarCore::VAR();
	}
	NectarCore::VAR Struct::operator|=(const NectarCore::VAR &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NectarCore::VAR();
	}
	NectarCore::VAR Struct::operator^=(const NectarCore::VAR &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NectarCore::VAR();
	}
	NectarCore::VAR Struct::operator>>=(const NectarCore::VAR &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NectarCore::VAR();
	}
	NectarCore::VAR Struct::operator<<=(const NectarCore::VAR &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NectarCore::VAR();
	}
	// TODO: ">>>" and ">>>=" operators
} // namespace NectarCore::Class
