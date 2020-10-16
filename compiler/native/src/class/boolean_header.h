#pragma once
#include "_meta.h"

namespace NJS::Class
{
	class Boolean : public virtual Base
	{
	public:
		// Constructors
		Boolean();
		Boolean(bool val);
		// Properties
		NJS::Type::object_t object;
		bool value = false;
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
		NJS::VAR toString(NJS::VAR* _args, int _length) const;
		NJS::VAR valueOf(NJS::VAR* _args, int _length) const;
	};
} // namespace NJS::Class
