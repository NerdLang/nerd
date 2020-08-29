#pragma once
#include "array_header.h"
#include <sstream>
#include <limits>

namespace NJS::Class
{
	// Constructors
	Array::Array() { ++counter; }
	Array::Array(vector_t &val) : value(val)
	{
		Array();
		(*this)["length"] = (int)value.size();
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
	Array::operator bool() const noexcept { return true; }
	Array::operator double() const noexcept
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
	Array::operator int() const noexcept
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
	Array::operator long long() const noexcept
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
	Array::operator std::string() const noexcept
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
	NJS::VAR const Array::operator[](NJS::VAR key) const
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
		int _j = obj.size();
		for (int _i = 0; _i < _j; _i++)
		{
			if (index.compare(obj[_i].first) == 0)
			{
				return obj[_i].second;
			}
		}
		return NJS::VAR();
	}
	NJS::VAR &Array::operator[](NJS::VAR key)
	{
		static NJS::VAR _retUndefined;
		if (key.type == NJS::Enum::Type::NUMBER)
		{
			auto i = (int)key;
			if (i < 0)
			{
				return _retUndefined;
			}
			else 
			{
				if (i >= value.size())
				{
					value.reserve(i + 1);
					value.resize(i + 1);
					(*this)["length"] = (int)value.size();
				}
			}
			return value[i];
		}
		auto &obj = this->object;
		auto index = (std::string)key;
		int _j = obj.size();
		for (int _i = 0; _i < _j; _i++)
		{
			if (index.compare(obj[_i].first) == 0)
			{
				return obj[_i].second;
			}
		}
		obj.push_back(pair_t(index.c_str(), __NJS_VAR()));
		return (*this)[key];
	}
	template <class... Args>
	NJS::VAR Array::operator()(Args... args) const { throw InvalidTypeException(); }
	// Comparation operators
	Array Array::operator!() const { throw InvalidTypeException(); }
	template <typename t> bool Array::operator==(const t &_v1) const { return false; }
	// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
	// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
	template <typename t> bool Array::operator!=(const t &_v1) const { return true; }
	template <typename t> bool Array::operator<(const t &_v1) const { return (*this)[0] < _v1[0]; }
	template <typename t> bool Array::operator<=(const t &_v1) const { return (*this)[0] <= _v1[0]; }
	template <typename t> bool Array::operator>(const t &_v1) const { return (*this)[0] > _v1[0]; }
	template <typename t> bool Array::operator>=(const t &_v1) const { return (*this)[0] >= _v1[0]; }
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
