#pragma once
#include "base.h"
#include "../values.h"

namespace NJS::Class::Value
{
	class undefined : Base
	{
		const char *name = "undefined";
		const unsigned int type = NJS::Enum::Type::UNDEFINED;
		undefined();
		operator NJS::VAR() const;
		explicit operator std::string() const;
		NJS::VAR const &operator[](NJS::VAR _index) const;
		NJS::VAR &operator[](NJS::VAR _index);
	};
	class null : undefined
	{
		const char *name = "object";
		const unsigned int type = NJS::Enum::Type::_NULL;
		null();
		operator NJS::VAR() const;
		explicit operator std::string() const;
	};
	class NaN : Number
	{
		const unsigned int type = NJS::Enum::Type::_NAN;
		NaN();
		operator NJS::VAR() const;
		explicit operator std::string() const;
		NaN operator=(const NaN &_v);
		NaN operator=(int &_v1);
		NaN operator=(double &_v1);
		/// Unary operators

		NaN operator-();
		/// Arithmetic operators

		NaN operator+(const NaN &_v1);
		NaN operator+=(const NaN &_v1);
		NaN operator-(const NaN &_v1);
		NaN operator-=(const NaN &_v1);
		NaN operator*(const NaN &_v1);
		NaN operator*=(const NaN &_v1);
		NaN operator/(const NaN &_v1);
		NaN operator/=(const NaN &_v1);
		NaN operator%(const NaN &_v1);
		NaN operator%=(const NaN &_v1);
		// TODO: "**" and "**=" operators
		NaN operator++(const int _v1);
		NaN operator--(const int _v1);
		bool operator==(const NaN &_v1);
		bool operator!=(const NaN &_v1);
		bool operator<(const NaN &_v1);
		bool operator<=(const NaN &_v1);
		bool operator>(const NaN &_v1);
		bool operator>=(const NaN &_v1);
	};
} // namespace NJS::Class::Value
