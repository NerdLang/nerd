#pragma once
#include "array_header.h"
#include <sstream>
#include <limits>
#define __NJS_Class_Array_Init() \
counter++; \
__NJS_CreateMethodToClass("@@iterator", __iterator); \
__NJS_CreateMethodToClass("@@unscopables", __unscopables); \
__NJS_CreateMethodToClass("concat", concat); \
__NJS_CreateMethodToClass("copyWithin", copyWithin); \
__NJS_CreateMethodToClass("entries", entries); \
__NJS_CreateMethodToClass("every", every); \
__NJS_CreateMethodToClass("fill", fill); \
__NJS_CreateMethodToClass("filter", filter); \
__NJS_CreateMethodToClass("find", find); \
__NJS_CreateMethodToClass("findIndex", findIndex); \
__NJS_CreateMethodToClass("flat", flat); \
__NJS_CreateMethodToClass("flatMap", flatMap); \
__NJS_CreateMethodToClass("forEach", forEach); \
__NJS_CreateMethodToClass("includes", includes); \
__NJS_CreateMethodToClass("indexOf", indexOf); \
__NJS_CreateMethodToClass("join", join); \
__NJS_CreateMethodToClass("keys", keys); \
__NJS_CreateMethodToClass("lastIndexOf", lastIndexOf); \
__NJS_CreateMethodToClass("map", map); \
__NJS_CreateMethodToClass("pop", pop); \
__NJS_CreateMethodToClass("push", push); \
__NJS_CreateMethodToClass("reduce", reduce); \
__NJS_CreateMethodToClass("reduceRight", reduceRight); \
__NJS_CreateMethodToClass("reverse", reverse); \
__NJS_CreateMethodToClass("shift", shift); \
__NJS_CreateMethodToClass("slice", slice); \
__NJS_CreateMethodToClass("some", some); \
__NJS_CreateMethodToClass("sort", sort); \
__NJS_CreateMethodToClass("splice", splice); \
__NJS_CreateMethodToClass("toLocaleString", toLocaleString); \
__NJS_CreateMethodToClass("toString", toString); \
__NJS_CreateMethodToClass("unshift", unshift); \
__NJS_CreateMethodToClass("values", values);
		
namespace NJS::Class
{
	// Constructors
	Array::Array() 
	{ 
		__NJS_Class_Array_Init();	
		object.push_back(NJS::Type::pair_t("length", 0));
	}
	Array::Array(NJS::Type::vector_t vec)
	{
		__NJS_Class_Array_Init();
		value = vec;
		__NJS_Object_Set("length", (int)vec.size(), &this->object);
	}
	// Methods
	void Array::Delete() noexcept
	{
		if (--counter < 1)
		{
			delete this;
		}
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
					__NJS_Object_Set("length", (int)value.size(), &this->object);
				}
			}
			return value[i];
		}
		
		for (auto & search : object)
		{
			if (((NJS::Class::String*)key._ptr)->value.compare(search.first) == 0)
			{
				return search.second;
			}
		}

		((NJS::Class::String*)key._ptr)->counter++;
		object.push_back(NJS::Type::pair_t(((NJS::Class::String*)key._ptr)->value.c_str(), __NJS_VAR()));
		return object[object.size() - 1].second;
	}
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
	
	
	NJS::VAR Array::__iterator(NJS::Type::vector_t args) const { return NJS::VAR(); }
	NJS::VAR Array::__unscopables(NJS::Type::vector_t args) const { return NJS::VAR(); }
	NJS::VAR Array::concat(NJS::Type::vector_t args) const
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
		return NJS::VAR();
	}
	NJS::VAR Array::copyWithin(NJS::Type::vector_t args)
	{
		/*
		auto &vec = value;
		int _size = args.size();
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
		return NJS::VAR();
	}
	NJS::VAR Array::entries(NJS::Type::vector_t args) const { return NJS::VAR(); }
	NJS::VAR Array::every(NJS::Type::vector_t args) const { return NJS::VAR(); }
	NJS::VAR Array::fill(NJS::Type::vector_t args) const
	{
		/*
		NJS::VAR value = args.size() ? args[0] : undefined;
		value.assign(value.size(), value);
		return *this;
		*/
		return NJS::VAR();
	};
	NJS::VAR Array::filter(NJS::Type::vector_t args) const { return NJS::VAR(); }
	NJS::VAR Array::find(NJS::Type::vector_t args) const { return NJS::VAR(); }
	NJS::VAR Array::findIndex(NJS::Type::vector_t args) const { return NJS::VAR(); }
	NJS::VAR Array::flat(NJS::Type::vector_t args) const { return NJS::VAR(); }
	NJS::VAR Array::flatMap(NJS::Type::vector_t args) const { return NJS::VAR(); }
	NJS::VAR Array::forEach(NJS::Type::vector_t args) const { return NJS::VAR(); }
	NJS::VAR Array::includes(NJS::Type::vector_t args) const { return NJS::VAR(); }
	NJS::VAR Array::indexOf(NJS::Type::vector_t args) const { return NJS::VAR(); }
	NJS::VAR Array::join(NJS::Type::vector_t args) const
	{
		auto _str = (std::string)(args.size() ? args[0] : undefined);
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
	NJS::VAR Array::keys(NJS::Type::vector_t args) const { return NJS::VAR(); }
	NJS::VAR Array::lastIndexOf(NJS::Type::vector_t args) const { return NJS::VAR(); }
	NJS::VAR Array::map(NJS::Type::vector_t args) const { return NJS::VAR(); }
	NJS::VAR Array::pop(NJS::Type::vector_t args) { return NJS::VAR(); }
	NJS::VAR Array::push(NJS::Type::vector_t args)
	{
		/*
		for (auto value : args)
		{
			value.push_back(value);
		}
		__NJS_Object_Set("length", (int)value.size(), &this->__Object);
		*/
		return this;
	};
	NJS::VAR Array::reduce(NJS::Type::vector_t args) const { return NJS::VAR(); }
	NJS::VAR Array::reduceRight(NJS::Type::vector_t args) const { return NJS::VAR(); }
	NJS::VAR Array::reverse(NJS::Type::vector_t args) {
		std::reverse(value.begin(), value.end());
		return this;
	}
	NJS::VAR Array::shift(NJS::Type::vector_t args) { return NJS::VAR(); }
	NJS::VAR Array::slice(NJS::Type::vector_t args) const { return NJS::VAR(); }
	NJS::VAR Array::some(NJS::Type::vector_t args) const { return NJS::VAR(); }
	NJS::VAR Array::sort(NJS::Type::vector_t args) const { return NJS::VAR(); }
	NJS::VAR Array::splice(NJS::Type::vector_t args) { return NJS::VAR(); }
	NJS::VAR Array::toLocaleString(NJS::Type::vector_t args) const
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
	NJS::VAR Array::toString(NJS::Type::vector_t args) const
	{
		return join(NJS::Type::vector_t({","}));
	}

	NJS::VAR Array::unshift(NJS::Type::vector_t values)
	{
		auto pos = value.begin();
		for (auto value : values)
		{
			//value.insert(pos, value);
		}
		return this;
	}
	NJS::VAR Array::values(NJS::Type::vector_t args) const { return NJS::VAR(); }
	
} // namespace NJS::Class
