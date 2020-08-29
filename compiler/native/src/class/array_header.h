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
		vector_t value;
		object_t object;
		// Methods
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
		Array operator!() const;
		
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
		
		NJS::VAR __iterator(std::vector<NJS::VAR> args) const;
		NJS::VAR __unscopables(std::vector<NJS::VAR> args) const;
		NJS::VAR concat(std::vector<NJS::VAR> args) const;
		NJS::VAR copyWithin(std::vector<NJS::VAR> args);
		NJS::VAR entries(std::vector<NJS::VAR> args) const;
		NJS::VAR every(std::vector<NJS::VAR> args) const;
		NJS::VAR fill(std::vector<NJS::VAR> args) const;
		NJS::VAR filter(std::vector<NJS::VAR> args) const;
		NJS::VAR find(std::vector<NJS::VAR> args) const;
		NJS::VAR findIndex(std::vector<NJS::VAR> args) const;
		NJS::VAR flat(std::vector<NJS::VAR> args) const;
		NJS::VAR flatMap(std::vector<NJS::VAR> args) const;
		NJS::VAR forEach(std::vector<NJS::VAR> args) const;
		NJS::VAR includes(std::vector<NJS::VAR> args) const;
		NJS::VAR indexOf(std::vector<NJS::VAR> args) const;
		NJS::VAR join(std::vector<NJS::VAR> args) const;
		NJS::VAR keys(std::vector<NJS::VAR> args) const;
		NJS::VAR lastIndexOf(std::vector<NJS::VAR> args) const;
		NJS::VAR map(std::vector<NJS::VAR> args) const;
		NJS::VAR pop(std::vector<NJS::VAR> args);
		NJS::VAR push(std::vector<NJS::VAR> args);
		NJS::VAR reduce(std::vector<NJS::VAR> args) const;
		NJS::VAR reduceRight(std::vector<NJS::VAR> args) const;
		NJS::VAR reverse(std::vector<NJS::VAR> args);
		NJS::VAR shift(std::vector<NJS::VAR> args);
		NJS::VAR slice(std::vector<NJS::VAR> args) const;
		NJS::VAR some(std::vector<NJS::VAR> args) const;
		NJS::VAR sort(std::vector<NJS::VAR> args) const;
		NJS::VAR splice(std::vector<NJS::VAR> args);
		NJS::VAR toLocaleString(std::vector<NJS::VAR> args) const;
		NJS::VAR toString(std::vector<NJS::VAR> args) const;
		NJS::VAR unshift(std::vector<NJS::VAR> values);
		NJS::VAR values(std::vector<NJS::VAR> args) const;
	};
} // namespace NJS::Class
