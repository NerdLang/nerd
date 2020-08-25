#pragma once
#include "_base.h"

namespace NJS::Class
{
	class Function : public Base
	{
	public:
		const char *name = "function";
		const NJS::Enum::Type type = NJS::Enum::Type::FUNCTION;
		Function();
		Function(void *_f);
		void *__NJS_VALUE;
		explicit operator std::string() const;
		template <class... Args>
		NJS::VAR operator()(Args... args) const;
	};
} // namespace NJS::Class
