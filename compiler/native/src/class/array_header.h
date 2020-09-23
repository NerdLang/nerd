#pragma once
#include "_meta.h"

namespace NJS::Class
{
	class Array : public virtual Base
	{
	public:
		// Constants
		const char *name = "array";
		const NJS::Enum::Type type = NJS::Enum::Type::Array;
		// Constructors
		Array();
		Array(NJS::Type::vector_t vec);
		// Properties
		count_t counter = 0;
		NJS::Type::vector_t value;
		NJS::Type::object_t object;
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
		
		NJS::VAR __iterator(NJS::Type::vector_t args) const;
		NJS::VAR __unscopables(NJS::Type::vector_t args) const;
		NJS::VAR concat(NJS::Type::vector_t args) const;
		NJS::VAR copyWithin(NJS::Type::vector_t args);
		NJS::VAR entries(NJS::Type::vector_t args) const;
		NJS::VAR every(NJS::Type::vector_t args) const;
		NJS::VAR fill(NJS::Type::vector_t args) const;
		NJS::VAR filter(NJS::Type::vector_t args) const;
		NJS::VAR find(NJS::Type::vector_t args) const;
		NJS::VAR findIndex(NJS::Type::vector_t args) const;
		NJS::VAR flat(NJS::Type::vector_t args) const;
		NJS::VAR flatMap(NJS::Type::vector_t args) const;
		NJS::VAR forEach(NJS::Type::vector_t args) const;
		NJS::VAR includes(NJS::Type::vector_t args) const;
		NJS::VAR indexOf(NJS::Type::vector_t args) const;
		NJS::VAR join(NJS::Type::vector_t args) const;
		NJS::VAR keys(NJS::Type::vector_t args) const;
		NJS::VAR lastIndexOf(NJS::Type::vector_t args) const;
		NJS::VAR map(NJS::Type::vector_t args) const;
		NJS::VAR pop(NJS::Type::vector_t args);
		NJS::VAR push(NJS::Type::vector_t args);
		NJS::VAR reduce(NJS::Type::vector_t args) const;
		NJS::VAR reduceRight(NJS::Type::vector_t args) const;
		NJS::VAR reverse(NJS::Type::vector_t args);
		NJS::VAR shift(NJS::Type::vector_t args);
		NJS::VAR slice(NJS::Type::vector_t args) const;
		NJS::VAR some(NJS::Type::vector_t args) const;
		NJS::VAR sort(NJS::Type::vector_t args) const;
		NJS::VAR splice(NJS::Type::vector_t args);
		NJS::VAR toLocaleString(NJS::Type::vector_t args) const;
		NJS::VAR toString(NJS::Type::vector_t args) const;
		NJS::VAR unshift(NJS::Type::vector_t values);
		NJS::VAR values(NJS::Type::vector_t args) const;
	};
} // namespace NJS::Class
