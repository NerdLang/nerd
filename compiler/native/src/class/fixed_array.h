#pragma once
#include "array_header.h"
#include <sstream>
#include <limits>
		
namespace NJS::Class
{
	// Constructors
	FixedArray::FixedArray() 
	{ 
		length = 8;
		value = new NJS::VAR[_length];
	}
	FixedArray::FixedArray(int _length)
	{
		length = _length;
		value = new NJS::VAR[_length];
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
	NJS::VAR const FixedArray::operator[](NJS::VAR key) const
	{
		if (key.type == NJS::Enum::Type::Number)
		{
			auto i = (int)key;
			if (i >= 0 && i <= (int)length)
			{
				return value[i];
			}
		}
		
		return NJS::Global::undefined;
	}
	NJS::VAR const FixedArray::operator[](int key) const
	{
		if (key >= 0 && key <= (int)length)
		{
			return value[key];
		}
		
		return NJS::Global::undefined;
	}
	
	#ifdef __NJS__OBJECT_HASHMAP
	NJS::VAR &FixedArray::operator[](NJS::VAR key)
	{	
		if (key.type == NJS::Enum::Type::Number)
		{
			auto i = (int)key;

			if (i < 0)
			{
				return NJS::Global::undefined;
			}
			else 
			{
				if (i >= (int)length)
				{
					return NJS::Global::undefined;
				}
			}
			return value[i];
		}
		
		std::string _str = ((std::string)key);
		NJS::Type::StringView _sview = _str;
		
		if(_sview.compare("length") == 0)
		{
			return length;
		}
		
		NJS::VAR& _obj = object[_str];
				
		return _obj;
	}
	#else
	NJS::VAR &FixedArray::operator[](NJS::VAR key)
	{
		if (key.type == NJS::Enum::Type::Number)
		{
			auto i = (int)key;
			
			if (i < 0)
			{
				return NJS::Global::undefined;
			}
			else 
			{
				if (i >= (int)length)
				{
					value.resize(i + 1);
				}
			}
			return value[i];
		}
		
		std::string _str = ((std::string)key);
		NJS::Type::StringView _sview = _str;
		
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
		
		object.push_back(NJS::Type::pair_t(_str, NJS::Global::undefined));
		return object[object.size() - 1].second;
	}
	#endif
	
	NJS::VAR &FixedArray::operator[](int key)
	{
		if (key < 0)
		{
			return NJS::Global::undefined;
		}
		else 
		{
			if (key >= (int)length)
			{
				return NJS::Global::undefined;
			}
		}
		return value[key];
	}
	
	NJS::VAR &FixedArray::operator[](double key)
	{
		if (key < 0)
		{
			return NJS::Global::undefined;
		}
		else 
		{
			if (key >= (int)length)
			{
				return NJS::Global::undefined;
			}
		}
		return value[(int)key];
	}
	
	#ifdef __NJS__OBJECT_HASHMAP
	NJS::VAR &FixedArray::operator[](const char* key)
	{		
		std::string _str = key;
		NJS::Type::StringView _sview = _str;
		
		if(_sview.compare("length") == 0)
		{
			return length;
		}
		
		NJS::VAR& _obj = object[_str];
		return _obj; 
	}
	#else
	NJS::VAR &FixedArray::operator[](const char* key)
	{
		std::string _str = key;
		NJS::Type::StringView _sview = _str;
		
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

		object.push_back(NJS::Type::pair_t(_str, NJS::Global::undefined));
		return object[object.size() - 1].second;
	}
	#endif
	
	// Comparation operators
	FixedArray FixedArray::operator!() const 
	{ 
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	
	template <typename t>
	bool FixedArray::operator==(const t &_v1) const { return false; }
	
	// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
	// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
	
	template <typename t>
	bool FixedArray::operator!=(const t &_v1) const { return true; }
	
	template <typename t>
	bool FixedArray::operator<(const t &_v1) const { return (*this)[0] < _v1;}
	
	template <typename t>
	bool FixedArray::operator<=(const t &_v1) const { return (*this)[0] <= _v1; }
	
	template <typename t>
	bool FixedArray::operator>(const t &_v1) const { return (*this)[0] > _v1; }
	
	template <typename t>
	bool FixedArray::operator>=(const t &_v1) const { return (*this)[0] >= _v1; }
	// Numeric operators
	FixedArray FixedArray::operator+() const
	{ 
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator-() const
	{ 
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator++(const int _v1)
	{ 
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator--(const int _v1)
	{ 
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator+(const FixedArray &_v1) const 
	{ 
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator+=(const FixedArray &_v1) 
	{ 
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator-(const FixedArray &_v1) const 
	{ 
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator-=(const FixedArray &_v1) 
	{ 
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator*(const FixedArray &_v1) const 
	{ 
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator*=(const FixedArray &_v1) 
	{ 
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	// TODO: "**" and "**=" operators
	FixedArray FixedArray::operator/(const FixedArray &_v1) const 
	{ 
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator/=(const FixedArray &_v1) 
	{ 
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator%(const FixedArray &_v1) const 
	{ 
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator%=(const FixedArray &_v1) 
	{ 
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator&(const FixedArray &_v1) const 
	{ 
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator|(const FixedArray &_v1) const 
	{ 
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator^(const FixedArray &_v1) const 
	{ 
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator~() const 
	{ 
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator>>(const FixedArray &_v1) const 
	{ 
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator<<(const FixedArray &_v1) const 
	{ 
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator&=(const FixedArray &_v1) 
	{ 
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator|=(const FixedArray &_v1) 
	{ 
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator^=(const FixedArray &_v1) 
	{ 
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator>>=(const FixedArray &_v1) 
	{ 
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	FixedArray FixedArray::operator<<=(const FixedArray &_v1) 
	{ 
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return FixedArray();
	}
	// TODO: ">>>" and ">>>=" operators
	
} // namespace NJS::Class
