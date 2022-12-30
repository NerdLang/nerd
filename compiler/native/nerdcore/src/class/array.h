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
	Array::Array() 
	{ 
		object["__proto__"] = NerdCore::Global::Array["prototype"];
	}
	Array::Array(NerdCore::Type::vector_t vec)
	{
		object["__proto__"] = NerdCore::Global::Array["prototype"];
		value = vec;
	}
	Array::Array(std::initializer_list<NerdCore::VAR> l) : value(l)
	{
		object["__proto__"] = NerdCore::Global::Array["prototype"];
	}
	
	// Methods
	inline void Array::Delete() noexcept
	{
		if (--counter == 0)
		{
			delete this;
		}
	}
	double Array::Size() 
	{
		return value.size();
	}
	inline void Array::jsDelete(NerdCore::VAR _key) noexcept
	{
		if(_key.type == NerdCore::Enum::Type::String)
		{
			// TODO: if string is a number, convert to number and erase
		}
		else if(_key.type == NerdCore::Enum::Type::Number)
		{
			value[(double)_key] = NerdCore::Global::null;
		}
	}
	inline void* Array::Copy() noexcept
	{
		counter++;
		return this;
	}
	// Native cast
	Array::operator bool() const noexcept { return true; }
	Array::operator double() const noexcept
	{
		if (value.size() == 1)
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
	Array::operator int() const noexcept
	{
		if (value.size() == 1)
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
	Array::operator long long() const noexcept
	{
		if (value.size() == 1)
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
	Array::operator std::string() const noexcept
	{
		auto l = value.size();
		if (l == 0)
			return "";
		std::stringstream stream;
		stream << (std::string)value[0];
		for (auto i = 1; i < l; i++)
		{
			stream << "," << (std::string)value[i];
		}
		return stream.str();
	}
	
	NerdCore::VAR &Array::GetSet(std::string key)
	{
		#ifndef __NERD__OBJECT_VECTOR
		// if current object[key] is null, we look for the prototypal chain
		if(object[key].type == NerdCore::Enum::Type::Null)
		{
			NerdCore::VAR __proto = object["__proto__"];
			while(__proto.type != NerdCore::Enum::Type::Null)
			{
					if(__proto[key].type != NerdCore::Enum::Type::Null)
					{
						object[key] = __proto[key];
						break;
					}
					__proto = __proto["__proto__"];
			}
		}
		/*
		if(object[key].type == NerdCore::Enum::Type::Function)
		{
			(__NERD_FUNCTION(object[key]))->object["this"] = NerdCore::VAR(this);
			__NERD_FUNCTION(object[key])->bind = bind;
		}
		*/
		return object[key];
		#else
		for (auto & search : object)
		{
			if (key.compare(search.first) == 0)
			{
				return search.second;
			}
		}

		object.push_back(NerdCore::Type::pair_t(key, NerdCore::Global::null));

		return object[object.size() - 1].second;
		#endif
	}
	
	// Main operators
	NerdCore::VAR const Array::operator[](int key) const
	{
		if (key >= 0 && key <= value.size())
		{
			return value.at(key);
		}
		
		return NerdCore::Global::null;
	}
	
	NerdCore::VAR &Array::operator[](NerdCore::VAR key)
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
				if (i >= value.size())
				{
					value.resize(i + 1);
				}
			}
			return value[i];
		}
		else
		{
			return GetSet(key);
		}
		return NerdCore::Global::null;
	}
	
	NerdCore::VAR &Array::operator[](int key)
	{
		if (key < 0)
		{
			return NerdCore::Global::null;
		}
		else 
		{
			if (key >= value.size())
			{
				value.resize(key + 1);
			}
		}
		return value[key];
	}
	
	NerdCore::VAR &Array::operator[](double key)
	{
		if (key < 0)
		{
			return NerdCore::Global::null;
		}
		else 
		{
			if (key >= value.size())
			{
				value.resize(key + 1);
			}
		}
		return value[key];
	}
	
	NerdCore::VAR &Array::operator[](const char* key)
	{		
		return GetSet(key);
	}
	
	// Comparation operators
	Array Array::operator!() const 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	
	// Numeric operators
	Array Array::operator+() const
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator-() const
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator++(const int _v1)
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator--(const int _v1)
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator+(const Array &_v1) const 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator+=(const Array &_v1) 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator-(const Array &_v1) const 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator-=(const Array &_v1) 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator*(const Array &_v1) const 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator*=(const Array &_v1) 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	// TODO: "**" and "**=" operators
	Array Array::operator/(const Array &_v1) const 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator/=(const Array &_v1) 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator%(const Array &_v1) const 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator%=(const Array &_v1) 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator&(const Array &_v1) const 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator|(const Array &_v1) const 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator^(const Array &_v1) const 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator~() const 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator>>(const Array &_v1) const 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator<<(const Array &_v1) const 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator&=(const Array &_v1) 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator|=(const Array &_v1) 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator^=(const Array &_v1) 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator>>=(const Array &_v1) 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator<<=(const Array &_v1) 
	{ 
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	// TODO: ">>>" and ">>>=" operators

	
} // namespace NerdCore::Class
