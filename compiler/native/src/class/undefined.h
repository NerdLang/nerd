#pragma once
#include "undefined_header.h"
#include <limits>

namespace NJS::Class
{
	// Constructors
	Undefined::Undefined() { ++counter; }
	// Methods
	Undefined::~Undefined() {}
	void Undefined::Delete() noexcept
	{
		if (--counter == 0)
		{
			delete this;
		}
	}
	// Main operators
	NJS::VAR const &Undefined::operator[](NJS::VAR key) const
	{
		throw NJS::VAR("TypeError: Cannot read property '" + (std::string)key + "' of undefined ");
	}
	NJS::VAR &Undefined::operator[](NJS::VAR key)
	{
		throw NJS::VAR("TypeError: Cannot read property '" + (std::string)key + "' of undefined ");
	}
	template <class... Args>
	NJS::VAR Undefined::operator()(Args... args) const { throw InvalidTypeException(); }
	// Comparation operators
	Undefined Undefined::operator!() const { throw InvalidTypeException(); }
	bool Undefined::operator==(const Undefined &_v1) const { return true; }
	// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
	// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
	bool Undefined::operator!=(const Undefined &_v1) const { return false; }
	bool Undefined::operator<(const Undefined &_v1) const { return false; }
	bool Undefined::operator<=(const Undefined &_v1) const { return false; }
	bool Undefined::operator>(const Undefined &_v1) const { return false; }
	bool Undefined::operator>=(const Undefined &_v1) const { return false; }
	// Numeric operators
	Undefined Undefined::operator+() const { throw InvalidTypeException(); }
	Undefined Undefined::operator-() const { throw InvalidTypeException(); }
	Undefined Undefined::operator++(const int _v1) { throw InvalidTypeException(); }
	Undefined Undefined::operator--(const int _v1) { throw InvalidTypeException(); }
	Undefined Undefined::operator+(const Undefined &_v1) const { throw InvalidTypeException(); }
	Undefined Undefined::operator+=(const Undefined &_v1) { throw InvalidTypeException(); }
	Undefined Undefined::operator-(const Undefined &_v1) const { throw InvalidTypeException(); }
	Undefined Undefined::operator-=(const Undefined &_v1) { throw InvalidTypeException(); }
	Undefined Undefined::operator*(const Undefined &_v1) const { throw InvalidTypeException(); }
	Undefined Undefined::operator*=(const Undefined &_v1) { throw InvalidTypeException(); }
	// TODO: "**" and "**=" operators
	Undefined Undefined::operator/(const Undefined &_v1) const { throw InvalidTypeException(); }
	Undefined Undefined::operator/=(const Undefined &_v1) { throw InvalidTypeException(); }
	Undefined Undefined::operator%(const Undefined &_v1) const { throw InvalidTypeException(); }
	Undefined Undefined::operator%=(const Undefined &_v1) { throw InvalidTypeException(); }
	Undefined Undefined::operator&(const Undefined &_v1) const { throw InvalidTypeException(); }
	Undefined Undefined::operator|(const Undefined &_v1) const { throw InvalidTypeException(); }
	Undefined Undefined::operator^(const Undefined &_v1) const { throw InvalidTypeException(); }
	Undefined Undefined::operator~() const { throw InvalidTypeException(); }
	Undefined Undefined::operator>>(const Undefined &_v1) const { throw InvalidTypeException(); }
	Undefined Undefined::operator<<(const Undefined &_v1) const { throw InvalidTypeException(); }
	Undefined Undefined::operator&=(const Undefined &_v1) { throw InvalidTypeException(); }
	Undefined Undefined::operator|=(const Undefined &_v1) { throw InvalidTypeException(); }
	Undefined Undefined::operator^=(const Undefined &_v1) { throw InvalidTypeException(); }
	Undefined Undefined::operator>>=(const Undefined &_v1) { throw InvalidTypeException(); }
	Undefined Undefined::operator<<=(const Undefined &_v1) { throw InvalidTypeException(); }
	// TODO: ">>>" and ">>>=" operators
} // namespace NJS::Class
