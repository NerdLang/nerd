#pragma once
#include "string_header.h"
#include <string>
#include <limits>

namespace NJS::Class
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
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
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
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
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
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
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
	NJS::VAR const String::operator[](NJS::VAR key) const
	{
		if (key.type == NJS::Enum::Type::Number)
		{
			auto i = (int)key;
			if (i >= 0 && i <= value.size())
			{
				return value.at(i);
			}
			else return undefined;
		}
		
		if(((std::string)key).compare("length") == 0)
		{
			return (int)value.size();
		}
		
		return undefined;
	}
	#ifdef __NJS__OBJECT_HASHMAP
	NJS::VAR &String::operator[](NJS::VAR key)
	{
		static NJS::VAR _char;
		static NJS::VAR _length;
		
		if (key.type == NJS::Enum::Type::Number)
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
		
		NJS::VAR& _obj = object[(std::string)key];
		if(_obj) return _obj; 
		
		__NJS_Method_Lazy_Loader("toString", toString);
		__NJS_Method_Lazy_Loader("split", split);
		__NJS_Method_Lazy_Loader("indexOf", indexOf);
		__NJS_Method_Lazy_Loader("lastIndexOf", lastIndexOf);
		__NJS_Method_Lazy_Loader("search", search);
		__NJS_Method_Lazy_Loader("slice", slice);
		__NJS_Method_Lazy_Loader("substr", substr);
		__NJS_Method_Lazy_Loader("replace", replace);
		
		if(((std::string)key).compare("length") == 0)
		{
			_length = (int)value.size();
			return _length;
		}

		return undefined;
	}
	#else
	NJS::VAR &String::operator[](NJS::VAR key)
	{
		static NJS::VAR _char;
		static NJS::VAR _length;
		
		if (key.type == NJS::Enum::Type::Number)
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
		
		
		for (auto & search : object)
		{
			if (((std::string)key).compare(search.first) == 0)
			{
				return search.second;
			}
		}
		
		__NJS_Method_Lazy_Loader("toString", toString);
		__NJS_Method_Lazy_Loader("split", split);
		__NJS_Method_Lazy_Loader("indexOf", indexOf);
		__NJS_Method_Lazy_Loader("lastIndexOf", lastIndexOf);
		__NJS_Method_Lazy_Loader("search", search);
		__NJS_Method_Lazy_Loader("slice", slice);
		__NJS_Method_Lazy_Loader("substr", substr);
		__NJS_Method_Lazy_Loader("replace", replace);

		if(((std::string)key).compare("length") == 0)
		{
			_length = (int)value.size();
			return _length;
		}
		
		object.push_back(NJS::Type::pair_t(((std::string)*this).c_str(), undefined));
		return object[object.size() - 1].second;
	}
	#endif
	
	template <class... Args>
	NJS::VAR String::operator()(Args... args) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return undefined;
	}
	// Comparation operators
	String String::operator!() const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	bool String::operator==(const String &_v1) const { return value.compare(_v1.value) == 0; }
	// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
	// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
	bool String::operator!=(const String &_v1) const { return value.compare(_v1.value) != 0; }
	bool String::operator<(const String &_v1) const { return value.at(0) < _v1.value.at(0); }
	bool String::operator<=(const String &_v1) const { return value.at(0) <= _v1.value.at(0); }
	bool String::operator>(const String &_v1) const { return value.at(0) > _v1.value.at(0); }
	bool String::operator>=(const String &_v1) const { return value.at(0) >= _v1.value.at(0); }
	// Numeric operators
	String String::operator+() const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator-() const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator++(const int _v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator--(const int _v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator+(const String &_v1) const { return value + _v1.value; }
	String String::operator+=(const String &_v1) { value += _v1.value; return *this; }
	String String::operator-(const String &_v1) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator-=(const String &_v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator*(const String &_v1) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator*=(const String &_v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	// TODO: "**" and "**=" operators
	String String::operator/(const String &_v1) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator/=(const String &_v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator%(const String &_v1) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator%=(const String &_v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator&(const String &_v1) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator|(const String &_v1) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator^(const String &_v1) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator~() const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator>>(const String &_v1) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator<<(const String &_v1) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator&=(const String &_v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator|=(const String &_v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator^=(const String &_v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator>>=(const String &_v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	String String::operator<<=(const String &_v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return String();
	}
	// TODO: ">>>" and ">>>=" operators
	/*** STRING METHODS ***/
	NJS::VAR String::toString(NJS::VAR* _args, int _length) const
	{
		return value;
	}
	
	NJS::VAR String::split(NJS::VAR* _args, int _length) const
	{
		var _needle;
		if (_length > 0)
			_needle = _args[0];
		else
			return NJS::VAR(this->value);

		NJS::VAR _arr = __NJS_Create_Array();
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
			__NJS_Object_Set(i, _new, _arr);
			free(_new);
			ptr = strtok(NULL, delim);
			i++;
		}

		free(delim);
		return _arr;
	}
	
	NJS::VAR String::indexOf(NJS::VAR* _args, int _length) const
	{
		var _needle;
		if (_length > 0)
			_needle = _args[0];
		else
			return NJS::VAR(-1);

		std::string::size_type loc = this->value.find((std::string)_needle, 0);
		if (loc != std::string::npos)
		{
			return NJS::VAR((int)loc);
		}
		return NJS::VAR(-1);
	}
	
	NJS::VAR String::lastIndexOf(NJS::VAR* _args, int _length) const
	{
		var _needle;
		if (_length > 0)
			_needle = _args[0];
		else
			return NJS::VAR(-1);

		std::string::size_type loc = this->value.find_last_of((std::string)_needle, 0);
		if (loc != std::string::npos)
		{
			return NJS::VAR((int)loc);
		}
		return NJS::VAR(-1);
	}
	
	NJS::VAR String::search(NJS::VAR* _args, int _length) const
	{
		var _needle;
		if (_length > 0)
			_needle = _args[0];
		else
			return NJS::VAR(-1);

		std::string::size_type loc = this->value.find((std::string)_needle, 0);
		if (loc != std::string::npos)
		{
			return NJS::VAR((int)loc);
		}
		return NJS::VAR(-1);
	}
	
	NJS::VAR String::slice(NJS::VAR* _args, int _length) const
	{
		var _start;
		var _end;
		if (_length > 0)
			_start = _args[0];
		else
			return NJS::VAR(this->value);
		if (_length > 1)
			_end = _args[1];

		if (_end.type == NJS::Enum::Type::Undefined)
			return NJS::VAR(this->value.substr((int)_start, std::string::npos));
		int _endIndex = (int)_end - (int)_start;
		return NJS::VAR(this->value.substr((int)_start, _endIndex));
	}
	
	NJS::VAR String::substr(NJS::VAR* _args, int _length) const
	{
		var _start;
		var _end;
		if (_length > 0)
			_start = _args[0];
		else
			return NJS::VAR(this->value);
		if (_length > 1)
			_end = _args[1];

		if (_end.type == NJS::Enum::Type::Undefined)
			return NJS::VAR(this->value.substr((int)_start, std::string::npos));
		return NJS::VAR(this->value.substr((int)_start, (int)_end));
	}
		
	NJS::VAR String::replace(NJS::VAR* _args, int _length) const
	{
		var _search;
		var _replace;
		if (_length > 0)
			_search = _args[0];
		else
			return NJS::VAR(this->value);
		if (_length > 1)
			_replace = _args[1];

		size_t start_pos = this->value.find((std::string)_search);
		if (start_pos == std::string::npos)
		{
			return var(value);
		}
		
		std::string _new = value;
		return var(_new.replace(start_pos, ((std::string)_search).length(), (std::string)_replace));
	}
	/* END STRING METHODS */
} // namespace NJS::Class