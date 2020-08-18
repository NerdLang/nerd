#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <memory>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdarg.h>

#ifdef __NJS_ARDUINO
#include <util/delay.h>
#include <string.h>
#include <WString.h>
#include <new.h>
#include <time.h>
#include <nonstd-function.h>
using namespace nonstd;
#else
#include <functional>
#endif

#include "enum.h"
#include "values.h"
#include "classes.h"

using namespace std;
using namespace NJS;
using namespace NJS::Enum;

/*** HELPERS ***/
#define __NJS_GET_STRING(_var) _var.get().s->__NJS_VALUE
#define var __NJS_VAR
#define let __NJS_VAR
#define __NJS_Create_Boolean(_value) __NJS_VAR(Type::BOOLEAN, _value)
#define __NJS_Create_Number(_value) __NJS_VAR(_value)
#define __NJS_Create_Function(_value) __NJS_VAR(Type::FUNCTION, _value)
#define __NJS_Create_Undefined() __NJS_VAR()
#define __NJS_DECL_FUNCTION function
#define __NJS_RETURN_UNDEFINED \
	var __undef = __NJS_VAR(); \
	return __undef;
#define __NJS_Create_String(_value) __NJS_VAR(_value)
#define Infinity NJS::Value::Infinity
#define __NJS_Create_Null() __NJS_VAR(Type::_NULL, 0)
#define __NJS_Create_Lambda(name) function<__NJS_VAR (vector<var>)>* name = new function<__NJS_VAR (vector<var>)>([](vector<var> __NJS_VARARGS)
#define __NJS_EXCEPTION_PARAMETER __NJS_VAR &e
#define finally ;
/*** END HELPERS ***/


class Class::String
{
public:
	int cnt = 0;
	void Delete();
	Class::String(string _str);
	string __NJS_VALUE;
	vector<pair<const char *, __NJS_VAR>> __OBJECT;
};



class Class::Function
{
public:
	int cnt = 0;
	void Delete();
	Class::Function(void *_f);
	void *__NJS_VALUE;
	vector<pair<const char *, __NJS_VAR>> __OBJECT;
};

class Class::Native
{
public:
	int cnt = 0;
	void Delete();
	Class::Native(void *_n);
	void *__NJS_VALUE;
	vector<pair<const char *, __NJS_VAR>> __OBJECT;
};

union __NJS_VAL {
	int i;
	double d;
	bool b;
	Class::String *s;
	Class::Array *a;
	Class::Object *o;
	Class::Function *f;
	Class::Native *n;
};

/*** REGISTER ***/

int FREE_PTR = -1;
int REGISTER_PTR = 0;
#ifdef CL_WINDOWS
__NJS_VAL REGISTER[{{REGISTER}}];
#else
__NJS_VAL REGISTER[{{REGISTER}}]{(__NJS_VAL){.i = 0}};
#endif
int FREE[{{REGISTER}}] = {0};

/*** END REGISTER ***/

__NJS_VAR __NJS_Log_Console(__NJS_VAR _var);
__NJS_VAR __NJS_Object_Keys(__NJS_VAR _var);
__NJS_VAR __NJS_Object_Stringify(__NJS_VAR _var);
__NJS_VAR __NJS_Object_Stringify(__NJS_VAR _var, bool _bracket);
__NJS_VAR __NJS_Create_Object();
__NJS_VAR __NJS_Create_Array();
__NJS_VAR __NJS_Object_Clone(__NJS_VAR _var);
__NJS_VAR __NJS_Object_Set(const char *_index, __NJS_VAR _value, vector<pair<const char *, __NJS_VAR>> *_obj);
/*** STRING MANIPULATION ***/
template <typename m, typename n>
string __NJS_Concat_To_Str(m _left, n _right)
{
	std::stringstream output;
	output << _left << _right;
	return output.str();
}
/* END STRING MANIPULATION */

/*** NUMBER MANIPULATION ***/
template <typename m>
int __NJS_Str_To_Int(m _left)
{
	int out;
	std::stringstream output;
	output << _left;
	output >> out;
	return out;
}
template <typename m>
double __NJS_Str_To_Double(m _left)
{
	double out;
	std::stringstream output;
	output << _left;
	output >> out;
	return out;
}
/* END NUMBER MANIPULATION */

struct __NJS_VAR
{
private:
	void setPtr()
	{
		if (_ptr > -1)
		{
			return;
		}
		if (FREE_PTR > -1)
		{
			_ptr = FREE[FREE_PTR--];
		}
		else
		{
			_ptr = REGISTER_PTR++;
		}
	}

public:
	Type type;
	int _ptr = -1;

	inline __NJS_VAL get() const
	{
		return REGISTER[_ptr];
	}

	__NJS_VAR()
	{
		setPtr();
		type = Type::UNDEFINED;
		REGISTER[_ptr].i = 0;
	}

	~__NJS_VAR()
	{
		if (type == Type::OBJECT)
		{
			REGISTER[_ptr].o->Delete();
		}
		else if (type == Type::STRING)
		{
			REGISTER[_ptr].s->Delete();
		}
		else if (type == Type::FUNCTION)
		{
			REGISTER[_ptr].f->Delete();
		}
		else if (type == Type::ARRAY)
		{
			REGISTER[_ptr].a->Delete();
		}
		else if (type == Type::NATIVE)
		{
			REGISTER[_ptr].n->Delete();
		}
		FREE[++FREE_PTR] = _ptr;
	}

	/**/
	__NJS_VAR(__NJS_VAR const &_v)
	{
		setPtr();
		type = _v.type;
		REGISTER[_ptr] = REGISTER[_v._ptr];
		if (_v.type == Type::OBJECT)
		{
			REGISTER[_ptr].o->cnt++;
		}
		else if (_v.type == Type::STRING)
		{
			REGISTER[_ptr].s = new Class::String(REGISTER[_v._ptr].s->__NJS_VALUE);
		}
		else if (_v.type == Type::FUNCTION)
		{
			REGISTER[_ptr].f->cnt++;
		}
		else if (_v.type == Type::ARRAY)
		{
			REGISTER[_ptr].a->cnt++;
		}
		else if (_v.type == Type::NATIVE)
		{
			REGISTER[_ptr].n->cnt++;
		}
	}
	/**/

	/*** CONSTRUCTOR ***/

	__NJS_VAR(Type _type, int _value)
	{
		setPtr();
		this->type = _type;
		REGISTER[_ptr].i = _value;
	}

	__NJS_VAR(int _value)
	{
		setPtr();
		this->type = Type::NUMBER;
		REGISTER[_ptr].i = _value;
	}

	__NJS_VAR(double _value)
	{
		setPtr();
		this->type = Type::DOUBLE;
		REGISTER[_ptr].d = _value;
	}

	__NJS_VAR(char *_value)
	{
		setPtr();
		type = Type::STRING;
		REGISTER[_ptr].s = new Class::String(_value);
	}

	__NJS_VAR(string _value)
	{
		setPtr();
		type = Type::STRING;
		REGISTER[_ptr].s = new Class::String(_value);
	}

	__NJS_VAR(const char *_value)
	{
		setPtr();
		type = Type::STRING;
		REGISTER[_ptr].s = new Class::String(_value);
	}

	/*__NJS_VAR(Class::Array *_value)
	{
		setPtr();
		type = Type::ARRAY;
		REGISTER[_ptr].a = _value;
	}
	__NJS_VAR(Class::Object *_value)
	{
		setPtr();
		type = Type::OBJECT;
		REGISTER[_ptr].o = _value;
	}
	*/
	__NJS_VAR(Class::Native *_value)
	{
		setPtr();
		type = Type::NATIVE;
		REGISTER[_ptr].n = _value;
	}
	__NJS_VAR(Type _type, void *_value)
	{
		setPtr();
		type = _type;
		REGISTER[_ptr].f = new Class::Function(_value);
	}

	__NJS_VAR(function<__NJS_VAR(vector<var>)> &_value)
	{
		setPtr();
		type = Type::FUNCTION;
		REGISTER[_ptr].f = new Class::Function(&_value);
	}

	/*** VARIADIC LAMBDAS ***/
	template <class... Args>
	__NJS_VAR(function<__NJS_VAR(Args...)> &_value)
	{
		setPtr();
		type = Type::FUNCTION;
		REGISTER[_ptr].f = new Class::Function(&_value);
	}
	/*** END VARIADIC LAMBDAS ***/
	
	/*** OVERLOAD ***/
	// WIP
	
	__NJS_VAR operator() ()
	{
		return __NJS_VAR();
	}
	
	__NJS_VAR operator[] (__NJS_VAR _index) const
	{
		if (this->type != Type::ARRAY && this->type != Type::OBJECT && this->type != Type::STRING && this->type != Type::FUNCTION && this->type != Type::NATIVE)
		{
			__NJS_RETURN_UNDEFINED;
		}
		if (this->type == Type::ARRAY && _index.type == Type::NUMBER)
		{
			if ((int)_index > this->get().a->__NJS_VALUE.size())
			{
				__NJS_RETURN_UNDEFINED;
			}
			return this->get().a->__NJS_VALUE[(int)_index];
		}
		else
		{
			if (_index.type != Type::STRING)
			{
				__NJS_RETURN_UNDEFINED;
			}
			vector<pair<const char *, __NJS_VAR>> *_obj;
			if (this->type == Type::OBJECT)
				_obj = &this->get().o->__OBJECT;
			else if (this->type == Type::ARRAY)
				_obj = &this->get().a->__OBJECT;
			else if (this->type == Type::STRING)
				_obj = &this->get().s->__OBJECT;
			else if (this->type == Type::FUNCTION)
				_obj = &this->get().f->__OBJECT;
			else
			{
				__NJS_RETURN_UNDEFINED;
			}
			int _j = (*_obj).size();
			for (int _i = 0; _i < _j; _i++)
			{
				if (_index.get().s->__NJS_VALUE.compare((*_obj)[_i].first) == 0)
				{
					return (*_obj)[_i].second;
				}
			}
		}
		__NJS_RETURN_UNDEFINED;
	}
	
	__NJS_VAR & operator[] (__NJS_VAR _index)
	{
		if (this->type == Type::ARRAY && _index.type == Type::NUMBER)
		{

			if (this->get().a->__NJS_VALUE.size() <= _index.get().i)
			{
				this->get().a->__NJS_VALUE.reserve(_index.get().i + 1);
				this->get().a->__NJS_VALUE.resize(_index.get().i + 1);
			}

			return this->get().a->__NJS_VALUE.at(_index.get().i);

			__NJS_Object_Set("length", (int)this->get().a->__NJS_VALUE.size(), &this->get().a->__OBJECT);
		}
		else if (this->type == Type::OBJECT || this->type == Type::STRING || this->type == Type::FUNCTION || this->type == Type::ARRAY || this->type == Type::NATIVE)
		{
			vector<pair<const char *, __NJS_VAR>> *_obj;
			if (this->type == Type::OBJECT)
				_obj = &this->get().o->__OBJECT;
			else if (this->type == Type::ARRAY)
				_obj = &this->get().a->__OBJECT;
			else if (this->type == Type::STRING)
				_obj = &this->get().s->__OBJECT;
			else if (this->type == Type::FUNCTION)
				_obj = &this->get().f->__OBJECT;
			else
			{
				__NJS_RETURN_UNDEFINED;
			}

			_index.get().s->cnt++;
			__NJS_Object_Set(_index.get().s->__NJS_VALUE.c_str(), __NJS_VAR(), _obj);
			return (*this)[_index];
		}

		__NJS_RETURN_UNDEFINED;
	}
	
	/* END OVERLOAD */

	/*** END CONSTRUCTOR ***/

	/*** OPERATOR ***/
	__NJS_VAR operator=(const __NJS_VAR &_v)
	{
		if (type == Type::OBJECT)
			REGISTER[_ptr].o->Delete();
		else if (type == Type::STRING)
			REGISTER[_ptr].s->Delete();
		else if (type == Type::FUNCTION)
			REGISTER[_ptr].f->Delete();
		else if (type == Type::ARRAY)
			REGISTER[_ptr].a->Delete();
		else if (type == Type::NATIVE)
			REGISTER[_ptr].n->Delete();

		type = _v.type;
		;
		if (_v.type == Type::OBJECT)
		{
			REGISTER[_ptr] = REGISTER[_v._ptr];
			REGISTER[_ptr].o->cnt++;
		}
		else if (_v.type == Type::STRING)
		{
			REGISTER[_ptr].s = new Class::String((string)_v);
		}
		else if (_v.type == Type::FUNCTION)
		{
			REGISTER[_ptr] = REGISTER[_v._ptr];
			REGISTER[_ptr].f->cnt++;
		}
		else if (_v.type == Type::ARRAY)
		{
			REGISTER[_ptr] = REGISTER[_v._ptr];
			REGISTER[_ptr].a->cnt++;
		}
		else if (_v.type == Type::NATIVE)
		{
			REGISTER[_ptr] = REGISTER[_v._ptr];
			REGISTER[_ptr].n->cnt++;
		}
		else
			REGISTER[_ptr] = REGISTER[_v._ptr];

		return *this;
	}

	/// Unary operators
	__NJS_VAR operator+()
	{
		if (type == Type::NUMBER || type == Type::DOUBLE)
			return *this;
		else
			return (double)*this;
	}
	__NJS_VAR operator-()
	{
		if (type == Type::NUMBER)
			return -(int)*this;
		else
			return -(double)*this;
	}
	__NJS_VAR operator!() { return !(bool)*this; };

	/// Logical operators
	__NJS_VAR operator&&(const __NJS_VAR &_v1) { return (bool)*this && (bool)_v1; }
	__NJS_VAR operator||(const __NJS_VAR &_v1) { return (bool)*this || (bool)_v1; }

	/// Arithmetic operators
	__NJS_VAR operator+(const __NJS_VAR &_v1)
	{
		if (type == Type::STRING || type == Type::ARRAY || type == Type::OBJECT || _v1.type == Type::STRING)
			return __NJS_Concat_To_Str((string) * this, (string)_v1);
		else if (type == Type::NUMBER)
			return __NJS_VAR((int)*this + (int)_v1);
		else if (type == Type::DOUBLE)
			return __NJS_VAR((double)*this + (double)_v1);
		else return __NJS_VAR();
	}
	__NJS_VAR operator+(const char _v1[])
	{
		return __NJS_Concat_To_Str((string)*this, _v1);
	}
	__NJS_VAR operator+=(const __NJS_VAR &_v1)
	{
		if(type == Type::NUMBER) 
			REGISTER[_ptr].i += (int)_v1;
		else if(type == Type::DOUBLE) 
			REGISTER[_ptr].d += (double)_v1;
		else if(type == Type::STRING) 
			REGISTER[_ptr].s->__NJS_VALUE += (string)_v1;
		else 
		{
			string _s = (string)*this;
			type = Type::STRING;
			REGISTER[_ptr].s = new Class::String("");
			REGISTER[_ptr].s->__NJS_VALUE += _s + (string)_v1;
		}
		return *this;
	}
	__NJS_VAR operator-(const __NJS_VAR &_v1)
	{
		if (type == Type::NUMBER )
			return __NJS_VAR((int)*this - (int)_v1);
		else if (type == Type::DOUBLE )
			return __NJS_VAR((double)*this - (double)_v1);
		else return "NaN";
	}
	__NJS_VAR operator-=(const __NJS_VAR &_v1)
	{
		if(type == Type::NUMBER && _v1.type == Type::NUMBER) 
			REGISTER[_ptr].i -= (int)_v1;
		else if(type == Type::NUMBER && _v1.type == Type::DOUBLE) 
			REGISTER[_ptr].i -= (double)_v1;
		else if(type == Type::DOUBLE && _v1.type == Type::NUMBER) 
			REGISTER[_ptr].d -= (int)_v1;
		else if(type == Type::DOUBLE && _v1.type == Type::DOUBLE) 
			REGISTER[_ptr].d -= (double)_v1;
		else 
		{
			type = Type::_NAN;
			REGISTER[_ptr].s = new Class::String("NaN");
		}
		return *this;
	}
	__NJS_VAR operator*(const __NJS_VAR &_v1)
	{
		if(type == Type::NUMBER) 
			return REGISTER[_ptr].i * (int)_v1;
		else if(type == Type::DOUBLE) 
			return REGISTER[_ptr].d * (double)_v1;
		return __NJS_VAR();
	}
	__NJS_VAR operator*=(const __NJS_VAR &_v1)
	{
		if(type == Type::NUMBER) 
			REGISTER[_ptr].i *= (int)_v1;
		else if(type == Type::DOUBLE) 
			REGISTER[_ptr].d *= (double)_v1;
		return __NJS_VAR();
	}
	__NJS_VAR operator/(const __NJS_VAR &_v1)
	{
		if (type == Type::NUMBER)
			return REGISTER[_ptr].i / (int)_v1;
		else if (type == Type::DOUBLE)
			return REGISTER[_ptr].d / (double)_v1;
		return __NJS_VAR();
	}
	__NJS_VAR operator/=(const __NJS_VAR &_v1)
	{
		if(type == Type::NUMBER) 
			REGISTER[_ptr].i /= (int)_v1;
		else if(type == Type::DOUBLE) 
			REGISTER[_ptr].d /= (double)_v1.get().d;
		return __NJS_VAR();
	}
	__NJS_VAR operator%(const __NJS_VAR &_v1)
	{
		if (type == Type::NUMBER && _v1.type == Type::NUMBER)
			return REGISTER[_ptr].i % (int)_v1;
		else
			return remainder(REGISTER[_ptr].d, (double)_v1);
	}
	__NJS_VAR operator%=(const __NJS_VAR &_v1)
	{
		if (type == Type::NUMBER && _v1.type == Type::NUMBER)
		{
			REGISTER[_ptr].i %= (int)_v1;
		}
		else
		{
			type = Type::DOUBLE;
			REGISTER[_ptr].d = remainder((double)*this, (double)_v1);
		}
		return *this;
	}
	// TODO: "**" and "**=" operators
	__NJS_VAR operator++(const int _v1)
	{
		if (type == Type::NUMBER)
		{
			REGISTER[_ptr].i++;
		}
		else if (type == Type::DOUBLE)
		{
			REGISTER[_ptr].d++;
		}
		else
		{
			type = Type::DOUBLE;
			REGISTER[_ptr].d = (double)*this;
		}
		return *this;
	}
	__NJS_VAR operator--(const int _v1)
	{
		if (type == Type::NUMBER)
			REGISTER[_ptr].i--;
		else if (type == Type::DOUBLE)
			REGISTER[_ptr].d--;
		else
		{
			type = Type::DOUBLE;
			REGISTER[_ptr].d = (double)*this;
		}
		return *this;
	}

	/// Comparison operators
	__NJS_VAR operator==(const __NJS_VAR &_v1)
	{
		if (type == _v1.type)
		{
			switch (type)
			{
			case Type::NUMBER:
				return __NJS_Create_Boolean(REGISTER[_ptr].i == (int)_v1);
			case Type::DOUBLE:
				return __NJS_Create_Boolean(REGISTER[_ptr].d == (double)_v1);
			//case Type::BIGNUMBER: return __NJS_VAR((long)*this == (long)_v1);
			case Type::BOOLEAN:
				return __NJS_Create_Boolean(REGISTER[_ptr].b == (bool)_v1);
			case Type::STRING:
				return __NJS_Create_Boolean((REGISTER[_ptr].s->__NJS_VALUE).compare((string)_v1) == 0);
			case Type::_INFINITY:
			case Type::_NULL:
			case Type::UNDEFINED:
				return __NJS_Create_Boolean(true);
			case Type::ARRAY:
			case Type::NATIVE:
			case Type::FUNCTION:
			case Type::OBJECT:
			case Type::_NAN:
				return __NJS_Create_Boolean(false);
			}
		}
		else
		{
			if (type == Type::STRING || _v1.type == Type::STRING)
			{
				return __NJS_Create_Boolean((string) * this == (string)_v1);
			}
			else
				return __NJS_Create_Boolean((double)*this == (double)_v1);
		}
	}
	// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
	__NJS_VAR operator!=(const __NJS_VAR &_v1)
	{
		return !(*this == _v1);
	}
	
	// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
	__NJS_VAR operator<(const __NJS_VAR &_v1)
	{
		if (type == _v1.type && type == Type::NUMBER)
			return (int)*this < (int)_v1;
		else
			return (double)*this < (double)_v1;
	}
	__NJS_VAR operator<=(const __NJS_VAR &_v1)
	{
		if (type == _v1.type && type == Type::NUMBER)
			return (int)*this <= (int)_v1;
		else
			return (double)*this <= (double)_v1;
	}
	__NJS_VAR operator>(const __NJS_VAR &_v1)
	{
		if (type == _v1.type && type == Type::NUMBER)
			return (int)*this > (int)_v1;
		else
			return (double)*this > (double)_v1;
	}
	__NJS_VAR operator>=(const __NJS_VAR &_v1)
	{
		if (type == _v1.type && type == Type::NUMBER)
			return (int)*this >= (int)_v1;
		else
			return (double)*this >= (double)_v1;
	}

	/// Bitwise operators
	__NJS_VAR operator&(const __NJS_VAR &_v1) { return (int)*this & (int)_v1; }
	__NJS_VAR operator&=(const __NJS_VAR &_v1)
	{
		type = Type::NUMBER;
		REGISTER[_ptr].i = (int)*this & (int)_v1;
		return *this;
	}
	__NJS_VAR operator|(const __NJS_VAR &_v1) { return (int)*this | (int)_v1; }
	__NJS_VAR operator|=(const __NJS_VAR &_v1)
	{
		type = Type::NUMBER;
		REGISTER[_ptr].i = (int)*this | (int)_v1;
		return *this;
	}
	__NJS_VAR operator^(const __NJS_VAR &_v1) { return (int)*this ^ (int)_v1; }
	__NJS_VAR operator^=(const __NJS_VAR &_v1)
	{
		type = Type::NUMBER;
		REGISTER[_ptr].i = (int)*this ^ (int)_v1;
		return *this;
	}
	__NJS_VAR operator~() { return ~(int)*this; }
	__NJS_VAR operator>>(const __NJS_VAR &_v1) { return (int)*this >> (int)_v1; }
	__NJS_VAR operator>>=(const __NJS_VAR &_v1)
	{
		type = Type::NUMBER;
		REGISTER[_ptr].i = (int)*this >> (int)_v1;
		return *this;
	}
	__NJS_VAR operator<<(const __NJS_VAR &_v1) { return (int)*this << (int)_v1; }
	__NJS_VAR operator<<=(const __NJS_VAR &_v1)
	{
		type = Type::NUMBER;
		REGISTER[_ptr].i = (int)*this << (int)_v1;
		return *this;
	}
	// TODO: ">>>" and ">>>=" operator support

	explicit operator int() const
	{
		switch (type)
		{
		case Type::NUMBER:
			return this->get().i;
		case Type::DOUBLE:
			return static_cast<int>(this->get().d);
		//case Type::BIGNUMBER: return static_cast<int>(this->get().l);
		case Type::BOOLEAN:
			return static_cast<int>(this->get().b);
		case Type::STRING:
			return strtol(this->get().s->__NJS_VALUE.c_str(), nullptr, 10);
		case Type::ARRAY:
			if (this->get().a->__NJS_VALUE.size() != 1)
				return 0;
			return static_cast<int>(this->get().a->__NJS_VALUE[0]);
		case Type::NATIVE:
		case Type::FUNCTION:
		case Type::OBJECT:
		case Type::_INFINITY:
		case Type::_NAN:
		case Type::_NULL:
		case Type::UNDEFINED:
			return 0;
		}
	}

	explicit operator double() const
	{
		switch (type)
		{
		case Type::NUMBER:
			return static_cast<double>(this->get().i);
		case Type::DOUBLE:
			return this->get().d;
		//case Type::BIGNUMBER:
		//	return static_cast<double>(this->get().l);
		case Type::BOOLEAN:
			return static_cast<double>(this->get().b);
		case Type::STRING:
			return strtod(this->get().s->__NJS_VALUE.c_str(), nullptr);
		case Type::ARRAY:
			if (this->get().a->__NJS_VALUE.size() == 0)
				return 0;
			if (this->get().a->__NJS_VALUE.size() > 1)
				return NAN;
			return static_cast<double>(this->get().a->__NJS_VALUE[0]);
		case Type::NATIVE:
		case Type::FUNCTION:
		case Type::OBJECT:
		case Type::_INFINITY:
		case Type::_NAN:
		case Type::_NULL:
		case Type::UNDEFINED:
			return 0;
		}
	}

	explicit operator bool() const
	{
		switch (type)
		{
		case Type::NUMBER:
			return static_cast<bool>(this->get().i);
		case Type::DOUBLE:
			return static_cast<bool>(this->get().d);
		//case Type::BIGNUMBER:
		//	return static_cast<bool>(this->get().l);
		case Type::BOOLEAN:
			return this->get().b;
		case Type::STRING:
			return static_cast<bool>(this->get().s->__NJS_VALUE.size());
		case Type::ARRAY:
		case Type::NATIVE:
		case Type::FUNCTION:
		case Type::OBJECT:
		case Type::_INFINITY:
			return true;
		case Type::_NAN:
		case Type::_NULL:
		case Type::UNDEFINED:
			return false;
		}
	}

	explicit operator string() const
	{
		switch (type)
		{
		case Type::NUMBER:
			return to_string(this->get().i);
		case Type::DOUBLE:
			return to_string(this->get().d);
		//case Type::BIGNUMBER: return to_string(this->get().l);
		case Type::BOOLEAN:
			return (bool)*this ? "true" : "false";
		case Type::STRING:
			return this->get().s->__NJS_VALUE;
		case Type::ARRAY:
			return __NJS_Object_Stringify(*this, false).get().s->__NJS_VALUE;
		case Type::NATIVE:
			return "[native code]";
		case Type::FUNCTION:
			return "[Function]";
		case Type::OBJECT:
			return "[object Object]";
		case Type::_INFINITY:
			return "Infinity";
		case Type::_NAN:
			return "NaN";
		case Type::_NULL:
			return "null";
		case Type::UNDEFINED:
			return "undefined";
		}
	}
};

namespace NECTAR
{
	__NJS_VAR null = __NJS_Create_Null();
	__NJS_VAR undefined = __NJS_VAR();
} // namespace NECTAR

/*** VARIADIC CALLS ***/
template <class... Args>
__NJS_VAR __NJS_Back_Var_Call_Function(__NJS_VAR _obj, Args... args)
{
	vector<var> _args = vector<var>{(var)args...};
	return (*static_cast<function<__NJS_VAR(vector<var>)> *>(_obj.get().f->__NJS_VALUE))(_args);
}

template <class... Args>
__NJS_VAR __NJS_Call_Function(__NJS_VAR _obj, Args... args)
{
	if (_obj.type != Type::FUNCTION)
	{
#ifndef __NJS_ARDUINO
		cout << "[!] Fatal error, object is not a function" << endl;
#endif
		exit(1);
	}
	return __NJS_Back_Var_Call_Function(_obj, (__NJS_VAR)(args)...);
}
/*** END VARIADIC CALLS ***/

/*** FIXED CALLS ***/
template <class... Args>
__NJS_VAR __NJS_Back_Var_Call_Fixed_Function(__NJS_VAR _obj, Args... args)
{
	return (*static_cast<function<__NJS_VAR(Args...)> *>(_obj.get().f->__NJS_VALUE))(args...);
}

template <class... Args>
__NJS_VAR __NJS_Call_Fixed_Function(__NJS_VAR _obj, Args... args)
{
	if (_obj.type != Type::FUNCTION)
	{
#ifndef __NJS_ARDUINO
		cout << "[!] Fatal error, object is not a function" << endl;
#endif
		exit(1);
	}
	return __NJS_Back_Var_Call_Fixed_Function(_obj, (__NJS_VAR)(args)...);
}
/*** END FIXED CALLS ***/

/*** FAST CALLS ***/
#define __NJS_Call_Fast_Function(_name, __VA_ARGS__) _name(__VA_ARGS__)
/*** END FAST CALLS ***/

__NJS_VAR __create_Array()
{
	Class::Array *_a = new Class::Array();
	return __NJS_VAR(Type::ARRAY, _a);
}

__NJS_VAR __NJS_Create_Array()
{
	Class::Array *_a = new Class::Array();
	return __NJS_VAR(_a);
}

int __NJS_Get_Int(__NJS_VAR _v)
{
	return _v.get().i;
}

const char *__NJS_Get_String(__NJS_VAR _v)
{
	if (_v.type != Type::STRING)
		return "";
	return _v.get().s->__NJS_VALUE.c_str();
}

__NJS_VAR __NJS_Typeof(__NJS_VAR _var)
{
	const char *_array[] = {"", "undefined", "number", "number", "object", "number", "boolean", "string", "native", "function", "array", "NaN", "number", "object"};
	return __NJS_Create_String(_array[_var.type]);
}

/*** ***/
__NJS_VAR __NJS_Object_Set(const char *_index, __NJS_VAR _value, vector<pair<const char *, __NJS_VAR>> *_obj)
{
	int _j = (*_obj).size();
	for (int _i = 0; _i < _j; _i++)
	{
		if (strcmp(_index, (*_obj)[_i].first) == 0)
		{

			if (_value.type == Type::STRING)
			{
				REGISTER[(*_obj)[_i].second._ptr].s = new Class::String((string)_value);
			}
			else
				REGISTER[(*_obj)[_i].second._ptr] = REGISTER[_value._ptr];

			return __NJS_VAR();
		}
	}

	(*_obj).push_back(pair<const char *, __NJS_VAR>(_index, _value));
	return __NJS_VAR();
}
/**/

__NJS_VAR __NJS_Object_Set(__NJS_VAR _index, __NJS_VAR _value, __NJS_VAR _array)
{
	if (_array.type == Type::ARRAY && _index.type == Type::NUMBER)
	{

		if (_array.get().a->__NJS_VALUE.size() <= _index.get().i)
		{
			_array.get().a->__NJS_VALUE.reserve(_index.get().i + 1);
			_array.get().a->__NJS_VALUE.resize(_index.get().i + 1);
		}

		_array.get().a->__NJS_VALUE.at(_index.get().i) = _value;

		__NJS_Object_Set("length", (int)_array.get().a->__NJS_VALUE.size(), &_array.get().a->__OBJECT);
		return __NJS_VAR();
	}
	else if (_array.type == Type::OBJECT || _array.type == Type::STRING || _array.type == Type::FUNCTION || _array.type == Type::ARRAY || _array.type == Type::NATIVE)
	{
		vector<pair<const char *, __NJS_VAR>> *_obj;
		if (_array.type == Type::OBJECT)
			_obj = &_array.get().o->__OBJECT;
		else if (_array.type == Type::ARRAY)
			_obj = &_array.get().a->__OBJECT;
		else if (_array.type == Type::STRING)
			_obj = &_array.get().s->__OBJECT;
		else if (_array.type == Type::FUNCTION)
			_obj = &_array.get().f->__OBJECT;
		else
			return __NJS_VAR();

		_index.get().s->cnt++;
		return __NJS_Object_Set(_index.get().s->__NJS_VALUE.c_str(), _value, _obj);
	}

	return __NJS_VAR();
}

__NJS_VAR __NJS_Object_Get(__NJS_VAR _index, __NJS_VAR _array)
{
	if (_array.type != Type::ARRAY && _array.type != Type::OBJECT && _array.type != Type::STRING && _array.type != Type::FUNCTION && _array.type != Type::NATIVE)
	{
		__NJS_RETURN_UNDEFINED;
	}
	if (_array.type == Type::ARRAY && _index.type == Type::NUMBER)
	{
		if (_index.get().i > _array.get().a->__NJS_VALUE.size())
		{
			__NJS_RETURN_UNDEFINED;
		}
		return _array.get().a->__NJS_VALUE[_index.get().i];
	}
	else
	{
		if (_index.type != Type::STRING)
		{
			__NJS_RETURN_UNDEFINED;
		}
		vector<pair<const char *, __NJS_VAR>> *_obj;
		if (_array.type == Type::OBJECT)
			_obj = &_array.get().o->__OBJECT;
		else if (_array.type == Type::ARRAY)
			_obj = &_array.get().a->__OBJECT;
		else if (_array.type == Type::STRING)
			_obj = &_array.get().s->__OBJECT;
		else if (_array.type == Type::FUNCTION)
			_obj = &_array.get().f->__OBJECT;
		else
		{
			__NJS_RETURN_UNDEFINED;
		}
		int _j = (*_obj).size();
		for (int _i = 0; _i < _j; _i++)
		{
			if (strcmp(_index.get().s->__NJS_VALUE.c_str(), (*_obj)[_i].first) == 0)
			{
				return (*_obj)[_i].second;
			}
		}
	}

	__NJS_RETURN_UNDEFINED;
}

Class::String::Class::String(string _value)
{
	cnt++;
	/*** toString ***/
	function<__NJS_VAR()> *__OBJ_TO_Type::STRING = new function<__NJS_VAR()>([&]() { return __NJS_Create_String(this->__NJS_VALUE); });
	__NJS_VAR toString = __NJS_VAR(Type::FUNCTION, __OBJ_TO_Type::STRING);
	__NJS_Object_Set("toString", toString, &this->__OBJECT);
	/*** end to string ***/

	/*** length ***/
	__NJS_Object_Set("length", __NJS_VAR((int)_value.size()), &this->__OBJECT);
	/*** end length ***/

	/*** split ***/
	function<__NJS_VAR(vector<var>)> *__OBJ_TO___NJS_SPLIT = new function<__NJS_VAR(vector<var>)>([&](vector<var> __NJS_VARARGS) {
		var _needle;
		if (__NJS_VARARGS.size() > 0)
			_needle = __NJS_VARARGS[0];
		else
			return __NJS_VAR(this->__NJS_VALUE);

		__NJS_VAR _arr = __NJS_Create_Array();
		char *_v = (char *)malloc(strlen(this->__NJS_VALUE.c_str()) + 1);
		strcpy(_v, this->__NJS_VALUE.c_str());
		char *delim = (char *)malloc(strlen(_needle.get().s->__NJS_VALUE.c_str()) + 1);
		strcpy(delim, _needle.get().s->__NJS_VALUE.c_str());

		char *ptr = strtok(_v, delim);
		int i = 0;
		char *_new;
		while (ptr != NULL)
		{
			_new = (char *)malloc(strlen(ptr) + 1);
			strcpy(_new, ptr);
			__NJS_Object_Set(i, _new, _arr);
			free(_new);
			ptr = strtok(NULL, delim);
			i++;
		}

		free(delim);
		return _arr;
	});

	__NJS_VAR __split = __NJS_VAR(Type::FUNCTION, __OBJ_TO___NJS_SPLIT);
	__NJS_Object_Set("split", __split, &this->__OBJECT);
	/*** end split ***/

#ifndef __NJS_ARDUINO
	/*** indexOf ***/
	function<__NJS_VAR(vector<var>)> *__OBJ_TO___NJS_INDEXOF = new function<__NJS_VAR(vector<var>)>([&](vector<var> __NJS_VARARGS) {
		var _needle;
		if (__NJS_VARARGS.size() > 0)
			_needle = __NJS_VARARGS[0];
		else
			return __NJS_VAR(-1);

		string::size_type loc = this->__NJS_VALUE.find(_needle.get().s->__NJS_VALUE, 0);
		if (loc != string::npos)
		{
			return __NJS_VAR((int)loc);
		}
		return __NJS_VAR(-1);
	});

	__NJS_VAR __indexof = __NJS_VAR(Type::FUNCTION, __OBJ_TO___NJS_INDEXOF);

	__NJS_Object_Set("indexOf", __indexof, &this->__OBJECT);
	/*** end indexOf ***/

	/*** lastIndexOf ***/
	function<__NJS_VAR(vector<var>)> *__OBJ_TO___NJS_LASTINDEXOF = new function<__NJS_VAR(vector<var>)>([&](vector<var> __NJS_VARARGS) {
		var _needle;
		if (__NJS_VARARGS.size() > 0)
			_needle = __NJS_VARARGS[0];
		else
			return __NJS_VAR(-1);

		string::size_type loc = this->__NJS_VALUE.find_last_of(_needle.get().s->__NJS_VALUE, 0);
		if (loc != string::npos)
		{
			return __NJS_VAR((int)loc);
		}
		return __NJS_VAR(-1);
	});

	__NJS_VAR __lastindexof = __NJS_VAR(Type::FUNCTION, __OBJ_TO___NJS_LASTINDEXOF);

	__NJS_Object_Set("lastIndexOf", __lastindexof, &this->__OBJECT);
	/*** end lastIndexOf ***/

	/*** search ***/
	function<__NJS_VAR(vector<var>)> *__OBJ_TO___NJS_SEARCH = new function<__NJS_VAR(vector<var>)>([&](vector<var> __NJS_VARARGS) {
		var _needle;
		if (__NJS_VARARGS.size() > 0)
			_needle = __NJS_VARARGS[0];
		else
			return __NJS_VAR(-1);

		string::size_type loc = this->__NJS_VALUE.find(_needle.get().s->__NJS_VALUE, 0);
		if (loc != string::npos)
		{
			return __NJS_VAR((int)loc);
		}
		return __NJS_VAR(-1);
	});

	__NJS_VAR __search = __NJS_VAR(Type::FUNCTION, __OBJ_TO___NJS_SEARCH);

	__NJS_Object_Set("search", __search, &this->__OBJECT);
	/*** end search ***/

	/*** slice ***/
	function<__NJS_VAR(vector<var>)> *__OBJ_TO___NJS_SLICE = new function<__NJS_VAR(vector<var>)>([&](vector<var> __NJS_VARARGS) {
		var _start;
		var _end;
		if (__NJS_VARARGS.size() > 0)
			_start = __NJS_VARARGS[0];
		else
			return __NJS_VAR(this->__NJS_VALUE);
		if (__NJS_VARARGS.size() > 1)
			_end = __NJS_VARARGS[1];

		if (_end.type == Type::UNDEFINED)
			return __NJS_VAR(this->__NJS_VALUE.substr(_start.get().i, string::npos));
		int _endIndex = _end.get().i - _start.get().i;
		return __NJS_VAR(this->__NJS_VALUE.substr(_start.get().i, _endIndex));
	});

	__NJS_VAR __slice = __NJS_VAR(Type::FUNCTION, __OBJ_TO___NJS_SLICE);

	__NJS_Object_Set("slice", __slice, &this->__OBJECT);
	__NJS_Object_Set("substring", __slice, &this->__OBJECT);
	/*** end slice ***/

	/*** substr ***/
	function<__NJS_VAR(vector<var>)> *__OBJ_TO___NJS_SUBSTR = new function<__NJS_VAR(vector<var>)>([&](vector<var> __NJS_VARARGS) {
		var _start;
		var _end;
		if (__NJS_VARARGS.size() > 0)
			_start = __NJS_VARARGS[0];
		else
			return __NJS_VAR(this->__NJS_VALUE);
		if (__NJS_VARARGS.size() > 1)
			_end = __NJS_VARARGS[1];

		if (_end.type == Type::UNDEFINED)
			return __NJS_VAR(this->__NJS_VALUE.substr(_start.get().i, string::npos));
		return __NJS_VAR(this->__NJS_VALUE.substr(_start.get().i, _end.get().i));
	});

	__NJS_VAR __substr = __NJS_VAR(Type::FUNCTION, __OBJ_TO___NJS_SUBSTR);

	__NJS_Object_Set("substr", __substr, &this->__OBJECT);
	/*** end substr ***/

	/*** replace ***/
	function<__NJS_VAR(vector<var>)> *__OBJ_TO___NJS_REPLACE = new function<__NJS_VAR(vector<var>)>([&](vector<var> __NJS_VARARGS) {
		var _search;
		var _replace;
		if (__NJS_VARARGS.size() > 0)
			_search = __NJS_VARARGS[0];
		else
			return __NJS_VAR(this->__NJS_VALUE);
		if (__NJS_VARARGS.size() > 1)
			_replace = __NJS_VARARGS[1];

		size_t start_pos = this->__NJS_VALUE.find(_search.get().s->__NJS_VALUE);
		if (start_pos == std::string::npos)
		{
			return var(this->__NJS_VALUE);
		}
		return var(this->__NJS_VALUE.replace(start_pos, _search.get().s->__NJS_VALUE.length(), _replace.get().s->__NJS_VALUE));
	});

	__NJS_VAR __replace = __NJS_VAR(Type::FUNCTION, __OBJ_TO___NJS_REPLACE);

	__NJS_Object_Set("replace", __replace, &this->__OBJECT);
	/*** end replace ***/
#endif

	__NJS_VALUE = _value;
}

Class::Array::Class::Array()
{
	cnt++;
	function<__NJS_VAR()> *__OBJ_TO_Type::STRING = new function<__NJS_VAR()>([&]() { return __NJS_Create_String("Array"); });
	__NJS_VAR toString = __NJS_VAR(Type::FUNCTION, __OBJ_TO_Type::STRING);
	__NJS_Object_Set("toString", toString, &this->__OBJECT);

	function<__NJS_VAR(vector<var>)> *Type::ARRAY_PUSH = new function<__NJS_VAR(vector<var>)>([&](vector<var> __NJS_VARARGS) {
		var _add;
		if (__NJS_VARARGS.size() > 0)
			_add = __NJS_VARARGS[0];
		else
			return (int)this->__NJS_VALUE.size();

		this->__NJS_VALUE.push_back(_add);
		__NJS_Object_Set("length", (int)this->__NJS_VALUE.size(), &this->__OBJECT);

		return (int)this->__NJS_VALUE.size();
	});
	__NJS_VAR arrayPush = __NJS_VAR(Type::FUNCTION, Type::ARRAY_PUSH);
	__NJS_Object_Set("push", arrayPush, &this->__OBJECT);

	__NJS_Object_Set("length", 0, &this->__OBJECT);
}



Class::Function::Class::Function(void *_f)
{
	cnt++;
	__NJS_VAR __proto = __NJS_Create_Object();
	__NJS_Object_Set("prototype", __proto, &this->__OBJECT);
	__NJS_VALUE = _f;
}

Class::Native::Class::Native(void *_n)
{
	cnt++;
	__NJS_VALUE = _n;
}

void Class::String::Delete()
{
	this->cnt--;
	if (this->cnt < 1)
	{
		delete this;
	}
}

void Class::Array::Delete()
{
	this->cnt--;
	if (this->cnt < 1)
	{
		delete this;
	}
}



void Class::Function::Delete()
{
	this->cnt--;
	if (this->cnt < 1)
	{
		delete this;
	}
}

void Class::Native::Delete()
{
	this->cnt--;
	if (this->cnt < 1)
	{
		delete this;
	}
}

__NJS_VAR Array()
{
	vector<__NJS_VAR> *_arr = new vector<__NJS_VAR>();
	return __NJS_VAR(Type::ARRAY, _arr);
}

__NJS_VAR __NJS_Boolean_Result(__NJS_VAR _v)
{
	if (_v.type == Type::NUMBER)
		return _v.get().i;
	else if (_v.type == Type::BOOLEAN)
		return _v.get().b;
	else if (_v.type == Type::STRING)
	{
		if (strlen(_v.get().s->__NJS_VALUE.c_str()) > 0)
			return true;
		else
			return false;
	}
	else if (_v.type == Type::ARRAY)
		return true;
	else
		return false;
}

ostream &operator<<(ostream &os, const __NJS_VAR &_v)
{
	switch (_v.type)
	{
	case Type::BOOLEAN:
		if (_v.get().b)
			os << "true";
		else
			os << "false";
		break;
	case Type::NUMBER:
		os << _v.get().i;
		break;
	case Type::DOUBLE:
		os << _v.get().d;
		break;
	case Type::STRING:
		os << _v.get().s->__NJS_VALUE;
		break;
	case Type::OBJECT:
		os << __NJS_Object_Stringify(_v);
		break;
	case Type::ARRAY:
		os << __NJS_Object_Stringify(_v);
		break;
	case Type::NATIVE:
		os << "[Native]";
		break;
	case Type::_NAN:
		os << "NaN";
		break;
	case Type::FUNCTION:
		os << "[Function]";
		break;
	case Type::_INFINITY:
		os << "Infinity";
		break;
	case Type::_NULL:
		os << "null";
		break;
	default:
		os << "undefined";
		break;
	}
	return os;
}

__NJS_VAR parseInt(__NJS_VAR _str)
{
	if (_str.type == Type::STRING)
	{
#ifdef __NJS_ARDUINO
		return __NJS_VAR();
#else
		return __NJS_Create_Number(stoi(_str.get().s->__NJS_VALUE));
#endif
	}
	else
		return __NJS_Create_Undefined();
}

__NJS_VAR __NJS_Log_Console(__NJS_VAR _var)
{
#ifdef __NJS_ARDUINO

#else
	cout << _var;
	cout << endl;
#endif

	return __NJS_VAR();
}

__NJS_VAR __NJS_Object_Keys(__NJS_VAR _var)
{
	if (_var.type != Type::OBJECT)
		return 0;
	var _res = __NJS_Create_Array();

	vector<pair<const char *, __NJS_VAR>> *_obj = &_var.get().o->__OBJECT;
	int _j = (*_obj).size();
	for (int _i = 0; _i < _j; _i++)
	{
		__NJS_Object_Set(_i, (*_obj)[_i].first, _res);
	}
	return _res;
}

__NJS_VAR __NJS_Object_Stringify(__NJS_VAR _var)
{
	return __NJS_Object_Stringify(_var, true);
}
__NJS_VAR __NJS_Object_Stringify(__NJS_VAR _var, bool _bracket)
{

	Type _t = _var.type;

	if (_t == Type::UNDEFINED)
		return "undefined";
	else if (_t == Type::_NAN)
		return "NaN";
	else if (_t == Type::NUMBER)
		return var("") + _var;
	else if (_t == Type::DOUBLE)
		return var("") + _var;
	else if (_t == Type::STRING)
		return var("\"") + _var + "\"";
	else if (_t == Type::FUNCTION)
		return var("\"") + "[Function]" + "\"";
	else if (_t == Type::ARRAY)
	{
		var _res = "";
		vector<__NJS_VAR> *_arr = &_var.get().a->__NJS_VALUE;
		if(_bracket) _res += "[";
		int j = (*_arr).size();
		for (int i = 0; i < j; i++)
		{
			if (i > 0)
				_res += ",";
			_res += __NJS_Object_Stringify((*_arr)[i], _bracket);
		}
		if(_bracket) _res += "]";

		return _res;
	}
	else if (_t == Type::OBJECT)
	{
		var _res = "";
		vector<pair<const char *, __NJS_VAR>> *_obj = &_var.get().o->__OBJECT;
		_res = "{";
		int j = (*_obj).size();
		for (int _i = 0; _i < j; _i++)
		{
			if (_i > 0)
				_res += ", ";
			_res += var("\"") + (*_obj)[_i].first + "\"";
			_res += ":";
			_res += __NJS_Object_Stringify((*_obj)[_i].second);
		}
		_res += "}";
		return _res;
	}
	else
		return "";
}

__NJS_VAR __NJS_Object_Clone(__NJS_VAR _var)
{
	Type _t = _var.type;
	switch(_t)
	{
		case Type::UNDEFINED:
		case Type::_NAN:
		case Type::NUMBER:
		case Type::DOUBLE:
		case Type::STRING:
		case Type::FUNCTION:
			return _var;
		case Type::ARRAY:
		{
			var _res = __NJS_Create_Array();
			vector<__NJS_VAR> *_arr = &_var.get().a->__NJS_VALUE;

			int j = (*_arr).size();
			for (int i = 0; i < j; i++)
			{
				__NJS_Object_Set(i, __NJS_Object_Clone((*_arr)[i]), _res);
			}
			return _res;
		}
		case Type::OBJECT:
		{
			var _res = __NJS_Create_Object();
			vector<pair<const char *, __NJS_VAR>> *_obj = &_var.get().o->__OBJECT;
			int j = (*_obj).size();
			for (int _i = 0; _i < j; _i++)
			{
				__NJS_Object_Set((*_obj)[_i].first, __NJS_Object_Clone((*_obj)[_i].second), _res);
			}
			return _res;
		}
		default:
			return __NJS_VAR();
	}
}

void __NJS_Object_Construct(__NJS_VAR _this, __NJS_VAR _prototype)
{
	if(_this.type == Type::OBJECT && _prototype.type == Type::OBJECT)
	{
		vector<pair<const char *, __NJS_VAR>> *_obj = &_prototype.get().o->__OBJECT;
		int j = (*_obj).size();
		for (int _i = 0; _i < j; _i++)
		{
			__NJS_VAR _tmp =  __NJS_Object_Get((*_obj)[_i].first, _this);
			if(_tmp.type == Type::UNDEFINED)
			{
				__NJS_Object_Set((*_obj)[_i].first, (*_obj)[_i].second, _this);
			}
		}
	}
	
}


__NJS_VAR __NJS_Create_Object()
{
	Class::Object *_obj = new Class::Object();
	return __NJS_VAR(_obj);
}

__NJS_VAR __NJS_CREATE_FUNCTION(void *_fn)
{
	return __NJS_VAR(Type::FUNCTION, _fn);
}

__NJS_VAR __NJS_Create_Native(void *_native)
{
	return __NJS_VAR(Type::UNDEFINED, _native);
}

/*
void* __NJS_Get_Function(__NJS_VAR _fn)
{
  return _fn.get().f;
}
*/

function<var(vector<var>)> *__NJS_Get_Function(__NJS_VAR _v)
{
	return (function<var(vector<var>)> *)_v.get().f->__NJS_VALUE;
}

void *__NJS_Get_Native(__NJS_VAR _native)
{
	return _native.get().f;
}

/*** REDIFINING STD OPERATORS ***/

template <typename t>
__NJS_VAR operator+(t _left, const __NJS_VAR &_right)
{
	return __NJS_VAR(_left) + _right;
}

template <typename t>
__NJS_VAR operator-(t _left, const __NJS_VAR &_right)
{
	return __NJS_VAR(_left) - _right;
}

template <typename t>
__NJS_VAR operator*(t _left, const __NJS_VAR &_right)
{
	return __NJS_VAR(_left) * _right;
}

template <typename t>
__NJS_VAR operator/(t _left, const __NJS_VAR &_right)
{
	return __NJS_VAR(_left) / _right;
}


/*** END REDIFINING STD OPERATORS ***/

__NJS_Create_Lambda(__IMPL_EVAL)
{
	__NJS_Log_Console("eval not implemented, return undefined");
	return var();
});
var eval = __NJS_Create_Function(__IMPL_EVAL);

function<__NJS_VAR(vector<var>)> *__NJS_IS_NAN = new function<__NJS_VAR(vector<var>)>([](vector<var> __NJS_VARARGS) {
	var _test;
	if (__NJS_VARARGS.size() > 0)
		_test = __NJS_VARARGS[0];
	else
		return __NJS_Create_Boolean(0);

	if (_test.type == Type::NUMBER || _test.type == Type::DOUBLE)
	{
		return __NJS_Create_Boolean(1);
	}

	return __NJS_Create_Boolean(0);
});

__NJS_VAR isNaN = __NJS_VAR(Type::FUNCTION, __NJS_IS_NAN);

__NJS_VAR __NJS_EQUAL_VALUE_AND_TYPE(__NJS_VAR _left, __NJS_VAR _right)
{
	if (_left.type == _right.type && _left == _right)
	{
		return __NJS_Create_Boolean(1);
	}

	return __NJS_Create_Boolean(0);
}

__NJS_VAR __NJS_NOT_EQUAL_VALUE_AND_TYPE(__NJS_VAR _left, __NJS_VAR _right)
{
	if (_left.type != _right.type || _left != _right)
	{
		return __NJS_Create_Boolean(1);
	}

	return __NJS_Create_Boolean(0);
}
