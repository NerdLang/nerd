#pragma once
#include "_meta.h"

namespace NJS::Class
{
	class Number
	{
	private:
		// Private methods
		inline int getInt() const noexcept;
		inline void setInt(int v) noexcept;
		inline double getDouble() const noexcept;
		inline void setDouble(double v) noexcept;
		inline bool isNaN() const noexcept;
		inline bool isFinite() const noexcept;
		inline bool isNegative() const noexcept;

	public:
		// Constants
		const char *name = "number";
		const NJS::Enum::Type type = NJS::Enum::Type::NUMBER;
		const int SMI_MAX = 1073741823;
		const int SMI_MIN = -1073741824;
		// Constructors
		Number();
		Number(const int val);
		Number(const double val);
		Number(const long long val);
		// Properties
		count_t counter = 0;
		uint32_t value = 0;
		object_t object;
		// Methods
		inline bool isInt() const noexcept;
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
		Number operator!() const;
		bool operator==(const Number &_v1) const;
		// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
		// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
		bool operator!=(const Number &_v1) const;
		bool operator<(const Number &_v1) const;
		bool operator<=(const Number &_v1) const;
		bool operator>(const Number &_v1) const;
		bool operator>=(const Number &_v1) const;
		// Numeric operators
		Number operator+() const;
		Number operator-() const;
		Number operator++(const int _v1);
		Number operator--(const int _v1);
		Number operator+(const Number &_v1) const;
		Number operator+=(const Number &_v1);
		Number operator-(const Number &_v1) const;
		Number operator-=(const Number &_v1);
		Number operator*(const Number &_v1) const;
		Number operator*=(const Number &_v1);
		// TODO: "**" and "**=" operators
		Number operator/(const Number &_v1) const;
		Number operator/=(const Number &_v1);
		Number operator%(const Number &_v1) const;
		Number operator%=(const Number &_v1);
		Number operator&(const Number &_v1) const;
		Number operator|(const Number &_v1) const;
		Number operator^(const Number &_v1) const;
		Number operator~() const;
		Number operator>>(const Number &_v1) const;
		Number operator<<(const Number &_v1) const;
		Number operator&=(const Number &_v1);
		Number operator|=(const Number &_v1);
		Number operator^=(const Number &_v1);
		Number operator>>=(const Number &_v1);
		Number operator<<=(const Number &_v1);
		// TODO: ">>>" and ">>>=" operators
	};
} // namespace NJS::Class
