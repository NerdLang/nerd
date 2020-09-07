#pragma once
#include "number_header.h"
#include <cmath>
#include <limits>

namespace NJS::Class
{
	// Private methods
	inline int Number::getInt() const noexcept
	{
		int _res;
		if (isInt())
		{
			_res = static_cast<int>(value >> 1u);
		}
		else
		{
			_res = static_cast<int>(*(reinterpret_cast<double *>(value >> 1u)));
		}
		return _res;
	}
	inline void Number::setInt(int v) noexcept
	{
		if (!isInt())
		{
			delete reinterpret_cast<double *>(value >> 1u);
		}
		value = static_cast<int>(v) << 1u;
	}
	inline double Number::getDouble() const noexcept
	{
		double _res;
		if (isInt())
		{
			_res = static_cast<double>(static_cast<int>(value >> 1u));
		}
		else
		{
			_res =  *(reinterpret_cast<double *>(value >> 1u));
		}
		return _res;
	}
	inline void Number::setDouble(double v) noexcept
	{
		if (!isInt())
		{
			delete reinterpret_cast<double *>(value >> 1u);
		}
		double *tmp = &v;
		value = (reinterpret_cast<long long>(tmp) << 1) | 1;
	}
	inline bool Number::isNaN() const noexcept
	{
		return !isInt() && std::isnan(getDouble());
	}
	inline bool Number::isFinite() const noexcept
	{
		return isInt() || std::isfinite(getDouble());
	}
	inline bool Number::isNegative() const noexcept
	{
		return std::signbit(getDouble());
	}

	// Constructors
	Number::Number() { counter++; setInt(0); }
	Number::Number(const int val)
	{
		counter++;
		setInt(val);
	}
	Number::Number(const double val)
	{
		counter++;
		double dummy;
		if (modf(val, &dummy) == 0.0 && val < SMI_MAX && val > SMI_MIN)
		{
			setInt(static_cast<int>(val));
		}
		else
		{
			setDouble(val);
		}
	}
	Number::Number(const long long val)
	{
		counter++;
		setDouble(static_cast<double>(val));
	}
	
	Number::Number(const Number& val)
	{
		counter++;
		value = val.value;
	}
	

	
	Number::Number(const NJS::VAR& val)
	{
		counter++;
		switch(val.type)
		{
			case NJS::Enum::Type::Number:
				value = ((NJS::Class::Number*)val._ptr)->value;
			break;
			default:
				value = (int)val;
			break;
		}
	}
	// Methods
	inline bool Number::isInt() const noexcept 
	{ 
		return (value & 1) == 0; 
	}
	void Number::Delete() noexcept
	{
		if (--counter == 0)
		{
			delete this;
		}
	}
	// Native cast
	Number::operator bool() const noexcept { return getInt(); }
	Number::operator double() const noexcept { return getDouble(); }
	Number::operator int() const noexcept { return getInt(); }
	Number::operator long long() const noexcept
	{
		if (isFinite())
		{
			if(isInt()) return (int)getInt();
			else return (double)getDouble();
		}
		if (isNaN())
		{
			return std::numeric_limits<long long>::quiet_NaN();
		}
		return std::numeric_limits<long long>::infinity() * (isNegative() ? -1 : 1);
	}
	Number::operator std::string() const noexcept
	{
		if (isFinite())
		{
			if(isInt() == 1)
			{
				return std::to_string(getInt());
			}
			else 
			{
				return to_string(getDouble());
			}
		}
		if (isNaN())
		{
			return "NaN";
		}
		return isNegative() ? "-Infinity" : "Infinity";
	}
	// Main operators
	NJS::VAR const Number::operator[](NJS::VAR key) const
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
	NJS::VAR &Number::operator[](NJS::VAR key)
	{
		for (auto & search : object)
		{
			if (((NJS::Class::String*)key._ptr)->value.compare(search.first) == 0)
			{
				return search.second;
			}
		}

		((NJS::Class::String*)key._ptr)->counter++;
		if(((NJS::Class::String*)key._ptr)->value.compare("toString") == 0  || ((NJS::Class::String*)key._ptr)->value.compare("toLocaleString") == 0)
		{
			object.push_back(pair_t(((NJS::Class::String*)key._ptr)->value.c_str(), __NJS_Create_Var_Scoped_Anon( return __NJS_Object_Stringify(this);)));
		}
		else if(((NJS::Class::String*)key._ptr)->value.compare("valueOf") == 0)
		{
			object.push_back(pair_t(((NJS::Class::String*)key._ptr)->value.c_str(), __NJS_Create_Var_Scoped_Anon( return this; )));
		}
		else 
		{
			object.push_back(pair_t(((NJS::Class::String*)key._ptr)->value.c_str(), __NJS_VAR()));
		}

		return object[object.size() - 1].second;
	}
	template <class... Args>
	NJS::VAR Number::operator()(Args... args) const { throw InvalidTypeException(); }
	// Comparation operators
	Number Number::operator!() const { throw InvalidTypeException(); }
	bool Number::operator==(const Number &_v1) const
	{
		if (isInt() && _v1.isInt())
		{
			return value == _v1.value;
		}
		else
		{
			return (double)*this == (double)_v1;
		}
	}
	// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
	// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
	bool Number::operator!=(const Number &_v1) const
	{
		if (isInt() && _v1.isInt())
		{
			return value != _v1.value;
		}
		else
		{
			return (double)*this != (double)_v1;
		}
	}
	bool Number::operator<(const Number &_v1) const
	{
		if (isInt() && _v1.isInt())
		{
			return value < _v1.value;
		}
		else
		{
			return (double)*this < (double)_v1;
		}
	}
	bool Number::operator<=(const Number &_v1) const
	{
		if (isInt() && _v1.isInt())
		{
			return value <= _v1.value;
		}
		else
		{
			return (double)*this <= (double)_v1;
		}
	}
	bool Number::operator>(const Number &_v1) const
	{
		if (isInt() && _v1.isInt())
		{
			return value > _v1.value;
		}
		else
		{
			return (double)*this > (double)_v1;
		}
	}
	bool Number::operator>=(const Number &_v1) const
	{
		if (isInt() && _v1.isInt())
		{
			return value >= _v1.value;
		}
		else
		{
			return (double)*this >= (double)_v1;
		}
	}
	// Numeric operators
	Number Number::operator+() const { throw InvalidTypeException(); }
	Number Number::operator-() const { if(isInt()) return (int)-getInt() ; else return (double)-getDouble(); }
	Number Number::operator++(const int _v1)
	{
		if (isInt())
		{
			int v = getInt();
			setInt(++v);
		}
		else
		{
			double v = getDouble();
			setDouble(++v);
		}
		return *this;
	}
	Number Number::operator--(const int _v1)
	{
		if (isInt())
		{
			int v = getInt();
			setInt(--v);
		}
		else
		{
			double v = getDouble();
			setDouble(--v);
		}
		return *this;
	}
	Number Number::operator+(const Number &_v1) const
	{
		if (isInt() && isInt())
		{
			int a = (int)*this;
			int b = (int)_v1;
			int c;
			if (!__builtin_add_overflow(a, b, &c))
			{
				return c;
			}
		}
		return (double)*this + (double)_v1;
	}
	Number Number::operator+=(const Number &_v1)
	{
		if (isInt() && _v1.isInt())
		{
			int a = (int)*this;
			int b = (int)_v1;
			int c;
			if (!__builtin_add_overflow(a, b, &c))
			{
				setInt(c);
				return *this;
			}
		}
		setDouble((double)*this + (double)_v1);
		return *this;
	}
	Number Number::operator-(const Number &_v1) const
	{
		if (isInt() && _v1.isInt())
		{
			int a = (int)*this;
			int b = (int)_v1;
			int c;
			if (!__builtin_sub_overflow(a, b, &c))
			{
				return c;
			}
		}
		return (double)*this - (double)_v1;
	}
	Number Number::operator-=(const Number &_v1)
	{
		if (isInt() && _v1.isInt())
		{
			int a = (int)*this;
			int b = (int)_v1;
			int c;
			if (!__builtin_sub_overflow(a, b, &c))
			{
				setInt(c);
				return *this;
			}
		}
		setDouble((double)*this - (double)_v1);
		return *this;
	}
	Number Number::operator*(const Number &_v1) const
	{
		if (isInt() && _v1.isInt())
		{
			int a = (int)*this;
			int b = (int)_v1;
			int c;
			if (!__builtin_mul_overflow(a, b, &c))
			{
				return c;
			}
		}
		return (double)*this * (double)_v1;
	}
	Number Number::operator*=(const Number &_v1)
	{
		if (isInt() && _v1.isInt())
		{
			int a = (int)*this;
			int b = (int)_v1;
			int c;
			if (!__builtin_mul_overflow(a, b, &c))
			{
				setInt(c);
				return *this;
			}
		}
		setDouble((double)*this * (double)_v1);
		return *this;
	}
	// TODO: "**" and "**=" operators
	Number Number::operator/(const Number &_v1) const
	{
		if (isInt() && _v1.isInt())
		{
			int a = (int)*this;
			int b = (int)_v1;
			if (a % b == 0)
			{
				return a / b;
			}
		}
		return (double)*this / (double)_v1;
	}
	Number Number::operator/=(const Number &_v1)
	{
		if (isInt() && _v1.isInt())
		{
			int a = (int)*this;
			int b = (int)_v1;
			if (a % b == 0)
			{
				setInt(a / b);
				return Number();
			}
		}
		setDouble((double)*this / (double)_v1);
		return *this;
	}
	Number Number::operator%(const Number &_v1) const
	{
		if (isInt() && _v1.isInt())
		{
			return (int)*this % (int)_v1;
		}
		else
		{
			return std::fmod((double)*this, (double)_v1);
		}
	}
	Number Number::operator%=(const Number &_v1)
	{
		if (isInt() && _v1.isInt())
		{
			setInt((int)*this % (int)_v1);
		}
		else
		{
			setDouble(std::fmod((double)*this, (double)_v1));
		}
		return *this;
	}
	Number Number::operator&(const Number &_v1) const { return (int)*this & (int)_v1; }
	Number Number::operator|(const Number &_v1) const { return (int)*this | (int)_v1; }
	Number Number::operator^(const Number &_v1) const { return (int)*this ^ (int)_v1; }
	Number Number::operator~() const { return ~(int)*this; }
	Number Number::operator>>(const Number &_v1) const { return (int)*this >> (int)_v1; }
	Number Number::operator<<(const Number &_v1) const { return (int)*this << (int)_v1; }
	Number Number::operator&=(const Number &_v1)
	{
		setInt((int)*this & (int)_v1);
		return *this;
	}
	Number Number::operator|=(const Number &_v1)
	{
		setInt((int)*this | (int)_v1);
		return *this;
	}
	Number Number::operator^=(const Number &_v1)
	{
		setInt((int)*this ^ (int)_v1);
		return *this;
	}
	Number Number::operator>>=(const Number &_v1)
	{
		setInt((int)*this >> (int)_v1);
		return *this;
	}
	Number Number::operator<<=(const Number &_v1)
	{
		setInt((int)*this << (int)_v1);
		return *this;
	}
	// TODO: ">>>" and ">>>=" operators
} // namespace NJS::Class