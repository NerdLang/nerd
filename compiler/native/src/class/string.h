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
		NJS::VAR &operator[](NJS::VAR _index) const;
		NJS::VAR &operator[](NJS::VAR _index);
		NJS::VAR __iterator();
		NJS::VAR charAt(std::vector<NJS::VAR> args);
		NJS::VAR charCodeAt();
		NJS::VAR codePointAt();
		NJS::VAR concat();
		NJS::VAR endsWith();
		NJS::VAR fixed();
		NJS::VAR includes();
		NJS::VAR indexOf();
		NJS::VAR lastIndexOf();
		NJS::VAR localeCompare();
		NJS::VAR match();
		NJS::VAR normalize();
		NJS::VAR padEnd();
		NJS::VAR padStart();
		NJS::VAR repeat();
		NJS::VAR replace();
		NJS::VAR search();
		NJS::VAR slice();
		NJS::VAR split();
		NJS::VAR startsWith();
		NJS::VAR substr();
		NJS::VAR substring();
		NJS::VAR toLocaleLowerCase();
		NJS::VAR toLocaleUpperCase();
		NJS::VAR toLowerCase();
		NJS::VAR toUpperCase();
		NJS::VAR trim();
		NJS::VAR trimEnd();
		NJS::VAR trimStart();
	};
} // namespace NJS::Class
