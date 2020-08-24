#include "var.h"
#include "memory.h"

namespace NJS
{
	struct VAR
	{
	private:
		inline void setPtr()
		{
			if (_ptr > -1)
				return;
			_ptr = NJS::MEMORY::get();
		}

		inline void delPtr()
		{
			NJS::MEMORY::release(_ptr);
		}

	public:
		NJS::Enum::Type type;
		int _ptr = -1;

		NJS::MEMORY::VAL get() const
		{
			return NJS::MEMORY::REGISTER[_ptr];
		}

		__NJS_VAR()
		{
			setPtr();
			type = __NJS_UNDEFINED;
			get().i = 0;
		}

		~__NJS_VAR()
		{
			get()->Delete();
			delPtr();
		}

		/**/
		__NJS_VAR(__NJS_VAR const &_v)
		{
			setPtr();
			type = _v.type;

			if (_v.type == __NJS_OBJECT)
			{
				get() = REGISTER[_v._ptr];
				get().o->cnt++;
			}
			else if (_v.type == __NJS_STRING)
			{

				get().s = new __NJS_Class_String(REGISTER[_v._ptr].s->__NJS_VALUE);
			}
			else if (_v.type == __NJS_FUNCTION)
			{
				get() = REGISTER[_v._ptr];
				get().f->cnt++;
			}
			else if (_v.type == __NJS_ARRAY)
			{
				get() = REGISTER[_v._ptr];
				get().a->cnt++;
			}
			else if (_v.type == __NJS_NATIVE)
			{
				get() = REGISTER[_v._ptr];
				get().n->cnt++;
			}
			else
			{
				get() = REGISTER[_v._ptr];
			}
		}
		/**/

		/*** CONSTRUCTOR ***/

		__NJS_VAR(__NJS_TYPE _type, int _value)
		{
			setPtr();
			this->type = _type;
			get().i = _value;
		}

		__NJS_VAR(int _value)
		{
			setPtr();
			this->type = __NJS_NUMBER;
			get().i = _value;
		}

		__NJS_VAR(double _value)
		{
			setPtr();
			this->type = __NJS_DOUBLE;
			get().d = _value;
		}

		__NJS_VAR(char *_value)
		{
			setPtr();
			type = __NJS_STRING;
			get().s = new __NJS_Class_String(_value);
		}

		__NJS_VAR(string _value)
		{
			setPtr();
			type = __NJS_STRING;
			get().s = new __NJS_Class_String(_value);
		}

		__NJS_VAR(const char *_value)
		{
			setPtr();
			type = __NJS_STRING;
			get().s = new __NJS_Class_String(_value);
		}

		__NJS_VAR(__NJS_Class_Array *_value)
		{
			setPtr();
			type = __NJS_ARRAY;
			get().a = _value;
		}
		__NJS_VAR(__NJS_Class_Object *_value)
		{
			setPtr();
			type = __NJS_OBJECT;
			get().o = _value;
		}
		__NJS_VAR(__NJS_Class_Native *_value)
		{
			setPtr();
			type = __NJS_NATIVE;
			get().n = _value;
		}
		__NJS_VAR(__NJS_TYPE _type, void *_value)
		{
			setPtr();
			type = _type;
			get().f = new __NJS_Class_Function(_value);
		}

		__NJS_VAR(function<__NJS_VAR(vector<var>)> &_value)
		{
			setPtr();
			type = __NJS_FUNCTION;
			get().f = new __NJS_Class_Function(&_value);
		}

		/*** VARIADIC LAMBDAS ***/
		template <class... Args>
		__NJS_VAR(function<__NJS_VAR(Args...)> &_value)
		{
			setPtr();
			type = __NJS_FUNCTION;
			get().f = new __NJS_Class_Function(&_value);
		}
		/*** END VARIADIC LAMBDAS ***/

		/*** CALL OVERLOAD ***/

		template <class... Args>
		__NJS_VAR __NJS_Class_Back_Var_Call_Function(Args... args)
		{
			vector<var> _args = vector<var>{(var)args...};
			return (*static_cast<function<__NJS_VAR(vector<var>)> *>(this->get().f->__NJS_VALUE))(_args);
		}

		template <class... Args>
		__NJS_VAR operator()(Args... args)
		{
			if (this->type != __NJS_FUNCTION)
			{
#ifndef __NJS_ARDUINO
				cout << "[!] Fatal error, object is not a function" << endl;
#endif
				exit(1);
			}
			return __NJS_Class_Back_Var_Call_Function((__NJS_VAR)(args)...);
		}

		/* END CALL OVERLOAD */

		/*** ACCESS OVERLOAD ***/
		// WIP

		__NJS_VAR operator[](__NJS_VAR _index) const
		{
			if (this->type == __NJS_ARRAY && _index.type == __NJS_NUMBER)
			{
				return this->get().a->__NJS_VALUE.at(_index.get().i);
			}
			else if (this->type == __NJS_OBJECT || this->type == __NJS_STRING || this->type == __NJS_FUNCTION || this->type == __NJS_ARRAY || this->type == __NJS_NATIVE)
			{
				vector<pair<const char *, __NJS_VAR>> *_obj;
				if (this->type == __NJS_OBJECT)
					_obj = &this->get().o->__OBJECT;
				else if (this->type == __NJS_ARRAY)
					_obj = &this->get().a->__OBJECT;
				else if (this->type == __NJS_STRING)
					_obj = &this->get().s->__OBJECT;
				else if (this->type == __NJS_FUNCTION)
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

		__NJS_VAR &operator[](__NJS_VAR _index)
		{
			static __NJS_VAR _retFN = __NJS_Create_Var_Scoped_Anon({ return __NJS_VAR(); });

			static __NJS_VAR _retUndefined;

			if (this->type == __NJS_UNDEFINED)
			{
#ifndef __NJS_ARDUINO
				throw __NJS_VAR("Uncaught TypeError: Cannot read property '" + _index.get().s->__NJS_VALUE + "' of undefined");
#endif
			}
			// 1..toString()
			if (this->type == __NJS_NUMBER || this->type == __NJS_DOUBLE)
			{
				if (_index == "toString")
				{
					if (this->type == __NJS_NUMBER)
					{
						REGISTER[_retFN._ptr].f->__NJS_VALUE = __NJS_Create_Ptr_Scoped_Anon({ return to_string((int)*this); });
					}
					else
					{
						REGISTER[_retFN._ptr].f->__NJS_VALUE = __NJS_Create_Ptr_Scoped_Anon({ return to_string((double)*this); });
					}
					return _retFN;
				}
				else if (_index == "valueOf")
				{

					REGISTER[_retFN._ptr].f->__NJS_VALUE = new function<__NJS_VAR(vector<var>)>([&](vector<var> __NJS_VARARGS) { return *this; });
					return _retFN;
				}
				return _retUndefined;
			}

			if (this->type != __NJS_ARRAY && this->type != __NJS_OBJECT && this->type != __NJS_STRING && this->type != __NJS_FUNCTION && this->type != __NJS_NATIVE)
			{
				return _retUndefined;
			}
			if (this->type == __NJS_ARRAY && _index.type == __NJS_NUMBER)
			{
				if ((int)_index > this->get().a->__NJS_VALUE.size())
				{
					return _retUndefined;
				}
				else
				{
					if (this->get().a->__NJS_VALUE.size() <= _index.get().i)
					{
						this->get().a->__NJS_VALUE.reserve(_index.get().i + 1);
						this->get().a->__NJS_VALUE.resize(_index.get().i + 1);
					}

					__NJS_Object_Set("length", (int)this->get().a->__NJS_VALUE.size(), &this->get().a->__OBJECT);
				}
				return this->get().a->__NJS_VALUE[(int)_index];
			}
			else if (this->type == __NJS_STRING && _index.type == __NJS_NUMBER)
			{
				static __NJS_VAR _ret = __NJS_Create_String("");
				__NJS_VAR _tmp = (*this)["substr"](_index, 1);
				REGISTER[_ret._ptr].s->__NJS_VALUE = _tmp.get().s->__NJS_VALUE;
				return _ret;
			}
			else
			{
				if (_index.type != __NJS_STRING)
				{
					return _retUndefined;
				}
				vector<pair<const char *, __NJS_VAR>> *_obj;
				if (this->type == __NJS_OBJECT)
					_obj = &this->get().o->__OBJECT;
				else if (this->type == __NJS_ARRAY)
					_obj = &this->get().a->__OBJECT;
				else if (this->type == __NJS_STRING)
					_obj = &this->get().s->__OBJECT;
				else if (this->type == __NJS_FUNCTION)
					_obj = &this->get().f->__OBJECT;
				else
				{
					return _retUndefined;
				}
				int _j = (*_obj).size();
				for (int _i = 0; _i < _j; _i++)
				{
					if (_index.get().s->__NJS_VALUE.compare((*_obj)[_i].first) == 0)
					{
						return (*_obj)[_i].second;
					}
				}

				_index.get().s->cnt++;
				__NJS_Object_Set(_index.get().s->__NJS_VALUE.c_str(), __NJS_VAR(), _obj);
				return (*this)[_index];
			}
			return _retUndefined;
		}

		/* END ACCESS OVERLOAD */

		/*** END CONSTRUCTOR ***/

		/*** OPERATOR ***/
		__NJS_VAR operator=(const __NJS_VAR &_v)
		{
			if (type == __NJS_OBJECT)
				get().o->Delete();
			else if (type == __NJS_STRING)
				get().s->Delete();
			else if (type == __NJS_FUNCTION)
				get().f->Delete();
			else if (type == __NJS_ARRAY)
				get().a->Delete();
			else if (type == __NJS_NATIVE)
				get().n->Delete();

			type = _v.type;
			;
			if (_v.type == __NJS_OBJECT)
			{
				get() = REGISTER[_v._ptr];
				get().o->cnt++;
			}
			else if (_v.type == __NJS_STRING)
			{
				get().s = new __NJS_Class_String((string)_v);
			}
			else if (_v.type == __NJS_FUNCTION)
			{
				get() = REGISTER[_v._ptr];
				get().f->cnt++;
			}
			else if (_v.type == __NJS_ARRAY)
			{
				get() = REGISTER[_v._ptr];
				get().a->cnt++;
			}
			else if (_v.type == __NJS_NATIVE)
			{
				get() = REGISTER[_v._ptr];
				get().n->cnt++;
			}
			else
				get() = REGISTER[_v._ptr];

			return *this;
		}

		/// Unary operators
		__NJS_VAR operator+()
		{
			if (type == __NJS_NUMBER || type == __NJS_DOUBLE)
				return *this;
			else
				return (double)*this;
		}
		__NJS_VAR operator-()
		{
			if (type == __NJS_NUMBER)
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
			if (type == __NJS_STRING || type == __NJS_ARRAY || type == __NJS_OBJECT || _v1.type == __NJS_STRING)
				return __NJS_Concat_To_Str((string) * this, (string)_v1);
			else if (type == __NJS_NUMBER)
				return __NJS_VAR((int)*this + (int)_v1);
			else if (type == __NJS_DOUBLE)
				return __NJS_VAR((double)*this + (double)_v1);
			else
				return __NJS_VAR();
		}
		__NJS_VAR operator+(const char _v1[])
		{
			return __NJS_Concat_To_Str((string) * this, _v1);
		}
		__NJS_VAR operator+=(const __NJS_VAR &_v1)
		{
			if (type == __NJS_NUMBER)
				get().i += (int)_v1;
			else if (type == __NJS_DOUBLE)
				get().d += (double)_v1;
			else if (type == __NJS_STRING)
				get().s->__NJS_VALUE += (string)_v1;
			else
			{
				string _s = (string) * this;
				type = __NJS_STRING;
				get().s = new __NJS_Class_String("");
				get().s->__NJS_VALUE += _s + (string)_v1;
			}
			return *this;
		}
		__NJS_VAR operator-(const __NJS_VAR &_v1)
		{
			if (type == __NJS_NUMBER)
				return __NJS_VAR((int)*this - (int)_v1);
			else if (type == __NJS_DOUBLE)
				return __NJS_VAR((double)*this - (double)_v1);
			else
				return "NaN";
		}
		__NJS_VAR operator-=(const __NJS_VAR &_v1)
		{
			if (type == __NJS_NUMBER && _v1.type == __NJS_NUMBER)
				get().i -= (int)_v1;
			else if (type == __NJS_NUMBER && _v1.type == __NJS_DOUBLE)
				get().i -= (double)_v1;
			else if (type == __NJS_DOUBLE && _v1.type == __NJS_NUMBER)
				get().d -= (int)_v1;
			else if (type == __NJS_DOUBLE && _v1.type == __NJS_DOUBLE)
				get().d -= (double)_v1;
			else
			{
				type = __NJS_NAN;
				get().s = new __NJS_Class_String("NaN");
			}
			return *this;
		}
		__NJS_VAR operator*(const __NJS_VAR &_v1)
		{
			if (type == __NJS_NUMBER)
				return REGISTER[_ptr].i * (int)_v1;
			else if (type == __NJS_DOUBLE)
				return REGISTER[_ptr].d * (double)_v1;
			return __NJS_VAR();
		}
		__NJS_VAR operator*=(const __NJS_VAR &_v1)
		{
			if (type == __NJS_NUMBER)
				get().i *= (int)_v1;
			else if (type == __NJS_DOUBLE)
				get().d *= (double)_v1;
			return __NJS_VAR();
		}
		__NJS_VAR operator/(const __NJS_VAR &_v1)
		{
			if (type == __NJS_NUMBER)
				return REGISTER[_ptr].i / (int)_v1;
			else if (type == __NJS_DOUBLE)
				return REGISTER[_ptr].d / (double)_v1;
			return __NJS_VAR();
		}
		__NJS_VAR operator/=(const __NJS_VAR &_v1)
		{
			if (type == __NJS_NUMBER)
				get().i /= (int)_v1;
			else if (type == __NJS_DOUBLE)
				get().d /= (double)_v1.get().d;
			return __NJS_VAR();
		}
		__NJS_VAR operator%(const __NJS_VAR &_v1)
		{
			if (type == __NJS_NUMBER && _v1.type == __NJS_NUMBER)
				return REGISTER[_ptr].i % (int)_v1;
			else
			{
				return remainder(REGISTER[_ptr].d, (double)_v1);
			}
		}
		__NJS_VAR operator%=(const __NJS_VAR &_v1)
		{
			if (type == __NJS_NUMBER && _v1.type == __NJS_NUMBER)
			{
				get().i %= (int)_v1;
			}
			else
			{
				type = __NJS_DOUBLE;
				get().d = remainder((double)*this, (double)_v1);
			}
			return *this;
		}
		// TODO: "**" and "**=" operators
		__NJS_VAR operator++(const int _v1)
		{
			if (type == __NJS_NUMBER)
			{
				get().i++;
			}
			else if (type == __NJS_DOUBLE)
			{
				get().d++;
			}
			else
			{
				type = __NJS_DOUBLE;
				get().d = (double)*this;
			}
			return *this;
		}
		__NJS_VAR operator--(const int _v1)
		{
			if (type == __NJS_NUMBER)
				get().i--;
			else if (type == __NJS_DOUBLE)
				get().d--;
			else
			{
				type = __NJS_DOUBLE;
				get().d = (double)*this;
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
				case __NJS_NUMBER:
					return __NJS_Create_Boolean(REGISTER[_ptr].i == (int)_v1);
				case __NJS_DOUBLE:
					return __NJS_Create_Boolean(REGISTER[_ptr].d == (double)_v1);
				//case __NJS_BIGNUMBER: return __NJS_VAR((long)*this == (long)_v1);
				case __NJS_BOOLEAN:
					return __NJS_Create_Boolean(REGISTER[_ptr].b == (bool)_v1);
				case __NJS_STRING:
					return __NJS_Create_Boolean((REGISTER[_ptr].s->__NJS_VALUE).compare((string)_v1) == 0);
				case __NJS_INFINITY:
				case __NJS_NULL:
				case __NJS_UNDEFINED:
					return __NJS_Create_Boolean(true);
				case __NJS_ARRAY:
				case __NJS_NATIVE:
				case __NJS_FUNCTION:
				case __NJS_OBJECT:
				case __NJS_NAN:
					return __NJS_Create_Boolean(false);
				}
			}
			else
			{
				if (type == __NJS_STRING || _v1.type == __NJS_STRING)
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
			if (type == _v1.type && type == __NJS_NUMBER)
				return (int)*this < (int)_v1;
			else
				return (double)*this < (double)_v1;
		}
		__NJS_VAR operator<=(const __NJS_VAR &_v1)
		{
			if (type == _v1.type && type == __NJS_NUMBER)
				return (int)*this <= (int)_v1;
			else
				return (double)*this <= (double)_v1;
		}
		__NJS_VAR operator>(const __NJS_VAR &_v1)
		{
			if (type == _v1.type && type == __NJS_NUMBER)
				return (int)*this > (int)_v1;
			else
				return (double)*this > (double)_v1;
		}
		__NJS_VAR operator>=(const __NJS_VAR &_v1)
		{
			if (type == _v1.type && type == __NJS_NUMBER)
				return (int)*this >= (int)_v1;
			else
				return (double)*this >= (double)_v1;
		}

		/// Bitwise operators
		__NJS_VAR operator&(const __NJS_VAR &_v1) { return (int)*this & (int)_v1; }
		__NJS_VAR operator&=(const __NJS_VAR &_v1)
		{
			type = __NJS_NUMBER;
			get().i = (int)*this & (int)_v1;
			return *this;
		}
		__NJS_VAR operator|(const __NJS_VAR &_v1) { return (int)*this | (int)_v1; }
		__NJS_VAR operator|=(const __NJS_VAR &_v1)
		{
			type = __NJS_NUMBER;
			get().i = (int)*this | (int)_v1;
			return *this;
		}
		__NJS_VAR operator^(const __NJS_VAR &_v1) { return (int)*this ^ (int)_v1; }
		__NJS_VAR operator^=(const __NJS_VAR &_v1)
		{
			type = __NJS_NUMBER;
			get().i = (int)*this ^ (int)_v1;
			return *this;
		}
		__NJS_VAR operator~() { return ~(int)*this; }
		__NJS_VAR operator>>(const __NJS_VAR &_v1) { return (int)*this >> (int)_v1; }
		__NJS_VAR operator>>=(const __NJS_VAR &_v1)
		{
			type = __NJS_NUMBER;
			get().i = (int)*this >> (int)_v1;
			return *this;
		}
		__NJS_VAR operator<<(const __NJS_VAR &_v1)
		{
			return (int)*this << (int)_v1;
		}
		__NJS_VAR operator<<=(const __NJS_VAR &_v1)
		{
			type = __NJS_NUMBER;
			get().i = (int)*this << (int)_v1;
			return *this;
		}
		// TODO: ">>>" and ">>>=" operator support

		explicit operator int() const
		{
			switch (type)
			{
			case __NJS_NUMBER:
				return this->get().i;
			case __NJS_DOUBLE:
				return static_cast<int>(this->get().d);
			//case __NJS_BIGNUMBER: return static_cast<int>(this->get().l);
			case __NJS_BOOLEAN:
				return static_cast<int>(this->get().b);
			case __NJS_STRING:
				return strtol(this->get().s->__NJS_VALUE.c_str(), nullptr, 10);
			case __NJS_ARRAY:
				if (this->get().a->__NJS_VALUE.size() != 1)
					return 0;
				return static_cast<int>(this->get().a->__NJS_VALUE[0]);
			case __NJS_NATIVE:
			case __NJS_FUNCTION:
			case __NJS_OBJECT:
			case __NJS_INFINITY:
			case __NJS_NAN:
			case __NJS_NULL:
			case __NJS_UNDEFINED:
				return 0;
			}
		}

		explicit operator double() const
		{
			switch (type)
			{
			case __NJS_NUMBER:
				return static_cast<double>(this->get().i);
			case __NJS_DOUBLE:
				return this->get().d;
			//case __NJS_BIGNUMBER:
			//	return static_cast<double>(this->get().l);
			case __NJS_BOOLEAN:
				return static_cast<double>(this->get().b);
			case __NJS_STRING:
				return strtod(this->get().s->__NJS_VALUE.c_str(), nullptr);
			case __NJS_ARRAY:
				if (this->get().a->__NJS_VALUE.size() == 0)
					return 0;
				if (this->get().a->__NJS_VALUE.size() > 1)
					return NAN;
				return static_cast<double>(this->get().a->__NJS_VALUE[0]);
			case __NJS_NATIVE:
			case __NJS_FUNCTION:
			case __NJS_OBJECT:
			case __NJS_INFINITY:
			case __NJS_NAN:
			case __NJS_NULL:
			case __NJS_UNDEFINED:
				return 0;
			}
		}

		explicit operator bool() const
		{
			switch (type)
			{
			case __NJS_NUMBER:
				return static_cast<bool>(this->get().i);
			case __NJS_DOUBLE:
				return static_cast<bool>(this->get().d);
			//case __NJS_BIGNUMBER:
			//	return static_cast<bool>(this->get().l);
			case __NJS_BOOLEAN:
				return this->get().b;
			case __NJS_STRING:
				return static_cast<bool>(this->get().s->__NJS_VALUE.size());
			case __NJS_ARRAY:
			case __NJS_NATIVE:
			case __NJS_FUNCTION:
			case __NJS_OBJECT:
			case __NJS_INFINITY:
				return true;
			case __NJS_NAN:
			case __NJS_NULL:
			case __NJS_UNDEFINED:
				return false;
			}
		}

		explicit operator string() const
		{
			switch (type)
			{
			case __NJS_NUMBER:
				return to_string(this->get().i);
			case __NJS_DOUBLE:
				return to_string(this->get().d);
			//case __NJS_BIGNUMBER: return to_string(this->get().l);
			case __NJS_BOOLEAN:
				return (bool)*this ? "true" : "false";
			case __NJS_STRING:
				return this->get().s->__NJS_VALUE;
			case __NJS_ARRAY:
				return __NJS_Object_Stringify(*this, false).get().s->__NJS_VALUE;
			case __NJS_NATIVE:
				return "[native code]";
			case __NJS_FUNCTION:
				return "[Function]";
			case __NJS_OBJECT:
				return "[object Object]";
			case __NJS_INFINITY:
				return "Infinity";
			case __NJS_NAN:
				return "NaN";
			case __NJS_NULL:
				return "null";
			case __NJS_UNDEFINED:
				return "undefined";
			}
		}
	};
} // namespace NJS
