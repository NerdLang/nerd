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
#include "object_header.h"
#include <limits>

namespace NectarCore::Class
{
	NectarCore::VAR __proxy;
	// Constructors
	Object::Object() { }
	// Methods
	inline void Object::Delete() noexcept
	{
		if (--counter == 0)
		{
			delete this;
		}
	}
	inline void Object::jsDelete(const std::string _key) noexcept
	{
		#ifndef __Nectar__OBJECT_VECTOR
			object.erase(_key);
		#else
			for (NectarCore::Type::object_t::iterator it = object.begin() ; it != object.end(); ++it)
			{
				if (_key.compare(it->first) == 0)
				{
					object.erase(it);
					return;
				}
			}
		#endif
	}
	inline void* Object::Copy() noexcept
	{
		counter++;
		return this;
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
	NectarCore::VAR const Object::operator[](NectarCore::VAR key) const
	{
		return NectarCore::Global::undefined;
	}
	
	#ifndef __Nectar__OBJECT_VECTOR
	NectarCore::VAR &Object::operator[](NectarCore::VAR key)
	{
		std::string _str = ((std::string)key);
		NectarCore::Type::StringView _sview = _str;
		
		NectarCore::VAR& _obj = object[_str];
		if(_obj.type != NectarCore::Enum::Type::Undefined) 
		{
			if(!property[1])
			{
				if(!property[0]) return _obj;
				else 
				{
					__proxy = _obj;
					return __proxy;
				}
				
			}
			else 
			{
				if(_obj.type == NectarCore::Enum::Type::Function)
				{
					((NectarCore::Class::Function*)_obj.data.ptr)->This.type = NectarCore::Enum::Type::Object;
					((NectarCore::Class::Function*)_obj.data.ptr)->This.data.ptr = this;
				}
				if(!property[0]) return _obj;
				else 
				{
					__proxy = _obj;
					return __proxy;
				}
			}
		}

		if(_sview.compare("toString") == 0  || _sview.compare("toLocaleString") == 0)
		{
			object[_str] = __Nectar_Create_Var_Scoped_Anon( return __Nectar_Object_Stringify(this););
		}
		else if(_sview.compare("valueOf") == 0)
		{
			object[_str] = __Nectar_Create_Var_Scoped_Anon( return this; );
		}

		if(!property[0]) return _obj;
		__proxy = NectarCore::Global::undefined;
		return __proxy;
	}
	#else
	NectarCore::VAR &Object::operator[](NectarCore::VAR key)
	{
		std::string _str = ((std::string)key);
		NectarCore::Type::StringView _sview = _str;
		
		if (key.type == NectarCore::Enum::Type::Number)
		{
			auto i = (int)key;
			
			if (i < 0)
			{
				return NectarCore::Global::undefined;
			}
			else 
			{
				if (i >= object.size())
				{
					object.reserve(i + 1);
					object.resize(i + 1);
				}
			}
			return object[i].second;
		}
		
		for (auto & search : object)
		{
			if (_sview.compare(search.first) == 0)
			{
				if(!property[1])
				{
					return search.second;
				}
				else 
				{
					if(search.second.type == NectarCore::Enum::Type::Function)
					{
						((NectarCore::Class::Function*)search.second.data.ptr)->This.type = NectarCore::Enum::Type::Object;
						((NectarCore::Class::Function*)search.second.data.ptr)->This.data.ptr = this;				
					}
					
					return search.second;
				}
			}
		}

		if(_sview.compare("toString") == 0  || _sview.compare("toLocaleString") == 0)
		{
			object.push_back(NectarCore::Type::pair_t(_str, __Nectar_Create_Var_Scoped_Anon( return __Nectar_Object_Stringify(this);)));
		}
		else if(_sview.compare("valueOf") == 0)
		{
			object.push_back(NectarCore::Type::pair_t(_str, __Nectar_Create_Var_Scoped_Anon( return this; )));
		}
		else 
		{
			object.push_back(NectarCore::Type::pair_t(_str, NectarCore::Global::undefined));
		}

		return object[object.size() - 1].second;
	}
	#endif
	
	#ifndef __Nectar__OBJECT_VECTOR
	NectarCore::VAR &Object::operator[](int key)
	{
		std::string _str = std::to_string(key);
		NectarCore::Type::StringView _sview = _str;
		
		NectarCore::VAR& _obj = object[_str];
		if(_obj.type != NectarCore::Enum::Type::Undefined) 
		{
			if(!property[1])
			{
				if(!property[0]) return _obj;
				else 
				{
					__proxy = _obj;
					return __proxy;
				}
				
			}
			else 
			{
				if(_obj.type == NectarCore::Enum::Type::Function)
				{
					((NectarCore::Class::Function*)_obj.data.ptr)->This.type = NectarCore::Enum::Type::Object;
					((NectarCore::Class::Function*)_obj.data.ptr)->This.data.ptr = this;
				}
				if(!property[0]) return _obj;
				else 
				{
					__proxy = _obj;
					return __proxy;
				}
			}
		}

		if(_sview.compare("toString") == 0  || _sview.compare("toLocaleString") == 0)
		{
			object[_str] = __Nectar_Create_Var_Scoped_Anon( return __Nectar_Object_Stringify(this););
		}
		else if(_sview.compare("valueOf") == 0)
		{
			object[_str] = __Nectar_Create_Var_Scoped_Anon( return this; );
		}

		if(!property[0]) return _obj;
		__proxy = NectarCore::Global::undefined;
		return __proxy;
	}
	#else
	NectarCore::VAR &Object::operator[](int key)
	{
		std::string _str = std::to_string(key);
		NectarCore::Type::StringView _sview = _str;
		
		for (auto & search : object)
		{
			if (_sview.compare(search.first) == 0)
			{
				if(!property[1])
				{
					return search.second;
				}
				else 
				{
					if(search.second.type == NectarCore::Enum::Type::Function)
					{
						((NectarCore::Class::Function*)search.second.data.ptr)->This.type = NectarCore::Enum::Type::Object;
						((NectarCore::Class::Function*)search.second.data.ptr)->This.data.ptr = this;				
					}
					
					return search.second;
				}
			}
		}

		if(_sview.compare("toString") == 0  || _sview.compare("toLocaleString") == 0)
		{
			object.push_back(NectarCore::Type::pair_t(_str, __Nectar_Create_Var_Scoped_Anon( return __Nectar_Object_Stringify(this);)));
		}
		else if(_sview.compare("valueOf") == 0)
		{
			object.push_back(NectarCore::Type::pair_t(_str, __Nectar_Create_Var_Scoped_Anon( return this; )));
		}
		else 
		{
			object.push_back(NectarCore::Type::pair_t(_str, NectarCore::Global::undefined));
		}

		return object[object.size() - 1].second;
	}
	#endif
	
	#ifndef __Nectar__OBJECT_VECTOR
	NectarCore::VAR &Object::operator[](double key)
	{
		std::string _str = std::to_string(key);
		NectarCore::Type::StringView _sview = _str;
		
		NectarCore::VAR& _obj = object[_str];
		if(_obj.type != NectarCore::Enum::Type::Undefined) 
		{
			if(!property[1])
			{
				if(!property[0]) return _obj;
				else 
				{
					__proxy = _obj;
					return __proxy;
				}
			}
			else 
			{
				if(_obj.type == NectarCore::Enum::Type::Function)
				{
					((NectarCore::Class::Function*)_obj.data.ptr)->This.type = NectarCore::Enum::Type::Object;
					((NectarCore::Class::Function*)_obj.data.ptr)->This.data.ptr = this;
				}
				if(!property[0]) return _obj;
				else 
				{
					__proxy = _obj;
					return __proxy;
				}
			}
		}

		if(_sview.compare("toString") == 0  || _sview.compare("toLocaleString") == 0)
		{
			object[_str] = __Nectar_Create_Var_Scoped_Anon( return __Nectar_Object_Stringify(this););
		}
		else if(_sview.compare("valueOf") == 0)
		{
			object[_str] = __Nectar_Create_Var_Scoped_Anon( return this; );
		}

		if(!property[0]) return _obj;
		__proxy = NectarCore::Global::undefined;
		return __proxy;
	}
	#else
	NectarCore::VAR &Object::operator[](double key)
	{
		std::string _str = std::to_string(key);
		NectarCore::Type::StringView _sview = _str;
		
		for (auto & search : object)
		{
			if (_sview.compare(search.first) == 0)
			{
				if(!property[1])
				{
					return search.second;
				}
				else 
				{
					if(search.second.type == NectarCore::Enum::Type::Function)
					{
						((NectarCore::Class::Function*)search.second.data.ptr)->This.type = NectarCore::Enum::Type::Object;
						((NectarCore::Class::Function*)search.second.data.ptr)->This.data.ptr = this;				
					}
					
					return search.second;
				}
			}
		}

		if(_sview.compare("toString") == 0  || _sview.compare("toLocaleString") == 0)
		{
			object.push_back(NectarCore::Type::pair_t(_str, __Nectar_Create_Var_Scoped_Anon( return __Nectar_Object_Stringify(this);)));
		}
		else if(_sview.compare("valueOf") == 0)
		{
			object.push_back(NectarCore::Type::pair_t(_str, __Nectar_Create_Var_Scoped_Anon( return this; )));
		}
		else 
		{
			object.push_back(NectarCore::Type::pair_t(_str, NectarCore::Global::undefined));
		}

		return object[object.size() - 1].second;
	}
	#endif
	
	#ifndef __Nectar__OBJECT_VECTOR
	NectarCore::VAR &Object::operator[](const char* key)
	{
		std::string _str = key;
		NectarCore::Type::StringView _sview = _str;
		
		NectarCore::VAR& _obj = object[_str];
		if(_obj.type != NectarCore::Enum::Type::Undefined) 
		{
			if(!property[1])
			{
				if(!property[0]) return _obj;
				else 
				{
					__proxy = _obj;
					return __proxy;
				}
			}
			else 
			{
				if(_obj.type == NectarCore::Enum::Type::Function)
				{
					((NectarCore::Class::Function*)_obj.data.ptr)->This.type = NectarCore::Enum::Type::Object;
					((NectarCore::Class::Function*)_obj.data.ptr)->This.data.ptr = this;
				}
				if(!property[0]) return _obj;
				else 
				{
					__proxy = _obj;
					return __proxy;
				}
			}
		}

		if(_sview.compare("toString") == 0  || _sview.compare("toLocaleString") == 0)
		{
			object[_str] = __Nectar_Create_Var_Scoped_Anon( return __Nectar_Object_Stringify(this););
		}
		else if(_sview.compare("valueOf") == 0)
		{
			object[_str] = __Nectar_Create_Var_Scoped_Anon( return this; );
		}

		if(!property[0]) return _obj;
		__proxy = NectarCore::Global::undefined;
		return __proxy;
	}
	#else
	NectarCore::VAR &Object::operator[](const char* key)
	{
		std::string _str = key;
		NectarCore::Type::StringView _sview = _str;

		for (auto & search : object)
		{
			if (_sview.compare(search.first) == 0)
			{
				if(!property[1])
				{
					return search.second;
				}
				else 
				{
					if(search.second.type == NectarCore::Enum::Type::Function)
					{
						((NectarCore::Class::Function*)search.second.data.ptr)->This.type = NectarCore::Enum::Type::Object;
						((NectarCore::Class::Function*)search.second.data.ptr)->This.data.ptr = this;				
					}
					
					return search.second;
				}
			}
		}

		if(_sview.compare("toString") == 0  || _sview.compare("toLocaleString") == 0)
		{
			object.push_back(NectarCore::Type::pair_t(_str, __Nectar_Create_Var_Scoped_Anon( return __Nectar_Object_Stringify(this);)));
		}
		else if(_sview.compare("valueOf") == 0)
		{
			object.push_back(NectarCore::Type::pair_t(_str, __Nectar_Create_Var_Scoped_Anon( return this; )));
		}
		else 
		{
			object.push_back(NectarCore::Type::pair_t(_str, NectarCore::Global::undefined));
		}

		return object[object.size() - 1].second;
	}
	#endif
	
	// Comparation operators
	Object Object::operator!() const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	bool Object::operator==(const Object &_v1) const { return false; }
	// === emulated with __Nectar_EQUAL_VALUE_AND_TYPE
	// !== emulated with __Nectar_NOT_EQUAL_VALUE_AND_TYPE
	bool Object::operator!=(const Object &_v1) const { return true; }
	bool Object::operator<(const Object &_v1) const { return false; }
	bool Object::operator<=(const Object &_v1) const { return true; }
	bool Object::operator>(const Object &_v1) const { return false; }
	bool Object::operator>=(const Object &_v1) const { return true; }
	// Numeric operators
	Object Object::operator+() const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator-() const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator++(const int _v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator--(const int _v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator+(const Object &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator+=(const Object &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator-(const Object &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator-=(const Object &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator*(const Object &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator*=(const Object &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	// TODO: "**" and "**=" operators
	Object Object::operator/(const Object &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator/=(const Object &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator%(const Object &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator%=(const Object &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator&(const Object &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator|(const Object &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator^(const Object &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator~() const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator>>(const Object &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator<<(const Object &_v1) const 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator&=(const Object &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator|=(const Object &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator^=(const Object &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator>>=(const Object &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	Object Object::operator<<=(const Object &_v1) 
	{
		#if !defined(__Nectar_ENV_ARDUINO) && !defined(__Nectar_ENV_ESP32)
		throw InvalidTypeException();
		#endif
		return Object();
	}
	// TODO: ">>>" and ">>>=" operators
} // namespace NectarCore::Class
