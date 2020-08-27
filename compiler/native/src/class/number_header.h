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
		Number(int val);
		Number(double val);
		Number(long long val);
		// Properties
		count_t counter = 0;
		uint32_t value = 0;
		object_t object = {};
		// Methods
		~Number();
		inline bool isInt() const noexcept;
		void Delete() noexcept;
		// Native cast
		explicit Number::operator bool() const noexcept { return getInt(); }
		explicit Number::operator double() const noexcept { return getDouble(); }
		explicit Number::operator int() const noexcept { return getInt(); }
		explicit Number::operator long long() const noexcept
		{
			if (isFinite())
			{
				return isInt() ? getInt() : getDouble();
			}
			if (isNaN())
			{
				return std::numeric_limits<long long>::quiet_NaN();
			}
			return std::numeric_limits<long long>::infinity() * (isNegative() ? -1 : 1);
		}
		explicit Number::operator std::string() const noexcept
		{
			if (isFinite())
			{
				return std::to_string(isInt() ? getInt() : getDouble());
			}
			if (isNaN())
			{
				return "NaN";
			}
			return isNegative() ? "-Infinity" : "Infinity";
		}
		// Main operators
		NJS::VAR const &operator[](NJS::VAR key) const;
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
