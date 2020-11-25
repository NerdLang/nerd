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
#include "function_header.h"
#include <functional>
#include <limits>

namespace Nectar::Class
{
	// Constructors
	Function::Function(){}
	Function::Function(void *val)
	{
		counter++;
		value = (Nectar::Type::function_t*)val;
	}
	Function::Function(void *val, Nectar::VAR bind)
	{
		counter++;
		This = bind;
		value = (Nectar::Type::function_t*)val;
	}
	// Methods
	inline void Function::Delete() noexcept
	{
		if (--counter == 0)
		{
			delete (Nectar::Type::function_t*)value;
			delete this;
		}
	}
	inline void Function::jsDelete(const std::string _key) noexcept
	{
		#ifndef __Nectar__OBJECT_VECTOR
			object.erase(_key);
		#else
			for (Nectar::Type::object_t::iterator it = object.begin() ; it != object.end(); ++it)
			{
				if (_key.compare(it->first) == 0)
				{
					object.erase(it);
					return;
				}
			}
		#endif
	}
	inline void* Function::Copy() noexcept
	{
		counter++;
		return this;
	}
	// Native cast
	Function::operator bool() const noexcept { return true; }
	Function::operator double() const noexcept
	{
		return std::numeric_limits<double>::quiet_NaN();
	}
	Function::operator int() const noexcept
	{
		return std::numeric_limits<int>::quiet_NaN();
	}
	Function::operator long long() const noexcept
	{
		return std::numeric_limits<long long>::quiet_NaN();
	}
	Function::operator std::string() const noexcept
	{
		#ifdef __Nectar_DEBUG
		return code;
		#else 
		return "[native code]";
		#endif
	}
	// Main operators
	Nectar::VAR const Function::operator[](Nectar::VAR key) const
	{
		return Nectar::Global::undefined;
	}
	
	#ifndef __Nectar__OBJECT_VECTOR
	Nectar::VAR &Function::operator[](Nectar::VAR key)
	{
		std::string _str = ((std::string)key);
		Nectar::Type::StringView _sview = _str;
		
		Nectar::VAR& _obj = object[_str];
		if(_obj.type != Nectar::Enum::Type::Undefined) return _obj; 		
		
		__Nectar_Object_Lazy_Loader("prototype");
		
		__Nectar_Method_Lazy_Loader("toString", toString);
		__Nectar_Method_Lazy_Loader("valueOf", valueOf);
		__Nectar_Method_Lazy_Loader("bind", bind);
		__Nectar_Method_Lazy_Loader("call", call);
		__Nectar_Method_Lazy_Loader("apply", apply);
		
		return _obj;
	}
	#else
	Nectar::VAR &Function::operator[](Nectar::VAR key)
	{
		std::string _str = ((std::string)key);
		Nectar::Type::StringView _sview = _str;
		
		for (auto & search : object)
		{
			if (_sview.compare(search.first) == 0)
			{
				return search.second;
			}
		}
		
		__Nectar_Object_Lazy_Loader("prototype");
		
		__Nectar_Method_Lazy_Loader("toString", toString);
		__Nectar_Method_Lazy_Loader("valueOf", valueOf);
		__Nectar_Method_Lazy_Loader("bind", bind);
		__Nectar_Method_Lazy_Loader("call", call);
		__Nectar_Method_Lazy_Loader("apply", apply);
		
		object.push_back(Nectar::Type::pair_t(_str, Nectar::Global::undefined));
		return object[object.size() - 1].second;
	}
	#endif
	
	#ifndef __Nectar__OBJECT_VECTOR
	Nectar::VAR &Function::operator[](int key)
	{
		std::string _str = std::to_string(key);
		Nectar::Type::StringView _sview = _str;
		
		Nectar::VAR& _obj = object[_str];
		if(_obj.type != Nectar::Enum::Type::Undefined) return _obj; 		
		
		__Nectar_Object_Lazy_Loader("prototype");
		
		__Nectar_Method_Lazy_Loader("toString", toString);
		__Nectar_Method_Lazy_Loader("valueOf", valueOf);
		__Nectar_Method_Lazy_Loader("bind", bind);
		__Nectar_Method_Lazy_Loader("call", call);
		__Nectar_Method_Lazy_Loader("apply", apply);
		
		return _obj;
	}
	#else
	Nectar::VAR &Function::operator[](int key)
	{
		std::string _str = std::to_string(key);
		Nectar::Type::StringView _sview = _str;
		
		for (auto & search : object)
		{
			if (_sview.compare(search.first) == 0)
			{
				return search.second;
			}
		}
		
		__Nectar_Object_Lazy_Loader("prototype");
		
		__Nectar_Method_Lazy_Loader("toString", toString);
		__Nectar_Method_Lazy_Loader("valueOf", valueOf);
		__Nectar_Method_Lazy_Loader("bind", bind);
		__Nectar_Method_Lazy_Loader("call", call);
		__Nectar_Method_Lazy_Loader("apply", apply);
		
		object.push_back(Nectar::Type::pair_t(_str, Nectar::Global::undefined));
		return object[object.size() - 1].second;
	}
	#endif
	
	#ifndef __Nectar__OBJECT_VECTOR
	Nectar::VAR &Function::operator[](double key)
	{
		std::string _str = std::to_string(key);
		Nectar::Type::StringView _sview = _str;
		
		Nectar::VAR& _obj = object[_str];
		if(_obj.type != Nectar::Enum::Type::Undefined) return _obj; 		
		
		__Nectar_Object_Lazy_Loader("prototype");
		
		__Nectar_Method_Lazy_Loader("toString", toString);
		__Nectar_Method_Lazy_Loader("valueOf", valueOf);
		__Nectar_Method_Lazy_Loader("bind", bind);
		__Nectar_Method_Lazy_Loader("call", call);
		__Nectar_Method_Lazy_Loader("apply", apply);
		
		return _obj;
	}
	#else
	Nectar::VAR &Function::operator[](double key)
	{
		std::string _str = std::to_string(key);
		Nectar::Type::StringView _sview = _str;
		
		for (auto & search : object)
		{
			if (_sview.compare(search.first) == 0)
			{
				return search.second;
			}
		}
		
		__Nectar_Object_Lazy_Loader("prototype");
		
		__Nectar_Method_Lazy_Loader("toString", toString);
		__Nectar_Method_Lazy_Loader("valueOf", valueOf);
		__Nectar_Method_Lazy_Loader("bind", bind);
		__Nectar_Method_Lazy_Loader("call", call);
		__Nectar_Method_Lazy_Loader("apply", apply);
		
		object.push_back(Nectar::Type::pair_t(_str, Nectar::Global::undefined));
		return object[object.size() - 1].second;
	}
	#endif
	
	#ifndef __Nectar__OBJECT_VECTOR
	Nectar::VAR &Function::operator[](const char* key)
	{
		std::string _str = key;
		Nectar::Type::StringView _sview = _str;
		
		Nectar::VAR& _obj = object[_str];
		if(_obj.type != Nectar::Enum::Type::Undefined) return _obj; 		
		
		__Nectar_Object_Lazy_Loader("prototype");
		
		__Nectar_Method_Lazy_Loader("toString", toString);
		__Nectar_Method_Lazy_Loader("valueOf", valueOf);
		__Nectar_Method_Lazy_Loader("bind", bind);
		__Nectar_Method_Lazy_Loader("call", call);
		__Nectar_Method_Lazy_Loader("apply", apply);
		
		return _obj;
	}
	#else
	Nectar::VAR &Function::operator[](const char* key)
	{
		std::string _str = key;
		Nectar::Type::StringView _sview = _str;
		
		for (auto & search : object)
		{
			if (_sview.compare(search.first) == 0)
			{
				return search.second;
			}
		}
		
		__Nectar_Object_Lazy_Loader("prototype");
		
		__Nectar_Method_Lazy_Loader("toString", toString);
		__Nectar_Method_Lazy_Loader("valueOf", valueOf);
		__Nectar_Method_Lazy_Loader("bind", bind);
		__Nectar_Method_Lazy_Loader("call", call);
		__Nectar_Method_Lazy_Loader("apply", apply);
		
		object.push_back(Nectar::Type::pair_t(_str, Nectar::Global::undefined));
		return object[object.size() - 1].second;
	}
	#endif
	
	// Comparation operators
	Nectar::VAR Function::operator!() const 
	{
		return __Nectar_Boolean_FALSE;
	}
	bool Function::operator==(const Function &_v1) const { return false; }
	// === emulated with __Nectar_EQUAL_VALUE_AND_TYPE
	// !== emulated with __Nectar_NOT_EQUAL_VALUE_AND_TYPE
	bool Function::operator!=(const Function &_v1) const { return true; }
	bool Function::operator<(const Function &_v1) const { return false; }
	bool Function::operator<=(const Function &_v1) const { return true; }
	bool Function::operator>(const Function &_v1) const { return false; }
	bool Function::operator>=(const Function &_v1) const { return true; }
	// Numeric operators
	Function Function::operator+() const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator-() const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator++(const int _v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator--(const int _v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator+(const Function &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator+=(const Function &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator-(const Function &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator-=(const Function &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator*(const Function &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator*=(const Function &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	// TODO: "**" and "**=" operators
	Function Function::operator/(const Function &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator/=(const Function &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator%(const Function &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator%=(const Function &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator&(const Function &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator|(const Function &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator^(const Function &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator~() const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator>>(const Function &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator<<(const Function &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator&=(const Function &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator|=(const Function &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator^=(const Function &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator>>=(const Function &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	Function Function::operator<<=(const Function &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Function();
	}
	// TODO: ">>>" and ">>>=" operators
	Nectar::VAR Function::toString(Nectar::VAR* _args, int _length) const
	{
		return (std::string)*this;
	}
	
	Nectar::VAR Function::valueOf(Nectar::VAR* _args, int _length) const
	{
		// TODO return this
		return Nectar::Global::undefined;
	}
	Nectar::VAR Function::bind(Nectar::VAR* _args, int _length)
	{
		return __Nectar_Create_Var_Scoped_Anon(
		counter++;
		Nectar::VAR _bind;
		if(_length > 0)
		{
			_bind = _args[0];
		}
		Nectar::VAR _binded = new Nectar::Class::Function(value, _bind);
		return _binded;
		);
	}
	
	Nectar::VAR Function::call(Nectar::VAR* _args, int _length)
	{
		Nectar::VAR __THIS;
		if(_length > 0)
		{
			__THIS = _args[0];
			_length--;
		}
		Nectar::VAR _newArgs[_length];
		for(int i = 1; i < _length; i++) _newArgs[i-1] = _args[i];
		
		return Call(__THIS, _newArgs, _length);
	}
	
	Nectar::VAR Function::apply(Nectar::VAR* _args, int _length)
	{
		Nectar::VAR __THIS;
		if(_length > 0)
		{
			__THIS = _args[0];
			_length--;
		}
		
		if(_length > 0)
		{
			Nectar::VAR _arr = _args[1];
			if(_arr.type == Nectar::Enum::Type::Array)
			{
				Nectar::Type::vector_t _v = ((Nectar::Class::Array*)_arr.data.ptr)->value;
				Nectar::VAR __ARGS[_v.size()];
				int i = 0;
				for( auto _var: _v)
				{
					__ARGS[i] = _var;
					i++;
				}
				return Call(__THIS, __ARGS, i);
			}
		}
		
		Nectar::VAR __ARGS[0];
		return Call(__THIS, __ARGS, 0);
	}
} // namespace Nectar::Class
