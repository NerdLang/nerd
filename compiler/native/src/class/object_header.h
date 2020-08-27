#pragma once
#include "_meta.h"

namespace NJS::Class
{
	class Object
	{
	public:
		// Constants
		const char *name = "object";
		const NJS::Enum::Type type = NJS::Enum::Type::OBJECT;
		// Constructors
		Object();
		Object(object_t obj);
		// Properties
		count_t counter = 0;
		object_t object = {};
		object_t &value = object;
		// Methods
		~Object();
		void Delete() noexcept;
		// Native cast
		explicit Object::operator bool() const noexcept { return true; }
		explicit Object::operator double() const noexcept
		{
			return std::numeric_limits<double>::quiet_NaN();
		}
		explicit Object::operator int() const noexcept
		{
			return std::numeric_limits<int>::quiet_NaN();
		}
		explicit Object::operator long long() const noexcept
		{
			return std::numeric_limits<long long>::quiet_NaN();
		}
		explicit Object::operator std::string() const noexcept
		{
			return "[object Object]";
		}
		// Main operators
		NJS::VAR const &operator[](NJS::VAR key) const;
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
