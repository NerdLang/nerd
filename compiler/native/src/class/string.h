#pragma once
#include "object.h"

namespace NJS::Class
{
	class String : public Object
	{
	public:
		const char *name = "string";
		const NJS::Enum::Type type = NJS::Enum::Type::STRING;
		String();
		String(const char *str);
		String(std::string str);
		std::string __NJS_VALUE;
		explicit operator bool() const;
		explicit operator double() const;
		explicit operator int() const;
		explicit operator std::string() const;
		explicit operator long long() const;
		NJS::VAR &operator[](NJS::VAR _index) const;
		NJS::VAR &operator[](NJS::VAR _index);
		NJS::VAR __iterator();
		String charAt(std::vector<NJS::VAR> args);
		int charCodeAt(std::vector<NJS::VAR> args);
		int codePointAt(std::vector<NJS::VAR> args);
		String concat(std::vector<NJS::VAR> args);
		bool endsWith(std::vector<NJS::VAR> args);
		String fixed();
		bool includes(std::vector<NJS::VAR> args);
		int indexOf(std::vector<NJS::VAR> args);
		int lastIndexOf();
		String localeCompare();
		String match();
		String normalize();
		String padEnd();
		String padStart();
		String repeat();
		String replace();
		String search();
		String slice();
		String split();
		bool startsWith();
		String substr();
		String substring();
		String toLocaleLowerCase();
		String toLocaleUpperCase();
		String toLowerCase();
		String toUpperCase();
		String trim();
		String trimEnd();
		String trimStart();
	};
} // namespace NJS::Class
