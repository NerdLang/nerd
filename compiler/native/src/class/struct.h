#pragma once
#include "struct_header.h"
#include <functional>
#include <limits>

namespace NJS::Class
{
	// Constructors
	Struct::Struct() {}
	Struct::Struct(void *val)
	{
		value = val;
	}
	Struct::Struct(void *val, void* fn)
	{
		value = val;
		Clean = (NJS::Type::clean_struct*)fn;
	}
	// Methods
	inline void Struct::Delete() noexcept
	{
		if (--counter == 0)
		{
			(*static_cast<NJS::Type::clean_struct *>(Clean))(value);
			delete Clean;
			delete this;
		}
	}
	
	inline void* Struct::Copy() noexcept
	{
		counter++;
		return this;
	}
	// Native cast
	Struct::operator bool() const noexcept { return true; }
	Struct::operator double() const noexcept
	{
		return std::numeric_limits<double>::quiet_NaN();
	}
	Struct::operator int() const noexcept
	{
		return std::numeric_limits<int>::quiet_NaN();
	}
	Struct::operator long long() const noexcept
	{
		return std::numeric_limits<long long>::quiet_NaN();
	}
	Struct::operator std::string() const noexcept
	{
		return "[native struct]";
	}
	// Main operators
	NJS::VAR const Struct::operator[](NJS::VAR key) const
	{
		return NJS::Global::undefined;
	}
	NJS::VAR &Struct::operator[](NJS::VAR key)
	{
		#ifdef __NJS__OBJECT_HASHMAP
		return object[(std::string)key];
		#else
		for (auto & search : object)
		{
			if (((std::string)key).compare(search.first) == 0)
			{
				return search.second;
			}
		}

		object.push_back(NJS::Type::pair_t((std::string)key, NJS::VAR()));
		return object[object.size() - 1].second;
		#endif
	}
	
	NJS::VAR &Struct::operator[](int key)
	{
		#ifdef __NJS__OBJECT_HASHMAP
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

		object.push_back(NJS::Type::pair_t(_str, NJS::VAR()));
		return object[object.size() - 1].second;
		#endif
	}
	
	NJS::VAR &Struct::operator[](double key)
	{
		#ifdef __NJS__OBJECT_HASHMAP
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

		object.push_back(NJS::Type::pair_t(_str, NJS::VAR()));
		return object[object.size() - 1].second;
		#endif
	}
	
	
	NJS::VAR &Struct::operator[](const char* key)
	{
		std::string str = key;
		#ifdef __NJS__OBJECT_HASHMAP
		return object[str];
		#else
		for (auto & search : object)
		{
			if (str.compare(search.first) == 0)
			{
				return search.second;
			}
		}

		object.push_back(NJS::Type::pair_t(str, NJS::VAR()));
		return object[object.size() - 1].second;
		#endif
	}
	
	template <class... Args>
	NJS::VAR Struct::operator()(Args... args) const
	{
		auto _args = NJS::Type::vector_t{(NJS::VAR)args...};
		return (*static_cast<std::function<NJS::VAR(NJS::Type::vector_t)> *>(value))(_args);
	}
	// Comparation operators
	NJS::VAR Struct::operator!() const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NJS::VAR();
	}
	bool Struct::operator==(const NJS::VAR &_v1) const { return false; }
	// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
	// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
	bool Struct::operator!=(const NJS::VAR &_v1) const { return true; }
	bool Struct::operator<(const NJS::VAR &_v1) const { return false; }
	bool Struct::operator<=(const NJS::VAR &_v1) const { return true; }
	bool Struct::operator>(const NJS::VAR &_v1) const { return false; }
	bool Struct::operator>=(const NJS::VAR &_v1) const { return true; }
	// Numeric operators
	NJS::VAR Struct::operator+() const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NJS::VAR();
	}
	NJS::VAR Struct::operator-() const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NJS::VAR();
	}
	NJS::VAR Struct::operator++(const int _v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NJS::VAR();
	}
	NJS::VAR Struct::operator--(const int _v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NJS::VAR();
	}
	NJS::VAR Struct::operator+(const NJS::VAR &_v1) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NJS::VAR();
	}
	NJS::VAR Struct::operator+=(const NJS::VAR &_v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NJS::VAR();
	}
	NJS::VAR Struct::operator-(const NJS::VAR &_v1) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NJS::VAR();
	}
	NJS::VAR Struct::operator-=(const NJS::VAR &_v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NJS::VAR();
	}
	NJS::VAR Struct::operator*(const NJS::VAR &_v1) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NJS::VAR();
	}
	NJS::VAR Struct::operator*=(const NJS::VAR &_v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NJS::VAR();
	}
	// TODO: "**" and "**=" operators
	NJS::VAR Struct::operator/(const NJS::VAR &_v1) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NJS::VAR();
	}
	NJS::VAR Struct::operator/=(const NJS::VAR &_v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NJS::VAR();
	}
	NJS::VAR Struct::operator%(const NJS::VAR &_v1) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NJS::VAR();
	}
	NJS::VAR Struct::operator%=(const NJS::VAR &_v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NJS::VAR();
	}
	NJS::VAR Struct::operator&(const NJS::VAR &_v1) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NJS::VAR();
	}
	NJS::VAR Struct::operator|(const NJS::VAR &_v1) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NJS::VAR();
	}
	NJS::VAR Struct::operator^(const NJS::VAR &_v1) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NJS::VAR();
	}
	NJS::VAR Struct::operator~() const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NJS::VAR();
	}
	NJS::VAR Struct::operator>>(const NJS::VAR &_v1) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NJS::VAR();
	}
	NJS::VAR Struct::operator<<(const NJS::VAR &_v1) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NJS::VAR();
	}
	NJS::VAR Struct::operator&=(const NJS::VAR &_v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NJS::VAR();
	}
	NJS::VAR Struct::operator|=(const NJS::VAR &_v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NJS::VAR();
	}
	NJS::VAR Struct::operator^=(const NJS::VAR &_v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NJS::VAR();
	}
	NJS::VAR Struct::operator>>=(const NJS::VAR &_v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NJS::VAR();
	}
	NJS::VAR Struct::operator<<=(const NJS::VAR &_v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NJS::VAR();
	}
	// TODO: ">>>" and ">>>=" operators
} // namespace NJS::Class
