#pragma once
#include "_meta.h"

namespace NJS::Class
{
	class String : public virtual Base
	{
	public:
		// Constants
		const NJS::Enum::Type type = NJS::Enum::Type::String;
		// Constructors
		String();
		String(std::string val);
		String(const char* val);
		// Properties
		count_t counter = 0;
		std::string value = "";
		NJS::Type::object_t object;
		// Methods
		void Delete() noexcept;
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
		NJS::VAR toString(NJS::Type::vector_t args) const;
		NJS::VAR split(NJS::Type::vector_t args) const;
		NJS::VAR indexOf(NJS::Type::vector_t args) const;
		NJS::VAR lastIndexOf(NJS::Type::vector_t args) const;
		NJS::VAR search(NJS::Type::vector_t args) const;
		NJS::VAR slice(NJS::Type::vector_t args) const;
		NJS::VAR substr(NJS::Type::vector_t args) const;
		NJS::VAR replace(NJS::Type::vector_t args) const;
		/* END STRING METHODS */
	};
} // namespace NJS::Class
