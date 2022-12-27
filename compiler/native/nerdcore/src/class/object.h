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
#include "object_header.h"
#include <limits>

namespace NerdCore::Class
{
	NerdCore::VAR __proxy;
	// Constructors
	Object::Object() { }
	
	/*
	Object::Object(const char* _key, NerdCore::VAR _value)
	{ 
		object[_key] = _value;
	}
	*/
	/*
	Object::Object(NerdCore::VAR _obj)
	{ 
		object = ((NerdCore::Class::Object*)_obj.data.ptr)->object;
	}
	*/
	
	Object::Object(NerdCore::Type::object_t obj)
	{ 
		object = obj;
	}
	
	Object::Object(std::initializer_list<NerdCore::Type::pair_t> obj)
	{
		for (NerdCore::Type::pair_t p : obj)
		{
			object[p.first] = p.second;
		}
	}
	
	// Methods
	double Object::Size()
	{
		return object.size();
	}

	inline void Object::Delete() noexcept
	{
		if (--counter < 1)
		{
			delete this;
		}
	}
	inline void Object::jsDelete(const std::string _key) noexcept
	{
		#ifndef __NERD__OBJECT_VECTOR
			object.erase(_key);
		#else
			for (NerdCore::Type::object_t::iterator it = object.begin() ; it != object.end(); ++it)
			{
				if (_key.compare(it->first) == 0)
				{
					object.erase(it);
					return;
				}
			}
		#endif
	}
	inline void* Object::Copy() noexcept
	{
		counter++;
		return this;
	}
	// Native cast
	Object::operator bool() const noexcept { return true; }
	Object::operator double() const noexcept
	{
		#ifdef __NERD_ENV_ARDUINO
		return 0;
		#else
		return std::numeric_limits<double>::quiet_NaN();
		#endif
	}
	Object::operator int() const noexcept
	{
		#ifdef __NERD_ENV_ARDUINO
		return 0;
		#else
		return std::numeric_limits<int>::quiet_NaN();
		#endif
	}
	Object::operator long long() const noexcept
	{
		#ifdef __NERD_ENV_ARDUINO
		return 0;
		#else
		return std::numeric_limits<long long>::quiet_NaN();
		#endif
	}
	Object::operator std::string() const noexcept
	{
		return "[object Object]";
	}
	// Main operators
	NerdCore::VAR const Object::operator[](NerdCore::VAR key) const
	{
		return NerdCore::Global::null;
	}
	
	NerdCore::VAR &Object::GetSet(std::string key)
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
	
	NerdCore::VAR &Object::operator[](NerdCore::VAR key)
	{
		return Object::GetSet(key);

	}

	NerdCore::VAR &Object::operator[](int key)
	{
		std::string _str = std::to_string(key);
		return Object::GetSet(_str);
	}

	NerdCore::VAR &Object::operator[](double key)
	{
		std::string _str = std::to_string(key);
		return Object::GetSet(_str);
	}
	
	NerdCore::VAR &Object::operator[](const char* key)
	{
		return Object::GetSet(key);
	}
	
	// Comparation operators
	Object Object::operator!() const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	bool Object::operator==(const Object &_v1) const { return false; }
	// === emulated with __NERD_EQUAL_VALUE_AND_TYPE
	// !== emulated with __NERD_NOT_EQUAL_VALUE_AND_TYPE
	bool Object::operator!=(const Object &_v1) const { return true; }
	bool Object::operator<(const Object &_v1) const { return false; }
	bool Object::operator<=(const Object &_v1) const { return true; }
	bool Object::operator>(const Object &_v1) const { return false; }
	bool Object::operator>=(const Object &_v1) const { return true; }
	// Numeric operators
	Object Object::operator+() const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator-() const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator++(const int _v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator--(const int _v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator+(const Object &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator+=(const Object &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator-(const Object &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator-=(const Object &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator*(const Object &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator*=(const Object &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	// TODO: "**" and "**=" operators
	Object Object::operator/(const Object &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator/=(const Object &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator%(const Object &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator%=(const Object &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator&(const Object &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator|(const Object &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator^(const Object &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator~() const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator>>(const Object &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator<<(const Object &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator&=(const Object &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator|=(const Object &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator^=(const Object &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator>>=(const Object &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator<<=(const Object &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	// TODO: ">>>" and ">>>=" operators
} // namespace NerdCore::Class
