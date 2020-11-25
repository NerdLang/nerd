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
#include "array_header.h"
#include <sstream>
#include <limits>
		
namespace NectarCore::Class
{
	// Constructors
	FixedArray::FixedArray() 
	{ 
		length = 8;
		value = new NectarCore::VAR[8];
	}
	FixedArray::FixedArray(NectarCore::VAR _length)
	{
		length = _length;
		value = new NectarCore::VAR[(int)_length];
	}
	// Methods
	inline void FixedArray::Delete() noexcept
	{
		if (--counter == 0)
		{
			delete[] value;
			delete this;
		}
	}
	inline void* FixedArray::Copy() noexcept
	{
		counter++;
		return this;
	}
	// Native cast
	FixedArray::operator bool() const noexcept { return true; }
	FixedArray::operator double() const noexcept
	{
		if ((int)length == 1)
		{
			return (double)value[0];
		}
		else
		{
			return std::numeric_limits<double>::quiet_NaN();
		}
	}
	FixedArray::operator int() const noexcept
	{
		if ((int)length == 1)
		{
			return (int)value[0];
		}
		else
		{
			return std::numeric_limits<int>::quiet_NaN();
		}
	}
	FixedArray::operator long long() const noexcept
	{
		if ((int)length == 1)
		{
			return (long long)value[0];
		}
		else
		{
			return std::numeric_limits<long long>::quiet_NaN();
		}
	}
	FixedArray::operator std::string() const noexcept
	{
		auto l = (int)length;
		std::stringstream stream;
		stream << (std::string)value[0];
		for (auto i = 1; i < l; i++)
		{
			stream << "," << (std::string)value[i];
		}
		return stream.str();
	}
	// Main operators
	NectarCore::VAR const FixedArray::operator[](NectarCore::VAR key) const
	{
		if (key.type == NectarCore::Enum::Type::Number)
		{
			auto i = (int)key;
			if (i >= 0 && i <= (int)length)
			{
				return value[i];
			}
		}
		
		return NectarCore::Global::undefined;
	}
	NectarCore::VAR const FixedArray::operator[](int key) const
	{
		if (key >= 0 && key <= (int)length)
		{
			return value[key];
		}
		
		return NectarCore::Global::undefined;
	}
	
	#ifndef __Nectar__OBJECT_VECTOR
	NectarCore::VAR &FixedArray::operator[](NectarCore::VAR key)
	{	
		if (key.type == NectarCore::Enum::Type::Number)
		{
			auto i = (int)key;

			if (i < 0)
			{
				return NectarCore::Global::undefined;
			}
			else 
			{
				if (i >= (int)length)
				{
					return NectarCore::Global::undefined;
				}
			}
			return value[i];
		}
		
		std::string _str = ((std::string)key);
		NectarCore::Type::StringView _sview = _str;
		
		if(_sview.compare("length") == 0)
		{
			return length;
		}
		
		NectarCore::VAR& _obj = object[_str];
				
		return _obj;
	}
	#else
	NectarCore::VAR &FixedArray::operator[](NectarCore::VAR key)
	{
		if (key.type == NectarCore::Enum::Type::Number)
		{
			auto i = (int)key;
			
			if (i < 0)
			{
				return NectarCore::Global::undefined;
			}
			else 
			{
				if (i >= (int)length)
				{
					return NectarCore::Global::undefined;
				}
			}
			return value[i];
		}
		
		std::string _str = ((std::string)key);
		NectarCore::Type::StringView _sview = _str;
		
		if(_sview.compare("length") == 0)
		{
			return length;
		}
		
		for (auto & search : object)
		{
			if (_sview.compare(search.first) == 0)
			{
				return search.second;
			}
		}
		
		object.push_back(NectarCore::Type::pair_t(_str, NectarCore::Global::undefined));
		return object[object.size() - 1].second;
	}
	#endif
	
	NectarCore::VAR &FixedArray::operator[](int key)
	{
		if (key < 0)
		{
			return NectarCore::Global::undefined;
		}
		else 
		{
			if (key >= (int)length)
			{
				return NectarCore::Global::undefined;
			}
		}
		return value[key];
	}
	
	NectarCore::VAR &FixedArray::operator[](double key)
	{
		if (key < 0)
		{
			return NectarCore::Global::undefined;
		}
		else 
		{
			if (key >= (int)length)
			{
				return NectarCore::Global::undefined;
			}
		}
		return value[(int)key];
	}
	
	#ifndef __Nectar__OBJECT_VECTOR
	NectarCore::VAR &FixedArray::operator[](const char* key)
	{		
		std::string _str = key;
		NectarCore::Type::StringView _sview = _str;
		
		if(_sview.compare("length") == 0)
		{
			return length;
		}
		
		NectarCore::VAR& _obj = object[_str];
		return _obj; 
	}
	#else
	NectarCore::VAR &FixedArray::operator[](const char* key)
	{
		std::string _str = key;
		NectarCore::Type::StringView _sview = _str;
		
		if(_sview.compare("length") == 0)
		{
			return length;
		}
		
		for (auto & search : object)
		{
			if (_sview.compare(search.first) == 0)
			{
				return search.second;
			}
		}

		object.push_back(NectarCore::Type::pair_t(_str, NectarCore::Global::undefined));
		return object[object.size() - 1].second;
	}
	#endif
	
	// Comparation operators
	FixedArray FixedArray::operator!() const 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	
	// Numeric operators
	FixedArray FixedArray::operator+() const
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator-() const
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator++(const int _v1)
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator--(const int _v1)
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator+(const FixedArray &_v1) const 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator+=(const FixedArray &_v1) 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator-(const FixedArray &_v1) const 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator-=(const FixedArray &_v1) 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator*(const FixedArray &_v1) const 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator*=(const FixedArray &_v1) 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	// TODO: "**" and "**=" operators
	FixedArray FixedArray::operator/(const FixedArray &_v1) const 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator/=(const FixedArray &_v1) 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator%(const FixedArray &_v1) const 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator%=(const FixedArray &_v1) 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator&(const FixedArray &_v1) const 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator|(const FixedArray &_v1) const 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator^(const FixedArray &_v1) const 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator~() const 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator>>(const FixedArray &_v1) const 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator<<(const FixedArray &_v1) const 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator&=(const FixedArray &_v1) 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator|=(const FixedArray &_v1) 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator^=(const FixedArray &_v1) 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator>>=(const FixedArray &_v1) 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator<<=(const FixedArray &_v1) 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	// TODO: ">>>" and ">>>=" operators
	
} // namespace NectarCore::Class
