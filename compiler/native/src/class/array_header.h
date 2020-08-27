#pragma once
#include "_meta.h"

namespace NJS::Class
{
	class Array
	{
	public:
		// Constants
		const char *name = "array";
		const NJS::Enum::Type type = NJS::Enum::Type::ARRAY;
		// Constructors
		Array();
		Array(std::vector<NJS::VAR> vec);
		// Properties
		count_t counter = 0;
		vector_t value = {};
		object_t object = {};
		// Methods
		~Array();
		void Delete() noexcept;
		// Native cast
		explicit Array::operator bool() const noexcept { return true; }
		explicit Array::operator double() const noexcept
		{
			if (value.size() < 2)
			{
				return (double)value[0];
			}
			else
			{
				return std::numeric_limits<double>::quiet_NaN();
			}
		}
		explicit Array::operator int() const noexcept
		{
			if (value.size() < 2)
			{
				return (int)value[0];
			}
			else
			{
				return std::numeric_limits<int>::quiet_NaN();
			}
		}
		explicit Array::operator long long() const noexcept
		{
			if (value.size() < 2)
			{
				return (long long)value[0];
			}
			else
			{
				return std::numeric_limits<long long>::quiet_NaN();
			}
		}
		explicit Array::operator std::string() const noexcept
		{
			auto l = value.size();
			if (l == 0)
				return "";
			std::stringstream stream;
			stream << (std::string)value[0];
			for (auto i = 1; i < l; i++)
			{
				stream << "," << (std::string)value[i];
			}
			return stream.str();
		}
		// Main operators
		NJS::VAR const &operator[](NJS::VAR key) const;
		NJS::VAR &operator[](NJS::VAR key);
		template <class... Args> NJS::VAR operator()(Args... args) const;
		// Comparation operators
		Array operator!() const;
		bool operator==(const Array &_v1) const;
		// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
		// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
		bool operator!=(const Array &_v1) const;
		bool operator<(const Array &_v1) const;
		bool operator<=(const Array &_v1) const;
		bool operator>(const Array &_v1) const;
		bool operator>=(const Array &_v1) const;
		// Numeric operators
		Array operator+() const;
		Array operator-() const;
		Array operator++(const int _v1);
		Array operator--(const int _v1);
		Array operator+(const Array &_v1) const;
		Array operator+=(const Array &_v1);
		Array operator-(const Array &_v1) const;
		Array operator-=(const Array &_v1);
		Array operator*(const Array &_v1) const;
		Array operator*=(const Array &_v1);
		// TODO: "**" and "**=" operators
		Array operator/(const Array &_v1) const;
		Array operator/=(const Array &_v1);
		Array operator%(const Array &_v1) const;
		Array operator%=(const Array &_v1);
		Array operator&(const Array &_v1) const;
		Array operator|(const Array &_v1) const;
		Array operator^(const Array &_v1) const;
		Array operator~() const;
		Array operator>>(const Array &_v1) const;
		Array operator<<(const Array &_v1) const;
		Array operator&=(const Array &_v1);
		Array operator|=(const Array &_v1);
		Array operator^=(const Array &_v1);
		Array operator>>=(const Array &_v1);
		Array operator<<=(const Array &_v1);
		// TODO: ">>>" and ">>>=" operators
	};
} // namespace NJS::Class
