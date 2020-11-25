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
		
namespace Nectar::Class
{
	// Constructors
	Array::Array() 
	{ 

	}
	Array::Array(Nectar::Type::vector_t vec)
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
	Nectar::VAR const Array::operator[](Nectar::VAR key) const
	{
		if (key.type == Nectar::Enum::Type::Number)
		{
			auto i = (int)key;
			if (i >= 0 && i <= value.size())
			{
				return value.at(i);
			}
		}
		
		return Nectar::Global::undefined;
	}
	Nectar::VAR const Array::operator[](int key) const
	{
		if (key >= 0 && key <= value.size())
		{
			return value.at(key);
		}
		
		return Nectar::Global::undefined;
	}
	
	#ifndef __Nectar__OBJECT_VECTOR
	Nectar::VAR &Array::operator[](Nectar::VAR key)
	{	
		if (key.type == Nectar::Enum::Type::Number)
		{
			auto i = (int)key;

			if (i < 0)
			{
				return Nectar::Global::undefined;
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
		Nectar::Type::StringView _sview = _str;
		
		if(_sview.compare("length") == 0)
		{
			length = (int)value.size();
			return length;
		}
		
		Nectar::VAR& _obj = object[_str];
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
	Nectar::VAR &Array::operator[](Nectar::VAR key)
	{
		if (key.type == Nectar::Enum::Type::Number)
		{
			auto i = (int)key;
			
			if (i < 0)
			{
				return Nectar::Global::undefined;
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
		Nectar::Type::StringView _sview = _str;
		
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
		

		object.push_back(Nectar::Type::pair_t(_str, Nectar::Global::undefined));
		return object[object.size() - 1].second;
	}
	#endif
	
	Nectar::VAR &Array::operator[](int key)
	{
		if (key < 0)
		{
			return Nectar::Global::undefined;
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
	
	Nectar::VAR &Array::operator[](double key)
	{
		if (key < 0)
		{
			return Nectar::Global::undefined;
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
	Nectar::VAR &Array::operator[](const char* key)
	{		
		std::string _str = key;
		Nectar::Type::StringView _sview = _str;
		
		if(_sview.compare("length") == 0)
		{
			length = (int)value.size();
			return length;
		}
		
		Nectar::VAR& _obj = object[_str];
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
	Nectar::VAR &Array::operator[](const char* key)
	{
		std::string _str = key;
		Nectar::Type::StringView _sview = _str;
		
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
		

		object.push_back(Nectar::Type::pair_t(_str, Nectar::Global::undefined));
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
	
	
	Nectar::VAR Array::__iterator(Nectar::VAR* args, int _length) const { return Nectar::Global::undefined; }
	Nectar::VAR Array::__unscopables(Nectar::VAR* args, int _length) const { return Nectar::Global::undefined; }
	Nectar::VAR Array::concat(Nectar::VAR* args, int _length) const
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
		return Nectar::Global::undefined;
	}
	Nectar::VAR Array::copyWithin(Nectar::VAR* args, int _length)
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
		return Nectar::Global::undefined;
	}
	Nectar::VAR Array::entries(Nectar::VAR* args, int _length) const { return Nectar::Global::undefined; }
	Nectar::VAR Array::every(Nectar::VAR* args, int _length) const { return Nectar::Global::undefined; }
	Nectar::VAR Array::fill(Nectar::VAR* args, int _length) const
	{
		/*
		Nectar::VAR value = _length ? args[0] : Nectar::Global::undefined;
		value.assign(value.size(), value);
		return *this;
		*/
		return Nectar::Global::undefined;
	};
	Nectar::VAR Array::filter(Nectar::VAR* args, int _length) const { return Nectar::Global::undefined; }
	Nectar::VAR Array::find(Nectar::VAR* args, int _length) const { return Nectar::Global::undefined; }
	Nectar::VAR Array::findIndex(Nectar::VAR* args, int _length) const { return Nectar::Global::undefined; }
	Nectar::VAR Array::flat(Nectar::VAR* args, int _length) const { return Nectar::Global::undefined; }
	Nectar::VAR Array::flatMap(Nectar::VAR* args, int _length) const { return Nectar::Global::undefined; }
	Nectar::VAR Array::forEach(Nectar::VAR* args, int _length) const { return Nectar::Global::undefined; }
	Nectar::VAR Array::includes(Nectar::VAR* args, int _length) const { return Nectar::Global::undefined; }
	Nectar::VAR Array::indexOf(Nectar::VAR* args, int _length) const { return Nectar::Global::undefined; }
	Nectar::VAR Array::join(Nectar::VAR* args, int _length) const
	{
		auto _str = (std::string)(_length ? args[0] : Nectar::Global::undefined);
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
	Nectar::VAR Array::keys(Nectar::VAR* args, int _length) const { return Nectar::Global::undefined; }
	Nectar::VAR Array::lastIndexOf(Nectar::VAR* args, int _length) const { return Nectar::Global::undefined; }
	Nectar::VAR Array::map(Nectar::VAR* args, int _length) const { return Nectar::Global::undefined; }
	Nectar::VAR Array::pop(Nectar::VAR* args, int _length) 
	{ 
		value.pop_back();
		return Nectar::Global::undefined; 
	}
	Nectar::VAR Array::push(Nectar::VAR* args, int _length)
	{
		for (int i = 0; i < _length; i++)
		{
			value.push_back(args[i]);
		}
		return this;
	};
	Nectar::VAR Array::reduce(Nectar::VAR* args, int _length) const { return Nectar::Global::undefined; }
	Nectar::VAR Array::reduceRight(Nectar::VAR* args, int _length) const { return Nectar::Global::undefined; }
	Nectar::VAR Array::reverse(Nectar::VAR* args, int _length) {
		std::reverse(value.begin(), value.end());
		return this;
	}
	Nectar::VAR Array::shift(Nectar::VAR* args, int _length) { return Nectar::Global::undefined; }
	Nectar::VAR Array::slice(Nectar::VAR* args, int _length) const 
	{ 
		if(_length == 1)
		{
			Nectar::Type::vector_t _ret;
			int start = 0;
			if(args[0].type == Nectar::Enum::Type::Number)
			{
				if((int)args[0] > -1) start = args[0];
				else start = value.size() + (int)args[0];
				if(start > value.size()) start = value.size();
			}
			_ret = Nectar::Type::vector_t(value.begin() + start, value.end());
			return new Nectar::Class::Array(_ret);
		}
		else if(_length > 1)
		{
			Nectar::Type::vector_t _ret;
			int start = 0;
			int end = value.size();
			if(args[0].type == Nectar::Enum::Type::Number) start = args[0];
			if(args[1].type == Nectar::Enum::Type::Number)
			{
				if((int)args[1] < 0)
				{
					end = abs((int)args[1]);
					if(end > value.size() - start) return new Nectar::Class::Array(_ret);
				}
				else if((int)args[1] < start) return new Nectar::Class::Array(_ret);
				else if((int)args[1] <= end) end = (end - (int)args[1]);
				else end = 0;
			}
			else end = 0;
			
			if(value.size() - end < start) return new Nectar::Class::Array(_ret);
			_ret = Nectar::Type::vector_t(value.begin() + start, value.end() - end);
			return new Nectar::Class::Array(_ret);
		}
		else return new Nectar::Class::Array(value);
	}
	Nectar::VAR Array::some(Nectar::VAR* args, int _length) const { return Nectar::Global::undefined; }
	Nectar::VAR Array::sort(Nectar::VAR* args, int _length) const 
	{ 
		return Nectar::Global::undefined; 
	}
	Nectar::VAR Array::splice(Nectar::VAR* args, int _length)
	{ 
		Nectar::VAR _ret = slice(args, _length);
		if(_length == 1)
		{
			int start = 0;
			if(args[0].type == Nectar::Enum::Type::Number)
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
			if(args[0].type == Nectar::Enum::Type::Number) start = args[0];
			
			if(args[1].type == Nectar::Enum::Type::Number)
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
	Nectar::VAR Array::toLocaleString(Nectar::VAR* args, int _length) const
	{
		/*
		int l = value.size();
		if (l == 0)
			return "";
		std::stringstream stream;
		stream << (std::string)value[0]["toLocaleString"]();
		for (int i = 1; i < l; i++)
		{
			Nectar::VAR val = value[i];
			stream << "," << (std::string)val["toLocaleString"]();
		}
		return stream.str();
		*/
		return this;
	}
	Nectar::VAR Array::toString(Nectar::VAR* args, int _length) const
	{
		Nectar::VAR _arg[1] = {","};
		return join(_arg, 1);
	}

	Nectar::VAR Array::unshift(Nectar::VAR* args, int _length)
	{
		return this;
	}
	Nectar::VAR Array::values(Nectar::VAR* args, int _length) const { return Nectar::Global::undefined; }
	
} // namespace Nectar::Class
