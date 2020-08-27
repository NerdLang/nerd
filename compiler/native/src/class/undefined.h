#pragma once
<<<<<<< HEAD
#include "../var.h"
#include "../enum.h"

class Empty {};

namespace NJS::Class
{
	class Undefined
	{
	public:
		const char *name = "undefined";
		const NJS::Enum::Type type = NJS::Enum::Type::UNDEFINED;
		unsigned int cnt = 0;
		Empty __NJS_VALUE;
		Undefined();
		void Delete();
		explicit operator bool() const;
		explicit operator double() const;
		explicit operator int() const;
		explicit operator std::string() const;
		explicit operator long long() const;
		template<typename T> NJS::VAR operator=(T &_v);
		NJS::VAR const &operator[](std::string _index) const;
		NJS::VAR &operator[](std::string _index);
		template <class... Args>
		NJS::VAR operator()(Args... args) const;
	};
=======
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
	// Native cast
	explicit Undefined::operator bool() const noexcept { return false; }
	explicit Undefined::operator double() const noexcept { return 0.0; }
	explicit Undefined::operator int() const noexcept { return 0; }
	explicit Undefined::operator long long() const noexcept { return 0L; }
	explicit Undefined::operator std::string() const noexcept { return "undefined"; }
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
>>>>>>> develop-classes
} // namespace NJS::Class
