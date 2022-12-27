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
#include "string_header.h"
#include <string>
#include <limits>

namespace NerdCore::Class
{
	
	// Constructors
	String::String()
	{ 
		object["__proto__"] = NerdCore::Global::String["prototype"];
	}
	String::String(std::string val)
	{
		object["__proto__"] = NerdCore::Global::String["prototype"];
		value = val;
	}
	
	String::String(const char* val)
	{
		object["__proto__"] = NerdCore::Global::String["prototype"];
		value = val;
	}
	
	// Methods
	inline void String::Delete() noexcept
	{
		if (--counter < 1)
		{
			delete this;
		}
	}
	inline void* String::Copy() noexcept
	{
		return new String(value);
	}
	// Native cast
	String::operator bool() const noexcept { return value.size() > 0; }
	String::operator double() const noexcept
	{
		std::string::size_type end;
		double res;
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		try
		{
			res = std::stod(value, &end);
		}catch(...){}
		#else
			res = std::stod(value, &end);
		#endif
		
		#ifdef __NERD_ENV_ARDUINO
		return 0;
		#else
		return end == value.size() ? res : std::numeric_limits<double>::quiet_NaN();
		#endif
	}
	String::operator int() const noexcept
	{
		std::string::size_type end;
		int res;
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		try
		{
			res = std::stoi(value, &end, 10);
		}catch(...){}
		#else
			res = std::stoi(value, &end, 10);
		#endif
		
		#ifdef __NERD_ENV_ARDUINO
		return 0;
		#else
		return end == value.size() ? res : std::numeric_limits<int>::quiet_NaN();
		#endif
	}
	String::operator long long() const noexcept
	{
		std::string::size_type end;
		long long res;
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		try
		{
			res = std::stoll(value, &end, 10);
		}catch(...){}
		#else
			res = std::stoll(value, &end, 10);
		#endif
		
		#ifdef __NERD_ENV_ARDUINO
		return 0;
		#else
		return end == value.size() ? res : std::numeric_limits<long long>::quiet_NaN();
		#endif
	}
	String::operator std::string() const noexcept { return value; }
	// Main operators
	NerdCore::VAR const String::operator[](NerdCore::VAR key) const
	{
		return NerdCore::Global::null;
	}
		
	static NerdCore::Global::var _char = "";	
		
		
	
	NerdCore::VAR &String::GetSet(NerdCore::VAR keyVar)
	{
		if(keyVar.type == NerdCore::Enum::Type::Number)
		{
			int key = (int)keyVar;

			if(key > value.size() - 1)
			{
				return NerdCore::Global::null;
			}
			else
			{
				_char = std::string(1, value[key]);
				return _char;
			}
		}
		else if(keyVar.type == NerdCore::Enum::Type::String)
		{
			std::string key = ((NerdCore::Class::String*)(keyVar.data.ptr))->value;
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
				value.copy((char*)__NERD_FUNCTION(object[key])->bind, value.length());
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
		else
		{
			return NerdCore::Global::null;
		}
	}
		
	
	NerdCore::VAR &String::operator[](NerdCore::VAR key)
	{
		return String::GetSet(key);
	}
	
	NerdCore::VAR &String::operator[](int key)
	{		
		return String::GetSet(key);
	}
	
	NerdCore::VAR &String::operator[](double key)
	{		
		return String::GetSet(key);
	}

	NerdCore::VAR &String::operator[](const char* key)
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
			//__NERD_FUNCTION(object[key])->bind = value.data();
			//value.copy((char*)__NERD_FUNCTION(object[key])->bind, value.length());
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

	// Comparation operators
	String String::operator!() const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	bool String::operator==(const String &_v1) const { return value.compare(_v1.value) == 0; }
	// === emulated with __NERD_EQUAL_VALUE_AND_TYPE
	// !== emulated with __NERD_NOT_EQUAL_VALUE_AND_TYPE
	bool String::operator!=(const String &_v1) const { return value.compare(_v1.value) != 0; }
	bool String::operator<(const String &_v1) const { return value.at(0) < _v1.value.at(0); }
	bool String::operator<=(const String &_v1) const { return value.at(0) <= _v1.value.at(0); }
	bool String::operator>(const String &_v1) const { return value.at(0) > _v1.value.at(0); }
	bool String::operator>=(const String &_v1) const { return value.at(0) >= _v1.value.at(0); }
	// Numeric operators
	String String::operator+() const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator-() const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator++(const int _v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator--(const int _v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator+(const String &_v1) const { return value + _v1.value; }
	String String::operator+=(const String &_v1) { value += _v1.value; return *this; }
	String String::operator-(const String &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator-=(const String &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator*(const String &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator*=(const String &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	// TODO: "**" and "**=" operators
	String String::operator/(const String &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator/=(const String &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator%(const String &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator%=(const String &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator&(const String &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator|(const String &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator^(const String &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator~() const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator>>(const String &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator<<(const String &_v1) const 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator&=(const String &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator|=(const String &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator^=(const String &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator>>=(const String &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator<<=(const String &_v1) 
	{
		#if !defined(__NERD_ENV_ARDUINO) && !defined(__NERD_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	// TODO: ">>>" and ">>>=" operators
	/*** STRING METHODS ***/
	NerdCore::VAR String::toString(NerdCore::VAR* _args, int _length) const
	{
		return value;
	}
	
	NerdCore::VAR String::split(NerdCore::VAR* _args, int _length) const
	{
		NerdCore::VAR _needle;
		if (_length > 0)
			_needle = _args[0];
		else
			return NerdCore::VAR(this->value);

		NerdCore::VAR _arr = new NerdCore::Class::Array();
		char *_v = (char *)malloc(strlen(this->value.c_str()) + 1);
		strcpy(_v, this->value.c_str());
		char *delim = (char *)malloc(strlen(((std::string)_needle).c_str()) + 1);
		strcpy(delim, ((std::string)_needle).c_str());

		char *ptr = strtok(_v, delim);
		int i = 0;
		char *_new;
		while (ptr != NULL)
		{
			_new = (char *)malloc(strlen(ptr) + 1);
			strcpy(_new, ptr);
			__NERD_Object_Set(i, _new, _arr);
			free(_new);
			ptr = strtok(NULL, delim);
			i++;
		}

		free(delim);
		return _arr;
	}
	
	NerdCore::VAR String::indexOf(NerdCore::VAR* _args, int _length) const
	{
		NerdCore::VAR _needle;
		if (_length > 0)
			_needle = _args[0];
		else
			return NerdCore::VAR(-1);

		std::string::size_type loc = this->value.find((std::string)_needle, 0);
		if (loc != std::string::npos)
		{
			return NerdCore::VAR((int)loc);
		}
		return NerdCore::VAR(-1);
	}
	
	NerdCore::VAR String::lastIndexOf(NerdCore::VAR* _args, int _length) const
	{
		NerdCore::VAR _needle;
		if (_length > 0)
			_needle = _args[0];
		else
			return NerdCore::VAR(-1);

		std::string::size_type loc = this->value.find_last_of((std::string)_needle, 0);
		if (loc != std::string::npos)
		{
			return NerdCore::VAR((int)loc);
		}
		return NerdCore::VAR(-1);
	}
	
	NerdCore::VAR String::search(NerdCore::VAR* _args, int _length) const
	{
		NerdCore::VAR _needle;
		if (_length > 0)
			_needle = _args[0];
		else
			return NerdCore::VAR(-1);

		std::string::size_type loc = this->value.find((std::string)_needle, 0);
		if (loc != std::string::npos)
		{
			return NerdCore::VAR((int)loc);
		}
		return NerdCore::VAR(-1);
	}
	
	NerdCore::VAR String::slice(NerdCore::VAR* _args, int _length) const
	{
		NerdCore::VAR _start;
		NerdCore::VAR _end;
		if (_length > 0)
			_start = _args[0];
		else
			return NerdCore::VAR(this->value);
		if (_length > 1)
			_end = _args[1];

		if (_end.type == NerdCore::Enum::Type::Null)
			return NerdCore::VAR(this->value.substr((int)_start, std::string::npos));
		int _endIndex = (int)_end - (int)_start;
		return NerdCore::VAR(this->value.substr((int)_start, _endIndex));
	}
	
	NerdCore::VAR String::substr(NerdCore::VAR* _args, int _length) const
	{
		NerdCore::VAR _start;
		NerdCore::VAR _end;
		if (_length > 0)
			_start = _args[0];
		else
			return NerdCore::VAR(this->value);
		if (_length > 1)
			_end = _args[1];

		if (_end.type == NerdCore::Enum::Type::Null)
			return NerdCore::VAR(this->value.substr((int)_start, std::string::npos));
		return NerdCore::VAR(this->value.substr((int)_start, (int)_end));
	}
		
	NerdCore::VAR String::replace(NerdCore::VAR* _args, int _length) const
	{
		NerdCore::VAR _search;
		NerdCore::VAR _replace;
		if (_length > 0)
			_search = _args[0];
		else
			return NerdCore::VAR(this->value);
		if (_length > 1)
			_replace = _args[1];

		size_t start_pos = this->value.find((std::string)_search);
		if (start_pos == std::string::npos)
		{
			return NerdCore::VAR(value);
		}
		
		std::string _new = value;
		return NerdCore::VAR(_new.replace(start_pos, ((std::string)_search).length(), (std::string)_replace));
	}
	/* END STRING METHODS */
} // namespace NerdCore::Class