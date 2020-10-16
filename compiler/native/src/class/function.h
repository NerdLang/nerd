#pragma once
#include "function_header.h"
#include <functional>
#include <limits>

namespace NJS::Class
{
	// Constructors
	Function::Function(){}
	Function::Function(void *val)
	{
		counter++;
		value = (NJS::Type::function_t*)val;
	}
	Function::Function(void *val, NJS::VAR bind)
	{
		counter++;
		This = bind;
		value = (NJS::Type::function_t*)val;
	}
	// Methods
	inline void Function::Delete() noexcept
	{
		if (--counter == 0)
		{
			delete (NJS::Type::function_t*)value;
			delete this;
		}
	}
	inline void Function::jsDelete(const std::string _key) noexcept
	{
		#ifdef __NJS__OBJECT_HASHMAP
			object.erase(_key);
		#else
			for (NJS::Type::object_t::iterator it = object.begin() ; it != object.end(); ++it)
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
		#ifdef __NJS_DEBUG
		return code;
		#else 
		return "[native code]";
		#endif
	}
	// Main operators
	NJS::VAR const Function::operator[](NJS::VAR key) const
	{
		return undefined;
	}
	
	#ifdef __NJS__OBJECT_HASHMAP
	NJS::VAR &Function::operator[](NJS::VAR key)
	{
		NJS::VAR& _obj = object[(std::string)key];
		if(_obj) return _obj; 
		
		__NJS_Object_Lazy_Loader("prototype");
		
		__NJS_Method_Lazy_Loader("toString", toString);
		__NJS_Method_Lazy_Loader("valueOf", valueOf);
		__NJS_Method_Lazy_Loader("bind", bind);
		__NJS_Method_Lazy_Loader("call", call);
		__NJS_Method_Lazy_Loader("apply", apply);
		
		return _obj;
	}
	#else
	NJS::VAR &Function::operator[](NJS::VAR key)
	{
		for (auto & search : object)
		{
			if (((std::string)key).compare(search.first) == 0)
			{
				return search.second;
			}
		}
		
		__NJS_Object_Lazy_Loader("prototype");
		
		__NJS_Method_Lazy_Loader("toString", toString);
		__NJS_Method_Lazy_Loader("valueOf", valueOf);
		__NJS_Method_Lazy_Loader("bind", bind);
		__NJS_Method_Lazy_Loader("call", call);
		__NJS_Method_Lazy_Loader("apply", apply);
		
		object.push_back(NJS::Type::pair_t((std::string)key, undefined));
		return object[object.size() - 1].second;
	}
	#endif
	
	NJS::VAR Function::Call(var& __NJS_THIS, NJS::VAR* _args, int i)
	{
		return (*static_cast<NJS::Type::function_t *>(value))(__NJS_THIS, _args, i);
	}
	
	
	template <class... Args>
	NJS::VAR Function::New(Args... args)
	{
		NJS::VAR _args[] = {args...};
		int i = sizeof...(args);
		
		NJS::VAR _this = __NJS_Object_Clone((*this)["prototype"]);
		if(_this.type == NJS::Enum::Type::Undefined) _this = __NJS_Create_Object();
		
		var _ret = this->Call(_this, _args, i);

		if(_ret.type == NJS::Enum::Type::Object)
		{
			((NJS::Class::Object*)_ret._ptr)->prototype = true;
			((NJS::Class::Object*)_ret._ptr)->instance.push_back((*this)["prototype"]._ptr);
			return _ret;
		}
		else
		{
			((NJS::Class::Object*)_this._ptr)->prototype = true;
			((NJS::Class::Object*)_this._ptr)->instance.push_back((*this)["prototype"]._ptr);
			return _this;
		}

	}
	
	template <class... Args>
	NJS::VAR Function::operator()(Args... args)
	{
		NJS::VAR _args[] = {args...};
		int i = sizeof...(args);
		return (*static_cast<NJS::Type::function_t *>(value))(This, _args, i);
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
	NJS::VAR Function::toString(NJS::VAR* _args, int _length) const
	{
		return (std::string)*this;
	}
	
	NJS::VAR Function::valueOf(NJS::VAR* _args, int _length) const
	{
		// TODO return this
		return undefined;
	}
	NJS::VAR Function::bind(NJS::VAR* _args, int _length)
	{
		return __NJS_Create_Var_Scoped_Anon(
		counter++;
		var _bind;
		if(_length > 0)
		{
			_bind = _args[0];
		}
		var _binded = new NJS::Class::Function(value, _bind);
		return _binded;
		);
	}
	
	NJS::VAR Function::call(NJS::VAR* _args, int _length)
	{
		NJS::VAR __THIS;
		if(_length > 0)
		{
			__THIS = _args[0];
			_length--;
		}
		NJS::VAR _newArgs[_length];
		for(int i = 1; i < _length; i++) _newArgs[i-1] = _args[i];
		
		return Call(__THIS, _newArgs, _length);
	}
	
	NJS::VAR Function::apply(NJS::VAR* _args, int _length)
	{
		NJS::VAR __THIS;
		if(_length > 0)
		{
			__THIS = _args[0];
			_length--;
		}
		
		if(_length > 0)
		{
			NJS::VAR _arr = _args[1];
			if(_arr.type == NJS::Enum::Type::Array)
			{
				NJS::Type::vector_t _v = ((NJS::Class::Array*)_arr._ptr)->value;
				NJS::VAR __ARGS[_v.size()];
				int i = 0;
				for( auto _var: _v)
				{
					__ARGS[i] = _var;
					i++;
				}
				return Call(__THIS, __ARGS, i);
			}
		}
		
		NJS::VAR __ARGS[0];
		return Call(__THIS, __ARGS, 0);
	}
} // namespace NJS::Class
