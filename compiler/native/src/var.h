#pragma once
#include <string>
#include <vector>
#include "enum.h"

namespace NJS
{
	struct VAR
	{
	private:
		void setPtr();
		void delPtr();

	public:
		NJS::Enum::Type type;
		int _ptr = -1;

		inline NJS::MEMORY::VAL get() const;
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
