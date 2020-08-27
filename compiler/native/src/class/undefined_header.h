#pragma once
#include "_meta.h"

namespace NJS::Class
{
	class Undefined
	{
	class Empty {};
	public:
		// Constants
		const char *name = "undefined";
		const NJS::Enum::Type type = NJS::Enum::Type::UNDEFINED;
		// Constructors
		Undefined();
		// Properties
		count_t counter = 0;
		Empty value;
		// Methods
		~Undefined();
		void Delete() noexcept;
		// Native cast
		explicit Undefined::operator bool() const noexcept { return false; }
		explicit Undefined::operator double() const noexcept { return 0.0; }
		explicit Undefined::operator int() const noexcept { return 0; }
		explicit Undefined::operator long long() const noexcept { return 0L; }
		explicit Undefined::operator std::string() const noexcept { return "undefined"; }
		// Main operators
		NJS::VAR const &operator[](NJS::VAR key) const;
		NJS::VAR &operator[](NJS::VAR key);
		template <class... Args> NJS::VAR operator()(Args... args) const;
		// Comparation operators
		Undefined operator!() const;
		bool operator==(const Undefined &_v1) const;
		// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
		// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
		bool operator!=(const Undefined &_v1) const;
		bool operator<(const Undefined &_v1) const;
		bool operator<=(const Undefined &_v1) const;
		bool operator>(const Undefined &_v1) const;
		bool operator>=(const Undefined &_v1) const;
		// Numeric operators
		Undefined operator+() const;
		Undefined operator-() const;
		Undefined operator++(const int _v1);
		Undefined operator--(const int _v1);
		Undefined operator+(const Undefined &_v1) const;
		Undefined operator+=(const Undefined &_v1);
		Undefined operator-(const Undefined &_v1) const;
		Undefined operator-=(const Undefined &_v1);
		Undefined operator*(const Undefined &_v1) const;
		Undefined operator*=(const Undefined &_v1);
		// TODO: "**" and "**=" operators
		Undefined operator/(const Undefined &_v1) const;
		Undefined operator/=(const Undefined &_v1);
		Undefined operator%(const Undefined &_v1) const;
		Undefined operator%=(const Undefined &_v1);
		Undefined operator&(const Undefined &_v1) const;
		Undefined operator|(const Undefined &_v1) const;
		Undefined operator^(const Undefined &_v1) const;
		Undefined operator~() const;
		Undefined operator>>(const Undefined &_v1) const;
		Undefined operator<<(const Undefined &_v1) const;
		Undefined operator&=(const Undefined &_v1);
		Undefined operator|=(const Undefined &_v1);
		Undefined operator^=(const Undefined &_v1);
		Undefined operator>>=(const Undefined &_v1);
		Undefined operator<<=(const Undefined &_v1);
		// TODO: ">>>" and ">>>=" operators
	};
} // namespace NJS::Class
