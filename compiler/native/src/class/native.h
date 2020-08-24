#pragma once
#include "function.h"

namespace NJS::Class
{
	class Native : public Function
	{
	public:
		const char *name = "function";
		const NJS::Enum::Type type = NJS::Enum::Type::NATIVE;
		Native();
		Native(void *_f);
		void *__NJS_VALUE;
		explicit operator std::string() const;
	};
} // namespace NJS::Class
