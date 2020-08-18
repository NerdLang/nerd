#include "number.h"
#include "baseobject.cpp"
#include <string>
#include <cmath>

#define __NJS_NUMBER_OPERATOR_TEMPLATE(method, op, func) \
	Number NJS::Class::Number::method(const Number &_v1) \
	{                                                    \
		if (__NJS_VALUE & 1 && _v1.__NJS_VALUE & 1)      \
		{                                                \
			int a = (int)*this;                          \
			int b = (int)_v1;                            \
			int *c;                                      \
			if (!func(a, b, c))                          \
			{                                            \
				return a op b;                           \
			}                                            \
		}                                                \
		return (double)*this op(double) _v1;             \
	}

NJS::Class::Number::Number()
{
	BaseObject();
	__NJS_VALUE = 0;
}
NJS::Class::Number::Number(int i)
{
	BaseObject();
	__NJS_VALUE = i << 1;
}

NJS::Class::Number::Number(double d)
{
	BaseObject();
	double dummy;
	if (modf(d, &dummy) == 0.0 && d < INT32_MAX && d > INT32_MIN)
	{
		__NJS_VALUE = (int)d;
		__NJS_VALUE <<= 1;
	}
	else
	{
		*__NJS_VALUE = d;
		__NJS_VALUE <<= 1;
		__NJS_VALUE |= 1;
	}
}

NJS::Class::Number::operator NJS::VAR() const
{
	auto _var = NJS::VAR();
	_var.type = NJS::Enum::Type::NUMBER;
	REGISTER[_ptr].i = this;
	return _var;
}
explicit NJS::Class::Number::operator bool() const
{
	return __NJS_VALUE != 0;
}
explicit NJS::Class::Number::operator double() const
{
	int p = __NJS_VALUE >> 1;
	return __NJS_VALUE & 1 ? *p : (double)p;
}
explicit NJS::Class::Number::operator int() const
{
	int p = __NJS_VALUE >> 1;
	return __NJS_VALUE & 1 ? (int)*p : p;
}
explicit NJS::Class::Number::operator std::string() const
{
	int p = __NJS_VALUE >> 1;
	return to_string(__NJS_VALUE & 1 ? *p : p);
}
explicit NJS::Class::Number::operator long long() const
{
	int p = __NJS_VALUE >> 1;
	return (long long)(__NJS_VALUE & 1 ? *p : p);
}
Number NJS::Class::Number::operator=(const Number &_v)
{
	__NJS_VALUE = _v.__NJS_VALUE;
	_v.Delete();
}
Number NJS::Class::Number::operator=(const int &_v)
{
	__NJS_VALUE = _v << 1;
}
Number NJS::Class::Number::operator=(const double &_v)
{
	*__NJS_VALUE = _v;
	__NJS_VALUE <<= 1;
	__NJS_VALUE |= 1;
}

Number NJS::Class::Number::operator-()
{
	int p = __NJS_VALUE >> 1;
	return -(__NJS_VALUE & 1 ? *p : p);
}

Number NJS::Class::Number::operator+(const Number &_v1)
{
	if (__NJS_VALUE & 1 && _v1.__NJS_VALUE & 1)
	{
		int a = (int)*this;
		int b = (int)_v1;
		int *c;
		if (!__builtin_add_overflow(a, b, c))
		{
			return a + b;
		}
	}
	return (double)*this + (double)_v1;
}

Number NJS::Class::Number::operator-(const Number &_v1)
{
	if (__NJS_VALUE & 1 && _v1.__NJS_VALUE & 1)
	{
		int a = (int)*this;
		int b = (int)_v1;
		int *c;
		if (!__builtin_sub_overflow(a, b, c))
		{
			return a - b;
		}
	}
	return (double)*this - (double)_v1;
}

Number NJS::Class::Number::operator*(const Number &_v1)
{
	if (__NJS_VALUE & 1 && _v1.__NJS_VALUE & 1)
	{
		int a = (int)*this;
		int b = (int)_v1;
		int *c;
		if (!__builtin_mul_overflow(a, b, c))
		{
			return a * b;
		}
	}
	return (double)*this * (double)_v1;
}

Number NJS::Class::Number::operator/(const Number &_v1)
{
	if ((__NJS_VALUE & 1) == 0 && (_v1.__NJS_VALUE & 1) == 0)
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
Number NJS::Class::Number::operator%(const Number &_v1)
{
	if ((__NJS_VALUE & 1) == 0 && (_v1.__NJS_VALUE & 1) == 0)
	{
		return (int)*this % (int)_v1;
	}
	return std::fmod((double)*this, (double)_v1);
}

Number NJS::Class::Number::operator+=(const Number &_v1) { return *this = *this + _v1; }
Number NJS::Class::Number::operator-=(const Number &_v1) { return *this = *this - _v1; }
Number NJS::Class::Number::operator*=(const Number &_v1) { return *this = *this * _v1; }
Number NJS::Class::Number::operator/=(const Number &_v1) { return *this = *this / _v1; }
Number NJS::Class::Number::operator%=(const Number &_v1) { return *this = *this % _v1; }
// TODO: "**" and "**=" operators
Number NJS::Class::Number::operator++(const int _v1)
{
	int p = __NJS_VALUE >> 1;
	if (__NJS_VALUE & 1)
	{
		*p++;
	}
	else
	{
		*this = ++p;
	}
}
Number NJS::Class::Number::operator--(const int _v1)
{
	int p = __NJS_VALUE >> 1;
	if (__NJS_VALUE & 1)
	{
		*p--;
	}
	else
	{
		*this = --p;
	}
}
// Comparison operators

Number operator<(const Number &_v1)
{
	if ((__NJS_VALUE & 1) == 0 && (_v1.__NJS_VALUE & 1) == 0)
	{
		return (int)*this < (int)_v1;
	}
	return (double)*this < (double)_v1;
}
Number operator<=(const Number &_v1)
{
	if ((__NJS_VALUE & 1) == 0 && (_v1.__NJS_VALUE & 1) == 0)
	{
		return (int)*this <= (int)_v1;
	}
	return (double)*this <= (double)_v1;
}
Number operator>(const Number &_v1)
{
	if ((__NJS_VALUE & 1) == 0 && (_v1.__NJS_VALUE & 1) == 0)
	{
		return (int)*this > (int)_v1;
	}
	return (double)*this > (double)_v1;
}
Number operator>=(const Number &_v1)
{
	if ((__NJS_VALUE & 1) == 0 && (_v1.__NJS_VALUE & 1) == 0)
	{
		return (int)*this >= (int)_v1;
	}
	return (double)*this >= (double)_v1;
}

Number NJS::Class::Number::operator&(const Number &_v1) { return (int)*this & (int)_v1; }
Number NJS::Class::Number::operator|(const Number &_v1) { return (int)*this | (int)_v1; }
Number NJS::Class::Number::operator^(const Number &_v1) { return (int)*this ^ (int)_v1; }
Number NJS::Class::Number::operator>>(const Number &_v1) { return (int)*this >> (int)_v1; }
Number NJS::Class::Number::operator<<(const Number &_v1) { return (int)*this << (int)_v1; }

Number operator&=(const Number &_v1) { return *this = *this & _v1; }
Number operator|=(const Number &_v1) { return *this = *this | _v1; }
Number operator^=(const Number &_v1) { return *this = *this ^ _v1; }
Number operator~() { return *this = ~(int)*this; }
Number operator>>=(const Number &_v1) { return *this = *this >> _v1; }
Number operator<<=(const Number &_v1) { return *this = *this << _v1; }
