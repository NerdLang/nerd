#pragma once
#include "_meta.h"

namespace NJS::Class
{
	class Boolean : public virtual Base
	{
	public:
		// Constants
		const char *name = "boolean";
		const NJS::Enum::Type type = NJS::Enum::Type::Boolean;
		// Constructors
		Boolean();
		Boolean(bool val);
		// Properties
		count_t counter = 0;
		NJS::Type::object_t object = {};
		bool value = false;
		// Methods
		void Delete() noexcept;
		// Native cast
		explicit operator bool() const noexcept;
		explicit operator double() const noexcept;
		explicit operator int() const noexcept;
		explicit operator long long() const noexcept;
		explicit operator std::string() const noexcept;
		// Main operators
		NJS::VAR &operator[](NJS::VAR key);
		template <class... Args> NJS::VAR operator()(Args... args) const;
		// Comparation operators
		Boolean operator!() const;
		bool operator==(const Boolean &_v1) const;
		// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
		// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
		bool operator!=(const Boolean &_v1) const;
		bool operator<(const Boolean &_v1) const;
		bool operator<=(const Boolean &_v1) const;
		bool operator>(const Boolean &_v1) const;
		bool operator>=(const Boolean &_v1) const;
		// Numeric operators
		Boolean operator+() const;
		Boolean operator-() const;
		Boolean operator++(const int _v1);
		Boolean operator--(const int _v1);
		Boolean operator+(const Boolean &_v1) const;
		Boolean operator+=(const Boolean &_v1);
		Boolean operator-(const Boolean &_v1) const;
		Boolean operator-=(const Boolean &_v1);
		Boolean operator*(const Boolean &_v1) const;
		Boolean operator*=(const Boolean &_v1);
		// TODO: "**" and "**=" operators
		Boolean operator/(const Boolean &_v1) const;
		Boolean operator/=(const Boolean &_v1);
		Boolean operator%(const Boolean &_v1) const;
		Boolean operator%=(const Boolean &_v1);
		Boolean operator&(const Boolean &_v1) const;
		Boolean operator|(const Boolean &_v1) const;
		Boolean operator^(const Boolean &_v1) const;
		Boolean operator~() const;
		Boolean operator>>(const Boolean &_v1) const;
		Boolean operator<<(const Boolean &_v1) const;
		Boolean operator&=(const Boolean &_v1);
		Boolean operator|=(const Boolean &_v1);
		Boolean operator^=(const Boolean &_v1);
		Boolean operator>>=(const Boolean &_v1);
		Boolean operator<<=(const Boolean &_v1);
		// TODO: ">>>" and ">>>=" operators
	};
} // namespace NJS::Class
