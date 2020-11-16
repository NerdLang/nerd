#pragma once
#include "undefined_header.h"
#include <limits>

namespace NJS::Class
{
	// Constructors
	Undefined::Undefined() { }
	// Methods
	inline void Undefined::Delete() noexcept
	{
	}
	inline void* Undefined::Copy() noexcept
	{
		return this;
	}
	// Native cast
	Undefined::operator bool() const noexcept { return false; }
	Undefined::operator double() const noexcept { return std::numeric_limits<double>::quiet_NaN(); }
	Undefined::operator int() const noexcept { return std::numeric_limits<int>::quiet_NaN(); }
	Undefined::operator long long() const noexcept { return std::numeric_limits<long long>::quiet_NaN(); }
	Undefined::operator std::string() const noexcept { return "undefined"; }
	// Main operators
	NJS::VAR const Undefined::operator[](NJS::VAR key) const
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw NJS::VAR("TypeError: Cannot read property '" + (std::string)key + "' of undefined ");
		#endif
		return NJS::Global::undefined;
	}
	NJS::VAR &Undefined::operator[](NJS::VAR key)
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw NJS::VAR("TypeError: Cannot read property '" + (std::string)key + "' of undefined ");
		#endif
		return NJS::Global::undefined;
	}
	NJS::VAR &Undefined::operator[](int key)
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw NJS::VAR("TypeError: Cannot read property " + std::to_string(key) + " of undefined ");
		#endif
		return NJS::Global::undefined;
	}
	NJS::VAR &Undefined::operator[](double key)
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw NJS::VAR("TypeError: Cannot read property " + std::to_string(key) + " of undefined ");
		#endif
		return NJS::Global::undefined;
	}
	NJS::VAR &Undefined::operator[](const char* key)
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw NJS::VAR("TypeError: Cannot read property '" + (std::string)key + "' of undefined ");
		#endif
		return NJS::Global::undefined;
	}
	template <class... Args>
	NJS::VAR Undefined::operator()(Args... args) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return NJS::Global::undefined;
	}
	// Comparation operators
	Undefined Undefined::operator!() const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	bool Undefined::operator==(const Undefined &_v1) const { return true; }
	// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
	// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
	bool Undefined::operator!=(const Undefined &_v1) const { return false; }
	bool Undefined::operator<(const Undefined &_v1) const { return false; }
	bool Undefined::operator<=(const Undefined &_v1) const { return false; }
	bool Undefined::operator>(const Undefined &_v1) const { return false; }
	bool Undefined::operator>=(const Undefined &_v1) const { return false; }
	// Numeric operators
	Undefined Undefined::operator+() const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator-() const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator++(const int _v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator--(const int _v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator+(const Undefined &_v1) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator+=(const Undefined &_v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator-(const Undefined &_v1) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator-=(const Undefined &_v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator*(const Undefined &_v1) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator*=(const Undefined &_v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	// TODO: "**" and "**=" operators
	Undefined Undefined::operator/(const Undefined &_v1) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator/=(const Undefined &_v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator%(const Undefined &_v1) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator%=(const Undefined &_v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator&(const Undefined &_v1) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator|(const Undefined &_v1) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator^(const Undefined &_v1) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator~() const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator>>(const Undefined &_v1) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator<<(const Undefined &_v1) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator&=(const Undefined &_v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator|=(const Undefined &_v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator^=(const Undefined &_v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator>>=(const Undefined &_v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	Undefined Undefined::operator<<=(const Undefined &_v1) 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Undefined();
	}
	// TODO: ">>>" and ">>>=" operators
} // namespace NJS::Class
