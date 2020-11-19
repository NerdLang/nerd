#pragma once
#include "_meta.h"

namespace NJS::Class
{
	class FixedArray : public virtual Base
	{
	public:
		// Constructors
		FixedArray();
		FixedArray(int length);
		// Properties
		count_t counter = 0;
		NJS::VAR length;
		NJS::VAR* value;
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
		NJS::VAR const operator[](int key) const;
		NJS::VAR &operator[](NJS::VAR key);
		NJS::VAR &operator[](int key);
		NJS::VAR &operator[](double key);
		NJS::VAR &operator[](const char* key);

		// Comparation operators
		FixedArray operator!() const;
		
		template <typename t>
		bool operator==(const t &_v1) const;
		
		// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
		// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
		
		template <typename t>
		bool operator!=(const t &_v1) const;
		
		template <typename t>
		bool operator<(const t &_v1) const;
		
		template <typename t>
		bool operator<=(const t &_v1) const;
		
		template <typename t>
		bool operator>(const t &_v1) const;
		
		template <typename t>
		bool operator>=(const t &_v1) const;
		// Numeric operators
		FixedArray operator+() const;
		FixedArray operator-() const;
		FixedArray operator++(const int _v1);
		FixedArray operator--(const int _v1);
		FixedArray operator+(const FixedArray &_v1) const;
		FixedArray operator+=(const FixedArray &_v1);
		FixedArray operator-(const FixedArray &_v1) const;
		FixedArray operator-=(const FixedArray &_v1);
		FixedArray operator*(const FixedArray &_v1) const;
		FixedArray operator*=(const FixedArray &_v1);
		// TODO: "**" and "**=" operators
		FixedArray operator/(const FixedArray &_v1) const;
		FixedArray operator/=(const FixedArray &_v1);
		FixedArray operator%(const FixedArray &_v1) const;
		FixedArray operator%=(const FixedArray &_v1);
		FixedArray operator&(const FixedArray &_v1) const;
		FixedArray operator|(const FixedArray &_v1) const;
		FixedArray operator^(const FixedArray &_v1) const;
		FixedArray operator~() const;
		FixedArray operator>>(const FixedArray &_v1) const;
		FixedArray operator<<(const FixedArray &_v1) const;
		FixedArray operator&=(const FixedArray &_v1);
		FixedArray operator|=(const FixedArray &_v1);
		FixedArray operator^=(const FixedArray &_v1);
		FixedArray operator>>=(const FixedArray &_v1);
		FixedArray operator<<=(const FixedArray &_v1);
		// TODO: ">>>" and ">>>=" operators
	};
} // namespace NJS::Class
