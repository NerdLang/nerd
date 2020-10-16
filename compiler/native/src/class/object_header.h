#pragma once
#include "_meta.h"

namespace NJS::Class
{
	class Object : public virtual Base
	{
	public:
		// Constructors
		Object();
		// Properties
		count_t counter = 0;
		NJS::Type::object_t object;
		bool prototype = false;
		NJS::Type::vector_p instance;
		// Methods
		inline void Delete() noexcept;
		inline void jsDelete(const std::string _key) noexcept;
		
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
		Object operator!() const;
		bool operator==(const Object &_v1) const;
		// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
		// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
		bool operator!=(const Object &_v1) const;
		bool operator<(const Object &_v1) const;
		bool operator<=(const Object &_v1) const;
		bool operator>(const Object &_v1) const;
		bool operator>=(const Object &_v1) const;
		// Numeric operators
		Object operator+() const;
		Object operator-() const;
		Object operator++(const int _v1);
		Object operator--(const int _v1);
		Object operator+(const Object &_v1) const;
		Object operator+=(const Object &_v1);
		Object operator-(const Object &_v1) const;
		Object operator-=(const Object &_v1);
		Object operator*(const Object &_v1) const;
		Object operator*=(const Object &_v1);
		// TODO: "**" and "**=" operators
		Object operator/(const Object &_v1) const;
		Object operator/=(const Object &_v1);
		Object operator%(const Object &_v1) const;
		Object operator%=(const Object &_v1);
		Object operator&(const Object &_v1) const;
		Object operator|(const Object &_v1) const;
		Object operator^(const Object &_v1) const;
		Object operator~() const;
		Object operator>>(const Object &_v1) const;
		Object operator<<(const Object &_v1) const;
		Object operator&=(const Object &_v1);
		Object operator|=(const Object &_v1);
		Object operator^=(const Object &_v1);
		Object operator>>=(const Object &_v1);
		Object operator<<=(const Object &_v1);
		// TODO: ">>>" and ">>>=" operators
	};
} // namespace NJS::Class
