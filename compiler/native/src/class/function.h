#pragma once
#include "object.h"

namespace NJS::Class
{
	class Function : Object
	{
	public:
		const char *name = "function";
		const unsigned int type = NJS::Enum::Type::FUNCTION;
		Function(void *_f);
		void *__NJS_VALUE;
		explicit operator std::string() const;
		template <class... Args>
		NJS::VAR operator()(Args... args) const;
	};
} // namespace NJS::Class
