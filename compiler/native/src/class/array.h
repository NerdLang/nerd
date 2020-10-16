#pragma once
#include "array_header.h"
#include <sstream>
#include <limits>
		
namespace NJS::Class
{
	// Constructors
	Array::Array() 
	{ 

	}
	Array::Array(NJS::Type::vector_t vec)
	{
		value = vec;
	}
	// Methods
	inline void Array::Delete() noexcept
	{
		if (--counter == 0)
		{
			delete this;
		}
	}
	inline void* Array::Copy() noexcept
	{
		counter++;
		return this;
	}
	// Native cast
	Array::operator bool() const noexcept { return true; }
	Array::operator double() const noexcept
	{
		if (value.size() < 2)
		{
			return (double)value[0];
		}
		else
		{
			return std::numeric_limits<double>::quiet_NaN();
		}
	}
	Array::operator int() const noexcept
	{
		if (value.size() < 2)
		{
			return (int)value[0];
		}
		else
		{
			return std::numeric_limits<int>::quiet_NaN();
		}
	}
	Array::operator long long() const noexcept
	{
		if (value.size() < 2)
		{
			return (long long)value[0];
		}
		else
		{
			return std::numeric_limits<long long>::quiet_NaN();
		}
	}
	Array::operator std::string() const noexcept
	{
		auto l = value.size();
		if (l == 0)
			return "";
		std::stringstream stream;
		stream << (std::string)value[0];
		for (auto i = 1; i < l; i++)
		{
			stream << "," << (std::string)value[i];
		}
		return stream.str();
	}
	// Main operators
	NJS::VAR const Array::operator[](NJS::VAR key) const
	{
		if (key.type == NJS::Enum::Type::Number)
		{
			auto i = (int)key;
			if (i >= 0 && i <= value.size())
			{
				return value.at(i);
			}
		}
		
		return undefined;
	}
	
	#ifdef __NJS__OBJECT_HASHMAP
	NJS::VAR &Array::operator[](NJS::VAR key)
	{	
		if (key.type == NJS::Enum::Type::Number)
		{
			auto i = (int)key;
			
			if (i < 0)
			{
				return undefined;
			}
			else 
			{
				if (i >= value.size())
				{
					
					value.reserve(i + 1);
					value.resize(i + 1);
				}
			}
			return value[i];
		}
		
		if(((std::string)key).compare("length") == 0)
		{
			length = (int)value.size();
			return length;
		}
		
		NJS::VAR& _obj = object[(std::string)key];
		if(_obj) return _obj; 
		
		__NJS_Method_Lazy_Loader("push", push);
		__NJS_Method_Lazy_Loader("@@iterator", __iterator);
		__NJS_Method_Lazy_Loader("@@unscopables", __unscopables);
		__NJS_Method_Lazy_Loader("concat", concat);
		__NJS_Method_Lazy_Loader("copyWithin", copyWithin);
		__NJS_Method_Lazy_Loader("entries", entries);
		__NJS_Method_Lazy_Loader("every", every);
		__NJS_Method_Lazy_Loader("fill", fill);
		__NJS_Method_Lazy_Loader("filter", filter);
		__NJS_Method_Lazy_Loader("find", find);
		__NJS_Method_Lazy_Loader("findIndex", findIndex);
		__NJS_Method_Lazy_Loader("flat", flat);
		__NJS_Method_Lazy_Loader("flatMap", flatMap);
		__NJS_Method_Lazy_Loader("forEach", forEach);
		__NJS_Method_Lazy_Loader("includes", includes);
		__NJS_Method_Lazy_Loader("indexOf", indexOf);
		__NJS_Method_Lazy_Loader("join", join);
		__NJS_Method_Lazy_Loader("keys", keys);
		__NJS_Method_Lazy_Loader("lastIndexOf", lastIndexOf);
		__NJS_Method_Lazy_Loader("map", map);
		__NJS_Method_Lazy_Loader("pop", pop);
		__NJS_Method_Lazy_Loader("push", push);
		__NJS_Method_Lazy_Loader("reduce", reduce);
		__NJS_Method_Lazy_Loader("reduceRight", reduceRight);
		__NJS_Method_Lazy_Loader("reverse", reverse);
		__NJS_Method_Lazy_Loader("shift", shift);
		__NJS_Method_Lazy_Loader("slice", slice);
		__NJS_Method_Lazy_Loader("some", some);
		__NJS_Method_Lazy_Loader("sort", sort);
		__NJS_Method_Lazy_Loader("splice", splice);
		__NJS_Method_Lazy_Loader("toLocaleString", toLocaleString);
		__NJS_Method_Lazy_Loader("toString", toString);
		__NJS_Method_Lazy_Loader("unshift", unshift);
		__NJS_Method_Lazy_Loader("values", values);
		
		return _obj;
	}
	#else
	NJS::VAR &Array::operator[](NJS::VAR key)
	{
		static NJS::VAR _retUndefined;

		if (key.type == NJS::Enum::Type::Number)
		{
			auto i = (int)key;
			
			if (i < 0)
			{
				return _retUndefined;
			}
			else 
			{
				if (i >= value.size())
				{
					
					value.reserve(i + 1);
					value.resize(i + 1);
				}
			}
			return value[i];
		}
		
		if(((std::string)key).compare("length") == 0)
		{
			length = (int)value.size();
			return length;
		}
		
		for (auto & search : object)
		{
			if (((std::string)key).compare(search.first) == 0)
			{
				return search.second;
			}
		}
		
		__NJS_Method_Lazy_Loader("push", push);
		__NJS_Method_Lazy_Loader("@@iterator", __iterator);
		__NJS_Method_Lazy_Loader("@@unscopables", __unscopables);
		__NJS_Method_Lazy_Loader("concat", concat);
		__NJS_Method_Lazy_Loader("copyWithin", copyWithin);
		__NJS_Method_Lazy_Loader("entries", entries);
		__NJS_Method_Lazy_Loader("every", every);
		__NJS_Method_Lazy_Loader("fill", fill);
		__NJS_Method_Lazy_Loader("filter", filter);
		__NJS_Method_Lazy_Loader("find", find);
		__NJS_Method_Lazy_Loader("findIndex", findIndex);
		__NJS_Method_Lazy_Loader("flat", flat);
		__NJS_Method_Lazy_Loader("flatMap", flatMap);
		__NJS_Method_Lazy_Loader("forEach", forEach);
		__NJS_Method_Lazy_Loader("includes", includes);
		__NJS_Method_Lazy_Loader("indexOf", indexOf);
		__NJS_Method_Lazy_Loader("join", join);
		__NJS_Method_Lazy_Loader("keys", keys);
		__NJS_Method_Lazy_Loader("lastIndexOf", lastIndexOf);
		__NJS_Method_Lazy_Loader("map", map);
		__NJS_Method_Lazy_Loader("pop", pop);
		__NJS_Method_Lazy_Loader("reduce", reduce);
		__NJS_Method_Lazy_Loader("reduceRight", reduceRight);
		__NJS_Method_Lazy_Loader("reverse", reverse);
		__NJS_Method_Lazy_Loader("shift", shift);
		__NJS_Method_Lazy_Loader("slice", slice);
		__NJS_Method_Lazy_Loader("some", some);
		__NJS_Method_Lazy_Loader("sort", sort);
		__NJS_Method_Lazy_Loader("splice", splice);
		__NJS_Method_Lazy_Loader("toLocaleString", toLocaleString);
		__NJS_Method_Lazy_Loader("toString", toString);
		__NJS_Method_Lazy_Loader("unshift", unshift);
		__NJS_Method_Lazy_Loader("values", values);
		

		object.push_back(NJS::Type::pair_t((std::string)key, undefined));
		return object[object.size() - 1].second;
	}
	#endif
	
	template <class... Args>
	NJS::VAR Array::operator()(Args... args) const 
	{ 
		#ifndef __NJS_ARDUINO
		throw InvalidTypeException(); 
		#endif
	}
	// Comparation operators
	Array Array::operator!() const 
	{ 
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException(); 
		#endif
	}
	
	template <typename t>
	bool Array::operator==(const t &_v1) const { return false; }
	
	// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
	// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
	
	template <typename t>
	bool Array::operator!=(const t &_v1) const { return true; }
	
	template <typename t>
	bool Array::operator<(const t &_v1) const { return (*this)[0] < _v1;}
	
	template <typename t>
	bool Array::operator<=(const t &_v1) const { return (*this)[0] <= _v1; }
	
	template <typename t>
	bool Array::operator>(const t &_v1) const { return (*this)[0] > _v1; }
	
	template <typename t>
	bool Array::operator>=(const t &_v1) const { return (*this)[0] >= _v1; }
	// Numeric operators
	Array Array::operator+() const
	{ 
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException(); 
		#endif
	}
	Array Array::operator-() const
	{ 
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException(); 
		#endif
	}
	Array Array::operator++(const int _v1)
	{ 
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException(); 
		#endif
	}
	Array Array::operator--(const int _v1)
	{ 
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException(); 
		#endif
	}
	Array Array::operator+(const Array &_v1) const 
	{ 
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException(); 
		#endif
	}
	Array Array::operator+=(const Array &_v1) 
	{ 
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException(); 
		#endif
	}
	Array Array::operator-(const Array &_v1) const 
	{ 
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException(); 
		#endif
	}
	Array Array::operator-=(const Array &_v1) 
	{ 
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException(); 
		#endif
	}
	Array Array::operator*(const Array &_v1) const 
	{ 
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException(); 
		#endif
	}
	Array Array::operator*=(const Array &_v1) 
	{ 
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException(); 
		#endif
	}
	// TODO: "**" and "**=" operators
	Array Array::operator/(const Array &_v1) const 
	{ 
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException(); 
		#endif
	}
	Array Array::operator/=(const Array &_v1) 
	{ 
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException(); 
		#endif
	}
	Array Array::operator%(const Array &_v1) const 
	{ 
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException(); 
		#endif
	}
	Array Array::operator%=(const Array &_v1) 
	{ 
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException(); 
		#endif
	}
	Array Array::operator&(const Array &_v1) const 
	{ 
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException(); 
		#endif
	}
	Array Array::operator|(const Array &_v1) const 
	{ 
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException(); 
		#endif
	}
	Array Array::operator^(const Array &_v1) const 
	{ 
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException(); 
		#endif
	}
	Array Array::operator~() const 
	{ 
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException(); 
		#endif
	}
	Array Array::operator>>(const Array &_v1) const 
	{ 
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException(); 
		#endif
	}
	Array Array::operator<<(const Array &_v1) const 
	{ 
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException(); 
		#endif
	}
	Array Array::operator&=(const Array &_v1) 
	{ 
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException(); 
		#endif
	}
	Array Array::operator|=(const Array &_v1) 
	{ 
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException(); 
		#endif
	}
	Array Array::operator^=(const Array &_v1) 
	{ 
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException(); 
		#endif
	}
	Array Array::operator>>=(const Array &_v1) 
	{ 
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException(); 
		#endif
	}
	Array Array::operator<<=(const Array &_v1) 
	{ 
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException(); 
		#endif
	}
	// TODO: ">>>" and ">>>=" operators
	
	
	NJS::VAR Array::__iterator(NJS::VAR* args, int _length) const { return undefined; }
	NJS::VAR Array::__unscopables(NJS::VAR* args, int _length) const { return undefined; }
	NJS::VAR Array::concat(NJS::VAR* args, int _length) const
	{
		/*
		auto &res = *new Array();
		auto &vec = res.value;
		for (auto _arr : args)
		{
			auto &arr = (Array)_arr;
			vec.insert(vec.end(), arr.begin(), arr.end());
		}
		return res;
		*/
		return undefined;
	}
	NJS::VAR Array::copyWithin(NJS::VAR* args, int _length)
	{
		/*
		auto &vec = value;
		int _size = _length;
		int target = _size > 0 ? (int)args[0] : 0;
		int start = _size > 1 ? (int)args[1] : 0;
		int end = _size > 2 ? (int)args[2] : vec.size();
		int size = vec.size();
		if (start < 0)
		{
			start += size;
		}
		if (end < 0)
		{
			end += size;
		}
		std::copy(vec.begin() + target, vec.begin() + end, vec.begin() + start);
		return *this;*/
		return undefined;
	}
	NJS::VAR Array::entries(NJS::VAR* args, int _length) const { return undefined; }
	NJS::VAR Array::every(NJS::VAR* args, int _length) const { return undefined; }
	NJS::VAR Array::fill(NJS::VAR* args, int _length) const
	{
		/*
		NJS::VAR value = _length ? args[0] : undefined;
		value.assign(value.size(), value);
		return *this;
		*/
		return undefined;
	};
	NJS::VAR Array::filter(NJS::VAR* args, int _length) const { return undefined; }
	NJS::VAR Array::find(NJS::VAR* args, int _length) const { return undefined; }
	NJS::VAR Array::findIndex(NJS::VAR* args, int _length) const { return undefined; }
	NJS::VAR Array::flat(NJS::VAR* args, int _length) const { return undefined; }
	NJS::VAR Array::flatMap(NJS::VAR* args, int _length) const { return undefined; }
	NJS::VAR Array::forEach(NJS::VAR* args, int _length) const { return undefined; }
	NJS::VAR Array::includes(NJS::VAR* args, int _length) const { return undefined; }
	NJS::VAR Array::indexOf(NJS::VAR* args, int _length) const { return undefined; }
	NJS::VAR Array::join(NJS::VAR* args, int _length) const
	{
		auto _str = (std::string)(_length ? args[0] : undefined);
		int l = value.size();
		if (l == 0)
			return "";
		std::stringstream stream;
		stream << (std::string)value[0];
		for (int i = 1; i < l; i++)
		{
			stream << _str << (std::string)value[i];
		}
		return stream.str();
	};
	NJS::VAR Array::keys(NJS::VAR* args, int _length) const { return undefined; }
	NJS::VAR Array::lastIndexOf(NJS::VAR* args, int _length) const { return undefined; }
	NJS::VAR Array::map(NJS::VAR* args, int _length) const { return undefined; }
	NJS::VAR Array::pop(NJS::VAR* args, int _length) 
	{ 
		value.pop_back();
		return undefined; 
	}
	NJS::VAR Array::push(NJS::VAR* args, int _length)
	{
		for (int i = 0; i < _length; i++)
		{
			value.push_back(args[i]);
		}
		return this;
	};
	NJS::VAR Array::reduce(NJS::VAR* args, int _length) const { return undefined; }
	NJS::VAR Array::reduceRight(NJS::VAR* args, int _length) const { return undefined; }
	NJS::VAR Array::reverse(NJS::VAR* args, int _length) {
		std::reverse(value.begin(), value.end());
		return this;
	}
	NJS::VAR Array::shift(NJS::VAR* args, int _length) { return undefined; }
	NJS::VAR Array::slice(NJS::VAR* args, int _length) const 
	{ 
		if(_length == 1)
		{
			NJS::Type::vector_t _ret;
			int start = 0;
			if(args[0].type == NJS::Enum::Type::Number)
			{
				if((int)args[0] > -1) start = args[0];
				else start = value.size() + (int)args[0];
				if(start > value.size()) start = value.size();
			}
			_ret = NJS::Type::vector_t(value.begin() + start, value.end());
			return new NJS::Class::Array(_ret);
		}
		else if(_length > 1)
		{
			NJS::Type::vector_t _ret;
			int start = 0;
			int end = value.size();
			if(args[0].type == NJS::Enum::Type::Number) start = args[0];
			if(args[1].type == NJS::Enum::Type::Number)
			{
				if((int)args[1] < 0)
				{
					end = abs((int)args[1]);
					if(end > value.size() - start) return new NJS::Class::Array(_ret);
				}
				else if((int)args[1] < start) return new NJS::Class::Array(_ret);
				else if((int)args[1] <= end) end = (end - (int)args[1]);
				else end = 0;
			}
			else end = 0;
			
			if(value.size() - end < start) return new NJS::Class::Array(_ret);
			_ret = NJS::Type::vector_t(value.begin() + start, value.end() - end);
			return new NJS::Class::Array(_ret);
		}
		else return new NJS::Class::Array(value);
	}
	NJS::VAR Array::some(NJS::VAR* args, int _length) const { return undefined; }
	NJS::VAR Array::sort(NJS::VAR* args, int _length) const { return undefined; }
	NJS::VAR Array::splice(NJS::VAR* args, int _length)
	{ 
		NJS::VAR _ret = slice(args, _length);
		if(_length == 1)
		{
			int start = 0;
			if(args[0].type == NJS::Enum::Type::Number)
			{
				if((int)args[0] > -1) start = args[0];
				else start = value.size() + (int)args[0];
				if(start > value.size()) start = value.size();
			}
			
			value.erase(value.begin() + start, value.end());
			return _ret;
		}
		else if(_length > 1)
		{
			int start = 0;
			int end = value.size();
			if(args[0].type == NJS::Enum::Type::Number) start = args[0];
			
			if(args[1].type == NJS::Enum::Type::Number)
			{
				if((int)args[1] < 0)
				{
					end = abs((int)args[1]);
					if(end > value.size() - start) return _ret;
					
				}
				else if((int)args[1] < start) return _ret;
				else if((int)args[1] <= end) end = (end - (int)args[1]) -1;
				else end = 0;
				
				if(start > value.size()) start = value.size();
			
			}
			else end = 0;
			
			if(value.size() - end < start) return _ret;
			value.erase(value.begin() + start, value.end() - end);

		}
		for(int i = 2; i < _length; i++)
		{
			value.push_back(args[i]);
		}
		return _ret;
	}
	NJS::VAR Array::toLocaleString(NJS::VAR* args, int _length) const
	{
		/*
		int l = value.size();
		if (l == 0)
			return "";
		std::stringstream stream;
		stream << (std::string)value[0]["toLocaleString"]();
		for (int i = 1; i < l; i++)
		{
			NJS::VAR val = value[i];
			stream << "," << (std::string)val["toLocaleString"]();
		}
		return stream.str();
		*/
		return this;
	}
	NJS::VAR Array::toString(NJS::VAR* args, int _length) const
	{
		NJS::VAR _arg[1] = {","};
		return join(_arg, 1);
	}

	NJS::VAR Array::unshift(NJS::VAR* args, int _length)
	{
		return this;
	}
	NJS::VAR Array::values(NJS::VAR* args, int _length) const { return undefined; }
	
} // namespace NJS::Class
