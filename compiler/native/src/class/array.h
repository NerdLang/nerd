/*
 * This file is part of NectarCPP
 * Copyright (c) 2020 - 2020 Adrien THIERRY
 * https://nectar-lang.org - https://seraum.com/
 *
 * sources : https://github.com/nectar-lang/NectarCPP
 * 
 * NectarCPP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NectarCPP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NectarCPP.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
 
#pragma once
#include "array_header.h"
#include <sstream>
#include <limits>
		
namespace NectarCore::Class
{
	// Constructors
	Array::Array() 
	{ 

	}
	Array::Array(NectarCore::Type::vector_t vec)
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
		if (value.size() == 1)
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
		if (value.size() == 1)
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
		if (value.size() == 1)
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
	NectarCore::VAR const Array::operator[](NectarCore::VAR key) const
	{
		if (key.type == NectarCore::Enum::Type::Number)
		{
			auto i = (int)key;
			if (i >= 0 && i <= value.size())
			{
				return value.at(i);
			}
		}
		
		return NectarCore::Global::undefined;
	}
	NectarCore::VAR const Array::operator[](int key) const
	{
		if (key >= 0 && key <= value.size())
		{
			return value.at(key);
		}
		
		return NectarCore::Global::undefined;
	}
	
	#ifndef __Nectar__OBJECT_VECTOR
	NectarCore::VAR &Array::operator[](NectarCore::VAR key)
	{	
		if (key.type == NectarCore::Enum::Type::Number)
		{
			auto i = (int)key;

			if (i < 0)
			{
				return NectarCore::Global::undefined;
			}
			else 
			{
				if (i >= value.size())
				{
					value.resize(i + 1);
				}
			}
			return value[i];
		}
		
		std::string _str = ((std::string)key);
		NectarCore::Type::StringView _sview = _str;
		
		if(_sview.compare("length") == 0)
		{
			length = (int)value.size();
			return length;
		}
		
		NectarCore::VAR& _obj = object[_str];
		if(_obj) return _obj; 
		
		__Nectar_Method_Lazy_Loader("push", push);
		__Nectar_Method_Lazy_Loader("@@iterator", __iterator);
		__Nectar_Method_Lazy_Loader("@@unscopables", __unscopables);
		__Nectar_Method_Lazy_Loader("concat", concat);
		__Nectar_Method_Lazy_Loader("copyWithin", copyWithin);
		__Nectar_Method_Lazy_Loader("entries", entries);
		__Nectar_Method_Lazy_Loader("every", every);
		__Nectar_Method_Lazy_Loader("fill", fill);
		__Nectar_Method_Lazy_Loader("filter", filter);
		__Nectar_Method_Lazy_Loader("find", find);
		__Nectar_Method_Lazy_Loader("findIndex", findIndex);
		__Nectar_Method_Lazy_Loader("flat", flat);
		__Nectar_Method_Lazy_Loader("flatMap", flatMap);
		__Nectar_Method_Lazy_Loader("forEach", forEach);
		__Nectar_Method_Lazy_Loader("includes", includes);
		__Nectar_Method_Lazy_Loader("indexOf", indexOf);
		__Nectar_Method_Lazy_Loader("join", join);
		__Nectar_Method_Lazy_Loader("keys", keys);
		__Nectar_Method_Lazy_Loader("lastIndexOf", lastIndexOf);
		__Nectar_Method_Lazy_Loader("map", map);
		__Nectar_Method_Lazy_Loader("pop", pop);
		__Nectar_Method_Lazy_Loader("push", push);
		__Nectar_Method_Lazy_Loader("reduce", reduce);
		__Nectar_Method_Lazy_Loader("reduceRight", reduceRight);
		__Nectar_Method_Lazy_Loader("reverse", reverse);
		__Nectar_Method_Lazy_Loader("shift", shift);
		__Nectar_Method_Lazy_Loader("slice", slice);
		__Nectar_Method_Lazy_Loader("some", some);
		__Nectar_Method_Lazy_Loader("sort", sort);
		__Nectar_Method_Lazy_Loader("splice", splice);
		__Nectar_Method_Lazy_Loader("toLocaleString", toLocaleString);
		__Nectar_Method_Lazy_Loader("toString", toString);
		__Nectar_Method_Lazy_Loader("unshift", unshift);
		__Nectar_Method_Lazy_Loader("values", values);
		
		return _obj;
	}
	#else
	NectarCore::VAR &Array::operator[](NectarCore::VAR key)
	{
		if (key.type == NectarCore::Enum::Type::Number)
		{
			auto i = (int)key;
			
			if (i < 0)
			{
				return NectarCore::Global::undefined;
			}
			else 
			{
				if (i >= value.size())
				{
					value.resize(i + 1);
				}
			}
			return value[i];
		}
		
		std::string _str = ((std::string)key);
		NectarCore::Type::StringView _sview = _str;
		
		if(_sview.compare("length") == 0)
		{
			length = (int)value.size();
			return length;
		}
		
		for (auto & search : object)
		{
			if (_sview.compare(search.first) == 0)
			{
				return search.second;
			}
		}
		
		__Nectar_Method_Lazy_Loader("push", push);
		__Nectar_Method_Lazy_Loader("@@iterator", __iterator);
		__Nectar_Method_Lazy_Loader("@@unscopables", __unscopables);
		__Nectar_Method_Lazy_Loader("concat", concat);
		__Nectar_Method_Lazy_Loader("copyWithin", copyWithin);
		__Nectar_Method_Lazy_Loader("entries", entries);
		__Nectar_Method_Lazy_Loader("every", every);
		__Nectar_Method_Lazy_Loader("fill", fill);
		__Nectar_Method_Lazy_Loader("filter", filter);
		__Nectar_Method_Lazy_Loader("find", find);
		__Nectar_Method_Lazy_Loader("findIndex", findIndex);
		__Nectar_Method_Lazy_Loader("flat", flat);
		__Nectar_Method_Lazy_Loader("flatMap", flatMap);
		__Nectar_Method_Lazy_Loader("forEach", forEach);
		__Nectar_Method_Lazy_Loader("includes", includes);
		__Nectar_Method_Lazy_Loader("indexOf", indexOf);
		__Nectar_Method_Lazy_Loader("join", join);
		__Nectar_Method_Lazy_Loader("keys", keys);
		__Nectar_Method_Lazy_Loader("lastIndexOf", lastIndexOf);
		__Nectar_Method_Lazy_Loader("map", map);
		__Nectar_Method_Lazy_Loader("pop", pop);
		__Nectar_Method_Lazy_Loader("reduce", reduce);
		__Nectar_Method_Lazy_Loader("reduceRight", reduceRight);
		__Nectar_Method_Lazy_Loader("reverse", reverse);
		__Nectar_Method_Lazy_Loader("shift", shift);
		__Nectar_Method_Lazy_Loader("slice", slice);
		__Nectar_Method_Lazy_Loader("some", some);
		__Nectar_Method_Lazy_Loader("sort", sort);
		__Nectar_Method_Lazy_Loader("splice", splice);
		__Nectar_Method_Lazy_Loader("toLocaleString", toLocaleString);
		__Nectar_Method_Lazy_Loader("toString", toString);
		__Nectar_Method_Lazy_Loader("unshift", unshift);
		__Nectar_Method_Lazy_Loader("values", values);
		

		object.push_back(NectarCore::Type::pair_t(_str, NectarCore::Global::undefined));
		return object[object.size() - 1].second;
	}
	#endif
	
	NectarCore::VAR &Array::operator[](int key)
	{
		if (key < 0)
		{
			return NectarCore::Global::undefined;
		}
		else 
		{
			if (key >= value.size())
			{
				value.resize(key + 1);
			}
		}
		return value[key];
	}
	
	NectarCore::VAR &Array::operator[](double key)
	{
		if (key < 0)
		{
			return NectarCore::Global::undefined;
		}
		else 
		{
			if (key >= value.size())
			{
				value.resize(key + 1);
			}
		}
		return value[key];
	}
	
	#ifndef __Nectar__OBJECT_VECTOR
	NectarCore::VAR &Array::operator[](const char* key)
	{		
		std::string _str = key;
		NectarCore::Type::StringView _sview = _str;
		
		if(_sview.compare("length") == 0)
		{
			length = (int)value.size();
			return length;
		}
		
		NectarCore::VAR& _obj = object[_str];
		if(_obj) return _obj; 
		
		__Nectar_Method_Lazy_Loader("push", push);
		__Nectar_Method_Lazy_Loader("@@iterator", __iterator);
		__Nectar_Method_Lazy_Loader("@@unscopables", __unscopables);
		__Nectar_Method_Lazy_Loader("concat", concat);
		__Nectar_Method_Lazy_Loader("copyWithin", copyWithin);
		__Nectar_Method_Lazy_Loader("entries", entries);
		__Nectar_Method_Lazy_Loader("every", every);
		__Nectar_Method_Lazy_Loader("fill", fill);
		__Nectar_Method_Lazy_Loader("filter", filter);
		__Nectar_Method_Lazy_Loader("find", find);
		__Nectar_Method_Lazy_Loader("findIndex", findIndex);
		__Nectar_Method_Lazy_Loader("flat", flat);
		__Nectar_Method_Lazy_Loader("flatMap", flatMap);
		__Nectar_Method_Lazy_Loader("forEach", forEach);
		__Nectar_Method_Lazy_Loader("includes", includes);
		__Nectar_Method_Lazy_Loader("indexOf", indexOf);
		__Nectar_Method_Lazy_Loader("join", join);
		__Nectar_Method_Lazy_Loader("keys", keys);
		__Nectar_Method_Lazy_Loader("lastIndexOf", lastIndexOf);
		__Nectar_Method_Lazy_Loader("map", map);
		__Nectar_Method_Lazy_Loader("pop", pop);
		__Nectar_Method_Lazy_Loader("push", push);
		__Nectar_Method_Lazy_Loader("reduce", reduce);
		__Nectar_Method_Lazy_Loader("reduceRight", reduceRight);
		__Nectar_Method_Lazy_Loader("reverse", reverse);
		__Nectar_Method_Lazy_Loader("shift", shift);
		__Nectar_Method_Lazy_Loader("slice", slice);
		__Nectar_Method_Lazy_Loader("some", some);
		__Nectar_Method_Lazy_Loader("sort", sort);
		__Nectar_Method_Lazy_Loader("splice", splice);
		__Nectar_Method_Lazy_Loader("toLocaleString", toLocaleString);
		__Nectar_Method_Lazy_Loader("toString", toString);
		__Nectar_Method_Lazy_Loader("unshift", unshift);
		__Nectar_Method_Lazy_Loader("values", values);
		
		return _obj;
	}
	#else
	NectarCore::VAR &Array::operator[](const char* key)
	{
		std::string _str = key;
		NectarCore::Type::StringView _sview = _str;
		
		if(_sview.compare("length") == 0)
		{
			length = (int)value.size();
			return length;
		}
		
		for (auto & search : object)
		{
			if (_sview.compare(search.first) == 0)
			{
				return search.second;
			}
		}
		
		__Nectar_Method_Lazy_Loader("push", push);
		__Nectar_Method_Lazy_Loader("@@iterator", __iterator);
		__Nectar_Method_Lazy_Loader("@@unscopables", __unscopables);
		__Nectar_Method_Lazy_Loader("concat", concat);
		__Nectar_Method_Lazy_Loader("copyWithin", copyWithin);
		__Nectar_Method_Lazy_Loader("entries", entries);
		__Nectar_Method_Lazy_Loader("every", every);
		__Nectar_Method_Lazy_Loader("fill", fill);
		__Nectar_Method_Lazy_Loader("filter", filter);
		__Nectar_Method_Lazy_Loader("find", find);
		__Nectar_Method_Lazy_Loader("findIndex", findIndex);
		__Nectar_Method_Lazy_Loader("flat", flat);
		__Nectar_Method_Lazy_Loader("flatMap", flatMap);
		__Nectar_Method_Lazy_Loader("forEach", forEach);
		__Nectar_Method_Lazy_Loader("includes", includes);
		__Nectar_Method_Lazy_Loader("indexOf", indexOf);
		__Nectar_Method_Lazy_Loader("join", join);
		__Nectar_Method_Lazy_Loader("keys", keys);
		__Nectar_Method_Lazy_Loader("lastIndexOf", lastIndexOf);
		__Nectar_Method_Lazy_Loader("map", map);
		__Nectar_Method_Lazy_Loader("pop", pop);
		__Nectar_Method_Lazy_Loader("reduce", reduce);
		__Nectar_Method_Lazy_Loader("reduceRight", reduceRight);
		__Nectar_Method_Lazy_Loader("reverse", reverse);
		__Nectar_Method_Lazy_Loader("shift", shift);
		__Nectar_Method_Lazy_Loader("slice", slice);
		__Nectar_Method_Lazy_Loader("some", some);
		__Nectar_Method_Lazy_Loader("sort", sort);
		__Nectar_Method_Lazy_Loader("splice", splice);
		__Nectar_Method_Lazy_Loader("toLocaleString", toLocaleString);
		__Nectar_Method_Lazy_Loader("toString", toString);
		__Nectar_Method_Lazy_Loader("unshift", unshift);
		__Nectar_Method_Lazy_Loader("values", values);
		

		object.push_back(NectarCore::Type::pair_t(_str, NectarCore::Global::undefined));
		return object[object.size() - 1].second;
	}
	#endif
	
	// Comparation operators
	Array Array::operator!() const 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	
	// Numeric operators
	Array Array::operator+() const
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator-() const
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator++(const int _v1)
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator--(const int _v1)
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator+(const Array &_v1) const 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator+=(const Array &_v1) 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator-(const Array &_v1) const 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator-=(const Array &_v1) 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator*(const Array &_v1) const 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator*=(const Array &_v1) 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	// TODO: "**" and "**=" operators
	Array Array::operator/(const Array &_v1) const 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator/=(const Array &_v1) 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator%(const Array &_v1) const 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator%=(const Array &_v1) 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator&(const Array &_v1) const 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator|(const Array &_v1) const 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator^(const Array &_v1) const 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator~() const 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator>>(const Array &_v1) const 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator<<(const Array &_v1) const 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator&=(const Array &_v1) 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator|=(const Array &_v1) 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator^=(const Array &_v1) 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator>>=(const Array &_v1) 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	Array Array::operator<<=(const Array &_v1) 
	{ 
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32) 
		throw InvalidTypeException(); 
		#endif
		return Array();
	}
	// TODO: ">>>" and ">>>=" operators
	
	
	NectarCore::VAR Array::__iterator(NectarCore::VAR* args, int _length) const { return NectarCore::Global::undefined; }
	NectarCore::VAR Array::__unscopables(NectarCore::VAR* args, int _length) const { return NectarCore::Global::undefined; }
	NectarCore::VAR Array::concat(NectarCore::VAR* args, int _length) const
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
		return NectarCore::Global::undefined;
	}
	NectarCore::VAR Array::copyWithin(NectarCore::VAR* args, int _length)
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
		return NectarCore::Global::undefined;
	}
	NectarCore::VAR Array::entries(NectarCore::VAR* args, int _length) const { return NectarCore::Global::undefined; }
	NectarCore::VAR Array::every(NectarCore::VAR* args, int _length) const { return NectarCore::Global::undefined; }
	NectarCore::VAR Array::fill(NectarCore::VAR* args, int _length) const
	{
		/*
		NectarCore::VAR value = _length ? args[0] : NectarCore::Global::undefined;
		value.assign(value.size(), value);
		return *this;
		*/
		return NectarCore::Global::undefined;
	};
	NectarCore::VAR Array::filter(NectarCore::VAR* args, int _length) const { return NectarCore::Global::undefined; }
	NectarCore::VAR Array::find(NectarCore::VAR* args, int _length) const { return NectarCore::Global::undefined; }
	NectarCore::VAR Array::findIndex(NectarCore::VAR* args, int _length) const { return NectarCore::Global::undefined; }
	NectarCore::VAR Array::flat(NectarCore::VAR* args, int _length) const { return NectarCore::Global::undefined; }
	NectarCore::VAR Array::flatMap(NectarCore::VAR* args, int _length) const { return NectarCore::Global::undefined; }
	NectarCore::VAR Array::forEach(NectarCore::VAR* args, int _length) const { return NectarCore::Global::undefined; }
	NectarCore::VAR Array::includes(NectarCore::VAR* args, int _length) const { return NectarCore::Global::undefined; }
	NectarCore::VAR Array::indexOf(NectarCore::VAR* args, int _length) const { return NectarCore::Global::undefined; }
	NectarCore::VAR Array::join(NectarCore::VAR* args, int _length) const
	{
		auto _str = (std::string)(_length ? args[0] : NectarCore::Global::undefined);
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
	NectarCore::VAR Array::keys(NectarCore::VAR* args, int _length) const { return NectarCore::Global::undefined; }
	NectarCore::VAR Array::lastIndexOf(NectarCore::VAR* args, int _length) const { return NectarCore::Global::undefined; }
	NectarCore::VAR Array::map(NectarCore::VAR* args, int _length) const { return NectarCore::Global::undefined; }
	NectarCore::VAR Array::pop(NectarCore::VAR* args, int _length) 
	{ 
		value.pop_back();
		return NectarCore::Global::undefined; 
	}
	NectarCore::VAR Array::push(NectarCore::VAR* args, int _length)
	{
		for (int i = 0; i < _length; i++)
		{
			value.push_back(args[i]);
		}
		return this;
	};
	NectarCore::VAR Array::reduce(NectarCore::VAR* args, int _length) const { return NectarCore::Global::undefined; }
	NectarCore::VAR Array::reduceRight(NectarCore::VAR* args, int _length) const { return NectarCore::Global::undefined; }
	NectarCore::VAR Array::reverse(NectarCore::VAR* args, int _length) {
		std::reverse(value.begin(), value.end());
		return this;
	}
	NectarCore::VAR Array::shift(NectarCore::VAR* args, int _length) { return NectarCore::Global::undefined; }
	NectarCore::VAR Array::slice(NectarCore::VAR* args, int _length) const 
	{ 
		if(_length == 1)
		{
			NectarCore::Type::vector_t _ret;
			int start = 0;
			if(args[0].type == NectarCore::Enum::Type::Number)
			{
				if((int)args[0] > -1) start = args[0];
				else start = value.size() + (int)args[0];
				if(start > value.size()) start = value.size();
			}
			_ret = NectarCore::Type::vector_t(value.begin() + start, value.end());
			return new NectarCore::Class::Array(_ret);
		}
		else if(_length > 1)
		{
			NectarCore::Type::vector_t _ret;
			int start = 0;
			int end = value.size();
			if(args[0].type == NectarCore::Enum::Type::Number) start = args[0];
			if(args[1].type == NectarCore::Enum::Type::Number)
			{
				if((int)args[1] < 0)
				{
					end = abs((int)args[1]);
					if(end > value.size() - start) return new NectarCore::Class::Array(_ret);
				}
				else if((int)args[1] < start) return new NectarCore::Class::Array(_ret);
				else if((int)args[1] <= end) end = (end - (int)args[1]);
				else end = 0;
			}
			else end = 0;
			
			if(value.size() - end < start) return new NectarCore::Class::Array(_ret);
			_ret = NectarCore::Type::vector_t(value.begin() + start, value.end() - end);
			return new NectarCore::Class::Array(_ret);
		}
		else return new NectarCore::Class::Array(value);
	}
	NectarCore::VAR Array::some(NectarCore::VAR* args, int _length) const { return NectarCore::Global::undefined; }
	NectarCore::VAR Array::sort(NectarCore::VAR* args, int _length) const 
	{ 
		return NectarCore::Global::undefined; 
	}
	NectarCore::VAR Array::splice(NectarCore::VAR* args, int _length)
	{ 
		NectarCore::VAR _ret = slice(args, _length);
		if(_length == 1)
		{
			int start = 0;
			if(args[0].type == NectarCore::Enum::Type::Number)
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
			if(args[0].type == NectarCore::Enum::Type::Number) start = args[0];
			
			if(args[1].type == NectarCore::Enum::Type::Number)
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
	NectarCore::VAR Array::toLocaleString(NectarCore::VAR* args, int _length) const
	{
		/*
		int l = value.size();
		if (l == 0)
			return "";
		std::stringstream stream;
		stream << (std::string)value[0]["toLocaleString"]();
		for (int i = 1; i < l; i++)
		{
			NectarCore::VAR val = value[i];
			stream << "," << (std::string)val["toLocaleString"]();
		}
		return stream.str();
		*/
		return this;
	}
	NectarCore::VAR Array::toString(NectarCore::VAR* args, int _length) const
	{
		NectarCore::VAR _arg[1] = {","};
		return join(_arg, 1);
	}

	NectarCore::VAR Array::unshift(NectarCore::VAR* args, int _length)
	{
		return this;
	}
	NectarCore::VAR Array::values(NectarCore::VAR* args, int _length) const { return NectarCore::Global::undefined; }
	
} // namespace NectarCore::Class
