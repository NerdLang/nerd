#include "values.h"
#include "./class/specials.h"

namespace NJS::Value
{
	NJS::VAR undefined = NJS::Class::Value::undefined();
	NJS::VAR null = NJS::VAR(NJS::Enum::Type::_NULL, 0);
	NJS::VAR Infinity = NJS::VAR(NJS::Enum::Type::_INFINITY, 0);
	NJS::VAR NaN = NJS::VAR(NJS::Enum::Type::_NAN, 0);
} // namespace NJS::Value
