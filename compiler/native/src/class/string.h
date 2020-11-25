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
#include "string_header.h"
#include <string>
#include <limits>

namespace NectarCore::Class
{
	// Constructors
	String::String()
	{ 

	}
	String::String(std::string val)
	{
		value = val;
	}
	String::String(const char* val)
	{
		value = val;
	}
	// Methods
	inline void String::Delete() noexcept
	{
		if(--counter == 0)
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
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		try
		{
			res = std::stod(value, &end);
		}catch(...){}
		#else
			res = std::stod(value, &end);
		#endif
		
		return end == value.size() ? res : std::numeric_limits<double>::quiet_NaN();
	}
	String::operator int() const noexcept
	{
		std::string::size_type end;
		int res;
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		try
		{
			res = std::stoi(value, &end, 10);
		}catch(...){}
		#else
			res = std::stoi(value, &end, 10);
		#endif
		
		return end == value.size() ? res : std::numeric_limits<int>::quiet_NaN();
	}
	String::operator long long() const noexcept
	{
		std::string::size_type end;
		long long res;
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		try
		{
			res = std::stoll(value, &end, 10);
		}catch(...){}
		#else
			res = std::stoll(value, &end, 10);
		#endif

		return end == value.size() ? res : std::numeric_limits<long long>::quiet_NaN();
	}
	String::operator std::string() const noexcept { return value; }
	// Main operators
	NectarCore::VAR const String::operator[](NectarCore::VAR key) const
	{
		if (key.type == NectarCore::Enum::Type::Number)
		{
			auto i = (int)key;
			if (i >= 0 && i <= value.size())
			{
				return value.at(i);
			}
			else return NectarCore::Global::undefined;
		}
		std::string _str = ((std::string)key);
		NectarCore::Type::StringView _sview = _str;
		
		if(_sview.compare("length") == 0)
		{
			return (int)value.size();
		}
		
		return NectarCore::Global::undefined;
	}
	static NectarCore::VAR _char;
	static NectarCore::VAR _length;
		
	#ifndef __Nectar__OBJECT_VECTOR
	NectarCore::VAR &String::operator[](NectarCore::VAR key)
	{
		if (key.type == NectarCore::Enum::Type::Number)
		{
			auto i = (int)key;
			if (i >= 0)
			{
				if (i >= value.size())
				{
					value.resize(i + 1);
				}
				_char = value.at(i);
			}
			else _char = "";
			return _char;
		}
		
		std::string _str = ((std::string)key);
		NectarCore::Type::StringView _sview = _str;
		
		NectarCore::VAR& _obj = object[_str];
		if(_obj) return _obj; 
		
		__Nectar_Method_Lazy_Loader("toString", toString);
		__Nectar_Method_Lazy_Loader("split", split);
		__Nectar_Method_Lazy_Loader("indexOf", indexOf);
		__Nectar_Method_Lazy_Loader("lastIndexOf", lastIndexOf);
		__Nectar_Method_Lazy_Loader("search", search);
		__Nectar_Method_Lazy_Loader("slice", slice);
		__Nectar_Method_Lazy_Loader("substr", substr);
		__Nectar_Method_Lazy_Loader("replace", replace);
		
		if(_sview.compare("length") == 0)
		{
			_length = (int)value.size();
			return _length;
		}

		return _obj;
	}
	#else
	NectarCore::VAR &String::operator[](NectarCore::VAR key)
	{		
		if (key.type == NectarCore::Enum::Type::Number)
		{
			auto i = (int)key;
			if (i >= 0)
			{
				if (i >= value.size())
				{
					value.resize(i + 1);
				}
				_char = value.at(i);
			}
			else _char = "";
			return _char;
		}
		
		std::string _str = ((std::string)key);
		NectarCore::Type::StringView _sview = _str;
		for (auto & search : object)
		{
			if (_sview.compare(search.first) == 0)
			{
				return search.second;
			}
		}
		
		__Nectar_Method_Lazy_Loader("toString", toString);
		__Nectar_Method_Lazy_Loader("split", split);
		__Nectar_Method_Lazy_Loader("indexOf", indexOf);
		__Nectar_Method_Lazy_Loader("lastIndexOf", lastIndexOf);
		__Nectar_Method_Lazy_Loader("search", search);
		__Nectar_Method_Lazy_Loader("slice", slice);
		__Nectar_Method_Lazy_Loader("substr", substr);
		__Nectar_Method_Lazy_Loader("replace", replace);

		if(_sview.compare("length") == 0)
		{
			_length = (int)value.size();
			return _length;
		}
		
		object.push_back(NectarCore::Type::pair_t(((std::string)*this), NectarCore::Global::undefined));
		return object[object.size() - 1].second;
	}
	#endif
	
	NectarCore::VAR &String::operator[](int key)
	{		
		if (key >= 0)
		{
			if (key >= value.size())
			{
				value.resize(key + 1);
			}
			_char = value.at(key);
		}
		else _char = "";
		return _char;
	}
	
	NectarCore::VAR &String::operator[](double key)
	{		
		if (key >= 0)
		{
			if (key >= value.size())
			{
				value.resize(key + 1);
			}
			_char = value.at(key);
		}
		else _char = "";
		return _char;
	}

	
	#ifndef __Nectar__OBJECT_VECTOR
	NectarCore::VAR &String::operator[](const char* key)
	{
		std::string _str = key;
		NectarCore::Type::StringView _sview = _str;
		
		NectarCore::VAR& _obj = object[_str];
		if(_obj) return _obj; 
		
		__Nectar_Method_Lazy_Loader("toString", toString);
		__Nectar_Method_Lazy_Loader("split", split);
		__Nectar_Method_Lazy_Loader("indexOf", indexOf);
		__Nectar_Method_Lazy_Loader("lastIndexOf", lastIndexOf);
		__Nectar_Method_Lazy_Loader("search", search);
		__Nectar_Method_Lazy_Loader("slice", slice);
		__Nectar_Method_Lazy_Loader("substr", substr);
		__Nectar_Method_Lazy_Loader("replace", replace);
		
		if(_sview.compare("length") == 0)
		{
			_length = (int)value.size();
			return _length;
		}

		return _obj;
	}
	#else
	NectarCore::VAR &String::operator[](const char* key)
	{		
		std::string _str = key;
		NectarCore::Type::StringView _sview = _str;
		for (auto & search : object)
		{
			if (_sview.compare(search.first) == 0)
			{
				return search.second;
			}
		}
		
		__Nectar_Method_Lazy_Loader("toString", toString);
		__Nectar_Method_Lazy_Loader("split", split);
		__Nectar_Method_Lazy_Loader("indexOf", indexOf);
		__Nectar_Method_Lazy_Loader("lastIndexOf", lastIndexOf);
		__Nectar_Method_Lazy_Loader("search", search);
		__Nectar_Method_Lazy_Loader("slice", slice);
		__Nectar_Method_Lazy_Loader("substr", substr);
		__Nectar_Method_Lazy_Loader("replace", replace);

		if(_sview.compare("length") == 0)
		{
			_length = (int)value.size();
			return _length;
		}
		
		object.push_back(NectarCore::Type::pair_t(((std::string)*this), NectarCore::Global::undefined));
		return object[object.size() - 1].second;
	}
	#endif
	
	// Comparation operators
	String String::operator!() const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	bool String::operator==(const String &_v1) const { return value.compare(_v1.value) == 0; }
	// === emulated with __Nectar_EQUAL_VALUE_AND_TYPE
	// !== emulated with __Nectar_NOT_EQUAL_VALUE_AND_TYPE
	bool String::operator!=(const String &_v1) const { return value.compare(_v1.value) != 0; }
	bool String::operator<(const String &_v1) const { return value.at(0) < _v1.value.at(0); }
	bool String::operator<=(const String &_v1) const { return value.at(0) <= _v1.value.at(0); }
	bool String::operator>(const String &_v1) const { return value.at(0) > _v1.value.at(0); }
	bool String::operator>=(const String &_v1) const { return value.at(0) >= _v1.value.at(0); }
	// Numeric operators
	String String::operator+() const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator-() const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator++(const int _v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator--(const int _v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator+(const String &_v1) const { return value + _v1.value; }
	String String::operator+=(const String &_v1) { value += _v1.value; return *this; }
	String String::operator-(const String &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator-=(const String &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator*(const String &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator*=(const String &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	// TODO: "**" and "**=" operators
	String String::operator/(const String &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator/=(const String &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator%(const String &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator%=(const String &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator&(const String &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator|(const String &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator^(const String &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator~() const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator>>(const String &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator<<(const String &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator&=(const String &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator|=(const String &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator^=(const String &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator>>=(const String &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator<<=(const String &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	// TODO: ">>>" and ">>>=" operators
	/*** STRING METHODS ***/
	NectarCore::VAR String::toString(NectarCore::VAR* _args, int _length) const
	{
		return value;
	}
	
	NectarCore::VAR String::split(NectarCore::VAR* _args, int _length) const
	{
		NectarCore::VAR _needle;
		if (_length > 0)
			_needle = _args[0];
		else
			return NectarCore::VAR(this->value);

		NectarCore::VAR _arr = new NectarCore::Class::Array();
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
			__Nectar_Object_Set(i, _new, _arr);
			free(_new);
			ptr = strtok(NULL, delim);
			i++;
		}

		free(delim);
		return _arr;
	}
	
	NectarCore::VAR String::indexOf(NectarCore::VAR* _args, int _length) const
	{
		NectarCore::VAR _needle;
		if (_length > 0)
			_needle = _args[0];
		else
			return NectarCore::VAR(-1);

		std::string::size_type loc = this->value.find((std::string)_needle, 0);
		if (loc != std::string::npos)
		{
			return NectarCore::VAR((int)loc);
		}
		return NectarCore::VAR(-1);
	}
	
	NectarCore::VAR String::lastIndexOf(NectarCore::VAR* _args, int _length) const
	{
		NectarCore::VAR _needle;
		if (_length > 0)
			_needle = _args[0];
		else
			return NectarCore::VAR(-1);

		std::string::size_type loc = this->value.find_last_of((std::string)_needle, 0);
		if (loc != std::string::npos)
		{
			return NectarCore::VAR((int)loc);
		}
		return NectarCore::VAR(-1);
	}
	
	NectarCore::VAR String::search(NectarCore::VAR* _args, int _length) const
	{
		NectarCore::VAR _needle;
		if (_length > 0)
			_needle = _args[0];
		else
			return NectarCore::VAR(-1);

		std::string::size_type loc = this->value.find((std::string)_needle, 0);
		if (loc != std::string::npos)
		{
			return NectarCore::VAR((int)loc);
		}
		return NectarCore::VAR(-1);
	}
	
	NectarCore::VAR String::slice(NectarCore::VAR* _args, int _length) const
	{
		NectarCore::VAR _start;
		NectarCore::VAR _end;
		if (_length > 0)
			_start = _args[0];
		else
			return NectarCore::VAR(this->value);
		if (_length > 1)
			_end = _args[1];

		if (_end.type == NectarCore::Enum::Type::Undefined)
			return NectarCore::VAR(this->value.substr((int)_start, std::string::npos));
		int _endIndex = (int)_end - (int)_start;
		return NectarCore::VAR(this->value.substr((int)_start, _endIndex));
	}
	
	NectarCore::VAR String::substr(NectarCore::VAR* _args, int _length) const
	{
		NectarCore::VAR _start;
		NectarCore::VAR _end;
		if (_length > 0)
			_start = _args[0];
		else
			return NectarCore::VAR(this->value);
		if (_length > 1)
			_end = _args[1];

		if (_end.type == NectarCore::Enum::Type::Undefined)
			return NectarCore::VAR(this->value.substr((int)_start, std::string::npos));
		return NectarCore::VAR(this->value.substr((int)_start, (int)_end));
	}
		
	NectarCore::VAR String::replace(NectarCore::VAR* _args, int _length) const
	{
		NectarCore::VAR _search;
		NectarCore::VAR _replace;
		if (_length > 0)
			_search = _args[0];
		else
			return NectarCore::VAR(this->value);
		if (_length > 1)
			_replace = _args[1];

		size_t start_pos = this->value.find((std::string)_search);
		if (start_pos == std::string::npos)
		{
			return NectarCore::VAR(value);
		}
		
		std::string _new = value;
		return NectarCore::VAR(_new.replace(start_pos, ((std::string)_search).length(), (std::string)_replace));
	}
	/* END STRING METHODS */
} // namespace NectarCore::Class