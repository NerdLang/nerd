/*
	Copyright (c) 2022 NerdLang - Adrien THIERRY and contributors

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
#include "function_header.h"
#include <functional>
#include <limits>

namespace NerdCore::Class
{
	// Constructors
	Function::Function()
	{
		(*this)["prototype"] = new NerdCore::Class::Object();
	}
	Function::Function(void *val)
	{
		counter++;
		value = (NerdCore::Type::function_t*)val;
		if((*this)["prototype"].type == NerdCore::Enum::Type::Null)
		{
			(*this)["prototype"] = new NerdCore::Class::Object();
		}
	}
	Function::Function(void *val, NerdCore::VAR __this)
	{
		counter++;
		(*this)["this"] = __this;
		value = (NerdCore::Type::function_t*)val;
		if((*this)["prototype"].type == NerdCore::Enum::Type::Null)
		{
			(*this)["prototype"] = new NerdCore::Class::Object();
		}
	}
	// Methods
	inline void Function::Delete() noexcept
	{
		if (--counter < 1)
		{
			delete (NerdCore::Type::function_t*)value;
			delete this;
		}
	}
	inline void Function::jsDelete(const std::string _key) noexcept
	{

	}
	inline void* Function::Copy() noexcept
	{
		counter++;
		return this;
	}
	
	// Main operators
	NerdCore::VAR const Function::operator[](NerdCore::VAR key) const
	{
		return NerdCore::Global::null;
	}
	
	#ifndef __NERD__OBJECT_VECTOR
	NerdCore::VAR &Function::operator[](NerdCore::VAR key)
	{
		/*
		if(hasLazy && LazyRTM.count(key) && !object.count(key))
		{
			object[key] = LazyRTM[key];
		}
		*/
		return object[key];
	}
	#else
	NerdCore::VAR &Function::operator[](NerdCore::VAR key)
	{
		std::string _str = ((std::string)key);
		NerdCore::Type::StringView _sview = _str;
		
		if (key.type == NerdCore::Enum::Type::Number)
		{
			auto i = (int)key;
			
			if (i < 0)
			{
				return NerdCore::Global::null;
			}
			else 
			{
				if (i >= object.size())
				{
					object.reserve(i + 1);
					object.resize(i + 1);
				}
			}
			return object[i].second;
		}
		
		for (auto & search : object)
		{
			if (_sview.compare(search.first) == 0)
			{
				return search.second;
			}
		}

		object.push_back(NerdCore::Type::pair_t(_str, NerdCore::Global::null));

		return object[object.size() - 1].second;
	}
	#endif
	
	#ifndef __NERD__OBJECT_VECTOR
	NerdCore::VAR &Function::operator[](int key)
	{
		std::string _str = std::to_string(key);
		NerdCore::Type::StringView _sview = _str;
		
		return object[_str];
	}
	#else
	NerdCore::VAR &Function::operator[](int key)
	{
		std::string _str = std::to_string(key);
		NerdCore::Type::StringView _sview = _str;
		
		for (auto & search : object)
		{
			if (_sview.compare(search.first) == 0)
			{
				return search.second;
			}
		}

		object.push_back(NerdCore::Type::pair_t(_str, NerdCore::Global::null));


		return object[object.size() - 1].second;
	}
	#endif
	
	#ifndef __NERD__OBJECT_VECTOR
	NerdCore::VAR &Function::operator[](double key)
	{
		std::string _str = std::to_string(key);
		NerdCore::Type::StringView _sview = _str;
		
		return object[_str];
	}
	#else
	NerdCore::VAR &Function::operator[](double key)
	{
		std::string _str = std::to_string(key);
		NerdCore::Type::StringView _sview = _str;
		
		for (auto & search : object)
		{
			if (_sview.compare(search.first) == 0)
			{
				return search.second;
			}
		}

		object.push_back(NerdCore::Type::pair_t(_str, NerdCore::Global::null));

		return object[object.size() - 1].second;
	}
	#endif
	
	#ifndef __NERD__OBJECT_VECTOR
	NerdCore::VAR &Function::operator[](const char* key)
	{
		/*
		if(hasLazy && LazyRTM.count(key) && !object.count(key))
		{
			object[key] = LazyRTM[key];
		}
		*/
		return object[key];
	}
	#else
	NerdCore::VAR &Function::operator[](const char* key)
	{
		std::string _str = key;
		NerdCore::Type::StringView _sview = _str;

		for (auto & search : object)
		{
			if (_sview.compare(search.first) == 0)
			{
				return search.second;
			}
		}

		object.push_back(NerdCore::Type::pair_t(_str, NerdCore::Global::null));


		return object[object.size() - 1].second;
	}
	#endif
	
	// Comparation operators
	NerdCore::VAR Function::operator!() const 
	{
		return __NERD_Boolean_FALSE;
	}
	bool Function::operator==(const Function &_v1) const { return false; }
	// === emulated with __NERD_EQUAL_VALUE_AND_TYPE
	// !== emulated with __NERD_NOT_EQUAL_VALUE_AND_TYPE
	bool Function::operator!=(const Function &_v1) const { return true; }
	bool Function::operator<(const Function &_v1) const { return false; }
	bool Function::operator<=(const Function &_v1) const { return true; }
	bool Function::operator>(const Function &_v1) const { return false; }
	bool Function::operator>=(const Function &_v1) const { return true; }
	// Numeric operators
	Function Function::operator+() const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator-() const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator++(const int _v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator--(const int _v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator+(const Function &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator+=(const Function &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator-(const Function &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator-=(const Function &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator*(const Function &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator*=(const Function &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	// TODO: "**" and "**=" operators
	Function Function::operator/(const Function &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator/=(const Function &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator%(const Function &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator%=(const Function &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator&(const Function &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator|(const Function &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator^(const Function &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator~() const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator>>(const Function &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator<<(const Function &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator&=(const Function &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator|=(const Function &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator^=(const Function &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator>>=(const Function &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator<<=(const Function &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	// TODO: ">>>" and ">>>=" operators
} // namespace NerdCore::Class
