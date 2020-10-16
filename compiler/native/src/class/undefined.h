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
	Undefined::operator double() const noexcept { return 0.0; }
	Undefined::operator int() const noexcept { return 0; }
	Undefined::operator long long() const noexcept { return 0L; }
	Undefined::operator std::string() const noexcept { return "undefined"; }
	// Main operators
	NJS::VAR const Undefined::operator[](NJS::VAR key) const
	{
		#ifndef __NJS_ARDUINO 
		throw NJS::VAR("TypeError: Cannot read property '" + (std::string)key + "' of undefined ");
		#endif
	}
	NJS::VAR &Undefined::operator[](NJS::VAR key)
	{
		#ifndef __NJS_ARDUINO 
		throw NJS::VAR("TypeError: Cannot read property '" + (std::string)key + "' of undefined ");
		#endif
	}
	template <class... Args>
	NJS::VAR Undefined::operator()(Args... args) const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	// Comparation operators
	Undefined Undefined::operator!() const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
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
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Undefined Undefined::operator-() const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Undefined Undefined::operator++(const int _v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Undefined Undefined::operator--(const int _v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Undefined Undefined::operator+(const Undefined &_v1) const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Undefined Undefined::operator+=(const Undefined &_v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Undefined Undefined::operator-(const Undefined &_v1) const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Undefined Undefined::operator-=(const Undefined &_v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Undefined Undefined::operator*(const Undefined &_v1) const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Undefined Undefined::operator*=(const Undefined &_v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	// TODO: "**" and "**=" operators
	Undefined Undefined::operator/(const Undefined &_v1) const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Undefined Undefined::operator/=(const Undefined &_v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Undefined Undefined::operator%(const Undefined &_v1) const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Undefined Undefined::operator%=(const Undefined &_v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Undefined Undefined::operator&(const Undefined &_v1) const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Undefined Undefined::operator|(const Undefined &_v1) const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Undefined Undefined::operator^(const Undefined &_v1) const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Undefined Undefined::operator~() const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Undefined Undefined::operator>>(const Undefined &_v1) const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Undefined Undefined::operator<<(const Undefined &_v1) const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Undefined Undefined::operator&=(const Undefined &_v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Undefined Undefined::operator|=(const Undefined &_v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Undefined Undefined::operator^=(const Undefined &_v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Undefined Undefined::operator>>=(const Undefined &_v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Undefined Undefined::operator<<=(const Undefined &_v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	// TODO: ">>>" and ">>>=" operators
} // namespace NJS::Class
