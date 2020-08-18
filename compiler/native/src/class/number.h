#pragma once
#include "baseobject.h"

namespace NJS::Class
{
	class Number : BaseObject
	{
	public:
		Number();
		Number(int i);
		Number(double d);
		Number(long long i);
		double *__NJS_VALUE;
		operator NJS::VAR() const;
		explicit operator bool() const;
		explicit operator double() const;
		explicit operator int() const;
		explicit operator std::string() const;
		explicit operator long long() const;
		Number operator=(const Number &_v);
		/// Unary operators

		Number operator+();
		Number operator-();
		Number operator!();
		/// Logical operators

		Number operator&&(const Number &_v1);
		Number operator||(const Number &_v1);
		/// Arithmetic operators

		Number operator+(const Number &_v1);
		Number operator+(const char _v1[]);
		Number operator+=(const Number &_v1);
		Number operator-(const Number &_v1);
		Number operator-=(const Number &_v1);
		Number operator*(const Number &_v1);
		Number operator*=(const Number &_v1);
		Number operator/(const Number &_v1);
		Number operator/=(const Number &_v1);
		Number operator%(const Number &_v1);
		Number operator%=(const Number &_v1);
		// TODO: "**" and "**=" operators

		Number operator++(const int _v1);
		Number operator--(const int _v1);
		// Comparison operators

		Number operator==(const Number &_v1);
		// === emulated with __NJS_EQUAL_VALUE_AND_TYPE

		Number operator!=(const Number &_v1);
		// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE

		Number operator<(const Number &_v1);
		Number operator<=(const Number &_v1);
		Number operator>(const Number &_v1);
		Number operator>=(const Number &_v1);
		// Bitwise operators

		Number operator&(const Number &_v1);
		Number operator&=(const Number &_v1);
		Number operator|(const Number &_v1);
		Number operator|=(const Number &_v1);
		Number operator^(const Number &_v1);
		Number operator^=(const Number &_v1);
		Number operator~();
		Number operator>>(const Number &_v1);
		Number operator>>=(const Number &_v1);
		Number operator<<(const Number &_v1);
		Number operator<<=(const Number &_v1);
	};
} // namespace NJS::Class
