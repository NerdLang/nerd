#pragma once
#include "function_header.h"
#include <functional>
#include <limits>

namespace NJS::Class
{
	// Constructors
	Function::Function() { ++counter; }
	Function::Function(void *val)
	{
		Function();
		value = val;
	}
	// Methods
	Function::~Function()
	{
		delete value;
		object.~vector();
	}
	void Function::Delete() noexcept
	{
		if (--counter == 0)
		{
			delete this;
		}
	}
	// Native cast
	Function::operator bool() const noexcept { return true; }
	Function::operator double() const noexcept
	{
		return std::numeric_limits<double>::quiet_NaN();
	}
	Function::operator int() const noexcept
	{
		return std::numeric_limits<int>::quiet_NaN();
	}
	Function::operator long long() const noexcept
	{
		return std::numeric_limits<long long>::quiet_NaN();
	}
	Function::operator std::string() const noexcept
	{
		return code;
	}
	// Main operators
	NJS::VAR const &Function::operator[](NJS::VAR key) const
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
		
		// TODO: mark this index as non enumarable
		key.get().s->counter++;
		__NJS_Object_Set(key.get().s->value.c_str(), VAR(), obj);
		return (*this)[key];
	}
	NJS::VAR &Function::operator[](NJS::VAR key)
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
	NJS::VAR Function::operator()(Args... args) const
	{
		auto _args = vector_t{(NJS::VAR)args...};
		return (*static_cast<std::function<NJS::VAR(vector_t)> *>(value))(_args);
	}
	// Comparation operators
	Function Function::operator!() const { throw InvalidTypeException(); }
	bool Function::operator==(const Function &_v1) const { return false; }
	// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
	// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
	bool Function::operator!=(const Function &_v1) const { return true; }
	bool Function::operator<(const Function &_v1) const { return false; }
	bool Function::operator<=(const Function &_v1) const { return true; }
	bool Function::operator>(const Function &_v1) const { return false; }
	bool Function::operator>=(const Function &_v1) const { return true; }
	// Numeric operators
	Function Function::operator+() const { throw InvalidTypeException(); }
	Function Function::operator-() const { throw InvalidTypeException(); }
	Function Function::operator++(const int _v1) { throw InvalidTypeException(); }
	Function Function::operator--(const int _v1) { throw InvalidTypeException(); }
	Function Function::operator+(const Function &_v1) const { throw InvalidTypeException(); }
	Function Function::operator+=(const Function &_v1) { throw InvalidTypeException(); }
	Function Function::operator-(const Function &_v1) const { throw InvalidTypeException(); }
	Function Function::operator-=(const Function &_v1) { throw InvalidTypeException(); }
	Function Function::operator*(const Function &_v1) const { throw InvalidTypeException(); }
	Function Function::operator*=(const Function &_v1) { throw InvalidTypeException(); }
	// TODO: "**" and "**=" operators
	Function Function::operator/(const Function &_v1) const { throw InvalidTypeException(); }
	Function Function::operator/=(const Function &_v1) { throw InvalidTypeException(); }
	Function Function::operator%(const Function &_v1) const { throw InvalidTypeException(); }
	Function Function::operator%=(const Function &_v1) { throw InvalidTypeException(); }
	Function Function::operator&(const Function &_v1) const { throw InvalidTypeException(); }
	Function Function::operator|(const Function &_v1) const { throw InvalidTypeException(); }
	Function Function::operator^(const Function &_v1) const { throw InvalidTypeException(); }
	Function Function::operator~() const { throw InvalidTypeException(); }
	Function Function::operator>>(const Function &_v1) const { throw InvalidTypeException(); }
	Function Function::operator<<(const Function &_v1) const { throw InvalidTypeException(); }
	Function Function::operator&=(const Function &_v1) { throw InvalidTypeException(); }
	Function Function::operator|=(const Function &_v1) { throw InvalidTypeException(); }
	Function Function::operator^=(const Function &_v1) { throw InvalidTypeException(); }
	Function Function::operator>>=(const Function &_v1) { throw InvalidTypeException(); }
	Function Function::operator<<=(const Function &_v1) { throw InvalidTypeException(); }
	// TODO: ">>>" and ">>>=" operators
} // namespace NJS::Class
