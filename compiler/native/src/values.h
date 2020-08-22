#pragma once
#include "var.h"
#include "enum.h"

namespace NJS::Value
{
	auto undefined = NJS::VAR(NJS::Enum::Type::UNDEFINED, 0);
	auto null = NJS::VAR(NJS::Enum::Type::_NULL, 0);
	auto Infinity = NJS::VAR(NJS::Enum::Type::NUMBER, INFINITY);
	auto NaN = NJS::VAR(NJS::Enum::Type::_NAN, 0);
} // namespace NJS::Value
