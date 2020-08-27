#pragma once
#include "_meta.h"

namespace NJS::Class
{
	class String
	{
	public:
		// Constants
		const char *name = "string";
		const NJS::Enum::Type type = NJS::Enum::Type::STRING;
		// Constructors
		String();
		String(std::string val);
		String(const char* val);
		// Properties
		count_t counter = 0;
		std::string value = "";
		object_t object = {};
		// Methods
		~String();
		void Delete() noexcept;
		// Native cast
		explicit String::operator bool() const noexcept { return value.size() > 0; }
		explicit String::operator double() const noexcept
		{
			std::string::size_type end;
			auto res = std::stod(value, &end);
			return end == value.size() ? res : std::numeric_limits<double>::quiet_NaN();
		}
		explicit String::operator int() const noexcept
		{
			std::string::size_type end;
			auto res = std::stoi(value, &end, 10);
			return end == value.size() ? res : std::numeric_limits<int>::quiet_NaN();
		}
		explicit String::operator long long() const noexcept
		{
			std::string::size_type end;
			auto res = std::stoll(value, &end, 10);
			return end == value.size() ? res : std::numeric_limits<long long>::quiet_NaN();
		}
		explicit String::operator std::string() const noexcept { return value; }
		// Main operators
		NJS::VAR const &operator[](NJS::VAR key) const;
		NJS::VAR &operator[](NJS::VAR key);
		template <class... Args> NJS::VAR operator()(Args... args) const;
		// Comparation operators
		String operator!() const;
		bool operator==(const String &_v1) const;
		// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
		// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
		bool operator!=(const String &_v1) const;
		bool operator<(const String &_v1) const;
		bool operator<=(const String &_v1) const;
		bool operator>(const String &_v1) const;
		bool operator>=(const String &_v1) const;
		// Numeric operators
		String operator+() const;
		String operator-() const;
		String operator++(const int _v1);
		String operator--(const int _v1);
		String operator+(const String &_v1) const;
		String operator+=(const String &_v1);
		String operator-(const String &_v1) const;
		String operator-=(const String &_v1);
		String operator*(const String &_v1) const;
		String operator*=(const String &_v1);
		// TODO: "**" and "**=" operators
		String operator/(const String &_v1) const;
		String operator/=(const String &_v1);
		String operator%(const String &_v1) const;
		String operator%=(const String &_v1);
		String operator&(const String &_v1) const;
		String operator|(const String &_v1) const;
		String operator^(const String &_v1) const;
		String operator~() const;
		String operator>>(const String &_v1) const;
		String operator<<(const String &_v1) const;
		String operator&=(const String &_v1);
		String operator|=(const String &_v1);
		String operator^=(const String &_v1);
		String operator>>=(const String &_v1);
		String operator<<=(const String &_v1);
		// TODO: ">>>" and ">>>=" operators
	};
} // namespace NJS::Class
