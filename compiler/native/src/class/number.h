#pragma once
#include "object.h"
#include <string>

namespace NJS::Class
{
	class Number : Object
	{
	private:
		inline bool isHeap() const;
		inline int getSmi() const;
		inline void setSmi(int &v);
		inline double getHeap() const;
		inline void setHeap(double &d);

	public:
		const char *name = "number";
		const unsigned int type = NJS::Enum::Type::NUMBER;
		Number();
		Number(int i);
		Number(double d);
		Number(long long i);
		unsigned int __NJS_VALUE;
		explicit operator bool() const;
		explicit operator double() const;
		explicit operator int() const;
		explicit operator std::string() const;
		explicit operator long long() const;
		Number operator=(const Number &_v);
		Number operator=(int &_v1);
		Number operator=(double &_v1);
		/// Unary operators

		Number operator-();

		/// Arithmetic operators

		Number operator+(const Number &_v1);
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

		bool operator==(const Number &_v1);
		// === emulated with __NJS_EQUAL_VALUE_AND_TYPE

		bool operator!=(const Number &_v1);
		// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE

		bool operator<(const Number &_v1);
		bool operator<=(const Number &_v1);
		bool operator>(const Number &_v1);
		bool operator>=(const Number &_v1);
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
