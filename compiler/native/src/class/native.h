#pragma once
#include "native_header.h"
#include <functional>
#include <limits>

namespace NJS::Class
{
	// Constructors
	Native::Native() { ++counter; }
	Native::Native(void *val)
	{
		Native();
		value = val;
	}
	// Methods
	Native::~Native()
	{
		delete value;
		object.~vector();
	}
	void Native::Delete()
	{
		if (--counter == 0)
		{
			delete this;
		}
	}
	// Native cast
	Native::operator bool() const noexcept { return true; }
	Native::operator double() const noexcept
	{
		return std::numeric_limits<double>::quiet_NaN();
	}
	Native::operator int() const noexcept
	{
		return std::numeric_limits<int>::quiet_NaN();
	}
	Native::operator long long() const noexcept
	{
		return std::numeric_limits<long long>::quiet_NaN();
	}
	Native::operator std::string() const noexcept
	{
		return "[native code]";
	}
	// Main operators
	NJS::VAR const &Native::operator[](NJS::VAR key) const
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
		return NJS::VAR();
	}
	NJS::VAR &Native::operator[](NJS::VAR key)
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
		auto value = NJS::VAR();
		obj.push_back(std::pair<const char *, NJS::VAR>(index.c_str(), value));
		return value;
	}
	template <class... Args>
	NJS::VAR Native::operator()(Args... args) const
	{
		auto _args = vector_t{(NJS::VAR)args...};
		return (*static_cast<std::function<NJS::VAR(vector_t)> *>(value))(_args);
	}
	// Comparation operators
	Native Native::operator!() const { throw InvalidTypeException(); }
	bool Native::operator==(const Native &_v1) const { return false; }
	// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
	// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
	bool Native::operator!=(const Native &_v1) const { return true; }
	bool Native::operator<(const Native &_v1) const { return false; }
	bool Native::operator<=(const Native &_v1) const { return true; }
	bool Native::operator>(const Native &_v1) const { return false; }
	bool Native::operator>=(const Native &_v1) const { return true; }
	// Numeric operators
	Native Native::operator+() const { throw InvalidTypeException(); }
	Native Native::operator-() const { throw InvalidTypeException(); }
	Native Native::operator++(const int _v1) { throw InvalidTypeException(); }
	Native Native::operator--(const int _v1) { throw InvalidTypeException(); }
	Native Native::operator+(const Native &_v1) const { throw InvalidTypeException(); }
	Native Native::operator+=(const Native &_v1) { throw InvalidTypeException(); }
	Native Native::operator-(const Native &_v1) const { throw InvalidTypeException(); }
	Native Native::operator-=(const Native &_v1) { throw InvalidTypeException(); }
	Native Native::operator*(const Native &_v1) const { throw InvalidTypeException(); }
	Native Native::operator*=(const Native &_v1) { throw InvalidTypeException(); }
	// TODO: "**" and "**=" operators
	Native Native::operator/(const Native &_v1) const { throw InvalidTypeException(); }
	Native Native::operator/=(const Native &_v1) { throw InvalidTypeException(); }
	Native Native::operator%(const Native &_v1) const { throw InvalidTypeException(); }
	Native Native::operator%=(const Native &_v1) { throw InvalidTypeException(); }
	Native Native::operator&(const Native &_v1) const { throw InvalidTypeException(); }
	Native Native::operator|(const Native &_v1) const { throw InvalidTypeException(); }
	Native Native::operator^(const Native &_v1) const { throw InvalidTypeException(); }
	Native Native::operator~() const { throw InvalidTypeException(); }
	Native Native::operator>>(const Native &_v1) const { throw InvalidTypeException(); }
	Native Native::operator<<(const Native &_v1) const { throw InvalidTypeException(); }
	Native Native::operator&=(const Native &_v1) { throw InvalidTypeException(); }
	Native Native::operator|=(const Native &_v1) { throw InvalidTypeException(); }
	Native Native::operator^=(const Native &_v1) { throw InvalidTypeException(); }
	Native Native::operator>>=(const Native &_v1) { throw InvalidTypeException(); }
	Native Native::operator<<=(const Native &_v1) { throw InvalidTypeException(); }
	// TODO: ">>>" and ">>>=" operators
} // namespace NJS::Class
