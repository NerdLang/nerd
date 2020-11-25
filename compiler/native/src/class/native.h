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
#include "native_header.h"
#include <functional>
#include <limits>

namespace NectarCore::Class
{
	// Constructors
	Native::Native() {}
	Native::Native(void *val)
	{
		value = val;
	}
	// Methods
	inline void Native::Delete() noexcept
	{
		if (--counter < 1)
		{
			if((*this)["__Nectar_On_Destroy"]) (*this)["__Nectar_On_Destroy"]();
			delete this;
		}
	}
	inline void* Native::Copy() noexcept
	{
		counter++;
		return this;
	}
	// Native cast
	Native::operator bool() const noexcept { return true; }
	Native::operator double() const noexcept
	{
		return std::numeric_limits<double>::quiet_NaN();
	}
	Native::operator int() const noexcept
	{
		return std::numeric_limits<int>::quiet_NaN();
	}
	Native::operator long long() const noexcept
	{
		return std::numeric_limits<long long>::quiet_NaN();
	}
	Native::operator std::string() const noexcept
	{
		return "[native code]";
	}
	// Main operators
	NectarCore::VAR const Native::operator[](NectarCore::VAR key) const
	{
		return NectarCore::Global::undefined;
	}
	NectarCore::VAR &Native::operator[](NectarCore::VAR key)
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
	
	NectarCore::VAR &Native::operator[](int key)
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
	
	NectarCore::VAR &Native::operator[](double key)
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
	
	
	NectarCore::VAR &Native::operator[](const char* key)
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
	Native Native::operator!() const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	bool Native::operator==(const Native &_v1) const { return false; }
	// === emulated with __Nectar_EQUAL_VALUE_AND_TYPE
	// !== emulated with __Nectar_NOT_EQUAL_VALUE_AND_TYPE
	bool Native::operator!=(const Native &_v1) const { return true; }
	bool Native::operator<(const Native &_v1) const { return false; }
	bool Native::operator<=(const Native &_v1) const { return true; }
	bool Native::operator>(const Native &_v1) const { return false; }
	bool Native::operator>=(const Native &_v1) const { return true; }
	// Numeric operators
	Native Native::operator+() const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator-() const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator++(const int _v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator--(const int _v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator+(const Native &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator+=(const Native &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator-(const Native &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator-=(const Native &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator*(const Native &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator*=(const Native &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	// TODO: "**" and "**=" operators
	Native Native::operator/(const Native &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator/=(const Native &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator%(const Native &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator%=(const Native &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator&(const Native &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator|(const Native &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator^(const Native &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator~() const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator>>(const Native &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator<<(const Native &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator&=(const Native &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator|=(const Native &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator^=(const Native &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator>>=(const Native &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	Native Native::operator<<=(const Native &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Native();
	}
	// TODO: ">>>" and ">>>=" operators
} // namespace NectarCore::Class
