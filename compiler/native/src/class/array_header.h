#pragma once
#include "_meta.h"

namespace NJS::Class
{
	class Array : public virtual Base
	{
	public:
		// Constructors
		Array();
		Array(NJS::Type::vector_t vec);
		// Properties
		count_t counter = 0;
		NJS::VAR length;
		NJS::Type::vector_t value;
		NJS::Type::object_t object;
		// Methods
		inline void Delete() noexcept;
		inline void* Copy() noexcept;
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
		
		NJS::VAR __iterator(NJS::VAR* args, int _length) const;
		NJS::VAR __unscopables(NJS::VAR* args, int _length) const;
		NJS::VAR concat(NJS::VAR* args, int _length) const;
		NJS::VAR copyWithin(NJS::VAR* args, int _length);
		NJS::VAR entries(NJS::VAR* args, int _length) const;
		NJS::VAR every(NJS::VAR* args, int _length) const;
		NJS::VAR fill(NJS::VAR* args, int _length) const;
		NJS::VAR filter(NJS::VAR* args, int _length) const;
		NJS::VAR find(NJS::VAR* args, int _length) const;
		NJS::VAR findIndex(NJS::VAR* args, int _length) const;
		NJS::VAR flat(NJS::VAR* args, int _length) const;
		NJS::VAR flatMap(NJS::VAR* args, int _length) const;
		NJS::VAR forEach(NJS::VAR* args, int _length) const;
		NJS::VAR includes(NJS::VAR* args, int _length) const;
		NJS::VAR indexOf(NJS::VAR* args, int _length) const;
		NJS::VAR join(NJS::VAR* args, int _length) const;
		NJS::VAR keys(NJS::VAR* args, int _length) const;
		NJS::VAR lastIndexOf(NJS::VAR* args, int _length) const;
		NJS::VAR map(NJS::VAR* args, int _length) const;
		NJS::VAR pop(NJS::VAR* args, int _length);
		NJS::VAR push(NJS::VAR* args, int _length);
		NJS::VAR reduce(NJS::VAR* args, int _length) const;
		NJS::VAR reduceRight(NJS::VAR* args, int _length) const;
		NJS::VAR reverse(NJS::VAR* args, int _length);
		NJS::VAR shift(NJS::VAR* args, int _length);
		NJS::VAR slice(NJS::VAR* args, int _length) const;
		NJS::VAR some(NJS::VAR* args, int _length) const;
		NJS::VAR sort(NJS::VAR* args, int _length) const;
		NJS::VAR splice(NJS::VAR* args, int _length);
		NJS::VAR toLocaleString(NJS::VAR* args, int _length) const;
		NJS::VAR toString(NJS::VAR* args, int _length) const;
		NJS::VAR unshift(NJS::VAR* args, int _length);
		NJS::VAR values(NJS::VAR* args, int _length) const;
	};
} // namespace NJS::Class
