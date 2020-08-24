#include "number.h"
#include "object.cpp"
#include <cmath>

NJS::Class::Number::Number()
{
	Object();
	__NJS_VALUE = 0;
}
NJS::Class::Number::Number(int i)
{
	Object();
	setSmi(i);
}

NJS::Class::Number::Number(double d)
{
	Object();
	double dummy;
	if (modf(d, &dummy) == 0.0 && d < INT32_MAX && d > INT32_MIN)
	{
		setSmi(static_cast<int>(d));
	}
	else
	{
		setHeap(d);
	}
}

NJS::Class::Number::Number(long long d)
{
	Object();
	setSmi(static_cast<int>(d));
}

inline bool NJS::Class::Number::isHeap() const
{
	return __NJS_VALUE & 1;
}
inline int NJS::Class::Number::getSmi() const
{
	return __NJS_VALUE >> 1;
}
inline void NJS::Class::Number::setSmi(int v)
{
	__NJS_VALUE = v << 1;
}
inline double NJS::Class::Number::getHeap() const
{
	return *(reinterpret_cast<double *>(__NJS_VALUE >> 1));
}
inline void NJS::Class::Number::setHeap(double d)
{
	*reinterpret_cast<double *>(__NJS_VALUE) = d;
	__NJS_VALUE = (__NJS_VALUE << 1) | 1;
}

explicit NJS::Class::Number::operator bool() const
{
	return __NJS_VALUE != 0 && !_isNaN();
}
explicit NJS::Class::Number::operator double() const
{
	return isHeap() ? getHeap() : (double)getSmi();
}
explicit NJS::Class::Number::operator int() const
{
	return isHeap() ? (int)getHeap() : getSmi();
}
explicit NJS::Class::Number::operator std::string() const
{
	if (_isFinite()) {
		return std::to_string(isHeap() ? getHeap() : getSmi());
	}
	if (_isNaN()) {
		return "NaN";
	}
	return _isNegative() ? "-Infinity" : "Infinity";
}
explicit NJS::Class::Number::operator long long() const
{
	if (_isFinite()) {
		return (long long)(isHeap() ? getHeap() : getSmi());
	}
	if (_isNaN()) {
		return std::numeric_limits<long long>::quiet_NaN();
	}
	return std::numeric_limits<long long>::infinity() * (_isNegative() ? -1 : 1);
}
NJS::Class::Number NJS::Class::Number::operator=(Number &_v)
{
	__NJS_VALUE = _v.__NJS_VALUE;
	_v.Delete();
	return *this;
}
NJS::Class::Number NJS::Class::Number::operator=(int &_v)
{
	setSmi(_v);
	return *this;
}
NJS::Class::Number NJS::Class::Number::operator=(double &_v)
{
	setHeap(_v);
	return *this;
}

NJS::Class::Number NJS::Class::Number::operator-()
{
	return -(isHeap() ? getHeap() : getSmi());
}

NJS::Class::Number NJS::Class::Number::operator+(const Number &_v1)
{
	if (!isHeap() && !_v1.isHeap())
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

NJS::Class::Number NJS::Class::Number::operator-(const Number &_v1)
{
	if (!isHeap() && !_v1.isHeap())
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

NJS::Class::Number NJS::Class::Number::operator*(const Number &_v1)
{
	if (!isHeap() && !_v1.isHeap())
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

NJS::Class::Number NJS::Class::Number::operator/(const Number &_v1)
{
	if (!isHeap() && !_v1.isHeap())
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
NJS::Class::Number NJS::Class::Number::operator%(const Number &_v1)
{
	if (!isHeap() && !_v1.isHeap())
	{
		return (int)*this % (int)_v1;
	}
	else
	{
		return std::fmod((double)*this, (double)_v1);
	}
}

NJS::Class::Number NJS::Class::Number::operator+=(const Number &_v1)
{
	if (!isHeap() && !_v1.isHeap())
	{
		int a = (int)*this;
		int b = (int)_v1;
		int *c;
		if (!__builtin_add_overflow(a, b, c))
		{
			setSmi((int)*this + (int)_v1);
			return;
		}
	}
	setHeap((double)*this + (double)_v1);
}
NJS::Class::Number NJS::Class::Number::operator-=(const Number &_v1)
{
	if (!isHeap() && !_v1.isHeap())
	{
		int a = (int)*this;
		int b = (int)_v1;
		int *c;
		if (!__builtin_sub_overflow(a, b, c))
		{
			setSmi(a - b);
			return;
		}
	}
	setHeap((double)*this - (double)_v1);
}
NJS::Class::Number NJS::Class::Number::operator*=(const Number &_v1)
{
	if (!isHeap() && !_v1.isHeap())
	{
		int a = (int)*this;
		int b = (int)_v1;
		int *c;
		if (!__builtin_mul_overflow(a, b, c))
		{
			setSmi(a * b);
			return;
		}
	}
	setHeap((double)*this * (double)_v1);
}
NJS::Class::Number NJS::Class::Number::operator/=(const Number &_v1)
{
	if (!isHeap() && !_v1.isHeap())
	{
		int a = (int)*this;
		int b = (int)_v1;
		if (a % b == 0)
		{
			setSmi(a / b);
			return;
		}
	}
	setHeap((double)*this / (double)_v1);
}
NJS::Class::Number NJS::Class::Number::operator%=(const Number &_v1)
{
	if (!isHeap() && !_v1.isHeap())
	{
		setSmi((int)*this % (int)_v1);
	}
	else
	{
		setHeap(std::fmod((double)*this, (double)_v1));
	}
}
// TODO: "**" and "**=" operators
NJS::Class::Number NJS::Class::Number::operator++(const int _v1)
{
	if (isHeap())
	{
		double v = getHeap();
		setHeap(++v);
	}
	else
	{
		int v = getSmi();
		setSmi(++v);
	}
}
NJS::Class::Number NJS::Class::Number::operator--(const int _v1)
{
	if (isHeap())
	{
		double v = getHeap();
		setHeap(--v);
	}
	else
	{
		int v = getSmi();
		setSmi(--v);
	}
}
// Comparison operators

bool NJS::Class::Number::operator<(const Number &_v1)
{
	if (!isHeap() && !_v1.isHeap())
	{
		return (int)*this < (int)_v1;
	}
	return (double)*this < (double)_v1;
}
bool NJS::Class::Number::operator<=(const Number &_v1)
{
	if (!isHeap() && !_v1.isHeap())
	{
		return (int)*this <= (int)_v1;
	}
	return (double)*this <= (double)_v1;
}
bool NJS::Class::Number::operator>(const Number &_v1)
{
	if (!isHeap() && !_v1.isHeap())
	{
		return (int)*this > (int)_v1;
	}
	return (double)*this > (double)_v1;
}
bool NJS::Class::Number::operator>=(const Number &_v1)
{
	if (!isHeap() && !_v1.isHeap())
	{
		return (int)*this >= (int)_v1;
	}
	return (double)*this >= (double)_v1;
}

int NJS::Class::Number::operator&(const Number &_v1) { return (int)*this & (int)_v1; }
int NJS::Class::Number::operator|(const Number &_v1) { return (int)*this | (int)_v1; }
int NJS::Class::Number::operator^(const Number &_v1) { return (int)*this ^ (int)_v1; }
int NJS::Class::Number::operator>>(const Number &_v1) { return (int)*this >> (int)_v1; }
int NJS::Class::Number::operator<<(const Number &_v1) { return (int)*this << (int)_v1; }
int NJS::Class::Number::operator~() { return ~(int)*this; }

NJS::Class::Number NJS::Class::Number::operator&=(const Number &_v1)
{
	setSmi(*this & _v1);
	return *this;
}
NJS::Class::Number NJS::Class::Number::operator|=(const Number &_v1)
{
	setSmi(*this | _v1);
	return *this;
}
NJS::Class::Number NJS::Class::Number::operator^=(const Number &_v1)
{
	setSmi(*this ^ _v1);
	return *this;
}
NJS::Class::Number NJS::Class::Number::operator>>=(const Number &_v1)
{
	setSmi(*this >> _v1);
	return *this;
}
NJS::Class::Number NJS::Class::Number::operator<<=(const Number &_v1)
{
	setSmi(*this << _v1);
	return *this;
}

inline bool NJS::Class::Number::_isNaN() const
{
	return isHeap() && std::isnan(getHeap());
}

inline bool NJS::Class::Number::_isFinite() const
{
	return !isHeap() || std::isfinite(getHeap());
}

inline bool NJS::Class::Number::_isNegative() const
{
	return isHeap() ? std::signbit(getHeap()) : getSmi() < 0;
}
