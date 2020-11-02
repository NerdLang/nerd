
namespace NJS
{
	
	VAR::VAR()
	{
		type = NJS::Enum::Type::Undefined;
		data.ptr = undefined.data.ptr;
	}

	VAR::~VAR()
	{
		if(type > NJS::Enum::Type::Number) ((NJS::Class::Base*)data.ptr)->Delete();
	}

	/*** COPY ***/
	 VAR::VAR(VAR const &_v)
	{
		if(property[0] != 0) return;
		
		property = _v.property;
		type = _v.type;
		if(type < NJS::Enum::Type::String)
		{
			data.number = (double)_v;
			//if(type == _v.type) data.number = _v.data.number;
			//else data.number = (double)_v;
		}
		else data.ptr = ((NJS::Class::Base*)_v.data.ptr)->Copy();
		
	}
	/* END COPY */
	
	/*** MOVE ***/
	VAR::VAR(VAR const &&_v)
	{
		property = _v.property;
		type = _v.type;
		if(type < NJS::Enum::Type::String)
		{
			data.number = _v.data.number;
		}
		else data.ptr = ((NJS::Class::Base*)_v.data.ptr)->Copy();
	}
	/* END MOVE */
	
	/*** CONSTRUCTOR ***/

	VAR::VAR(NJS::Enum::Type _type, int _value)
	{
		this->type = _type;
		data.number = _value;
	}
	
	VAR::VAR(NJS::Enum::Type _type, double _value)
	{
		this->type = _type;
		data.number = _value;
	}

	VAR::VAR(int _value)
	{
		this->type = NJS::Enum::Type::Number;
		data.number = _value;
	}

	VAR::VAR(double _value)
	{
		this->type = NJS::Enum::Type::Number;
		data.number = _value;
	}
	
	VAR::VAR(long long _value)
	{
		this->type = NJS::Enum::Type::Number;
		data.number = _value;
	}

	VAR::VAR(char *_value)
	{
		type = NJS::Enum::Type::String;
		data.ptr = new NJS::Class::String(_value);
	}

	VAR::VAR(std::string _value)
	{
		type = NJS::Enum::Type::String;
		data.ptr = new NJS::Class::String(_value);
	}

	VAR::VAR(const char *_value)
	{
		type = NJS::Enum::Type::String;
		data.ptr = new NJS::Class::String(_value);
	}

	VAR::VAR(NJS::Class::Array *_value)
	{
		type = NJS::Enum::Type::Array;
		_value->counter++;
		data.ptr = _value;
	}
	
	VAR::VAR(const NJS::Class::Array *_value)
	{
		type = NJS::Enum::Type::Array;
		data.ptr = (NJS::Class::Array *)_value;
		((NJS::Class::Array*)data.ptr)->counter++;
	}
	
	VAR::VAR(bool _value)
	{
		type = NJS::Enum::Type::Boolean;
		data.number =_value;
	}
	
	VAR::VAR(NJS::Class::Function *_value)
	{
		type = NJS::Enum::Type::Function;
		_value->counter++;
		data.ptr = _value;
	}
	
	VAR::VAR(NJS::Class::Object *_value)
	{
		type = NJS::Enum::Type::Object;
		_value->counter++;
		data.ptr = _value;
	}
	
	VAR::VAR(NJS::Class::String *_value)
	{
		type = NJS::Enum::Type::String;
		data.ptr = new NJS::Class::String(_value->value);
	}
	
	VAR::VAR(NJS::Class::Native *_value)
	{
		type = NJS::Enum::Type::Native;
		_value->counter++;
		data.ptr = _value;
	}
	
	VAR::VAR(NJS::Class::Undefined *_value)
	{
		type = NJS::Enum::Type::Undefined;
		data.ptr = _value;
	}
	
	VAR::VAR(NJS::Enum::Type _type, void *_value)
	{
		type = _type;
		data.ptr = new NJS::Class::Function(_value);
	}
	
	VAR::VAR(NJS::Enum::Type _type, void *_value, var _this)
	{
		type = _type;
		data.ptr = new NJS::Class::Function(_value);
		if(_this.data.ptr == ::__NJS_THIS.data.ptr) ((NJS::Class::Object*)_this.data.ptr)->counter++;

		((NJS::Class::Function*)data.ptr)->This.data.ptr = _this.data.ptr;
		((NJS::Class::Function*)data.ptr)->This.type = _this.type;

	}

	template <class... Args>
	VAR VAR::operator() (Args... args)
	{
		if (type != NJS::Enum::Type::Function)
		{
	#ifndef __NJS_NO_EXCEPT
			throw NJS::VAR("TypeError: object is not a function");
	#endif
			exit(1);
		}
		else return (*(NJS::Class::Function*)data.ptr)((VAR)(args)...);
	}
	
	template <class... Args>
	VAR VAR::operator() (Args... args) const
	{
		if (type != NJS::Enum::Type::Function)
		{
	#ifndef __NJS_NO_EXCEPT
			throw NJS::VAR("TypeError: object is not a function");
	#endif
			exit(1);
		}
		else return (*(NJS::Class::Function*)data.ptr)((VAR)(args)...);
	}
	
	/* END CALL OVERLOAD */

	VAR & VAR::operator[] (VAR _index)
	{
		if(type < NJS::Enum::Type::String) return NJS::Class::NUMBER::Accessor(*this, _index);
		return (*(NJS::Class::Base*)data.ptr)[_index];
	}
	
	VAR & VAR::operator[] (VAR _index) const
	{
		if(type < NJS::Enum::Type::String) return NJS::Class::NUMBER::Accessor(*this, _index);
		return (*(NJS::Class::Base*)data.ptr)[_index];
	}
	
	VAR & VAR::operator[] (int _index) const
	{
		if(type < NJS::Enum::Type::String) return undefined;
		return (*(NJS::Class::Base*)data.ptr)[NJS::VAR(_index)];
	}
	
	VAR & VAR::operator[] (int _index)
	{
		if(type < NJS::Enum::Type::String) return undefined;
		return (*(NJS::Class::Base*)data.ptr)[NJS::VAR(_index)];
	}
	
	VAR & VAR::operator[] (const char* _index)
	{
		if(type < NJS::Enum::Type::String) return NJS::Class::NUMBER::Accessor(*this, NJS::VAR(_index));
		return (*(NJS::Class::Base*)data.ptr)[_index];
	}
	
	/* END ACCESS OVERLOAD */

	/*** END CONSTRUCTOR ***/

	/*** OPERATOR ***/
	void VAR::operator=(const VAR &_v)
	{
		if(property[0] != 0) return;
		
		property = _v.property;
		type = _v.type;
		if(type < NJS::Enum::Type::String)
		{
			data.number = (double)_v;
			//if(type == _v.type) data.number = _v.data.number;
			//else data.number = (double)_v;
		}
		else data.ptr = ((NJS::Class::Base*)_v.data.ptr)->Copy();
	}

	/// Unary VAR::operators
	VAR VAR::operator+()
	{
		if(type < NJS::Enum::Type::String) return data.number;
		return (double)*this;
	}
	
	VAR VAR::operator-()
	{
		if(type < NJS::Enum::Type::String) return -data.number;
		return -(double)*this;
	}
	VAR VAR::operator!() 
	{ 
		if(type < NJS::Enum::Type::String) return !data.number;
		return !(bool)*this; 
	};

	/// Logical VAR::operators
	VAR VAR::operator&&(const VAR &_v1) { return (bool)*this && (bool)_v1; }
	VAR VAR::operator||(const VAR &_v1) { return (bool)*this || (bool)_v1; }

	/// Arithmetic VAR::operators
	VAR VAR::operator+(const VAR &_v1)
	{
		if (type < NJS::Enum::Type::String) return data.number + _v1;
		else if (type == NJS::Enum::Type::String || type == NJS::Enum::Type::Array || type == NJS::Enum::Type::Object || _v1.type == NJS::Enum::Type::String)
			return __NJS_Concat_To_Str((std::string) * this, (std::string)_v1);
		else return VAR();
		
	}
	VAR VAR::operator+(const char _v1[])
	{
		return __NJS_Concat_To_Str((std::string)*this, _v1);
	}
	
	void VAR::operator+=(const VAR &_v1)
	{
		if(type < NJS::Enum::Type::String) data.number += _v1;
		else if(type == NJS::Enum::Type::String) 
			((NJS::Class::String*)data.ptr)->value += (std::string)_v1;
		else 
		{
			std::string _s = (std::string)*this;
			type = NJS::Enum::Type::String;
			data.ptr = new NJS::Class::String("");
			((NJS::Class::String*)data.ptr)->value += _s + (std::string)_v1;
		}
	}
	VAR VAR::operator-(const VAR &_v1)
	{	
		if (type < NJS::Enum::Type::String ) return data.number - _v1;
		else return "NaN";
	}
	VAR VAR::operator-=(const VAR &_v1)
	{
		if(type < NJS::Enum::Type::String) data.number -= _v1;
		else 
		{
			type = NJS::Enum::Type::ISNAN;
			data.ptr = new NJS::Class::String("NaN");
		}
		return *this;
	}
	VAR VAR::operator*(const VAR &_v1)
	{
		if(type < NJS::Enum::Type::String) return data.number * _v1;
		return VAR();
	}
	void VAR::operator*=(const VAR &_v1)
	{
		if(type < NJS::Enum::Type::String) data.number *= _v1;
	}
	VAR VAR::operator/(const VAR &_v1)
	{
		if (type < NJS::Enum::Type::String) return data.number / _v1;
		return VAR();
	}
	void VAR::operator/=(const VAR &_v1)
	{
		if(type < NJS::Enum::Type::String) 
			data.number /= _v1;
	}
	VAR VAR::operator%(const VAR &_v1)
	{
		if (type < NJS::Enum::Type::String && _v1.type < NJS::Enum::Type::String)
			return data.number % _v1;
		else
		{
			return remainder((int)data.number, (int)_v1);
		}
	}
	VAR VAR::operator%=(const VAR &_v1)
	{
		if (type < NJS::Enum::Type::String)
		{
			data.number %= _v1;
		}
		else
		{
			return NaN;
		}
		return *this;
	}
	// TODO: "**" and "**=" VAR::operators
	// var++
	VAR VAR::operator++(const int _v1)
	{
		if (type < NJS::Enum::Type::String)
		{
			data.number++;
		}
		return *this;
	}
	// ++var
	void VAR::operator++()
	{
		if (type < NJS::Enum::Type::String)
		{
			++data.number;
		}
	}
	// var--
	VAR VAR::operator--(const int _v1)
	{
		if (type < NJS::Enum::Type::String)
		{
			data.number--;
		}
		return *this;
	}
	// --var
	void VAR::operator--()
	{
		if (type < NJS::Enum::Type::String)
		{
			--data.number;
		}
	}

	/// Comparison VAR::operators
	VAR VAR::operator==(const VAR &_v1)
	{
		if (type == _v1.type)
		{
			switch (type)
			{
			case NJS::Enum::Type::Number:
				return (bool)(data.number == _v1);
			case NJS::Enum::Type::Boolean:
				return __NJS_Create_Boolean((bool)data.number == (bool)_v1);
			case NJS::Enum::Type::String:
				return __NJS_Create_Boolean((((NJS::Class::String*)data.ptr)->value).compare((std::string)_v1) == 0);
			case NJS::Enum::Type::ISINFINITY:
			case NJS::Enum::Type::ISNULL:
			case NJS::Enum::Type::Undefined:
				return __NJS_Create_Boolean(true);
			case NJS::Enum::Type::Array:
			case NJS::Enum::Type::Native:
			case NJS::Enum::Type::Function:
			case NJS::Enum::Type::Object:
			case NJS::Enum::Type::ISNAN:
			default:
				return __NJS_Create_Boolean(false);
			}
		}
		else
		{
			if (type == NJS::Enum::Type::String || _v1.type == NJS::Enum::Type::String)
			{
				return __NJS_Create_Boolean((std::string) * this == (std::string)_v1);
			}
			else
				return __NJS_Create_Boolean((double)*this == (double)_v1);
		}
	}
	// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
	VAR VAR::operator!=(const VAR &_v1)
	{
		return !(*this == _v1);
	}
	
	// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
	VAR VAR::operator<(const VAR &_v1)
	{
		return data.number < _v1.data.number;
	}
	VAR VAR::operator<=(const VAR &_v1)
	{
		return (int)*this <= (int)_v1;
	}
	VAR VAR::operator>(const VAR &_v1)
	{
		return (int)*this > (int)_v1;
	}
	VAR VAR::operator>=(const VAR &_v1)
	{
		return (int)*this >= (int)_v1;
	}

	/// Bitwise VAR::operators
	VAR VAR::operator&(const VAR &_v1) { return (int)*this & (int)_v1; }
	VAR VAR::operator&=(const VAR &_v1)
	{
		type = NJS::Enum::Type::Number;
		data.number = (int)*this & (int)_v1;
		return *this;
	}
	
	VAR VAR::operator|(const VAR &_v1)
	{ 
		return (int)*this | (int)_v1;
	}
	VAR VAR::operator|=(const VAR &_v1)
	{
		if (type < NJS::Enum::Type::String)
		{
			data.number = (int)data.number | (int)_v1;
		}
		else
		{
			return NaN;
		}
		return *this;
	}
	VAR VAR::operator^(const VAR &_v1) { return (int)*this ^ (int)_v1; }
	VAR VAR::operator^=(const VAR &_v1)
	{
		if (type < NJS::Enum::Type::String)
		{
			data.number = (int)data.number ^ (int)_v1;
		}
		else
		{
			return NaN;
		}
		return *this;
	}
	VAR VAR::operator~() { return ~(int)*this; }
	VAR VAR::operator>>(const VAR &_v1) { return (int)*this >> (int)_v1; }
	VAR VAR::operator>>=(const VAR &_v1)
	{
		if (type < NJS::Enum::Type::String)
		{
			data.number = (int)data.number >> (int)_v1;
		}
		else
		{
			return NaN;
		}
		return *this;
	}
	VAR VAR::operator<<(const VAR &_v1) 
	{ 
		return (int)*this << (int)_v1; 
	}
	VAR VAR::operator<<=(const VAR &_v1)
	{
		if (type < NJS::Enum::Type::String)
		{
			data.number = (int)data.number << (int)_v1;
		}
		else
		{
			return NaN;
		}
		return *this;
	}

	VAR::operator int() const
	{
		if(type < NJS::Enum::Type::String) return data.number;
		return (int)(*(NJS::Class::Base*)data.ptr);
	}
	
	VAR::operator int()
	{
		if(type < NJS::Enum::Type::String) return data.number;
		return (int)(*(NJS::Class::Base*)data.ptr);
	}

	VAR::operator double() const
	{
		if(type < NJS::Enum::Type::String) return data.number;
		return (double)(*(NJS::Class::Base*)data.ptr);
	}
	
	VAR::operator double()
	{
		if(type < NJS::Enum::Type::String) return data.number;
		return (double)(*(NJS::Class::Base*)data.ptr);
	}

	VAR::operator bool() const
	{
		if(type < NJS::Enum::Type::String) return data.number;
		return (bool)(*(NJS::Class::Base*)data.ptr);
	}
	
	VAR::operator bool()
	{
		if(type < NJS::Enum::Type::String) return data.number;
		return (bool)(*(NJS::Class::Base*)data.ptr);
	}

	VAR::operator std::string() const
	{
		if(type < NJS::Enum::Type::String) return __NJS_DOUBLE_TO_STRING(data.number);
		return (std::string)(*(NJS::Class::Base*)data.ptr);
	}
	
	VAR::operator std::string()
	{
		if(type < NJS::Enum::Type::String) return __NJS_DOUBLE_TO_STRING(data.number);
		return (std::string)(*(NJS::Class::Base*)data.ptr);
	}

	VAR::operator long long() const
	{
		if(type < NJS::Enum::Type::String) return data.number;
		return (long long)((double)*this);
	}

		
} // namespace NJS