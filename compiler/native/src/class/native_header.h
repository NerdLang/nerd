#pragma once
#include "_meta.h"

namespace NJS::Class
{
	class Native : public virtual Base
	{
	public:
		// Constructors
		Native();
		Native(void* val);
		// Properties
		count_t counter = 1;
		void* value = nullptr;
		NJS::Type::object_t object;
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
		Native operator!() const;
		bool operator==(const Native &_v1) const;
		// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
		// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
		bool operator!=(const Native &_v1) const;
		bool operator<(const Native &_v1) const;
		bool operator<=(const Native &_v1) const;
		bool operator>(const Native &_v1) const;
		bool operator>=(const Native &_v1) const;
		// Numeric operators
		Native operator+() const;
		Native operator-() const;
		Native operator++(const int _v1);
		Native operator--(const int _v1);
		Native operator+(const Native &_v1) const;
		Native operator+=(const Native &_v1);
		Native operator-(const Native &_v1) const;
		Native operator-=(const Native &_v1);
		Native operator*(const Native &_v1) const;
		Native operator*=(const Native &_v1);
		// TODO: "**" and "**=" operators
		Native operator/(const Native &_v1) const;
		Native operator/=(const Native &_v1);
		Native operator%(const Native &_v1) const;
		Native operator%=(const Native &_v1);
		Native operator&(const Native &_v1) const;
		Native operator|(const Native &_v1) const;
		Native operator^(const Native &_v1) const;
		Native operator~() const;
		Native operator>>(const Native &_v1) const;
		Native operator<<(const Native &_v1) const;
		Native operator&=(const Native &_v1);
		Native operator|=(const Native &_v1);
		Native operator^=(const Native &_v1);
		Native operator>>=(const Native &_v1);
		Native operator<<=(const Native &_v1);
		// TODO: ">>>" and ">>>=" operators
	};
} // namespace NJS::Class
