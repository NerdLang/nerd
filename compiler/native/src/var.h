// #include <iostream>
// #include <sstream>
// #include <memory>
#include <cstring>
#include <string>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
// #include<stdarg.h>

//#define __NJS_VAR NJS::VAR
//#define __NJS_VAL NJS::VAL
//#define __NJS_Class_ NJS::CLASS::

#ifdef __NJS_ARDUINO
#include <nonstd-function.h>
using namespace nonstd;
#else
#include <functional>
#endif

using namespace std;

int FREE_PTR = -1;
int REGISTER_PTR = 0;
#ifdef CL_WINDOWS
NJS::VAL REGISTER[{{REGISTER}}];
#else
NJS::VAL REGISTER[{{REGISTER}}]{(NJS::VAL){.i = 0}};
#endif
int FREE[{{REGISTER}}] = {0};

namespace NJS
{
	enum TYPE
	{
		_UNDEFINED = 1,
		_NUMBER,
		_DOUBLE,
		_OBJECT,
		_BIGINT,
		_BOOLEAN,
		_STRING,
		_NATIVE,
		_FUNCTION,
		_ARRAY,
		_NAN,
		_INFINITY,
		_NULL
	};

	union VAL {
		int t;
		bool b;
		CLASS::Number *i;
		CLASS::String *s;
		CLASS::Array *a;
		CLASS::Object *o;
		CLASS::Function *f;
		CLASS::Native *n;
	};

	namespace CLASS
	{
		class BaseObject
		{
		public:
			BaseObject()
			{
				cnt++;
			};
			int cnt = 0;
			void Delete()
			{
				this->cnt--;
				if (this->cnt < 1)
				{
					delete this;
				}
			};
			vector<pair<const char *, VAR>> __OBJECT;
		};
		class Object : public BaseObject
		{
		public:
			Object();
			vector<pair<const char *, VAR>> __OBJECT;
		};
		class Number : public BaseObject
		{
		public:
			Number(int _val);
			Number(double _val);
			Number(long _val);
			double __NJS_VALUE;
		};
		class String : public BaseObject
		{
		public:
			String(string _str);
			string __NJS_VALUE;
		};
		class Array : public BaseObject
		{
		public:
			Array();
			vector<VAR> __NJS_VALUE = vector<VAR>();
		};
		class Function : public BaseObject
		{
		public:
			Function(void *_f)
			{
				cnt++;
				__NJS_VALUE = _f;
			}
			void *__NJS_VALUE;
		};
		class Native : public BaseObject
		{
		public:
			Native(void *_n)
			{
				cnt++;
				__NJS_VALUE = _n;
			}
			void *__NJS_VALUE;
		};
	}; // namespace CLASS

	struct VAR
	{
	private:
		void setPtr()
		{
			if (_ptr > -1)
				return;
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
		TYPE type;
		int _ptr = -1;

		inline VAL get() const { return REGISTER[_ptr]; }
		inline void Delete() const
		{
			switch (type)
			{
			case TYPE::_OBJECT:
				get().o->Delete();
				break;
			case TYPE::_STRING:
				get().s->Delete();
				break;
			case TYPE::_FUNCTION:
				get().f->Delete();
				break;
			case TYPE::_ARRAY:
				get().a->Delete();
				break;
			case TYPE::_NATIVE:
				get().n->Delete();
				break;
			}
		}
		inline void RegIncrement() const
		{
			switch (type)
			{
			case TYPE::_OBJECT:
				REGISTER[_ptr].o->cnt++;
				break;
			case TYPE::_STRING:
				REGISTER[_ptr].s->cnt++;
				break;
			case TYPE::_FUNCTION:
				REGISTER[_ptr].f->cnt++;
				break;
			case TYPE::_ARRAY:
				REGISTER[_ptr].a->cnt++;
				break;
			case TYPE::_NATIVE:
				REGISTER[_ptr].n->cnt++;
				break;
			}
		}

		VAR()
		{
			setPtr();
			type = TYPE::_UNDEFINED;
			REGISTER[_ptr].i = 0;
		}

		~VAR()
		{
			Delete();
			FREE[++FREE_PTR] = _ptr;
		}

		/**/
		VAR(VAR const &_v)
		{
			setPtr();
			type = _v.type;
			REGISTER[_ptr] = REGISTER[_v._ptr];
			RegIncrement();
		}
		/**/

		/*** CONSTRUCTOR ***/

		VAR(TYPE _type, int _value)
		{
			setPtr();
			this->type = _type;
			REGISTER[_ptr].i = _value;
		}

		VAR(int _value)
		{
			setPtr();
			this->type = TYPE::_NUMBER;
			REGISTER[_ptr].i = _value;
		}

		VAR(double _value)
		{
			setPtr();
			this->type = TYPE::_DOUBLE;
			REGISTER[_ptr].d = _value;
		}

		VAR(long _value)
		{
			setPtr();
			this->type = TYPE::_BIGINT;
			REGISTER[_ptr].l = _value;
		}

		VAR(char *_value)
		{
			setPtr();
			type = TYPE::_STRING;
			REGISTER[_ptr].s = new CLASS::String(_value);
		}

		VAR(string _value)
		{
			setPtr();
			type = TYPE::_STRING;
			REGISTER[_ptr].s = new CLASS::String(_value);
		}

		VAR(const char *_value)
		{
			setPtr();
			type = TYPE::_STRING;
			REGISTER[_ptr].s = new CLASS::String(_value);
		}
		VAR(CLASS::Array *_value)
		{
			setPtr();
			type = TYPE::_ARRAY;
			REGISTER[_ptr].a = _value;
		}
		VAR(CLASS::Object *_value)
		{
			setPtr();
			type = TYPE::_OBJECT;
			REGISTER[_ptr].o = _value;
		}
		VAR(CLASS::Native *_value)
		{
			setPtr();
			type = TYPE::_NATIVE;
			REGISTER[_ptr].n = _value;
		}
		VAR(TYPE _type, void *_value)
		{
			setPtr();
			type = _type;
			REGISTER[_ptr].f = new CLASS::Function(_value);
		}
		VAR(function<VAR(vector<VAR>)> &_value)
		{
			setPtr();
			type = TYPE::_FUNCTION;
			REGISTER[_ptr].f = new CLASS::Function(&_value);
		}

		/*** VARIADIC LAMBDAS ***/
		template <class... Args>
		VAR(function<VAR(Args...)> &_value)
		{
			setPtr();
			type = TYPE::_FUNCTION;
			REGISTER[_ptr].f = new CLASS::Function(&_value);
		}
		/*** END VARIADIC LAMBDAS ***/

		/*** END CONSTRUCTOR ***/

		/*** OPERATOR ***/
		VAR operator=(const VAR &_v)
		{
			Delete();
			type = _v.type;
			REGISTER[_ptr] = REGISTER[_v._ptr];
			RegIncrement();
			return *this;
		}

		/// Unary operators
		VAR operator+()
		{
			if (type == TYPE::_NUMBER || type == TYPE::_BIGINT || type == TYPE::_DOUBLE)
				return *this;
			else
				return (double)*this;
		}
		VAR operator-()
		{
			if (type == TYPE::_NUMBER)
				return -(int)*this;
			else if (type == TYPE::_BIGINT)
				return -(long)*this;
			else
				return -(double)*this;
		}
		VAR operator!() { return !(bool)*this; };

		/// Logical operators
		VAR operator&&(const VAR &_v1) { return (bool)*this && (bool)_v1; }
		VAR operator||(const VAR &_v1) { return (bool)*this || (bool)_v1; }

		/// Arithmetic operators
		VAR operator+(const VAR &_v1)
		{
			if (type == __NJS_STRING || type == __NJS_ARRAY || type == __NJS_OBJECT || _v1.type == TYPE::_STRING)
				return __NJS_Concat_To_Str((string) * this, (string)_v1);
			else if (type == TYPE::_NUMBER)
				return (int)*this + (int)_v1;
			else if (type == TYPE::_BIGINT)
				return (long)*this + (long)_v1;
			else if (type == TYPE::_DOUBLE)
				return (double)*this + (double)_v1;
			else
				return VAR();
		}
		VAR operator+(const char _v1[])
		{
			return __NJS_Concat_To_Str((string) * this, _v1);
		}
		VAR operator+=(const VAR &_v1)
		{
			if (type == TYPE::_NUMBER)
				REGISTER[_ptr].i += (int)_v1;
			else if (type == TYPE::_BIGINT)
				*REGISTER[_ptr].l += (long)_v1;
			else if (type == TYPE::_DOUBLE)
				REGISTER[_ptr].d += (double)_v1;
			else if (type == TYPE::_STRING)
				REGISTER[_ptr].s->__NJS_VALUE += (string)_v1;
			else
			{
				string _s = (string) * this;
				type = TYPE::_STRING;
				REGISTER[_ptr].s = new __NJS_Class_String("");
				REGISTER[_ptr].s->__NJS_VALUE += _s + (string)_v1;
			}
			return *this;
		}
		VAR operator-(const VAR &_v1)
		{
			if (type == TYPE::_NUMBER)
				return VAR((int)*this - (int)_v1);
			else if (type == TYPE::_BIGINT)
				return VAR((long)*this - (long)_v1);
			else if (type == TYPE::_DOUBLE)
				return VAR((double)*this - (double)_v1);
			else
				return "NaN";
		}
		VAR operator-=(const VAR &_v1)
		{
			if (type == TYPE::_NUMBER && _v1.type == TYPE::_NUMBER)
				REGISTER[_ptr].i -= (int)_v1;
			else if (type == TYPE::_NUMBER && _v1.type == TYPE::_DOUBLE)
				REGISTER[_ptr].i -= (double)_v1;
			else if (type == TYPE::_DOUBLE && _v1.type == TYPE::_NUMBER)
				REGISTER[_ptr].d -= (int)_v1;
			else if (type == TYPE::_BIGINT && _v1.type == TYPE::_DOUBLE)
				*REGISTER[_ptr].l -= (long)_v1;
			else if (type == TYPE::_DOUBLE && _v1.type == TYPE::_DOUBLE)
				REGISTER[_ptr].d -= (double)_v1;
			else
			{
				type = TYPE::_NAN;
				REGISTER[_ptr].s = new __NJS_Class_String("NaN");
			}
			return *this;
		}
		VAR operator*(const VAR &_v1)
		{
			if (type == TYPE::_NUMBER)
				return REGISTER[_ptr].i * (int)_v1;
			else if (type == TYPE::_DOUBLE)
				return REGISTER[_ptr].d * (double)_v1;
			return VAR();
		}
		VAR operator*=(const VAR &_v1)
		{
			if (type == TYPE::_NUMBER)
				REGISTER[_ptr].i *= (int)_v1;
			else if (type == TYPE::_DOUBLE)
				REGISTER[_ptr].d *= (double)_v1;
			return VAR();
		}
		VAR operator/(const VAR &_v1)
		{
			if (type == TYPE::_NUMBER)
				return REGISTER[_ptr].i / (int)_v1;
			else if (type == TYPE::_DOUBLE)
				return REGISTER[_ptr].d / (double)_v1;
			return VAR();
		}
		VAR operator/=(const VAR &_v1)
		{
			if (type == TYPE::_NUMBER)
				return get().i /= _v1.get().i;
			return VAR();
		}
		VAR operator%(const VAR &_v1)
		{
			if (type == __NJS_NUMBER && _v1.type == TYPE::_NUMBER)
				return REGISTER[_ptr].i % (int)_v1;
			else
				return remainder(REGISTER[_ptr].d, (double)_v1);
		}
		VAR operator%=(const VAR &_v1)
		{
			if (type == __NJS_NUMBER && _v1.type == TYPE::_NUMBER)
			{
				REGISTER[_ptr].i %= (int)_v1;
			}
			else
			{
				type = TYPE::_DOUBLE;
				REGISTER[_ptr].d = remainder((double)*this, (double)_v1);
			}
			return *this;
		}
		// TODO: "**" and "**=" operators
		VAR operator++(const int _v1)
		{
			if (type == TYPE::_NUMBER)
			{
				REGISTER[_ptr].i++;
			}
			else if (type == TYPE::_DOUBLE)
			{
				REGISTER[_ptr].d++;
			}
			else
			{
				type = TYPE::_DOUBLE;
				REGISTER[_ptr].d = (double)*this;
			}
			return *this;
		}
		VAR operator--(const int _v1)
		{
			if (type == TYPE::_NUMBER)
				REGISTER[_ptr].i--;
			else if (type == TYPE::_DOUBLE)
				REGISTER[_ptr].d--;
			else
			{
				type = TYPE::_DOUBLE;
				REGISTER[_ptr].d = (double)*this;
			}
			return *this;
		}

		/// Comparison operators
		VAR operator==(const VAR &_v1)
		{
			if (type == _v1.type)
			{
				switch (type)
				{
				case TYPE::_NUMBER:
					return get().i == (int)_v1;
				case TYPE::_DOUBLE:
					return get().d == (double)_v1;
				case TYPE::_BIGINT:
					return *get().l == (long)_v1;
				case TYPE::_BOOLEAN:
					return get().b == (bool)_v1;
				case TYPE::_STRING:
					return get().s->__NJS_VALUE.compare((string)_v1) == 0;
				case TYPE::_INFINITY:
				case TYPE::_NULL:
				case TYPE::_UNDEFINED:
					return true;
				case TYPE::_ARRAY:
				case TYPE::_NATIVE:
				case TYPE::_FUNCTION:
				case TYPE::_OBJECT:
				case TYPE::_NAN:
					return false;
				}
			}
			else
			{
				if (type == __NJS_STRING || _v1.type == TYPE::_STRING)
				{
					return (string)*this == (string)_v1;
				}
				else
					return (double)*this == (double)_v1;
			}
		}
		// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
		VAR operator!=(const VAR &_v1)
		{
			return !(*this == _v1);
		}

		// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
		VAR operator<(const VAR &_v1)
		{
			if (type == _v1.type && type == TYPE::_NUMBER)
				return (int)*this < (int)_v1;
			else
				return (double)*this < (double)_v1;
		}
		VAR operator<=(const VAR &_v1)
		{
			if (type == _v1.type && type == TYPE::_NUMBER)
				return (int)*this <= (int)_v1;
			else
				return (double)*this <= (double)_v1;
		}
		VAR operator>(const VAR &_v1)
		{
			if (type == _v1.type && type == TYPE::_NUMBER)
				return (int)*this > (int)_v1;
			else
				return (double)*this > (double)_v1;
		}
		VAR operator>=(const VAR &_v1)
		{
			if (type == _v1.type && type == TYPE::_NUMBER)
				return (int)*this >= (int)_v1;
			else
				return (double)*this >= (double)_v1;
		}

		/// Bitwise operators
		VAR operator&(const VAR &_v1) { return (int)*this & (int)_v1; }
		VAR operator&=(const VAR &_v1)
		{
			type = TYPE::_NUMBER;
			REGISTER[_ptr].i = (int)*this & (int)_v1;
			return *this;
		}
		VAR operator|(const VAR &_v1) { return (int)*this | (int)_v1; }
		VAR operator|=(const VAR &_v1)
		{
			type = TYPE::_NUMBER;
			REGISTER[_ptr].i = (int)*this | (int)_v1;
			return *this;
		}
		VAR operator^(const VAR &_v1) { return (int)*this ^ (int)_v1; }
		VAR operator^=(const VAR &_v1)
		{
			type = TYPE::_NUMBER;
			REGISTER[_ptr].i = (int)*this ^ (int)_v1;
			return *this;
		}
		VAR operator~() { return ~(int)*this; }
		VAR operator>>(const VAR &_v1) { return (int)*this >> (int)_v1; }
		VAR operator>>=(const VAR &_v1)
		{
			type = TYPE::_NUMBER;
			REGISTER[_ptr].i = (int)*this >> (int)_v1;
			return *this;
		}
		VAR operator<<(const VAR &_v1) { return (int)*this << (int)_v1; }
		VAR operator<<=(const VAR &_v1)
		{
			type = TYPE::_NUMBER;
			REGISTER[_ptr].i = (int)*this << (int)_v1;
			return *this;
		}
		// TODO: ">>>" and ">>>=" operator support

		explicit operator int() const
		{
			switch (type)
			{
			case TYPE::_NUMBER:
				return this->get().i;
			case TYPE::_DOUBLE:
				return this->get().d;
			case TYPE::_BIGINT:
				return reinterpret_cast<int>(this->get().l);
			case TYPE::_BOOLEAN:
				return this->get().b;
			case TYPE::_STRING:
				return strtol(this->get().s->__NJS_VALUE.c_str(), nullptr, 10);
			case TYPE::_ARRAY:
				if (this->get().a->__NJS_VALUE.size() != 1)
					return 0;
				return static_cast<int>(this->get().a->__NJS_VALUE[0]);
			case TYPE::_NATIVE:
			case TYPE::_FUNCTION:
			case TYPE::_OBJECT:
			case TYPE::_INFINITY:
			case TYPE::_NAN:
			case TYPE::_NULL:
			case TYPE::_UNDEFINED:
				return 0;
			}
		}

		explicit operator double() const
		{
			switch (type)
			{
			case TYPE::_NUMBER:
				return this->get().i;
			case TYPE::_DOUBLE:
				return this->get().d;
			case TYPE::_BIGINT:
				return reinterpret_cast<int>(this->get().l);
			case TYPE::_BOOLEAN:
				return this->get().b;
			case TYPE::_STRING:
				return strtod(this->get().s->__NJS_VALUE.c_str(), nullptr);
			case TYPE::_ARRAY:
				if (this->get().a->__NJS_VALUE.size() == 0)
					return 0;
				if (this->get().a->__NJS_VALUE.size() > 1)
					return NAN;
				return static_cast<double>(this->get().a->__NJS_VALUE[0]);
			case TYPE::_NATIVE:
			case TYPE::_FUNCTION:
			case TYPE::_OBJECT:
			case TYPE::_INFINITY:
			case TYPE::_NAN:
			case TYPE::_NULL:
			case TYPE::_UNDEFINED:
				return 0;
			}
		}

		explicit operator long() const
		{
			switch (type)
			{
			case TYPE::_NUMBER:
				return this->get().i;
			case TYPE::_DOUBLE:
				return this->get().d;
			case TYPE::_BIGINT:
				return *this->get().l;
			case TYPE::_BOOLEAN:
				return this->get().b;
			case TYPE::_STRING:
				return strtol(this->get().s->__NJS_VALUE.c_str(), nullptr, 10);
			case TYPE::_ARRAY:
				if (this->get().a->__NJS_VALUE.size() == 0)
					return 0;
				if (this->get().a->__NJS_VALUE.size() > 1)
					return NAN;
				return static_cast<long>(this->get().a->__NJS_VALUE[0]);
			case TYPE::_NATIVE:
			case TYPE::_FUNCTION:
			case TYPE::_OBJECT:
			case TYPE::_INFINITY:
			case TYPE::_NAN:
			case TYPE::_NULL:
			case TYPE::_UNDEFINED:
				return 0;
			}
		}

		explicit operator bool() const
		{
			switch (type)
			{
			case TYPE::_NUMBER:
				return this->get().i;
			case TYPE::_DOUBLE:
				return this->get().d;
			case TYPE::_BIGINT:
				return this->get().l;
			case TYPE::_BOOLEAN:
				return this->get().b;
			case TYPE::_STRING:
				return this->get().s->__NJS_VALUE.size();
			case TYPE::_ARRAY:
			case TYPE::_NATIVE:
			case TYPE::_FUNCTION:
			case TYPE::_OBJECT:
			case TYPE::_INFINITY:
				return true;
			case TYPE::_NAN:
			case TYPE::_NULL:
			case TYPE::_UNDEFINED:
				return false;
			}
		}

		explicit operator string() const
		{
			switch (type)
			{
			case TYPE::_NUMBER:
				return to_string(this->get().i);
			case TYPE::_DOUBLE:
				return to_string(this->get().d);
			//case TYPE::_BIGNUMBER: return to_string(this->get().l);
			case TYPE::_BOOLEAN:
				return (bool)*this ? "true" : "false";
			case TYPE::_STRING:
				return this->get().s->__NJS_VALUE;
			case TYPE::_ARRAY:
				return __NJS_Object_Stringify(*this, false).get().s->__NJS_VALUE;
			case TYPE::_NATIVE:
				return "[native code]";
			case TYPE::_FUNCTION:
				return "[Function]";
			case TYPE::_OBJECT:
				return "[object Object]";
			case TYPE::_INFINITY:
				return "Infinity";
			case TYPE::_NAN:
				return "NaN";
			case TYPE::_NULL:
				return "null";
			case TYPE::_UNDEFINED:
				return "undefined";
			}
		}
	};
}; // namespace NJS
