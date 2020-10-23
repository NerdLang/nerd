#pragma once
#include "number_header.h"

namespace NJS::Class
{
	// Private methods
	inline int Number::getInt() const noexcept
	{
		if(isInt) return value.i;
		return value.d;
	}
	inline void Number::setInt(int v) noexcept
	{
		isInt = true;
		value.i = v;
	}
	inline double Number::getDouble() const noexcept
	{
		if(isInt) return value.i;
		return value.d;
	}
	inline void Number::setDouble(double v) noexcept
	{
		isInt = false;
		value.d = v;
	}
	inline bool Number::isNaN() const noexcept
	{
		return !isInt && std::isnan(getDouble());
	}
	inline bool Number::isFinite() const noexcept
	{
		return isInt || std::isfinite(getDouble());
	}
	inline bool Number::isNegative() const noexcept
	{
		return std::signbit(getDouble());
	}

	// Constructors
	Number::Number() { setInt(0); }
	Number::Number(int val)
	{
		isInt = true;
		setInt(val);
	}

	Number::Number(double val)
	{
		double dummy;
		if (modf(val, &dummy) == 0.0 && val < SMI_MAX && val > SMI_MIN)
		{
			isInt = true;
			setInt(val);
		}
		else
		{
			isInt = false;
			setDouble(val);
		}
	}
	Number::Number(long long val)
	{
		isInt = false;
		setDouble(val);
	}
	
	Number::Number(const Number* val)
	{
		value = val->value;
		isInt = val->isInt;
	}

	Number::Number(const NJS::VAR& val)
	{
		isInt = ((NJS::Class::Number*)val._ptr)->isInt;
		switch(val.type)
		{
			case NJS::Enum::Type::Number:
				value = ((NJS::Class::Number*)val._ptr)->value;
			break;
			default:
				value.i = (int)val;
			break;
		}
	}
	// Methods
	inline void Number::Delete() noexcept
	{
		if(--counter == 0)
		{
			delete this;
		}
	}
	inline void* Number::Copy() noexcept
	{
		return new Number(this);
	}
	// Native cast
	Number::operator bool() const noexcept { return getInt(); }
	Number::operator double() const noexcept { return getDouble(); }
	Number::operator int() const noexcept { return getInt(); }
	Number::operator long long() const noexcept
	{
		if (isFinite())
		{
			if(isInt) return getInt();
			else return getDouble();
		}
		if (isNaN())
		{
			return std::numeric_limits<long long>::quiet_NaN();
		}
		return std::numeric_limits<long long>::infinity() * (isNegative() ? -1 : 1);
	}
	Number::operator std::string() const noexcept
	{
		if (isFinite())
		{
			if(isInt)
			{
				return std::to_string(value.i);
			}
			else 
			{
				std::ostringstream strout ;
				strout << std::fixed << std::setprecision(14) << value.d ;
				std::string str = strout.str() ;
				
				size_t end = str.find_last_not_of( '0' ) + 1 ;
				str = str.erase( end ) ;
				
				end = str.find_last_not_of( '.' ) + 1 ;
				str = str.erase( end ) ;
				
				int exp = str.length();
				if(exp > 20)
				{
					std::string first = str.substr(0, 1);
					std::string second = str.substr(1, 15);
					str = first + "." + second + "e+" + std::to_string(exp-1);
				}
				return str;
			}
		}
		if (isNaN())
		{
			return "NaN";
		}
		return isNegative() ? "-Infinity" : "Infinity";
	}
	// Main operators
	NJS::VAR const Number::operator[](NJS::VAR key) const
	{
		return undefined;
	}
	NJS::VAR &Number::operator[](NJS::VAR key)
	{		
		#ifdef __NJS__OBJECT_HASHMAP
		
		NJS::VAR& _obj = object[(std::string)key];
		if(_obj) return object[_obj];
		
		#else
			
		for (auto & search : object)
		{
			if (((std::string)key).compare(search.first) == 0)
			{
				return search.second;
			}
		}
		
		#endif
		
		__NJS_Method_Lazy_Loader("toString", toString);
		__NJS_Method_Lazy_Loader("valueOf", valueOf);
		__NJS_Method_Lazy_Loader("toFixed", toFixed);

		return undefined;
	}
	template <class... Args>
	NJS::VAR Number::operator()(Args... args) const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return undefined;
	}
	// Comparation operators
	Number Number::operator!() const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Number();
	}
	bool Number::operator==(const Number &_v1) const
	{
		if (isInt && _v1.isInt)
		{
			return value.i == _v1.value.i;
		}
		else
		{
			return (double)*this == (double)_v1;
		}
	}
	// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
	// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
	bool Number::operator!=(const Number &_v1) const
	{
		if (isInt && _v1.isInt)
		{
			return value.i != _v1.value.i;
		}
		else
		{
			return (double)*this != (double)_v1;
		}
	}
	bool Number::operator<(const Number &_v1) const
	{
		if (isInt && _v1.isInt)
		{
			return value.i < _v1.value.i;
		}
		else
		{
			return (double)*this < (double)_v1;
		}
	}
	bool Number::operator<=(const Number &_v1) const
	{
		if (isInt && _v1.isInt)
		{
			return value.i <= _v1.value.i;
		}
		else
		{
			return (double)*this <= (double)_v1;
		}
	}
	bool Number::operator>(const Number &_v1) const
	{
		if (isInt && _v1.isInt)
		{
			return value.i > _v1.value.i;
		}
		else
		{
			return (double)*this > (double)_v1;
		}
	}
	bool Number::operator>=(const Number &_v1) const
	{
		if (isInt && _v1.isInt)
		{
			return value.i >= _v1.value.i;
		}
		else
		{
			return (double)*this >= (double)_v1;
		}
	}
	// Numeric operators
	Number Number::operator+() const 
	{
		#if !defined(__NJS_ENV_ARDUINO) && !defined(__NJS_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Number();
	}
	Number Number::operator-() const 
	{ 
		if(isInt)
		{
			return -getInt(); 
		}
		else
		{
			return (double)-getDouble();
		}
	}
	Number Number::operator++(const int _v1)
	{
		Number old(*this);
		if (isInt)
		{
			int v = getInt();
			setInt(++v);
		}
		else
		{
			double v = getDouble();
			setDouble(++v);
		}
		return old;
	}
	void Number::operator++()
	{
		if (isInt)
		{
			int v = getInt();
			setInt(++v);
		}
		else
		{
			double v = getDouble();
			setDouble(++v);
		}
	}
	Number Number::operator--(const int _v1)
	{
		Number old(*this);
		if (isInt)
		{
			int v = getInt();
			setInt(--v);
		}
		else
		{
			double v = getDouble();
			setDouble(--v);
		}
		return old;
	}
	void Number::operator--()
	{
		if (isInt)
		{
			int v = getInt();
			setInt(--v);
		}
		else
		{
			double v = getDouble();
			setDouble(--v);
		}
	}
	Number Number::operator+(const Number &_v1) const
	{
		if (isInt && _v1.isInt)
		{
			int a = (int)*this;
			int b = (int)_v1;
			int c;
			if (!__builtin_add_overflow(a, b, &c))
			{
				return c;
			}
		}
		
		return ((double)*this) + (double)_v1;
	}
	void Number::operator+=(const Number &_v1)
	{
		if (isInt && _v1.isInt)
		{
			int a = value.i;
			int b = _v1.value.i;
			int c;
			if (!__builtin_add_overflow(a, b, &c))
			{
				setInt(c);
				return;
			}
		}
		setDouble((double)*this + (double)_v1);
	}
	Number Number::operator-(const Number &_v1) const
	{
		if (isInt && _v1.isInt)
		{
			int a = (int)*this;
			int b = (int)_v1;
			int c;
			if (!__builtin_sub_overflow(a, b, &c))
			{
				return c;
			}
		}
		return (double)*this - (double)_v1;
	}
	Number Number::operator-=(const Number &_v1)
	{
		if (isInt && _v1.isInt)
		{
			int a = (int)*this;
			int b = (int)_v1;
			int c;
			if (!__builtin_sub_overflow(a, b, &c))
			{
				setInt(c);
				return *this;
			}
		}
		setDouble((double)*this - (double)_v1);
		return *this;
	}
	Number Number::operator*(const Number &_v1) const
	{
		if (isInt && _v1.isInt)
		{
			int a = (int)*this;
			int b = (int)_v1;
			int c;
			if (!__builtin_mul_overflow(a, b, &c))
			{
				return c;
			}
		}
		return ((double)*this) * (double)_v1;
	}
	void Number::operator*=(const Number &_v1)
	{
		if (isInt && _v1.isInt)
		{
			int a = (int)*this;
			int b = (int)_v1;
			int c;
			if (!__builtin_mul_overflow(a, b, &c))
			{
				setInt(c);
				return;
			}
		}
		setDouble(((double)*this) * (double)_v1);
	}
	// TODO: "**" and "**=" operators
	Number Number::operator/(const Number &_v1) const
	{
		if (isInt && _v1.isInt)
		{
			int a = (int)*this;
			int b = (int)_v1;
			if (a % b == 0)
			{
				return a / b;
			}
		}
		return ((double)*this) / (double)_v1;
	}
	void Number::operator/=(const Number &_v1)
	{
		if (isInt && _v1.isInt)
		{
			int a = (int)*this;
			int b = (int)_v1;
			if (a % b == 0)
			{
				setInt(a / b);
				return;
			}
		}
		setDouble( ((double)*this) / (double)_v1);
	}
	Number Number::operator%(const Number &_v1) const
	{
		if (isInt && _v1.isInt)
		{
			return (int)*this % (int)_v1;
		}
		else
		{
			return std::fmod((double)*this, (double)_v1);
		}
	}
	Number Number::operator%=(const Number &_v1)
	{
		if (isInt && _v1.isInt)
		{
			setInt((int)*this % (int)_v1);
		}
		else
		{
			setDouble(std::fmod((double)*this, (double)_v1));
		}
		return *this;
	}
	Number Number::operator&(const Number &_v1) const { return (int)*this & (int)_v1; }
	Number Number::operator|(const Number &_v1) const { return (int)*this | (int)_v1; }
	Number Number::operator^(const Number &_v1) const { return (int)*this ^ (int)_v1; }
	Number Number::operator~() const { return ~(int)*this; }
	Number Number::operator>>(const Number &_v1) const { return (int)*this >> (int)_v1; }
	Number Number::operator<<(const Number &_v1) const { return (int)*this << (int)_v1; }
	Number Number::operator&=(const Number &_v1)
	{
		setInt((int)*this & (int)_v1);
		return *this;
	}
	Number Number::operator|=(const Number &_v1)
	{
		setInt( ((int)*this) | (int)_v1);
		return *this;
	}
	Number Number::operator^=(const Number &_v1)
	{
		setInt( ((int)*this) ^ (int)_v1);
		return *this;
	}
	Number Number::operator>>=(const Number &_v1)
	{
		setInt( ((int)*this) >> (int)_v1);
		return *this;
	}
	Number Number::operator<<=(const Number &_v1)
	{
		setInt( ((int)*this) << (int)_v1);
		return *this;
	}
	// TODO: ">>>" and ">>>=" operators
	
	NJS::VAR Number::toString(NJS::VAR* _args, int _length) const
	{
		return (std::string)*this;
	}
	
	NJS::VAR Number::valueOf(NJS::VAR* _args, int _length) const
	{
		return value.d;
	}
	
	NJS::VAR Number::toFixed(NJS::VAR* _args, int _length) const
	{
		int precision;
		if(_length > 0)
		{
			precision = _args[0];
		}
		else precision = 0;
		std::ostringstream strout ;
		strout << std::fixed << std::setprecision(precision) << (double)*this ;
		std::string str = strout.str() ;
		return str;
	}
	
} // namespace NJS::Class