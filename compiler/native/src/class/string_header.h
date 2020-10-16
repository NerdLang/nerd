#pragma once
#include "_meta.h"

namespace NJS::Class
{
	class String : public virtual Base
	{
	public:
		// Constructors
		String();
		String(std::string val);
		String(const char* val);
		// Properties
		std::string value;
		NJS::Type::object_t object;
		count_t counter = 1;
		// Methods
		inline void Delete() noexcept;
		inline void* Copy() noexcept;
		// Native cast
		explicit operator bool() const noexcept;
		explicit operator double() const noexcept;
		explicit operator int() const noexcept;
		explicit operator long long() const noexcept;
		explicit operator std::string() const noexcept;
		// Main operators
		NJS::VAR const operator[](NJS::VAR key) const;
		NJS::VAR &operator[](NJS::VAR key);
		template <class... Args> NJS::VAR operator()(Args... args) const;
		// Comparation operators
		String operator!() const;
		bool operator==(const String &_v1) const;
		// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
		// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
		bool operator!=(const String &_v1) const;
		bool operator<(const String &_v1) const;
		bool operator<=(const String &_v1) const;
		bool operator>(const String &_v1) const;
		bool operator>=(const String &_v1) const;
		// Numeric operators
		String operator+() const;
		String operator-() const;
		String operator++(const int _v1);
		String operator--(const int _v1);
		String operator+(const String &_v1) const;
		String operator+=(const String &_v1);
		String operator-(const String &_v1) const;
		String operator-=(const String &_v1);
		String operator*(const String &_v1) const;
		String operator*=(const String &_v1);
		// TODO: "**" and "**=" operators
		String operator/(const String &_v1) const;
		String operator/=(const String &_v1);
		String operator%(const String &_v1) const;
		String operator%=(const String &_v1);
		String operator&(const String &_v1) const;
		String operator|(const String &_v1) const;
		String operator^(const String &_v1) const;
		String operator~() const;
		String operator>>(const String &_v1) const;
		String operator<<(const String &_v1) const;
		String operator&=(const String &_v1);
		String operator|=(const String &_v1);
		String operator^=(const String &_v1);
		String operator>>=(const String &_v1);
		String operator<<=(const String &_v1);
		// TODO: ">>>" and ">>>=" operators
		/*** STRING METHODS ***/
		NJS::VAR toString(NJS::VAR* _args, int _length) const;
		NJS::VAR split(NJS::VAR* _args, int _length) const;
		NJS::VAR indexOf(NJS::VAR* _args, int _length) const;
		NJS::VAR lastIndexOf(NJS::VAR* _args, int _length) const;
		NJS::VAR search(NJS::VAR* _args, int _length) const;
		NJS::VAR slice(NJS::VAR* _args, int _length) const;
		NJS::VAR substr(NJS::VAR* _args, int _length) const;
		NJS::VAR replace(NJS::VAR* _args, int _length) const;
		/* END STRING METHODS */
	};
} // namespace NJS::Class
