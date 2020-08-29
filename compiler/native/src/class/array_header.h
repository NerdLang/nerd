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
		Array(vector_t vec);
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
		
		NJS::VAR __iterator(vector_t args) const;
		NJS::VAR __unscopables(vector_t args) const;
		NJS::VAR concat(vector_t args) const;
		NJS::VAR copyWithin(vector_t args);
		NJS::VAR entries(vector_t args) const;
		NJS::VAR every(vector_t args) const;
		NJS::VAR fill(vector_t args) const;
		NJS::VAR filter(vector_t args) const;
		NJS::VAR find(vector_t args) const;
		NJS::VAR findIndex(vector_t args) const;
		NJS::VAR flat(vector_t args) const;
		NJS::VAR flatMap(vector_t args) const;
		NJS::VAR forEach(vector_t args) const;
		NJS::VAR includes(vector_t args) const;
		NJS::VAR indexOf(vector_t args) const;
		NJS::VAR join(vector_t args) const;
		NJS::VAR keys(vector_t args) const;
		NJS::VAR lastIndexOf(vector_t args) const;
		NJS::VAR map(vector_t args) const;
		NJS::VAR pop(vector_t args);
		NJS::VAR push(vector_t args);
		NJS::VAR reduce(vector_t args) const;
		NJS::VAR reduceRight(vector_t args) const;
		NJS::VAR reverse(vector_t args);
		NJS::VAR shift(vector_t args);
		NJS::VAR slice(vector_t args) const;
		NJS::VAR some(vector_t args) const;
		NJS::VAR sort(vector_t args) const;
		NJS::VAR splice(vector_t args);
		NJS::VAR toLocaleString(vector_t args) const;
		NJS::VAR toString(vector_t args) const;
		NJS::VAR unshift(vector_t values);
		NJS::VAR values(vector_t args) const;
	};
} // namespace NJS::Class
