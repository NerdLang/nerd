#pragma once
#include "object_header.h"
#include <limits>

namespace NJS::Class
{
	// Constructors
	Object::Object() { counter++; }
	// Methods
	void Object::Delete() noexcept
	{
		if (--counter < 1)
		{
			delete this;
		}
	}
	// Native cast
	Object::operator bool() const noexcept { return true; }
	Object::operator double() const noexcept
	{
		return std::numeric_limits<double>::quiet_NaN();
	}
	Object::operator int() const noexcept
	{
		return std::numeric_limits<int>::quiet_NaN();
	}
	Object::operator long long() const noexcept
	{
		return std::numeric_limits<long long>::quiet_NaN();
	}
	Object::operator std::string() const noexcept
	{
		return "[object Object]";
	}
	// Main operators
	NJS::VAR const Object::operator[](NJS::VAR key) const
	{
		auto *obj = &this->object;
		auto index = (std::string)key;
		for (auto pair : *obj)
		{
			if (index.compare(pair.first) == 0)
			{
				return pair.second;
			}
		}
		
		return NJS::VAR();
	}
	NJS::VAR &Object::operator[](NJS::VAR key)
	{
		auto &obj = this->object;
		auto index = (std::string)key;
		for (auto pair : obj)
		{
			if (index.compare(pair.first) == 0)
			{
				return pair.second;
			}
		}

		obj.push_back(std::pair<const char *, NJS::VAR>(index.c_str(), NJS::VAR()));
		return (*this)[key];
	}
	template <class... Args>
	NJS::VAR Object::operator()(Args... args) const { throw InvalidTypeException(); }
	// Comparation operators
	Object Object::operator!() const { throw InvalidTypeException(); }
	bool Object::operator==(const Object &_v1) const { return false; }
	// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
	// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
	bool Object::operator!=(const Object &_v1) const { return true; }
	bool Object::operator<(const Object &_v1) const { return false; }
	bool Object::operator<=(const Object &_v1) const { return true; }
	bool Object::operator>(const Object &_v1) const { return false; }
	bool Object::operator>=(const Object &_v1) const { return true; }
	// Numeric operators
	Object Object::operator+() const { throw InvalidTypeException(); }
	Object Object::operator-() const { throw InvalidTypeException(); }
	Object Object::operator++(const int _v1) { throw InvalidTypeException(); }
	Object Object::operator--(const int _v1) { throw InvalidTypeException(); }
	Object Object::operator+(const Object &_v1) const { throw InvalidTypeException(); }
	Object Object::operator+=(const Object &_v1) { throw InvalidTypeException(); }
	Object Object::operator-(const Object &_v1) const { throw InvalidTypeException(); }
	Object Object::operator-=(const Object &_v1) { throw InvalidTypeException(); }
	Object Object::operator*(const Object &_v1) const { throw InvalidTypeException(); }
	Object Object::operator*=(const Object &_v1) { throw InvalidTypeException(); }
	// TODO: "**" and "**=" operators
	Object Object::operator/(const Object &_v1) const { throw InvalidTypeException(); }
	Object Object::operator/=(const Object &_v1) { throw InvalidTypeException(); }
	Object Object::operator%(const Object &_v1) const { throw InvalidTypeException(); }
	Object Object::operator%=(const Object &_v1) { throw InvalidTypeException(); }
	Object Object::operator&(const Object &_v1) const { throw InvalidTypeException(); }
	Object Object::operator|(const Object &_v1) const { throw InvalidTypeException(); }
	Object Object::operator^(const Object &_v1) const { throw InvalidTypeException(); }
	Object Object::operator~() const { throw InvalidTypeException(); }
	Object Object::operator>>(const Object &_v1) const { throw InvalidTypeException(); }
	Object Object::operator<<(const Object &_v1) const { throw InvalidTypeException(); }
	Object Object::operator&=(const Object &_v1) { throw InvalidTypeException(); }
	Object Object::operator|=(const Object &_v1) { throw InvalidTypeException(); }
	Object Object::operator^=(const Object &_v1) { throw InvalidTypeException(); }
	Object Object::operator>>=(const Object &_v1) { throw InvalidTypeException(); }
	Object Object::operator<<=(const Object &_v1) { throw InvalidTypeException(); }
	// TODO: ">>>" and ">>>=" operators
} // namespace NJS::Class
