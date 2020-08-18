#pragma once
#include "baseobject.h"

namespace NJS::Class
{
	class String : BaseObject
	{
	public:
		String();
		String(const char *str);
		std::string __NJS_VALUE;
		operator NJS::VAR() const;
		explicit operator bool() const;
		explicit operator double() const;
		explicit operator int() const;
		explicit operator std::string() const;
		explicit operator long long() const;
		String &operator[](NJS::VAR _index) const;
		String &operator[](NJS::VAR _index);
		NJS::VAR __iterator();
		String charAt(std::vector<NJS::VAR> args);
		Number charCodeAt();
		String codePointAt();
		String concat();
		String endsWith();
		String fixed();
		String includes();
		String indexOf();
		String lastIndexOf();
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
		String startsWith();
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
