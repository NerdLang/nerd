#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <memory>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdarg.h>

#ifdef __NJS_ARDUINO
#include <util/delay.h>
#include <string.h>
#include <WString.h>
#include <new.h>
#include <time.h>
#include <nonstd-function.h>
using namespace nonstd;
#else
#include <functional>
#endif

#include "enum.h"
#include "values.h"
#include "classes.h"

#define __NJS_VAR NJS::VAR
#define var __NJS_VAR
#define let __NJS_VAR
#define __NJS_Create_Ptr_Scoped_Anon(__CONTENT__) new function<__NJS_VAR (vector<VAR>)>([&](vector<VAR> __NJS_VARARGS){ __CONTENT__ })
#define __NJS_Create_Ptr_Unscoped_Anon(__CONTENT__) new function<__NJS_VAR (vector<VAR>)>([](vector<VAR> __NJS_VARARGS){ __CONTENT__ })
#define __NJS_Create_Var_Scoped_Anon(__CONTENT__) __NJS_VAR(NJS::Enum::Type::FUNCTION, __NJS_Create_Ptr_Scoped_Anon(__CONTENT__))
#define __NJS_Create_Var_Unscoped_Anon(__CONTENT__) __NJS_VAR(NJS::Enum::Type::FUNCTION, __NJS_Create_Ptr_Unscoped_Anon(__CONTENT__))

union __NJS_VAL {
	int i;
	double d;
	bool b;
	NJS::Class::String *s;
	NJS::Class::Array *a;
	NJS::Class::Object *o;
	NJS::Class::Function *f;
	NJS::Class::Native *n;
};

/*** REGISTER ***/

/*** END REGISTER ***/

namespace NJS
{
	class VAR
	{
	private:
		void setPtr();

	public:
		NJS::Enum::Type type;
		int _ptr = -1;

		inline __NJS_VAL get() const;
		VAR();
		~VAR();

		/**/
		VAR(VAR const &_v);
		/**/

		/*** CONSTRUCTOR ***/
		VAR(NJS::Enum::Type _type, int _value);
		VAR(int _value);
		VAR(double _value);
		VAR(char *_value);
		VAR(std::string _value);
		VAR(const char *_value);
		/*VAR(Class::Array *_value);
	VAR(Class::Object *_value);
	VAR(Class::Native *_value);
	*/
		VAR(NJS::Enum::Type _type, void *_value);
		VAR(std::function<VAR(std::vector<VAR>)> &_value);

		/*** VARIADIC LAMBDAS ***/
		template <class... Args>
		VAR(std::function<VAR(Args...)> &_value);
		/*** END VARIADIC LAMBDAS ***/

		/*** OVERLOAD ***/
		// WIP

		VAR operator()() const;
		VAR operator[](VAR _index) const;
		VAR &operator[](VAR _index);
		/* END OVERLOAD */

		/*** END CONSTRUCTOR ***/

		/*** OPERATOR ***/
		VAR operator=(const VAR &_v);

		/// Unary operators
		VAR operator+();
		VAR operator-();
		VAR operator!();

		/// Logical operators
		VAR operator&&(const VAR &_v1);
		VAR operator||(const VAR &_v1);

		/// Arithmetic operators
		VAR operator+(const VAR &_v1);
		VAR operator+(const char _v1[]);
		VAR operator+=(const VAR &_v1);
		VAR operator-(const VAR &_v1);
		VAR operator-=(const VAR &_v1);
		VAR operator*(const VAR &_v1);
		VAR operator*=(const VAR &_v1);
		VAR operator/(const VAR &_v1);
		VAR operator/=(const VAR &_v1);
		VAR operator%(const VAR &_v1);
		VAR operator%=(const VAR &_v1);
		// TODO: "**" and "**=" operators
		VAR operator++(const int _v1);
		VAR operator--(const int _v1);
		/// Comparison operators
		VAR operator==(const VAR &_v1);
		// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
		VAR operator!=(const VAR &_v1);
		// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
		VAR operator<(const VAR &_v1);
		VAR operator<=(const VAR &_v1);
		VAR operator>(const VAR &_v1);
		VAR operator>=(const VAR &_v1);
		/// Bitwise operators
		VAR operator&(const VAR &_v1);
		VAR operator&=(const VAR &_v1);
		VAR operator|(const VAR &_v1);
		VAR operator|=(const VAR &_v1);
		VAR operator^(const VAR &_v1);
		VAR operator^=(const VAR &_v1);
		VAR operator~();
		VAR operator>>(const VAR &_v1);
		VAR operator>>=(const VAR &_v1);
		VAR operator<<(const VAR &_v1);
		VAR operator<<=(const VAR &_v1);
		// TODO: ">>>" and ">>>=" operator support

		explicit operator int() const;
		explicit operator double() const;
		explicit operator bool() const;
		explicit operator std::string() const;
		explicit operator long long() const;
	};
} // namespace NJS
