#pragma once
#include "function_header.h"
#include <functional>
#include <limits>

namespace NJS::Class
{
	// Constructors
	Function::Function() { ++counter; }
	Function::Function(void *val) : value(val) { Function(); }
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
	NJS::VAR const Function::operator[](NJS::VAR key) const
	{
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
	NJS::VAR &Function::operator[](NJS::VAR key)
	{
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
		
		if(index.compare("toString") == 0  || index.compare("toLocaleString") == 0)
		{
			key.get().s->counter++;
			__NJS_Object_Set(index.c_str(), __NJS_Create_Var_Scoped_Anon( return (std::string)*this;), &this->object);
			return (*this)[key];
		}
		else if(index.compare("valueOf") == 0)
		{
			key.get().s->counter++;
			__NJS_Object_Set(index.c_str(), __NJS_Create_Var_Scoped_Anon( return this; ), &this->object);
			return (*this)[key];
		}
		
		obj.push_back(pair_t(index.c_str(), __NJS_VAR()));
		return (*this)[key];
	}
	NJS::VAR Function::Call(var __INJECTED_THIS, vector<var> __NJS_VARARGS)
	{
		return (*static_cast<function<NJS::VAR(var, vector<NJS::VAR>)> *>(value))(__INJECTED_THIS, __NJS_VARARGS);
	}
		
	
	template <class... Args>
	NJS::VAR Function::operator()(Args... args)
	{
		vector<NJS::VAR> _args = vector<var>{(NJS::VAR)args...};
		return (*static_cast<function<NJS::VAR(var, vector<NJS::VAR>)> *>(value))(__NJS_Create_Undefined(), _args);
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
