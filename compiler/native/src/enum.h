#pragma once

namespace NJS::Enum
{
	enum Type
	{
		UNDEFINED = 1,
		NUMBER,
		DOUBLE,
		OBJECT,
		BIGNUMBER,
		BOOLEAN,
		STRING,
		NATIVE,
		FUNCTION,
		ARRAY,
		_NAN,
		_INFINITY,
		_NULL
	};
}