#pragma once
#include "object_header.h"
#include <limits>

namespace NJS::Class
{
	// Constructors
	Object::Object() { counter++; }
	// Methods
	void Object::Delete() noexcept
	{
		if (--counter < 1)
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
			if (((NJS::Class::String*)key._ptr)->value.compare(search.first) == 0)
			{
				if(!prototype)
				{
					return search.second;
				}
				else 
				{
					if(search.second.type == NJS::Enum::Type::Function)
					{
						((NJS::Class::Function*)search.second._ptr)->This = this;
					}
					return search.second;
				}
			}
		}
		((NJS::Class::String*)key._ptr)->counter++;
		if(((NJS::Class::String*)key._ptr)->value.compare("toString") == 0  || ((NJS::Class::String*)key._ptr)->value.compare("toLocaleString") == 0)
		{
			object.push_back(pair_t(((NJS::Class::String*)key._ptr)->value.c_str(), __NJS_Create_Var_Scoped_Anon( return __NJS_Object_Stringify(this);)));
		}
		else if(((NJS::Class::String*)key._ptr)->value.compare("valueOf") == 0)
		{
			object.push_back(pair_t(((NJS::Class::String*)key._ptr)->value.c_str(), __NJS_Create_Var_Scoped_Anon( return this; )));
		}
		else 
		{
			object.push_back(pair_t(((NJS::Class::String*)key._ptr)->value.c_str(), __NJS_VAR()));
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
