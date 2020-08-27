#include "boolean_header.h"

namespace NJS::Class
{
	// Constructors
	Boolean::Boolean() { ++counter; }
	Boolean::Boolean(bool val)
	{
		Boolean();
		value = val;
	}
	// Methods
	Boolean::~Boolean()
	{
		object.~vector();
	}
	void Boolean::Delete()
	{
		if (--counter == 0)
		{
			delete this;
		}
	}
	// Main operators
	NJS::VAR const &Boolean::operator[](NJS::VAR key) const
	{
		auto &obj = this->object;
		auto index = (std::string)key;
		for (auto pair : obj)
		{
			if (index.compare(pair.first) == 0)
			{
				return pair.second;
			}
		}
		return NJS::VAR();
	}
	NJS::VAR &Boolean::operator[](NJS::VAR key)
	{
		auto &obj = this->object;
		auto index = (std::string)key;
		for (auto pair : obj)
		{
			if (index.compare(pair.first) == 0)
			{
				return pair.second;
			}
		}
		auto value = NJS::VAR();
		obj.push_back(std::pair<const char *, NJS::VAR>(index.c_str(), value));
		return value;
	}
	template <class... Args>
	NJS::VAR Boolean::operator()(Args... args) const { throw InvalidTypeException(); }
	// Comparation operators
	Boolean Boolean::operator!() const { return !value; }
	bool Boolean::operator==(const Boolean &_v1) const { return value == _v1.value; }
	// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
	// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
	bool Boolean::operator!=(const Boolean &_v1) const { return value != _v1.value; }
	bool Boolean::operator<(const Boolean &_v1) const { return value < _v1.value; }
	bool Boolean::operator<=(const Boolean &_v1) const { return value <= _v1.value; }
	bool Boolean::operator>(const Boolean &_v1) const { return value > _v1.value; }
	bool Boolean::operator>=(const Boolean &_v1) const { return value >= _v1.value; }
	// Numeric operators
	Boolean Boolean::operator+() const { throw InvalidTypeException(); }
	Boolean Boolean::operator-() const { throw InvalidTypeException(); }
	Boolean Boolean::operator++(const int _v1) { throw InvalidTypeException(); }
	Boolean Boolean::operator--(const int _v1) { throw InvalidTypeException(); }
	Boolean Boolean::operator+(const Boolean &_v1) const { throw InvalidTypeException(); }
	Boolean Boolean::operator+=(const Boolean &_v1) { throw InvalidTypeException(); }
	Boolean Boolean::operator-(const Boolean &_v1) const { throw InvalidTypeException(); }
	Boolean Boolean::operator-=(const Boolean &_v1) { throw InvalidTypeException(); }
	Boolean Boolean::operator*(const Boolean &_v1) const { throw InvalidTypeException(); }
	Boolean Boolean::operator*=(const Boolean &_v1) { throw InvalidTypeException(); }
	// TODO: "**" and "**=" operators
	Boolean Boolean::operator/(const Boolean &_v1) const { throw InvalidTypeException(); }
	Boolean Boolean::operator/=(const Boolean &_v1) { throw InvalidTypeException(); }
	Boolean Boolean::operator%(const Boolean &_v1) const { throw InvalidTypeException(); }
	Boolean Boolean::operator%=(const Boolean &_v1) { throw InvalidTypeException(); }
	Boolean Boolean::operator&(const Boolean &_v1) const { throw InvalidTypeException(); }
	Boolean Boolean::operator|(const Boolean &_v1) const { throw InvalidTypeException(); }
	Boolean Boolean::operator^(const Boolean &_v1) const { throw InvalidTypeException(); }
	Boolean Boolean::operator~() const { throw InvalidTypeException(); }
	Boolean Boolean::operator>>(const Boolean &_v1) const { throw InvalidTypeException(); }
	Boolean Boolean::operator<<(const Boolean &_v1) const { throw InvalidTypeException(); }
	Boolean Boolean::operator&=(const Boolean &_v1) { throw InvalidTypeException(); }
	Boolean Boolean::operator|=(const Boolean &_v1) { throw InvalidTypeException(); }
	Boolean Boolean::operator^=(const Boolean &_v1) { throw InvalidTypeException(); }
	Boolean Boolean::operator>>=(const Boolean &_v1) { throw InvalidTypeException(); }
	Boolean Boolean::operator<<=(const Boolean &_v1) { throw InvalidTypeException(); }
	// TODO: ">>>" and ">>>=" operators
} // namespace NJS::Class
