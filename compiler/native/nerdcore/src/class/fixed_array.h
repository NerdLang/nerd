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
#include "array_header.h"
#include <sstream>
#include <limits>
		
namespace NerdCore::Class
{
	// Constructors
	FixedArray::FixedArray() 
	{ 
		length = 8;
		value = new NerdCore::VAR[8];
	}
	FixedArray::FixedArray(NerdCore::VAR _length)
	{
		length = _length;
		value = new NerdCore::VAR[(int)_length];
	}
	FixedArray::FixedArray(int _length)
	{
		length = _length;
		value = new NerdCore::VAR[_length];
	}
	FixedArray::FixedArray(NerdCore::VAR* _var, int _length)
	{
		length = _length;
		value = new NerdCore::VAR[_length];
		for(int i = 0; i < _length; i++)
		{
			value[i] = _var[i];
		}
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
			#ifdef __NERD_ENV_ARDUINO
			return 0;
			#else
			return std::numeric_limits<double>::quiet_NaN();
			#endif
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
			#ifdef __NERD_ENV_ARDUINO
			return 0;
			#else
			return std::numeric_limits<int>::quiet_NaN();
			#endif
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
			#ifdef __NERD_ENV_ARDUINO
			return 0;
			#else
			return std::numeric_limits<long long>::quiet_NaN();
			#endif
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
	NerdCore::VAR const FixedArray::operator[](NerdCore::VAR key) const
	{
		if (key.type == NerdCore::Enum::Type::Number)
		{
			auto i = (int)key;
			if (i >= 0 && i <= (int)length)
			{
				return value[i];
			}
		}
		
		return NerdCore::Global::null;
	}
	NerdCore::VAR const FixedArray::operator[](int key) const
	{
		if (key >= 0 && key <= (int)length)
		{
			return value[key];
		}
		
		return NerdCore::Global::null;
	}
	
	NerdCore::VAR &FixedArray::operator[](NerdCore::VAR key)
	{	
		if (key.type == NerdCore::Enum::Type::Number)
		{
			auto i = (int)key;

			if (i < 0)
			{
				return NerdCore::Global::null;
			}
			else 
			{
				if (i >= (int)length)
				{
					return NerdCore::Global::null;
				}
			}
			return value[i];
		}
			
		return NerdCore::Global::null;
	}
	
	NerdCore::VAR &FixedArray::operator[](int key)
	{
		if (key < 0)
		{
			return NerdCore::Global::null;
		}
		else 
		{
			if (key >= (int)length)
			{
				return NerdCore::Global::null;
			}
		}
		return value[key];
	}
	
	NerdCore::VAR &FixedArray::operator[](double key)
	{
		if (key < 0)
		{
			return NerdCore::Global::null;
		}
		else 
		{
			if (key >= (int)length)
			{
				return NerdCore::Global::null;
			}
		}
		return value[(int)key];
	}
	
	NerdCore::VAR &FixedArray::operator[](const char* key)
	{		
		return NerdCore::Global::null;
	}
	
	// Comparation operators
	FixedArray FixedArray::operator!() const 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	
	// Numeric operators
	FixedArray FixedArray::operator+() const
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator-() const
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator++(const int _v1)
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator--(const int _v1)
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator+(const FixedArray &_v1) const 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator+=(const FixedArray &_v1) 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator-(const FixedArray &_v1) const 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator-=(const FixedArray &_v1) 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator*(const FixedArray &_v1) const 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator*=(const FixedArray &_v1) 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	// TODO: "**" and "**=" operators
	FixedArray FixedArray::operator/(const FixedArray &_v1) const 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator/=(const FixedArray &_v1) 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator%(const FixedArray &_v1) const 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator%=(const FixedArray &_v1) 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator&(const FixedArray &_v1) const 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator|(const FixedArray &_v1) const 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator^(const FixedArray &_v1) const 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator~() const 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator>>(const FixedArray &_v1) const 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator<<(const FixedArray &_v1) const 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator&=(const FixedArray &_v1) 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator|=(const FixedArray &_v1) 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator^=(const FixedArray &_v1) 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator>>=(const FixedArray &_v1) 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator<<=(const FixedArray &_v1) 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	// TODO: ">>>" and ">>>=" operators
	
} // namespace NerdCore::Class
