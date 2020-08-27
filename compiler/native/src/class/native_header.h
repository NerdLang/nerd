#pragma once
#include "_meta.h"

namespace NJS::Class
{
	class Native
	{
	public:
		// Constants
		const char *name = "native";
		const NJS::Enum::Type type = NJS::Enum::Type::NATIVE;
		// Constructors
		Native();
		Native(void* val);
		// Properties
		count_t counter = 0;
		void* value = nullptr;
		object_t object = {};
		// Methods
		~Native();
		void Delete() noexcept;
		// Native cast
		explicit Native::operator bool() const noexcept { return true; }
		explicit Native::operator double() const noexcept
		{
			return std::numeric_limits<double>::quiet_NaN();
		}
		explicit Native::operator int() const noexcept
		{
			return std::numeric_limits<int>::quiet_NaN();
		}
		explicit Native::operator long long() const noexcept
		{
			return std::numeric_limits<long long>::quiet_NaN();
		}
		explicit Native::operator std::string() const noexcept
		{
			return "[native code]";
		}
		// Main operators
		NJS::VAR const &operator[](NJS::VAR key) const;
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
