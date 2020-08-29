namespace NJS
{

	struct VAR
	{
	private:
		void setPtr()
		{
			if (_ptr > -1)
			{
				return;
			}
			if (NJS::MEMORY::FREE_PTR > -1)
			{
				_ptr = NJS::MEMORY::FREE[NJS::MEMORY::FREE_PTR--];
			}
			else
			{
				_ptr = NJS::MEMORY::REGISTER_PTR++;
			}
		}

	public:
		NJS::Enum::Type type;
		int _ptr = -1;
		
		inline NJS::VAL get() const
		{
			return NJS::MEMORY::REGISTER[_ptr];
		}

		VAR()
		{
			setPtr();
			type = NJS::Enum::Type::UNDEFINED;
			NJS::MEMORY::REGISTER[_ptr].i = 0;
		}

		~VAR()
		{
			if (type == NJS::Enum::Type::OBJECT)
			{
				NJS::MEMORY::REGISTER[_ptr].o->Delete();
			}
			else if (type == NJS::Enum::Type::STRING)
			{
				NJS::MEMORY::REGISTER[_ptr].s->Delete();
			}
			else if (type == NJS::Enum::Type::FUNCTION)
			{
				NJS::MEMORY::REGISTER[_ptr].f->Delete();
			}
			else if (type == NJS::Enum::Type::ARRAY)
			{
				NJS::MEMORY::REGISTER[_ptr].a->Delete();
			}
			else if (type == NJS::Enum::Type::NATIVE)
			{
				NJS::MEMORY::REGISTER[_ptr].n->Delete();
			}
			NJS::MEMORY::FREE[++NJS::MEMORY::FREE_PTR] = _ptr;
		}

		/**/
		VAR(VAR const &_v)
		{
			setPtr();
			type = _v.type;

			if (_v.type == NJS::Enum::Type::OBJECT)
			{
				NJS::MEMORY::REGISTER[_ptr] = NJS::MEMORY::REGISTER[_v._ptr];
				NJS::MEMORY::REGISTER[_ptr].o->counter++;
			}
			else if (_v.type == NJS::Enum::Type::STRING)
			{

				NJS::MEMORY::REGISTER[_ptr].s = new NJS::Class::String(NJS::MEMORY::REGISTER[_v._ptr].s->value);
			}
			else if (_v.type == NJS::Enum::Type::FUNCTION)
			{
				NJS::MEMORY::REGISTER[_ptr] = NJS::MEMORY::REGISTER[_v._ptr];
				NJS::MEMORY::REGISTER[_ptr].f->counter++;
			}
			else if (_v.type == NJS::Enum::Type::ARRAY)
			{
				NJS::MEMORY::REGISTER[_ptr] = NJS::MEMORY::REGISTER[_v._ptr];
				NJS::MEMORY::REGISTER[_ptr].a->counter++;
			}
			else if (_v.type == NJS::Enum::Type::NATIVE)
			{
				NJS::MEMORY::REGISTER[_ptr] = NJS::MEMORY::REGISTER[_v._ptr];
				NJS::MEMORY::REGISTER[_ptr].n->counter++;
			}
			else
			{
				NJS::MEMORY::REGISTER[_ptr] = NJS::MEMORY::REGISTER[_v._ptr];
			}
		}
		/**/

		/*** CONSTRUCTOR ***/

		VAR(NJS::Enum::Type _type, int _value)
		{
			setPtr();
			this->type = _type;
			NJS::MEMORY::REGISTER[_ptr].i = _value;
		}

		VAR(int _value)
		{
			setPtr();
			this->type = NJS::Enum::Type::NUMBER;
			NJS::MEMORY::REGISTER[_ptr].i = _value;
		}

		VAR(double _value)
		{
			setPtr();
			this->type = NJS::Enum::Type::DOUBLE;
			NJS::MEMORY::REGISTER[_ptr].d = _value;
		}
		
		VAR(long long _value)
		{
			setPtr();
			this->type = NJS::Enum::Type::DOUBLE;
			NJS::MEMORY::REGISTER[_ptr].d = (double)_value;
		}

		VAR(char *_value)
		{
			setPtr();
			type = NJS::Enum::Type::STRING;
			NJS::MEMORY::REGISTER[_ptr].s = new NJS::Class::String(_value);
		}

		VAR(std::string _value)
		{
			setPtr();
			type = NJS::Enum::Type::STRING;
			NJS::MEMORY::REGISTER[_ptr].s = new NJS::Class::String(_value);
		}

		VAR(const char *_value)
		{
			setPtr();
			type = NJS::Enum::Type::STRING;
			NJS::MEMORY::REGISTER[_ptr].s = new NJS::Class::String(_value);
		}

		VAR(NJS::Class::Array *_value)
		{
			setPtr();
			type = NJS::Enum::Type::ARRAY;
			_value->counter++;
			NJS::MEMORY::REGISTER[_ptr].a = _value;
		}
		
		VAR(const NJS::Class::Array *_value)
		{
			setPtr();
			type = NJS::Enum::Type::ARRAY;
			NJS::MEMORY::REGISTER[_ptr].a = (NJS::Class::Array *)_value;
			NJS::MEMORY::REGISTER[_ptr].a->counter++;
		}
		
		VAR(NJS::Class::Boolean *_value)
		{
			setPtr();
			type = NJS::Enum::Type::BOOLEAN;
			_value->counter++;
			NJS::MEMORY::REGISTER[_ptr].b = _value;
		}
		
		VAR(NJS::Class::Function *_value)
		{
			setPtr();
			type = NJS::Enum::Type::FUNCTION;
			_value->counter++;
			NJS::MEMORY::REGISTER[_ptr].f = _value;
		}
		
		VAR(NJS::Class::Object *_value)
		{
			setPtr();
			type = NJS::Enum::Type::OBJECT;
			_value->counter++;
			NJS::MEMORY::REGISTER[_ptr].o = _value;
		}
		
		VAR(NJS::Class::String *_value)
		{
			setPtr();
			type = NJS::Enum::Type::STRING;
			_value->counter++;
			NJS::MEMORY::REGISTER[_ptr].s = new NJS::Class::String(_value->value);
		}
		
		VAR(NJS::Class::Number *_value)
		{
			setPtr();
			type = NJS::Enum::Type::STRING;
			_value->counter++;
			NJS::MEMORY::REGISTER[_ptr].i = 0; // TODO: replace when Class::Number is integrated
		}
		
		VAR(NJS::Class::Native *_value)
		{
			setPtr();
			type = NJS::Enum::Type::NATIVE;
			_value->counter++;
			NJS::MEMORY::REGISTER[_ptr].n = _value;
		}
		VAR(NJS::Enum::Type _type, void *_value)
		{
			setPtr();
			type = _type;
			NJS::MEMORY::REGISTER[_ptr].f = new NJS::Class::Function(_value);
		}

		VAR(function<VAR(vector<var>)> &_value)
		{
			setPtr();
			type = NJS::Enum::Type::FUNCTION;
			NJS::MEMORY::REGISTER[_ptr].f = new NJS::Class::Function(&_value);
		}

		/*** VARIADIC LAMBDAS ***/
		template <class... Args>
		VAR(function<VAR(Args...)> &_value)
		{
			setPtr();
			type = NJS::Enum::Type::FUNCTION;
			NJS::MEMORY::REGISTER[_ptr].f = new NJS::Class::Function(&_value);
		}
		/*** END VARIADIC LAMBDAS ***/
		
		/*** CALL OVERLOAD ***/
		
		template <class... Args>
		VAR __NJS_Class_Back_Var_Call_Function(Args... args)
		{
			vector<var> _args = vector<var>{(var)args...};
			return (*static_cast<function<VAR(vector<var>)> *>(this->get().f->value))(_args);
		}

		template <class... Args>
		VAR operator() (Args... args)
		{
			if (this->type != NJS::Enum::Type::FUNCTION)
			{
		#ifndef __NJS_ARDUINO
				cout << "[!] Fatal error, object is not a function" << endl;
		#endif
				exit(1);
			}
			else return (*this->get().f)((VAR)(args)...);
		}
		
		/* END CALL OVERLOAD */
		
		/*** ACCESS OVERLOAD ***/
		// WIP
		/*
		VAR operator[] (VAR _index) const
		{
			if (this->type == NJS::Enum::Type::ARRAY && _index.type == NJS::Enum::Type::NUMBER)
			{
				return this->get().a->value.at(_index.get().i);
			}
			else if (this->type == NJS::Enum::Type::OBJECT || this->type == NJS::Enum::Type::STRING || this->type == NJS::Enum::Type::FUNCTION || this->type == NJS::Enum::Type::ARRAY || this->type == NJS::Enum::Type::NATIVE)
			{
				vector<pair<const char *, VAR>> *_obj;
				if (this->type == NJS::Enum::Type::OBJECT)
					_obj = &this->get().o->object;
				else if (this->type == NJS::Enum::Type::ARRAY)
					_obj = &this->get().a->object;
				else if (this->type == NJS::Enum::Type::STRING)
					_obj = &this->get().s->object;
				else if (this->type == NJS::Enum::Type::FUNCTION)
					_obj = &this->get().f->object;
				else
				{
					__NJS_RETURN_UNDEFINED;
				}

				_index.get().s->counter++;
				__NJS_Object_Set(_index.get().s->value.c_str(), VAR(), _obj);
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
				throw VAR("Uncaught TypeError: Cannot read property '" + _index.get().s->value + "' of undefined");
				#endif
			}
			
			/*** NEW IMPL ***/
			switch(this->type)
			{
				case NJS::Enum::Type::ARRAY:
					return (*this->get().a)[_index];
				case NJS::Enum::Type::OBJECT:
				    if (_index.type != NJS::Enum::Type::STRING) return _retUndefined;
					return (*this->get().o)[_index];
				break;
				case NJS::Enum::Type::FUNCTION:
					if (_index.type != NJS::Enum::Type::STRING) return _retUndefined;
					return (*this->get().f)[_index];
				break;
				case NJS::Enum::Type::STRING:
					return (*this->get().s)[_index];
				break;
				default:
				break;
			}
			/* END NEW IMPL */
			
			// 1..toString()
			if(this->type == NJS::Enum::Type::NUMBER || this->type == NJS::Enum::Type::DOUBLE)
			{
				if(_index == "toString")
				{
					if(this->type == NJS::Enum::Type::NUMBER)
					{
						NJS::MEMORY::REGISTER[_retFN._ptr].f->value = __NJS_Create_Ptr_Scoped_Anon({ return to_string((int)*this);});
					}
					else 
					{
						NJS::MEMORY::REGISTER[_retFN._ptr].f->value = __NJS_Create_Ptr_Scoped_Anon({ return to_string((double)*this);});
					}
					return _retFN;
				}
				else if(_index == "valueOf")
				{

					NJS::MEMORY::REGISTER[_retFN._ptr].f->value = new function<VAR(vector<var>)>([&](vector<var> _NJS_VARARGS) { return *this;});
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
				NJS::MEMORY::REGISTER[_ptr].o->Delete();
			else if (type == NJS::Enum::Type::STRING)
				NJS::MEMORY::REGISTER[_ptr].s->Delete();
			else if (type == NJS::Enum::Type::FUNCTION)
				NJS::MEMORY::REGISTER[_ptr].f->Delete();
			else if (type == NJS::Enum::Type::ARRAY)
				NJS::MEMORY::REGISTER[_ptr].a->Delete();
			else if (type == NJS::Enum::Type::NATIVE)
				NJS::MEMORY::REGISTER[_ptr].n->Delete();

			type = _v.type;
			;
			if (_v.type == NJS::Enum::Type::OBJECT)
			{
				NJS::MEMORY::REGISTER[_ptr] = NJS::MEMORY::REGISTER[_v._ptr];
				NJS::MEMORY::REGISTER[_ptr].o->counter++;
			}
			else if (_v.type == NJS::Enum::Type::STRING)
			{
				NJS::MEMORY::REGISTER[_ptr].s = new NJS::Class::String((string)_v);
			}
			else if (_v.type == NJS::Enum::Type::FUNCTION)
			{
				NJS::MEMORY::REGISTER[_ptr] = NJS::MEMORY::REGISTER[_v._ptr];
				NJS::MEMORY::REGISTER[_ptr].f->counter++;
			}
			else if (_v.type == NJS::Enum::Type::ARRAY)
			{
				NJS::MEMORY::REGISTER[_ptr] = NJS::MEMORY::REGISTER[_v._ptr];
				NJS::MEMORY::REGISTER[_ptr].a->counter++;
			}
			else if (_v.type == NJS::Enum::Type::NATIVE)
			{
				NJS::MEMORY::REGISTER[_ptr] = NJS::MEMORY::REGISTER[_v._ptr];
				NJS::MEMORY::REGISTER[_ptr].n->counter++;
			}
			else
				NJS::MEMORY::REGISTER[_ptr] = NJS::MEMORY::REGISTER[_v._ptr];

			return *this;
		}

		/// Unary operators
		VAR operator+()
		{
			if (type == NJS::Enum::Type::NUMBER || type == NJS::Enum::Type::DOUBLE)
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
				return VAR((int)*this + (int)_v1);
			else if (type == NJS::Enum::Type::DOUBLE)
				return VAR((double)*this + (double)_v1);
			else return VAR();
			
		}
		VAR operator+(const char _v1[])
		{
			return __NJS_Concat_To_Str((string)*this, _v1);
		}
		VAR operator+=(const VAR &_v1)
		{
			if(type == NJS::Enum::Type::NUMBER) 
				NJS::MEMORY::REGISTER[_ptr].i += (int)_v1;
			else if(type == NJS::Enum::Type::DOUBLE) 
				NJS::MEMORY::REGISTER[_ptr].d += (double)_v1;
			else if(type == NJS::Enum::Type::STRING) 
				NJS::MEMORY::REGISTER[_ptr].s->value += (string)_v1;
			else 
			{
				string _s = (string)*this;
				type = NJS::Enum::Type::STRING;
				NJS::MEMORY::REGISTER[_ptr].s = new NJS::Class::String("");
				NJS::MEMORY::REGISTER[_ptr].s->value += _s + (string)_v1;
			}
			return *this;
		}
		VAR operator-(const VAR &_v1)
		{
			if (type == NJS::Enum::Type::NUMBER )
				return VAR((int)*this - (int)_v1);
			else if (type == NJS::Enum::Type::DOUBLE )
				return VAR((double)*this - (double)_v1);
			else return "NaN";
		}
		VAR operator-=(const VAR &_v1)
		{
			if(type == NJS::Enum::Type::NUMBER && _v1.type == NJS::Enum::Type::NUMBER) 
				NJS::MEMORY::REGISTER[_ptr].i -= (int)_v1;
			else if(type == NJS::Enum::Type::NUMBER && _v1.type == NJS::Enum::Type::DOUBLE) 
				NJS::MEMORY::REGISTER[_ptr].i -= (double)_v1;
			else if(type == NJS::Enum::Type::DOUBLE && _v1.type == NJS::Enum::Type::NUMBER) 
				NJS::MEMORY::REGISTER[_ptr].d -= (int)_v1;
			else if(type == NJS::Enum::Type::DOUBLE && _v1.type == NJS::Enum::Type::DOUBLE) 
				NJS::MEMORY::REGISTER[_ptr].d -= (double)_v1;
			else 
			{
				type = NJS::Enum::Type::ISNAN;
				NJS::MEMORY::REGISTER[_ptr].s = new NJS::Class::String("NaN");
			}
			return *this;
		}
		VAR operator*(const VAR &_v1)
		{
			if(type == NJS::Enum::Type::NUMBER) 
				return NJS::MEMORY::REGISTER[_ptr].i * (int)_v1;
			else if(type == NJS::Enum::Type::DOUBLE) 
				return NJS::MEMORY::REGISTER[_ptr].d * (double)_v1;
			return VAR();
		}
		VAR operator*=(const VAR &_v1)
		{
			if(type == NJS::Enum::Type::NUMBER) 
				NJS::MEMORY::REGISTER[_ptr].i *= (int)_v1;
			else if(type == NJS::Enum::Type::DOUBLE) 
				NJS::MEMORY::REGISTER[_ptr].d *= (double)_v1;
			return VAR();
		}
		VAR operator/(const VAR &_v1)
		{
			if (type == NJS::Enum::Type::NUMBER)
				return NJS::MEMORY::REGISTER[_ptr].i / (int)_v1;
			else if (type == NJS::Enum::Type::DOUBLE)
				return NJS::MEMORY::REGISTER[_ptr].d / (double)_v1;
			return VAR();
		}
		VAR operator/=(const VAR &_v1)
		{
			if(type == NJS::Enum::Type::NUMBER) 
				NJS::MEMORY::REGISTER[_ptr].i /= (int)_v1;
			else if(type == NJS::Enum::Type::DOUBLE) 
				NJS::MEMORY::REGISTER[_ptr].d /= (double)_v1.get().d;
			return VAR();
		}
		VAR operator%(const VAR &_v1)
		{
			if (type == NJS::Enum::Type::NUMBER && _v1.type == NJS::Enum::Type::NUMBER)
				return NJS::MEMORY::REGISTER[_ptr].i % (int)_v1;
			else
			{
				return remainder(NJS::MEMORY::REGISTER[_ptr].d, (double)_v1);
			}
		}
		VAR operator%=(const VAR &_v1)
		{
			if (type == NJS::Enum::Type::NUMBER && _v1.type == NJS::Enum::Type::NUMBER)
			{
				NJS::MEMORY::REGISTER[_ptr].i %= (int)_v1;
			}
			else
			{
				type = NJS::Enum::Type::DOUBLE;
				NJS::MEMORY::REGISTER[_ptr].d = remainder((double)*this, (double)_v1);
			}
			return *this;
		}
		// TODO: "**" and "**=" operators
		VAR operator++(const int _v1)
		{
			if (type == NJS::Enum::Type::NUMBER)
			{
				NJS::MEMORY::REGISTER[_ptr].i++;
			}
			else if (type == NJS::Enum::Type::DOUBLE)
			{
				NJS::MEMORY::REGISTER[_ptr].d++;
			}
			else
			{
				type = NJS::Enum::Type::DOUBLE;
				NJS::MEMORY::REGISTER[_ptr].d = (double)*this;
			}
			return *this;
		}
		VAR operator--(const int _v1)
		{
			if (type == NJS::Enum::Type::NUMBER)
				NJS::MEMORY::REGISTER[_ptr].i--;
			else if (type == NJS::Enum::Type::DOUBLE)
				NJS::MEMORY::REGISTER[_ptr].d--;
			else
			{
				type = NJS::Enum::Type::DOUBLE;
				NJS::MEMORY::REGISTER[_ptr].d = (double)*this;
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
				case NJS::Enum::Type::NUMBER:
					return __NJS_Create_Boolean(NJS::MEMORY::REGISTER[_ptr].i == (int)_v1);
				case NJS::Enum::Type::DOUBLE:
					return __NJS_Create_Boolean(NJS::MEMORY::REGISTER[_ptr].d == (double)_v1);
				//case NJS::Enum::Type::BIGNUMBER: return VAR((long)*this == (long)_v1);
				case NJS::Enum::Type::BOOLEAN:
					return __NJS_Create_Boolean(NJS::MEMORY::REGISTER[_ptr].b == (bool)_v1);
				case NJS::Enum::Type::STRING:
					return __NJS_Create_Boolean((NJS::MEMORY::REGISTER[_ptr].s->value).compare((string)_v1) == 0);
				case NJS::Enum::Type::ISINFINITY:
				case NJS::Enum::Type::ISNULL:
				case NJS::Enum::Type::UNDEFINED:
					return __NJS_Create_Boolean(true);
				case NJS::Enum::Type::ARRAY:
				case NJS::Enum::Type::NATIVE:
				case NJS::Enum::Type::FUNCTION:
				case NJS::Enum::Type::OBJECT:
				case NJS::Enum::Type::ISNAN:
				default: // XXX: Is this correct???
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
			if (type == _v1.type && type == NJS::Enum::Type::NUMBER)
				return (int)*this < (int)_v1;
			else
				return (double)*this < (double)_v1;
		}
		VAR operator<=(const VAR &_v1)
		{
			if (type == _v1.type && type == NJS::Enum::Type::NUMBER)
				return (int)*this <= (int)_v1;
			else
				return (double)*this <= (double)_v1;
		}
		VAR operator>(const VAR &_v1)
		{
			if (type == _v1.type && type == NJS::Enum::Type::NUMBER)
				return (int)*this > (int)_v1;
			else
				return (double)*this > (double)_v1;
		}
		VAR operator>=(const VAR &_v1)
		{
			if (type == _v1.type && type == NJS::Enum::Type::NUMBER)
				return (int)*this >= (int)_v1;
			else
				return (double)*this >= (double)_v1;
		}

		/// Bitwise operators
		VAR operator&(const VAR &_v1) { return (int)*this & (int)_v1; }
		VAR operator&=(const VAR &_v1)
		{
			type = NJS::Enum::Type::NUMBER;
			NJS::MEMORY::REGISTER[_ptr].i = (int)*this & (int)_v1;
			return *this;
		}
		VAR operator|(const VAR &_v1) { return (int)*this | (int)_v1; }
		VAR operator|=(const VAR &_v1)
		{
			type = NJS::Enum::Type::NUMBER;
			NJS::MEMORY::REGISTER[_ptr].i = (int)*this | (int)_v1;
			return *this;
		}
		VAR operator^(const VAR &_v1) { return (int)*this ^ (int)_v1; }
		VAR operator^=(const VAR &_v1)
		{
			type = NJS::Enum::Type::NUMBER;
			NJS::MEMORY::REGISTER[_ptr].i = (int)*this ^ (int)_v1;
			return *this;
		}
		VAR operator~() { return ~(int)*this; }
		VAR operator>>(const VAR &_v1) { return (int)*this >> (int)_v1; }
		VAR operator>>=(const VAR &_v1)
		{
			type = NJS::Enum::Type::NUMBER;
			NJS::MEMORY::REGISTER[_ptr].i = (int)*this >> (int)_v1;
			return *this;
		}
		VAR operator<<(const VAR &_v1) 
		{ 
			return (int)*this << (int)_v1; 
		}
		VAR operator<<=(const VAR &_v1)
		{
			type = NJS::Enum::Type::NUMBER;
			NJS::MEMORY::REGISTER[_ptr].i = (int)*this << (int)_v1;
			return *this;
		}
		// TODO: ">>>" and ">>>=" operator support

		explicit operator int() const
		{
			switch (type)
			{
			case NJS::Enum::Type::NUMBER:
				return this->get().i;
			case NJS::Enum::Type::DOUBLE:
				return static_cast<int>(this->get().d);
			//case NJS::Enum::Type::BIGNUMBER: return static_cast<int>(this->get().l);
			case NJS::Enum::Type::BOOLEAN:
				return static_cast<int>(this->get().b);
			case NJS::Enum::Type::STRING:
				return strtol(this->get().s->value.c_str(), nullptr, 10);
			case NJS::Enum::Type::ARRAY:
				if (this->get().a->value.size() != 1)
					return 0;
				return static_cast<int>(this->get().a->value[0]);
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
				return static_cast<double>(this->get().i);
			case NJS::Enum::Type::DOUBLE:
				return this->get().d;
			//case NJS::Enum::Type::BIGNUMBER:
			//	return static_cast<double>(this->get().l);
			case NJS::Enum::Type::BOOLEAN:
				return static_cast<double>(this->get().b);
			case NJS::Enum::Type::STRING:
				return strtod(this->get().s->value.c_str(), nullptr);
			case NJS::Enum::Type::ARRAY:
				if (this->get().a->value.size() == 0)
					return 0;
				if (this->get().a->value.size() > 1)
					return NAN;
				return static_cast<double>(this->get().a->value[0]);
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
				return static_cast<bool>(this->get().i);
			case NJS::Enum::Type::DOUBLE:
				return static_cast<bool>(this->get().d);
			//case NJS::Enum::Type::BIGNUMBER:
			//	return static_cast<bool>(this->get().l);
			case NJS::Enum::Type::BOOLEAN:
				return this->get().b;
			case NJS::Enum::Type::STRING:
				return static_cast<bool>(this->get().s->value.size());
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
				return to_string(this->get().i);
			case NJS::Enum::Type::DOUBLE:
				return to_string(this->get().d);
			//case NJS::Enum::Type::BIGNUMBER: return to_string(this->get().l);
			case NJS::Enum::Type::BOOLEAN:
				return (bool)*this ? "true" : "false";
			case NJS::Enum::Type::STRING:
				return this->get().s->value;
			case NJS::Enum::Type::ARRAY:
				return __NJS_Object_Stringify(*this, false).get().s->value;
			case NJS::Enum::Type::NATIVE:
				return "[native code]";
			case NJS::Enum::Type::FUNCTION:
				return (std::string)*this->get().f;
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