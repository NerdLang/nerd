#pragma once
#include "base.h"
#include "../values.h"

namespace NJS::Class::Value
{
	class undefined : Base
	{
		undefined();
		operator NJS::VAR() const;
		explicit operator std::string() const;
		NJS::VAR const &operator[](NJS::VAR _index) const;
		NJS::VAR &operator[](NJS::VAR _index);
	};
	class null : undefined
	{
		null();
		operator NJS::VAR() const;
		explicit operator std::string() const;
	};
	class NaN : Number 
	{
		NaN();
		operator NJS::VAR() const;
		explicit operator std::string() const;
	};
	class Infinity : Number
	{
		Infinity();
		explicit operator std::string() const;
	}
} // namespace NJS::Class::Value
