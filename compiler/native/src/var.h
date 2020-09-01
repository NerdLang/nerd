namespace NJS
{

	struct VAR
	{
	public:
		NJS::Enum::Type type;
		void* _ptr;

		VAR()
		{
			type = NJS::Enum::Type::UNDEFINED;
			_ptr = new NJS::Class::Undefined();
		}
		
		template <typename T>
		void DeleteByType(T type)
		{
			type->Delete();
		}

		~VAR()
		{
			if (type == NJS::Enum::Type::OBJECT)
			{
				((NJS::Class::Object*)_ptr)->Delete();
			}
			else if (type == NJS::Enum::Type::STRING)
			{
				((NJS::Class::String*)_ptr)->Delete();
			}
			else if (type == NJS::Enum::Type::FUNCTION)
			{
				((NJS::Class::Function*)_ptr)->Delete();
			}
			else if (type == NJS::Enum::Type::ARRAY)
			{
				((NJS::Class::Array*)_ptr)->Delete();
			}
			else if (type == NJS::Enum::Type::NATIVE)
			{
				((NJS::Class::Native*)_ptr)->Delete();
			}
			else if (type == NJS::Enum::Type::NUMBER)
			{
				((NJS::Class::Number*)_ptr)->Delete();
			}
			else if (type == NJS::Enum::Type::UNDEFINED)
			{
				((NJS::Class::Undefined*)_ptr)->Delete();
			}
			else if (type == NJS::Enum::Type::BOOLEAN)
			{
				((NJS::Class::Boolean*)_ptr)->Delete();
			}
		}

		/**/
		VAR(VAR const &_v)
		{
			
			type = _v.type;

			if (_v.type == NJS::Enum::Type::OBJECT)
			{
				_ptr = _v._ptr;
				((NJS::Class::Object*)_ptr)->counter++;
			}
			else if (_v.type == NJS::Enum::Type::STRING)
			{
				_ptr = new NJS::Class::String(((NJS::Class::String*)_v._ptr)->value);
			}
			else if (_v.type == NJS::Enum::Type::NUMBER)
			{
				_ptr = new NJS::Class::Number(((NJS::Class::Number*)_v._ptr));
			}
			else if (_v.type == NJS::Enum::Type::FUNCTION)
			{
				_ptr = _v._ptr;
				((NJS::Class::Function*)_ptr)->counter++;
			}
			else if (_v.type == NJS::Enum::Type::ARRAY)
			{
				_ptr = _v._ptr;
				((NJS::Class::Array*)_ptr)->counter++;
			}
			else if (_v.type == NJS::Enum::Type::NATIVE)
			{
				_ptr = _v._ptr;
				((NJS::Class::Native*)_ptr)->counter++;
			}
			else if (_v.type == NJS::Enum::Type::BOOLEAN)
			{
				_ptr = _v._ptr;
				((NJS::Class::Boolean*)_ptr)->counter++;
			}
			else if (_v.type == NJS::Enum::Type::UNDEFINED)
			{
				_ptr = _v._ptr;
				((NJS::Class::Undefined*)_ptr)->counter++;
			}
			else
			{
				_ptr = _v._ptr;
			}
		}
		/**/

		/*** CONSTRUCTOR ***/

		VAR(NJS::Enum::Type _type, int _value)
		{
			this->type = _type;
			_ptr = new NJS::Class::Number(_value);
		}

		VAR(int _value)
		{
			this->type = NJS::Enum::Type::NUMBER;
			_ptr = new NJS::Class::Number(_value);
		}

		VAR(double _value)
		{
			this->type = NJS::Enum::Type::NUMBER;
			_ptr = new NJS::Class::Number(_value);
		}
		
		VAR(long long _value)
		{
			this->type = NJS::Enum::Type::NUMBER;
			_ptr = new NJS::Class::Number(_value);
		}

		VAR(char *_value)
		{
			type = NJS::Enum::Type::STRING;
			_ptr = new NJS::Class::String(_value);
		}

		VAR(std::string _value)
		{
			type = NJS::Enum::Type::STRING;
			_ptr = new NJS::Class::String(_value);
		}

		VAR(const char *_value)
		{
			type = NJS::Enum::Type::STRING;
			_ptr = new NJS::Class::String(_value);
		}

		VAR(NJS::Class::Array *_value)
		{
			type = NJS::Enum::Type::ARRAY;
			_value->counter++;
			_ptr = _value;
		}
		
		VAR(const NJS::Class::Array *_value)
		{
			type = NJS::Enum::Type::ARRAY;
			_ptr = (NJS::Class::Array *)_value;
			((NJS::Class::Array*)_ptr)->counter++;
		}
		
		VAR(NJS::Class::Boolean *_value)
		{
			type = NJS::Enum::Type::BOOLEAN;
			_value->counter++;
			_ptr = _value;
		}
		
		VAR(NJS::Class::Function *_value)
		{
			type = NJS::Enum::Type::FUNCTION;
			_value->counter++;
			_ptr = _value;
		}
		
		VAR(NJS::Class::Object *_value)
		{
			type = NJS::Enum::Type::OBJECT;
			_value->counter++;
			_ptr = _value;
		}
		
		VAR(NJS::Class::String *_value)
		{
			type = NJS::Enum::Type::STRING;
			_value->counter++;
			_ptr = new NJS::Class::String(_value->value);
		}
		
		VAR(NJS::Class::Number _value)
		{
			type = NJS::Enum::Type::NUMBER;
			_ptr = new NJS::Class::Number(_value);
		}
		
		VAR(NJS::Class::Number *_value)
		{
			type = NJS::Enum::Type::NUMBER;
			_value->counter++;
			_ptr = _value;
		}
		
		VAR(NJS::Class::Native *_value)
		{
			type = NJS::Enum::Type::NATIVE;
			_value->counter++;
			_ptr = _value;
		}
		
		VAR(NJS::Class::Undefined *_value)
		{
			type = NJS::Enum::Type::UNDEFINED;
			_value->counter++;
			_ptr = _value;
		}
		
		VAR(NJS::Enum::Type _type, void *_value)
		{
			type = _type;
			_ptr = new NJS::Class::Function(_value);
		}

		VAR(function<VAR(vector<var>)> &_value)
		{
			type = NJS::Enum::Type::FUNCTION;
			_ptr = new NJS::Class::Function(&_value);
		}

		template <class... Args>
		VAR operator() (Args... args)
		{
			if (this->type != NJS::Enum::Type::FUNCTION)
			{
		#ifndef __NJS_ARDUINO
				throw NJS::VAR("TypeError: object is not a function");
		#endif
				exit(1);
			}
			else return (*(NJS::Class::Function*)_ptr)((VAR)(args)...);
		}
		
		/* END CALL OVERLOAD */
		
		/*** ACCESS OVERLOAD ***/
		// WIP
		/*
		VAR operator[] (VAR _index) const
		{
			if (this->type == NJS::Enum::Type::ARRAY && _index.type == NJS::Enum::Type::NUMBER)
			{
				return ((NJS::Class::Array*)_ptr)->value.at(_index.get().i);
			}
			else if (this->type == NJS::Enum::Type::OBJECT || this->type == NJS::Enum::Type::STRING || this->type == NJS::Enum::Type::FUNCTION || this->type == NJS::Enum::Type::ARRAY || this->type == NJS::Enum::Type::NATIVE)
			{
				vector<pair<const char *, VAR>> *_obj;
				if (this->type == NJS::Enum::Type::OBJECT)
					_obj = &this->get().o->object;
				else if (this->type == NJS::Enum::Type::ARRAY)
					_obj = &((NJS::Class::Array*)_ptr)->object;
				else if (this->type == NJS::Enum::Type::STRING)
					_obj = &((NJS::Class::String*)_ptr)->object;
				else if (this->type == NJS::Enum::Type::FUNCTION)
					_obj = &this->get().f->object;
				else
				{
					__NJS_RETURN_UNDEFINED;
				}

				((NJS::Class::String*)_ptr)->counter++;
				__NJS_Object_Set(((NJS::Class::String*)_ptr)->value.c_str(), VAR(), _obj);
				return (*this)[_index];
			}

			__NJS_RETURN_UNDEFINED;
		}
		
		
		*/
		VAR & operator[] (VAR _index)
		{
			static VAR _retFN = __NJS_Create_Var_Scoped_Anon({ return VAR();});
			static VAR _retObj;
			static VAR _retUndefined;

			if(this->type == NJS::Enum::Type::UNDEFINED)
			{

				#ifndef __NJS_ARDUINO
				throw VAR("Uncaught TypeError: Cannot read property '" + ((NJS::Class::String*)_ptr)->value + "' of undefined");
				#endif
			}
			
			/*** NEW IMPL ***/
			switch(this->type)
			{
				case NJS::Enum::Type::ARRAY:
					return (*(NJS::Class::Array*)_ptr)[_index];
				case NJS::Enum::Type::OBJECT:
				    if (_index.type != NJS::Enum::Type::STRING) return _retUndefined;
					return ((*(NJS::Class::Object*)_ptr)[_index]);
				break;
				case NJS::Enum::Type::FUNCTION:
					if (_index.type != NJS::Enum::Type::STRING) return _retUndefined;
					return (*(NJS::Class::Function*)_ptr)[_index];
				break;
				case NJS::Enum::Type::STRING:
					return (*(NJS::Class::String*)_ptr)[_index];
				break;
				case NJS::Enum::Type::NUMBER:
					return ((*(NJS::Class::Number*)_ptr))[_index];
				break;
				case NJS::Enum::Type::BOOLEAN:
					return (*(NJS::Class::Boolean*)_ptr)[_index];
				break;
				case NJS::Enum::Type::UNDEFINED:
					return (*(NJS::Class::Undefined*)_ptr)[_index];
				break;
				default:
				break;
			}
			/* END NEW IMPL */

			// 1..toString()
			if(this->type == NJS::Enum::Type::NUMBER)
			{
				if(_index == "toString")
				{
					if(this->type == NJS::Enum::Type::NUMBER)
					{
						((NJS::Class::Function*)_ptr)->value = __NJS_Create_Ptr_Scoped_Anon({ return to_string((int)*this);});
					}
					else 
					{
						((NJS::Class::Function*)_ptr)->value = __NJS_Create_Ptr_Scoped_Anon({ return to_string((double)*this);});
					}
					return _retFN;
				}
				else if(_index == "valueOf")
				{

					((NJS::Class::Function*)_ptr)->value = new function<VAR(vector<var>)>([&](vector<var> _NJS_VARARGS) { return *this;});
					return _retFN;
				}
				return _retUndefined;
			}
			
			return _retUndefined;
		}
		
		/* END ACCESS OVERLOAD */

		/*** END CONSTRUCTOR ***/

		/*** OPERATOR ***/
		VAR operator=(const VAR &_v)
		{
			if (type == NJS::Enum::Type::OBJECT)
				((NJS::Class::Object*)_ptr)->Delete();
			else if (type == NJS::Enum::Type::STRING)
				((NJS::Class::String*)_ptr)->Delete();
			else if (type == NJS::Enum::Type::FUNCTION)
				((NJS::Class::Function*)_ptr)->Delete();
			else if (type == NJS::Enum::Type::ARRAY)
				((NJS::Class::Array*)_ptr)->Delete();
			else if (type == NJS::Enum::Type::NATIVE)
				((NJS::Class::Native*)_ptr)->Delete();
			else if (type == NJS::Enum::Type::NUMBER)
				((NJS::Class::Number*)_ptr)->Delete();
			else if (type == NJS::Enum::Type::UNDEFINED)
				((NJS::Class::Undefined*)_ptr)->Delete();
			else if (type == NJS::Enum::Type::BOOLEAN)
				((NJS::Class::Boolean*)_ptr)->Delete();

			type = _v.type;

			if (_v.type == NJS::Enum::Type::OBJECT)
			{
				_ptr = _v._ptr;
				((NJS::Class::Object*)_ptr)->counter++;
			}
			else if (_v.type == NJS::Enum::Type::STRING)
			{
				_ptr = new NJS::Class::String((string)_v);
			}
			else if (_v.type == NJS::Enum::Type::NUMBER)
			{
				_ptr = new NJS::Class::Number((NJS::Class::Number*)_v._ptr);
			}
			else if (_v.type == NJS::Enum::Type::FUNCTION)
			{
				_ptr = _v._ptr;
				((NJS::Class::Function*)_ptr)->counter++;
			}
			else if (_v.type == NJS::Enum::Type::ARRAY)
			{
				_ptr = _v._ptr;
				((NJS::Class::Array*)_ptr)->counter++;
			}
			else if (_v.type == NJS::Enum::Type::NATIVE)
			{
				_ptr = _v._ptr;
				((NJS::Class::Native*)_ptr)->counter++;
			}
			else if (_v.type == NJS::Enum::Type::BOOLEAN)
			{
				_ptr = _v._ptr;
				((NJS::Class::Boolean*)_ptr)->counter++;
			}
			else if (_v.type == NJS::Enum::Type::UNDEFINED)
			{
				_ptr = _v._ptr;
				((NJS::Class::Undefined*)_ptr)->counter++;
			}
			else
			{
				_ptr = _v._ptr;
			}

			return *this;
		}

		/// Unary operators
		VAR operator+()
		{
			if (type == NJS::Enum::Type::NUMBER)
				return *this;
			else
				return (double)*this;
		}
		VAR operator-()
		{
			if (type == NJS::Enum::Type::NUMBER)
				return -(int)*this;
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
			if (type == NJS::Enum::Type::STRING || type == NJS::Enum::Type::ARRAY || type == NJS::Enum::Type::OBJECT || _v1.type == NJS::Enum::Type::STRING)
				return __NJS_Concat_To_Str((string) * this, (string)_v1);
			else if (type == NJS::Enum::Type::NUMBER)
			{
				return ((*(NJS::Class::Number*)_ptr)) + _v1;
			}
			else return VAR();
			
		}
		VAR operator+(const char _v1[])
		{
			return __NJS_Concat_To_Str((string)*this, _v1);
		}
		VAR operator+=(const VAR &_v1)
		{
			if(type == NJS::Enum::Type::NUMBER) 
				(*((NJS::Class::Number*)_ptr)) += _v1;
			else if(type == NJS::Enum::Type::STRING) 
				((NJS::Class::String*)_ptr)->value += (string)_v1;
			else 
			{
				string _s = (string)*this;
				type = NJS::Enum::Type::STRING;
				_ptr = new NJS::Class::String("");
				((NJS::Class::String*)_ptr)->value += _s + (string)_v1;
			}
			return *this;
		}
		VAR operator-(const VAR &_v1)
		{
			if (type == NJS::Enum::Type::NUMBER )
				return ((*(NJS::Class::Number*)_ptr)) - _v1;
			else return "NaN";
		}
		VAR operator-=(const VAR &_v1)
		{
			if(type == NJS::Enum::Type::NUMBER && _v1.type == NJS::Enum::Type::NUMBER) 
				(*((NJS::Class::Number*)_ptr)) -= _v1;
			else 
			{
				type = NJS::Enum::Type::ISNAN;
				_ptr = new NJS::Class::String("NaN");
			}
			return *this;
		}
		VAR operator*(const VAR &_v1)
		{
			if(type == NJS::Enum::Type::NUMBER) 
				return (*((NJS::Class::Number*)_ptr)) * _v1;
			return VAR();
		}
		VAR operator*=(const VAR &_v1)
		{
			if(type == NJS::Enum::Type::NUMBER) 
				(*((NJS::Class::Number*)_ptr)) *= _v1;
			return VAR();
		}
		VAR operator/(const VAR &_v1)
		{
			if (type == NJS::Enum::Type::NUMBER)
				return (*((NJS::Class::Number*)_ptr)) / _v1;
			return VAR();
		}
		VAR operator/=(const VAR &_v1)
		{
			if(type == NJS::Enum::Type::NUMBER) 
				(*((NJS::Class::Number*)_ptr)) /= _v1;
			return VAR();
		}
		VAR operator%(const VAR &_v1)
		{
			if (type == NJS::Enum::Type::NUMBER && _v1.type == NJS::Enum::Type::NUMBER)
				return (*((NJS::Class::Number*)_ptr)) % _v1;
			else
			{
				return remainder((int)(*((NJS::Class::Number*)_ptr)), (int)_v1);
			}
		}
		VAR operator%=(const VAR &_v1)
		{
			if (type == NJS::Enum::Type::NUMBER && _v1.type == NJS::Enum::Type::NUMBER)
			{
				(*((NJS::Class::Number*)_ptr)) %= _v1;
			}
			else
			{
				_ptr = new NJS::Class::Number(remainder((int)*this, (int)_v1));
			}
			return *this;
		}
		// TODO: "**" and "**=" operators
		VAR operator++(const int _v1)
		{
			if (type == NJS::Enum::Type::NUMBER)
			{
				(*((NJS::Class::Number*)_ptr))++;
			}
			return *this;
		}
		VAR operator--(const int _v1)
		{
			if (type == NJS::Enum::Type::NUMBER)
				(*((NJS::Class::Number*)_ptr))--;
			return *this;
		}

		/// Comparison operators
		VAR operator==(const VAR &_v1)
		{
			if (type == _v1.type)
			{
				switch (type)
				{
				case NJS::Enum::Type::NUMBER:
					return (bool)((*((NJS::Class::Number*)_ptr)) == (int)_v1);
				case NJS::Enum::Type::BOOLEAN:
					return __NJS_Create_Boolean((bool)((NJS::Class::Boolean*)_ptr) == (bool)_v1);
				case NJS::Enum::Type::STRING:
					return __NJS_Create_Boolean((((NJS::Class::String*)_ptr)->value).compare((string)_v1) == 0);
				case NJS::Enum::Type::ISINFINITY:
				case NJS::Enum::Type::ISNULL:
				case NJS::Enum::Type::UNDEFINED:
					return __NJS_Create_Boolean(true);
				case NJS::Enum::Type::ARRAY:
				case NJS::Enum::Type::NATIVE:
				case NJS::Enum::Type::FUNCTION:
				case NJS::Enum::Type::OBJECT:
				case NJS::Enum::Type::ISNAN:
				default:
					return __NJS_Create_Boolean(false);
				}
			}
			else
			{
				if (type == NJS::Enum::Type::STRING || _v1.type == NJS::Enum::Type::STRING)
				{
					return __NJS_Create_Boolean((string) * this == (string)_v1);
				}
				else
					return __NJS_Create_Boolean((double)*this == (double)_v1);
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
			return (int)*this < (int)_v1;
		}
		VAR operator<=(const VAR &_v1)
		{
			return (int)*this <= (int)_v1;
		}
		VAR operator>(const VAR &_v1)
		{
			return (int)*this > (int)_v1;
		}
		VAR operator>=(const VAR &_v1)
		{
			return (int)*this >= (int)_v1;
		}

		/// Bitwise operators
		VAR operator&(const VAR &_v1) { return (int)*this & (int)_v1; }
		VAR operator&=(const VAR &_v1)
		{
			type = NJS::Enum::Type::NUMBER;
			_ptr = new NJS::Class::Number((int)*this & (int)_v1);
			return *this;
		}
		VAR operator|(const VAR &_v1) { return (int)*this | (int)_v1; }
		VAR operator|=(const VAR &_v1)
		{
			type = NJS::Enum::Type::NUMBER;
			_ptr = new NJS::Class::Number((int)*this | (int)_v1);
			return *this;
		}
		VAR operator^(const VAR &_v1) { return (int)*this ^ (int)_v1; }
		VAR operator^=(const VAR &_v1)
		{
			type = NJS::Enum::Type::NUMBER;
			_ptr = new NJS::Class::Number((int)*this ^ (int)_v1);
			return *this;
		}
		VAR operator~() { return ~(int)*this; }
		VAR operator>>(const VAR &_v1) { return (int)*this >> (int)_v1; }
		VAR operator>>=(const VAR &_v1)
		{
			type = NJS::Enum::Type::NUMBER;
			_ptr = new NJS::Class::Number((int)*this >> (int)_v1);
			return *this;
		}
		VAR operator<<(const VAR &_v1) 
		{ 
			return (int)*this << (int)_v1; 
		}
		VAR operator<<=(const VAR &_v1)
		{
			type = NJS::Enum::Type::NUMBER;
			_ptr = new NJS::Class::Number((int)*this << (int)_v1);
			return *this;
		}
		// TODO: ">>>" and ">>>=" operator support

		explicit operator int() const
		{
			switch (type)
			{
			case NJS::Enum::Type::NUMBER:
				return (int)(*(NJS::Class::Number*)_ptr);
			case NJS::Enum::Type::BOOLEAN:
				return (int)(*(NJS::Class::Boolean*)_ptr);
			case NJS::Enum::Type::STRING:
				return strtol(((NJS::Class::String*)_ptr)->value.c_str(), nullptr, 10);
			case NJS::Enum::Type::ARRAY:
				if (((NJS::Class::Array*)_ptr)->value.size() != 1)
					return 0;
				return static_cast<int>(((NJS::Class::Array*)_ptr)->value[0]);
			case NJS::Enum::Type::NATIVE:
			case NJS::Enum::Type::FUNCTION:
			case NJS::Enum::Type::OBJECT:
			case NJS::Enum::Type::ISINFINITY:
			case NJS::Enum::Type::ISNAN:
			case NJS::Enum::Type::ISNULL:
			case NJS::Enum::Type::UNDEFINED:
			default:
				return 0;
			}
		}

		explicit operator double() const
		{
			switch (type)
			{
			case NJS::Enum::Type::NUMBER:
				return (double)((*(NJS::Class::Number*)_ptr));
			case NJS::Enum::Type::BOOLEAN:
				return (double)(*(NJS::Class::Boolean*)_ptr);
			case NJS::Enum::Type::STRING:
				 return (double)(*(NJS::Class::String*)_ptr);
			case NJS::Enum::Type::ARRAY:
				if (((NJS::Class::Array*)_ptr)->value.size() == 0)
					return 0;
				if (((NJS::Class::Array*)_ptr)->value.size() > 1)
					return NAN;
				return static_cast<double>(((NJS::Class::Array*)_ptr)->value[0]);
			case NJS::Enum::Type::NATIVE:
			case NJS::Enum::Type::FUNCTION:
			case NJS::Enum::Type::OBJECT:
			case NJS::Enum::Type::ISINFINITY:
			case NJS::Enum::Type::ISNAN:
			case NJS::Enum::Type::ISNULL:
			case NJS::Enum::Type::UNDEFINED:
			default:
				return 0;
			}
		}

		explicit operator bool() const
		{
			switch (type)
			{
			case NJS::Enum::Type::NUMBER:
				return (bool)((*(NJS::Class::Number*)_ptr));
			case NJS::Enum::Type::BOOLEAN:
				return (NJS::Class::Boolean*)this;
			case NJS::Enum::Type::STRING:
				return (bool)((NJS::Class::String*)_ptr);
			case NJS::Enum::Type::ARRAY:
			case NJS::Enum::Type::NATIVE:
			case NJS::Enum::Type::FUNCTION:
			case NJS::Enum::Type::OBJECT:
			case NJS::Enum::Type::ISINFINITY:
				return true;
			case NJS::Enum::Type::ISNAN:
			case NJS::Enum::Type::ISNULL:
			case NJS::Enum::Type::UNDEFINED:
			default:
				return false;
			}
		}

		explicit operator string() const
		{
			switch (type)
			{
			case NJS::Enum::Type::NUMBER:
				return (string)((*(NJS::Class::Number*)_ptr));
			case NJS::Enum::Type::BOOLEAN:
				return (bool)*this ? "true" : "false";
			case NJS::Enum::Type::STRING:
				return ((NJS::Class::String*)_ptr)->value;
			case NJS::Enum::Type::ARRAY:
				return ((NJS::Class::String*)__NJS_Object_Stringify(*this, false)._ptr)->value;
			case NJS::Enum::Type::NATIVE:
				return "[native code]";
			case NJS::Enum::Type::FUNCTION:
				return (std::string)(*(NJS::Class::Function*)_ptr);
			case NJS::Enum::Type::OBJECT:
				return "[object Object]";
			case NJS::Enum::Type::ISINFINITY:
				return "Infinity";
			case NJS::Enum::Type::ISNAN:
				return "NaN";
			case NJS::Enum::Type::ISNULL:
				return "null";
			case NJS::Enum::Type::UNDEFINED:
			default:
				return "undefined";
			}
		}
		
		explicit operator const char*() const
		{
			return ((string)*this).c_str();
		}
		
		explicit operator const long long() const
		{
			return (long long)((double)*this);
		}

		
	};
} // namespace NJS