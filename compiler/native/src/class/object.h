#pragma once
#include "object_header.h"
#include <limits>

namespace NJS::Class
{
	// Constructors
	Object::Object() { ++counter; }
	Object::Object(object_t &val) : value(val) { Object(); }
	// Methods
	Object::~Object()
	{
		object.~vector();
	}
	void Object::Delete() noexcept
	{
		if (--counter == 0)
		{
			delete this;
		}
	}
	// Native cast
	Object::operator bool() const noexcept { return true; }
	Object::operator double() const noexcept
	{
		return std::numeric_limits<double>::quiet_NaN();
	}
	Object::operator int() const noexcept
	{
		return std::numeric_limits<int>::quiet_NaN();
	}
	Object::operator long long() const noexcept
	{
		return std::numeric_limits<long long>::quiet_NaN();
	}
	Object::operator std::string() const noexcept
	{
		return "[object Object]";
	}
	// Main operators
	NJS::VAR const Object::operator[](NJS::VAR key) const
	{
		auto &obj = this->object;
		auto index = (std::string)key;
		int _j = obj.size();
		for (int _i = 0; _i < _j; _i++)
		{
			if (index.compare(obj[_i].first) == 0)
			{
				return obj[_i].second;
			}
		}
		return NJS::VAR();
	}
	NJS::VAR &Object::operator[](NJS::VAR key)
	{
		for (auto & search : object)
		{
			if (key.get().s->value.compare(search.first) == 0)
			{
				return search.second;
			}
		}

		key.get().s->counter++;
		if(key.get().s->value.compare("toString") == 0  || key.get().s->value.compare("toLocaleString") == 0)
		{
			object.push_back(pair_t(key.get().s->value.c_str(), __NJS_Create_Var_Scoped_Anon( counter++; return __NJS_Object_Stringify(this);)));
		}
		else if(key.get().s->value.compare("valueOf") == 0)
		{
			object.push_back(pair_t(key.get().s->value.c_str(), __NJS_Create_Var_Scoped_Anon( counter++; return this; )));
		}
		else 
		{
			object.push_back(pair_t(key.get().s->value.c_str(), __NJS_VAR()));
		}

		return object[object.size() - 1].second;
	}
	template <class... Args>
	NJS::VAR Object::operator()(Args... args) const { throw InvalidTypeException(); }
	// Comparation operators
	Object Object::operator!() const { throw InvalidTypeException(); }
	bool Object::operator==(const Object &_v1) const { return false; }
	// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
	// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
	bool Object::operator!=(const Object &_v1) const { return true; }
	bool Object::operator<(const Object &_v1) const { return false; }
	bool Object::operator<=(const Object &_v1) const { return true; }
	bool Object::operator>(const Object &_v1) const { return false; }
	bool Object::operator>=(const Object &_v1) const { return true; }
	// Numeric operators
	Object Object::operator+() const { throw InvalidTypeException(); }
	Object Object::operator-() const { throw InvalidTypeException(); }
	Object Object::operator++(const int _v1) { throw InvalidTypeException(); }
	Object Object::operator--(const int _v1) { throw InvalidTypeException(); }
	Object Object::operator+(const Object &_v1) const { throw InvalidTypeException(); }
	Object Object::operator+=(const Object &_v1) { throw InvalidTypeException(); }
	Object Object::operator-(const Object &_v1) const { throw InvalidTypeException(); }
	Object Object::operator-=(const Object &_v1) { throw InvalidTypeException(); }
	Object Object::operator*(const Object &_v1) const { throw InvalidTypeException(); }
	Object Object::operator*=(const Object &_v1) { throw InvalidTypeException(); }
	// TODO: "**" and "**=" operators
	Object Object::operator/(const Object &_v1) const { throw InvalidTypeException(); }
	Object Object::operator/=(const Object &_v1) { throw InvalidTypeException(); }
	Object Object::operator%(const Object &_v1) const { throw InvalidTypeException(); }
	Object Object::operator%=(const Object &_v1) { throw InvalidTypeException(); }
	Object Object::operator&(const Object &_v1) const { throw InvalidTypeException(); }
	Object Object::operator|(const Object &_v1) const { throw InvalidTypeException(); }
	Object Object::operator^(const Object &_v1) const { throw InvalidTypeException(); }
	Object Object::operator~() const { throw InvalidTypeException(); }
	Object Object::operator>>(const Object &_v1) const { throw InvalidTypeException(); }
	Object Object::operator<<(const Object &_v1) const { throw InvalidTypeException(); }
	Object Object::operator&=(const Object &_v1) { throw InvalidTypeException(); }
	Object Object::operator|=(const Object &_v1) { throw InvalidTypeException(); }
	Object Object::operator^=(const Object &_v1) { throw InvalidTypeException(); }
	Object Object::operator>>=(const Object &_v1) { throw InvalidTypeException(); }
	Object Object::operator<<=(const Object &_v1) { throw InvalidTypeException(); }
	// TODO: ">>>" and ">>>=" operators
} // namespace NJS::Class
