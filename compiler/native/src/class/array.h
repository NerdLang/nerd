#pragma once
#include "array_header.h"
#include <sstream>
#include <limits>

namespace NJS::Class
{
	// Constructors
	Array::Array() { ++counter; }
	Array::Array(vector_t vec)
	{
		Array();
		value = vec;
		(*this)["length"] = (int)vec.size();
	}
	// Methods
	Array::~Array()
	{
		value.~vector();
		object.~vector();
	}
	void Array::Delete() noexcept
	{
		if (--counter == 0)
		{
			delete this;
		}
	}
	// Native cast
	explicit Array::operator bool() const noexcept { return true; }
	explicit Array::operator double() const noexcept
	{
		if (value.size() < 2)
		{
			return (double)value[0];
		}
		else
		{
			return std::numeric_limits<double>::quiet_NaN();
		}
	}
	explicit Array::operator int() const noexcept
	{
		if (value.size() < 2)
		{
			return (int)value[0];
		}
		else
		{
			return std::numeric_limits<int>::quiet_NaN();
		}
	}
	explicit Array::operator long long() const noexcept
	{
		if (value.size() < 2)
		{
			return (long long)value[0];
		}
		else
		{
			return std::numeric_limits<long long>::quiet_NaN();
		}
	}
	explicit Array::operator std::string() const noexcept
	{
		auto l = value.size();
		if (l == 0)
			return "";
		std::stringstream stream;
		stream << (std::string)value[0];
		for (auto i = 1; i < l; i++)
		{
			stream << "," << (std::string)value[i];
		}
		return stream.str();
	}
	// Main operators
	NJS::VAR const &Array::operator[](NJS::VAR key) const
	{
		if (key.type == NJS::Enum::Type::NUMBER)
		{
			auto i = (int)key;
			if (i >= 0 && i <= value.size())
			{
				return value.at(i);
			}
		}
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
	NJS::VAR &Array::operator[](NJS::VAR key)
	{
		if (key.type == NJS::Enum::Type::NUMBER)
		{
			auto i = (int)key;
			if (i >= 0)
			{
				if (i >= value.size())
				{
					value.resize(i + 1);
					(*this)["length"] = (int)value.size();
				}
				return value.at(i);
			}
		}
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
	NJS::VAR Array::operator()(Args... args) const { throw InvalidTypeException(); }
	// Comparation operators
	Array Array::operator!() const { throw InvalidTypeException(); }
	bool Array::operator==(const Array &_v1) const { return false; }
	// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
	// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
	bool Array::operator!=(const Array &_v1) const { return true; }
	bool Array::operator<(const Array &_v1) const { return (*this)[0] < _v1[0]; }
	bool Array::operator<=(const Array &_v1) const { return (*this)[0] <= _v1[0]; }
	bool Array::operator>(const Array &_v1) const { return (*this)[0] > _v1[0]; }
	bool Array::operator>=(const Array &_v1) const { return (*this)[0] >= _v1[0]; }
	// Numeric operators
	Array Array::operator+() const { throw InvalidTypeException(); }
	Array Array::operator-() const { throw InvalidTypeException(); }
	Array Array::operator++(const int _v1) { throw InvalidTypeException(); }
	Array Array::operator--(const int _v1) { throw InvalidTypeException(); }
	Array Array::operator+(const Array &_v1) const { throw InvalidTypeException(); }
	Array Array::operator+=(const Array &_v1) { throw InvalidTypeException(); }
	Array Array::operator-(const Array &_v1) const { throw InvalidTypeException(); }
	Array Array::operator-=(const Array &_v1) { throw InvalidTypeException(); }
	Array Array::operator*(const Array &_v1) const { throw InvalidTypeException(); }
	Array Array::operator*=(const Array &_v1) { throw InvalidTypeException(); }
	// TODO: "**" and "**=" operators
	Array Array::operator/(const Array &_v1) const { throw InvalidTypeException(); }
	Array Array::operator/=(const Array &_v1) { throw InvalidTypeException(); }
	Array Array::operator%(const Array &_v1) const { throw InvalidTypeException(); }
	Array Array::operator%=(const Array &_v1) { throw InvalidTypeException(); }
	Array Array::operator&(const Array &_v1) const { throw InvalidTypeException(); }
	Array Array::operator|(const Array &_v1) const { throw InvalidTypeException(); }
	Array Array::operator^(const Array &_v1) const { throw InvalidTypeException(); }
	Array Array::operator~() const { throw InvalidTypeException(); }
	Array Array::operator>>(const Array &_v1) const { throw InvalidTypeException(); }
	Array Array::operator<<(const Array &_v1) const { throw InvalidTypeException(); }
	Array Array::operator&=(const Array &_v1) { throw InvalidTypeException(); }
	Array Array::operator|=(const Array &_v1) { throw InvalidTypeException(); }
	Array Array::operator^=(const Array &_v1) { throw InvalidTypeException(); }
	Array Array::operator>>=(const Array &_v1) { throw InvalidTypeException(); }
	Array Array::operator<<=(const Array &_v1) { throw InvalidTypeException(); }
	// TODO: ">>>" and ">>>=" operators
} // namespace NJS::Class
