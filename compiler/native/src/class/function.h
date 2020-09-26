#pragma once
#include "function_header.h"
#include <functional>
#include <limits>

namespace NJS::Class
{
	// Constructors
	Function::Function()
	{ 
		counter++; 
		object.push_back(NJS::Type::pair_t("prototype", __NJS_Create_Object()));
	}
	Function::Function(void *val)
	{
		counter++;
		object.push_back(NJS::Type::pair_t("prototype", __NJS_Create_Object()));
		value = (NJS::Type::function_t*)val;
	}
	// Methods
	void Function::Delete() noexcept
	{
		if (--counter < 1)
		{
			delete (NJS::Type::function_t*)value;
			delete this;
		}
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
		return code;
	}
	// Main operators
	NJS::VAR const Function::operator[](NJS::VAR key) const
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
	NJS::VAR &Function::operator[](NJS::VAR key)
	{
		for (auto & search : object)
		{
			if (((std::string)key).compare(search.first) == 0)
			{
				return search.second;
			}
		}
		
		if(((std::string)key).compare("toString") == 0  || ((std::string)key).compare("toLocaleString") == 0)
		{
			object.push_back(NJS::Type::pair_t((std::string)key, __NJS_Create_Var_Scoped_Anon( return (std::string)*this;)));
		}
		else if(((std::string)key).compare("valueOf") == 0)
		{
			object.push_back(NJS::Type::pair_t((std::string)key, __NJS_Create_Var_Scoped_Anon( return this; )));
		}
		else if(((std::string)key).compare("call") == 0)
		{
			object.push_back(NJS::Type::pair_t((std::string)key, __NJS_Create_Var_Scoped_Anon(
				counter++;
				NJS::VAR __THIS;
				if(__NJS_VARARGS.size() > 0)
				{
					__THIS = __NJS_VARARGS[0];
					__NJS_VARARGS.erase(__NJS_VARARGS.begin());
				}
				return Call(__THIS, __NJS_VARARGS);
			)));
		}
		else object.push_back(NJS::Type::pair_t((std::string)key, __NJS_VAR()));
		
		return object[object.size() - 1].second;
	}
	
	NJS::VAR Function::Call(var __NJS_THIS, NJS::Type::vector_t __NJS_VARARGS)
	{
		NJS::VAR _result = (*static_cast<std::function<NJS::VAR(var, NJS::Type::vector_t)> *>(value))(__NJS_THIS, __NJS_VARARGS);
		((NJS::Class::Object*)__NJS_THIS._ptr)->counter--;
		return _result;
	}
	
	
	template <class... Args>
	NJS::VAR Function::New(Args... args)
	{
		NJS::Type::vector_t _args = NJS::Type::vector_t{(NJS::VAR)args...};
		
		NJS::VAR _this = __NJS_Create_Object();
		NJS::Type::object_t object = ((NJS::Class::Object*)(*this)["prototype"]._ptr)->object;
		
		for (auto & search : object)
		{
			_this[search.first] = search.second;
		}

		var _ret = this->Call(_this, _args);
		
		if(_ret.type == NJS::Enum::Type::Object)
		{
			((NJS::Class::Object*)_ret._ptr)->prototype = true;
			((NJS::Class::Object*)_ret._ptr)->instance.push_back((*this)["prototype"]._ptr);
			return _ret;
		}
		else
		{
			((NJS::Class::Base*)_ret._ptr)->Delete();
			((NJS::Class::Object*)_this._ptr)->prototype = true;
			((NJS::Class::Object*)_this._ptr)->instance.push_back((*this)["prototype"]._ptr);
			return _this;
		}

	}
	
	template <class... Args>
	NJS::VAR Function::operator()(Args... args)
	{
		NJS::Type::vector_t _args = NJS::Type::vector_t{(NJS::VAR)args...};
		return (*static_cast<std::function<NJS::VAR(var, NJS::Type::vector_t)> *>(value))(This, _args);
	}
	// Comparation operators
	Function Function::operator!() const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	bool Function::operator==(const Function &_v1) const { return false; }
	// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
	// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
	bool Function::operator!=(const Function &_v1) const { return true; }
	bool Function::operator<(const Function &_v1) const { return false; }
	bool Function::operator<=(const Function &_v1) const { return true; }
	bool Function::operator>(const Function &_v1) const { return false; }
	bool Function::operator>=(const Function &_v1) const { return true; }
	// Numeric operators
	Function Function::operator+() const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Function Function::operator-() const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Function Function::operator++(const int _v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Function Function::operator--(const int _v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Function Function::operator+(const Function &_v1) const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Function Function::operator+=(const Function &_v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Function Function::operator-(const Function &_v1) const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Function Function::operator-=(const Function &_v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Function Function::operator*(const Function &_v1) const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Function Function::operator*=(const Function &_v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	// TODO: "**" and "**=" operators
	Function Function::operator/(const Function &_v1) const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Function Function::operator/=(const Function &_v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Function Function::operator%(const Function &_v1) const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Function Function::operator%=(const Function &_v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Function Function::operator&(const Function &_v1) const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Function Function::operator|(const Function &_v1) const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Function Function::operator^(const Function &_v1) const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Function Function::operator~() const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Function Function::operator>>(const Function &_v1) const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Function Function::operator<<(const Function &_v1) const 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Function Function::operator&=(const Function &_v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Function Function::operator|=(const Function &_v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Function Function::operator^=(const Function &_v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Function Function::operator>>=(const Function &_v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	Function Function::operator<<=(const Function &_v1) 
	{
		#ifndef __NJS_ARDUINO 
		throw InvalidTypeException();
		#endif
	}
	// TODO: ">>>" and ">>>=" operators
} // namespace NJS::Class
