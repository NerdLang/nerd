#pragma once
#include "function.h"

namespace NJS::Class
{
	class Native : public Function
	{
	public:
		const char *name = "function";
		const unsigned int type = NJS::Enum::Type::NATIVE;
		Native(void *_f);
		void *__NJS_VALUE;
		explicit operator std::string() const;
	};
} // namespace NJS::Class
