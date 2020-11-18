#pragma once
#include "_meta.h"

namespace NJS::Class
{
	class Struct : public virtual Base
	{
	public:
		// Constructors
		Struct();
		Struct(void* val);
		Struct(void* val, void* fn);
		// Properties
		count_t counter = 1;
		void* value = nullptr;
		NJS::Type::object_t object;
		NJS::Type::clean_struct* Clean;
		// Methods
		inline void Delete() noexcept;
		inline void StructDelete() noexcept;
		inline void* Copy() noexcept;
		// Struct cast
		explicit operator bool() const noexcept;
		explicit operator double() const noexcept;
		explicit operator int() const noexcept;
		explicit operator long long() const noexcept;
		explicit operator std::string() const noexcept;
		// Main operators
		NJS::VAR const operator[](NJS::VAR key) const;
		NJS::VAR &operator[](NJS::VAR key);
		NJS::VAR &operator[](int key);
		NJS::VAR &operator[](double key);
		NJS::VAR &operator[](const char* key);
		template <class... Args> NJS::VAR operator()(Args... args) const;
		// Comparation operators
		NJS::VAR operator!() const;
		bool operator==(const NJS::VAR &_v1) const;
		// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
		// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
		bool operator!=(const NJS::VAR &_v1) const;
		bool operator<(const NJS::VAR &_v1) const;
		bool operator<=(const NJS::VAR &_v1) const;
		bool operator>(const NJS::VAR &_v1) const;
		bool operator>=(const NJS::VAR &_v1) const;
		// Numeric operators
		NJS::VAR operator+() const;
		NJS::VAR operator-() const;
		NJS::VAR operator++(const int _v1);
		NJS::VAR operator--(const int _v1);
		NJS::VAR operator+(const NJS::VAR &_v1) const;
		NJS::VAR operator+=(const NJS::VAR &_v1);
		NJS::VAR operator-(const NJS::VAR &_v1) const;
		NJS::VAR operator-=(const NJS::VAR &_v1);
		NJS::VAR operator*(const NJS::VAR &_v1) const;
		NJS::VAR operator*=(const NJS::VAR &_v1);
		// TODO: "**" and "**=" operators
		NJS::VAR operator/(const NJS::VAR &_v1) const;
		NJS::VAR operator/=(const NJS::VAR &_v1);
		NJS::VAR operator%(const NJS::VAR &_v1) const;
		NJS::VAR operator%=(const NJS::VAR &_v1);
		NJS::VAR operator&(const NJS::VAR &_v1) const;
		NJS::VAR operator|(const NJS::VAR &_v1) const;
		NJS::VAR operator^(const NJS::VAR &_v1) const;
		NJS::VAR operator~() const;
		NJS::VAR operator>>(const NJS::VAR &_v1) const;
		NJS::VAR operator<<(const NJS::VAR &_v1) const;
		NJS::VAR operator&=(const NJS::VAR &_v1);
		NJS::VAR operator|=(const NJS::VAR &_v1);
		NJS::VAR operator^=(const NJS::VAR &_v1);
		NJS::VAR operator>>=(const NJS::VAR &_v1);
		NJS::VAR operator<<=(const NJS::VAR &_v1);
		// TODO: ">>>" and ">>>=" operators
	};
} // namespace NJS::Class
