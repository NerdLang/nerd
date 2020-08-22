#pragma once
#include "../var.h"
#include "object.h"

namespace NJS::Class
{
	class Array : Object
	{
	public:
		const char *name = "array";
		const unsigned int type = NJS::Enum::Type::ARRAY;
		Array();
		std::vector<NJS::VAR> __NJS_VALUE = std::vector<NJS::VAR>();
		explicit operator double() const;
		explicit operator int() const;
		explicit operator std::string() const;
		explicit operator long long() const;
		NJS::VAR const &operator[](NJS::VAR _index) const;
		NJS::VAR &operator[](NJS::VAR _index);
		NJS::VAR __iterator() const;
		NJS::VAR __unscopables() const;
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
		NJS::VAR keys() const;
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
		NJS::VAR toLocaleString() const;
		NJS::VAR toString() const;
		NJS::VAR unshift(std::vector<NJS::VAR> values);
		NJS::VAR values() const;
	};
} // namespace NJS::Class
