#pragma once
#include "_meta.h"

namespace NJS::Class
{
	class Function
	{
	public:
		// Constants
		const char *name = "function";
		const NJS::Enum::Type type = NJS::Enum::Type::FUNCTION;
		std::string code = "[native code]";
		// Constructors
		Function();
		Function(void* val);
		// Properties
		count_t counter = 0;
		void* value = nullptr;
		object_t object = {};
		// Methods
		~Function();
		void Delete() noexcept;
		// Native cast
		explicit Function::operator bool() const noexcept { return true; }
		explicit Function::operator double() const noexcept
		{
			return std::numeric_limits<double>::quiet_NaN();
		}
		explicit Function::operator int() const noexcept
		{
			return std::numeric_limits<int>::quiet_NaN();
		}
		explicit Function::operator long long() const noexcept
		{
			return std::numeric_limits<long long>::quiet_NaN();
		}
		explicit Function::operator std::string() const noexcept
		{
			return "[native code]";
		}
		// Main operators
		NJS::VAR const &operator[](NJS::VAR key) const;
		NJS::VAR &operator[](NJS::VAR key);
		template <class... Args> NJS::VAR operator()(Args... args) const;
		// Comparation operators
		Function operator!() const;
		bool operator==(const Function &_v1) const;
		// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
		// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
		bool operator!=(const Function &_v1) const;
		bool operator<(const Function &_v1) const;
		bool operator<=(const Function &_v1) const;
		bool operator>(const Function &_v1) const;
		bool operator>=(const Function &_v1) const;
		// Numeric operators
		Function operator+() const;
		Function operator-() const;
		Function operator++(const int _v1);
		Function operator--(const int _v1);
		Function operator+(const Function &_v1) const;
		Function operator+=(const Function &_v1);
		Function operator-(const Function &_v1) const;
		Function operator-=(const Function &_v1);
		Function operator*(const Function &_v1) const;
		Function operator*=(const Function &_v1);
		// TODO: "**" and "**=" operators
		Function operator/(const Function &_v1) const;
		Function operator/=(const Function &_v1);
		Function operator%(const Function &_v1) const;
		Function operator%=(const Function &_v1);
		Function operator&(const Function &_v1) const;
		Function operator|(const Function &_v1) const;
		Function operator^(const Function &_v1) const;
		Function operator~() const;
		Function operator>>(const Function &_v1) const;
		Function operator<<(const Function &_v1) const;
		Function operator&=(const Function &_v1);
		Function operator|=(const Function &_v1);
		Function operator^=(const Function &_v1);
		Function operator>>=(const Function &_v1);
		Function operator<<=(const Function &_v1);
		// TODO: ">>>" and ">>>=" operators
	};
} // namespace NJS::Class
