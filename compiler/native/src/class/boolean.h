#include "boolean_header.h"

namespace NJS::Class
{
	// Constructors
	Boolean::Boolean() { }
	Boolean::Boolean(bool val)
	{
		value = val;
	}
	// Methods
	inline void Boolean::Delete() noexcept
	{
		if(--counter == 0)
		{
			delete this;
		}
	}
	inline void* Boolean::Copy() noexcept
	{
		return new Boolean();
	}
	// Native cast
	Boolean::operator bool() const noexcept { return value; }
	Boolean::operator double() const noexcept { return value; }
	Boolean::operator int() const noexcept { return value; }
	Boolean::operator long long() const noexcept { return value; }
	Boolean::operator std::string() const noexcept
	{
		return value ? "true" : "false";
	}
	// Main operators
	#ifdef __NJS__OBJECT_HASHMAP
	NJS::VAR &Boolean::operator[](NJS::VAR key)
	{
		NJS::VAR& _obj = object[(std::string)key];
		if(_obj) return object[_obj]; 

		__NJS_Method_Lazy_Loader("toString", toString);
		__NJS_Method_Lazy_Loader("valueOf", valueOf);

		return object[(std::string)key];
	}
	#else
	NJS::VAR &Boolean::operator[](NJS::VAR key)
	{
		for (auto & search : object)
		{
			if (((std::string)key).compare(search.first) == 0)
			{
				return search.second;
			}
		}

		__NJS_Method_Lazy_Loader("toString", toString);
		__NJS_Method_Lazy_Loader("valueOf", valueOf);

		return object.back().second;
	}
	#endif
	
	template <class... Args>
	NJS::VAR Boolean::operator()(Args... args) const 
	{ 
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException(); 
		#endif
	}
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
	Boolean Boolean::operator+() const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Boolean Boolean::operator-() const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Boolean Boolean::operator++(const int _v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Boolean Boolean::operator--(const int _v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Boolean Boolean::operator+(const Boolean &_v1) const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Boolean Boolean::operator+=(const Boolean &_v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Boolean Boolean::operator-(const Boolean &_v1) const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Boolean Boolean::operator-=(const Boolean &_v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Boolean Boolean::operator*(const Boolean &_v1) const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Boolean Boolean::operator*=(const Boolean &_v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	// TODO: "**" and "**=" operators
	Boolean Boolean::operator/(const Boolean &_v1) const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Boolean Boolean::operator/=(const Boolean &_v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Boolean Boolean::operator%(const Boolean &_v1) const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Boolean Boolean::operator%=(const Boolean &_v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Boolean Boolean::operator&(const Boolean &_v1) const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Boolean Boolean::operator|(const Boolean &_v1) const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Boolean Boolean::operator^(const Boolean &_v1) const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Boolean Boolean::operator~() const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Boolean Boolean::operator>>(const Boolean &_v1) const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Boolean Boolean::operator<<(const Boolean &_v1) const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Boolean Boolean::operator&=(const Boolean &_v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Boolean Boolean::operator|=(const Boolean &_v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Boolean Boolean::operator^=(const Boolean &_v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Boolean Boolean::operator>>=(const Boolean &_v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Boolean Boolean::operator<<=(const Boolean &_v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	// TODO: ">>>" and ">>>=" operators
	NJS::VAR Boolean::toString(NJS::VAR* _args, int _length) const
	{
		return (std::string)*this;
	}
	
	NJS::VAR Boolean::valueOf(NJS::VAR* _args, int _length) const
	{
		return value;
	}
} // namespace NJS::Class
