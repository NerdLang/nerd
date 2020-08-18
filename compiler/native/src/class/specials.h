#pragma once
#include "base.h"
#include "../values.h"

namespace NJS::Class::Value
{
	class undefined : Base
	{
		undefined();
		operator NJS::VAR() const;
		NJS::VAR const &operator[](NJS::VAR _index) const;
		NJS::VAR &operator[](NJS::VAR _index);
		NJS::VAR operator()() const;
	};
} // namespace NJS::Class::Value
