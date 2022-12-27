/*
	Copyright (c) 2021 NerdLang - Adrien THIERRY and contributors

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

*/

namespace NerdCore
{
	
	VAR::VAR()
	{
		type = NerdCore::Enum::Type::Null;
		data.number = 0;
	}

	VAR::~VAR()
	{
		if(type > NerdCore::Enum::Type::Number)
		{
			((NerdCore::Class::Base*)data.ptr)->Delete();
		}
	}
	
	/*** COPY ***/
	 VAR::VAR(VAR const &_v)
	{
		type = _v.type;
		if(type < NerdCore::Enum::Type::String)
		{
			data.number = _v.data.number;
		}
		else data.ptr = ((NerdCore::Class::Base*)_v.data.ptr)->Copy();
		
	}
	/* END COPY */
	
	/*** MOVE ***/
	VAR::VAR(VAR const &&_v) 
	{
		type = _v.type;
		if(type < NerdCore::Enum::Type::String)
		{
			data.number = _v.data.number;
		}
		else data.ptr = ((NerdCore::Class::Base*)_v.data.ptr)->Copy();
	}
	/* END MOVE */
	
	/*** CONSTRUCTOR ***/

	VAR::VAR(NerdCore::Enum::Type _type, int _value)
	{
		this->type = _type;
		data.number = _value;
	}
	
	VAR::VAR(NerdCore::Enum::Type _type, double _value)
	{
		this->type = _type;
		data.number = _value;
	}

	VAR::VAR(int _value)
	{
		this->type = NerdCore::Enum::Type::Number;
		data.number = _value;
	}

	VAR::VAR(double _value)
	{
		this->type = NerdCore::Enum::Type::Number;
		data.number = _value;
	}
	
	VAR::VAR(unsigned long _value)
	{
		this->type = NerdCore::Enum::Type::Number;
		data.number = _value;
	}
	
	VAR::VAR(long long _value)
	{
		this->type = NerdCore::Enum::Type::Number;
		data.number = _value;
	}
	
	VAR::VAR(long long unsigned int _value)
	{
		this->type = NerdCore::Enum::Type::Number;
		data.number = _value;
	}

	VAR::VAR(char *_value)
	{
		type = NerdCore::Enum::Type::String;
		data.ptr = new NerdCore::Class::String(_value);
	}
	
	VAR::VAR(const std::string _value)
	{
		type = NerdCore::Enum::Type::String;
		data.ptr = new NerdCore::Class::String(_value);
	}

	VAR::VAR(const char *_value)
	{
		type = NerdCore::Enum::Type::String;
		data.ptr = new NerdCore::Class::String(_value);
	}
	
	VAR::VAR(std::string_view _value)
	{
		type = NerdCore::Enum::Type::String;
		data.ptr = new NerdCore::Class::String({_value.data(), _value.size()});
	}

	VAR::VAR(NerdCore::Class::FixedArray *_value)
	{
		type = NerdCore::Enum::Type::FixedArray;
		_value->counter++;
		data.ptr = _value;
	}

	VAR::VAR(NerdCore::Class::Array *_value)
	{
		type = NerdCore::Enum::Type::Array;
		_value->counter++;
		data.ptr = _value;
	}
	
	VAR::VAR(std::initializer_list<NerdCore::VAR> l)
	{
		type = NerdCore::Enum::Type::Array;
		NerdCore::Class::Array* _arr = new NerdCore::Class::Array(l);
		_arr->counter++;
		data.ptr = _arr;
	}
	
	VAR::VAR(const NerdCore::Class::Array *_value)
	{
		type = NerdCore::Enum::Type::Array;
		data.ptr = (NerdCore::Class::Array *)_value;
		((NerdCore::Class::Array*)data.ptr)->counter++;
	}
	
	VAR::VAR(bool _value)
	{
		type = NerdCore::Enum::Type::Boolean;
		data.number =_value;
	}
	
	VAR::VAR(NerdCore::Class::Function *_value)
	{
		type = NerdCore::Enum::Type::Function;
		_value->counter++;
		data.ptr = _value;
	}
	
	VAR::VAR(NerdCore::Class::Object *_value)
	{
		type = NerdCore::Enum::Type::Object;
		_value->counter++;
		data.ptr = _value;
	}

	VAR::VAR(NerdCore::Class::String *_value)
	{
		type = NerdCore::Enum::Type::String;
		data.ptr = new NerdCore::Class::String(_value->value);
	}
	
	VAR::VAR(NerdCore::Class::Native *_value)
	{
		type = NerdCore::Enum::Type::Native;
		_value->counter++;
		data.ptr = _value;
	}
	
	VAR::VAR(void *_value, void* fn)
	{
		type = NerdCore::Enum::Type::Struct;
		data.ptr = new NerdCore::Class::Struct(_value, (NerdCore::Type::clean_struct*)fn);
	}
	VAR::VAR(NerdCore::Enum::Type _type, void *_value)
	{
		type = _type;
		data.ptr = new NerdCore::Class::Function(_value);
	}
	
	/* END CALL OVERLOAD */
	
	VAR & VAR::operator[] (VAR _index)
	{
		if(type < NerdCore::Enum::Type::String) return NerdCore::Global::null;
		return (*(NerdCore::Class::Base*)data.ptr)[_index];
	}
	
	VAR & VAR::operator[] (VAR _index) const
	{
		if(type < NerdCore::Enum::Type::String) return NerdCore::Global::null;
		return (*(NerdCore::Class::Base*)data.ptr)[_index];
	}
	
	VAR & VAR::operator[] (int _index) const
	{
		if(type < NerdCore::Enum::Type::String) return NerdCore::Global::null;
		return (*(NerdCore::Class::Base*)data.ptr)[_index];
	}
	
	VAR & VAR::operator[] (int _index)
	{
		if(type < NerdCore::Enum::Type::String) return NerdCore::Global::null;
		return (*(NerdCore::Class::Base*)data.ptr)[_index];
	}
	
	VAR & VAR::operator[] (double _index)
	{
		if(type < NerdCore::Enum::Type::String) return NerdCore::Global::null;
		return (*(NerdCore::Class::Base*)data.ptr)[_index];
	}
	
	VAR & VAR::operator[] (const char* _index)
	{
		if(type < NerdCore::Enum::Type::String) return NerdCore::Global::null;
		return (*(NerdCore::Class::Base*)data.ptr)[_index];
	}
	
	/* END ACCESS OVERLOAD */

	/*** END CONSTRUCTOR ***/

	/*** OPERATOR ***/
	void VAR::operator=(const VAR &_v)
	{
		if(this == &_v)
		{
			return;
		}
		
		if(type > NerdCore::Enum::Type::Number) 
		{
			((NerdCore::Class::Base*)data.ptr)->Delete();
		}

		type = _v.type;
		if(type < NerdCore::Enum::Type::String)
		{
			data.number = (double)_v;
		}
		else
		{
			data.ptr = ((NerdCore::Class::Base*)_v.data.ptr)->Copy();
		}
	}

	/// Unary VAR::operators
	VAR VAR::operator+()
	{
		if(type < NerdCore::Enum::Type::String) return data.number;
		return (double)*this;
	}
	
	VAR VAR::operator-()
	{
		if(type < NerdCore::Enum::Type::String) return -data.number;
		return -(double)*this;
	}
	VAR VAR::operator!() 
	{ 
		if(type < NerdCore::Enum::Type::String) return !data.number;
		return !(bool)*this; 
	};

	/// Logical VAR::operators
	VAR VAR::operator&&(const VAR &_v1) const { return (bool)*this && (bool)_v1; }
	VAR VAR::operator||(const VAR &_v1) const { return (bool)*this || (bool)_v1; }

	/// Arithmetic VAR::operators
	VAR VAR::operator+(const VAR &_v1)
	{
		if (type < NerdCore::Enum::Type::String)
		{
			return data.number + _v1;
		}
		else if (type == NerdCore::Enum::Type::String || type == NerdCore::Enum::Type::Array || type == NerdCore::Enum::Type::Object || _v1.type == NerdCore::Enum::Type::String)
		{
			if(_v1.type == NerdCore::Enum::Type::Null) return ((std::string)*this) + "null";
			else return __NERD_Concat_To_Str((std::string)*this, (std::string)_v1);
		}
		else
		{
			return NerdCore::Global::NaN;
		}
		
	}
	VAR VAR::operator+(const char _v1[])
	{
		return __NERD_Concat_To_Str((std::string)*this, _v1);
	}
	
	VAR& VAR::operator+=(const VAR &_v1)
	{
		if(type < NerdCore::Enum::Type::String)
		{
			data.number += _v1;
		}
		else if(type == NerdCore::Enum::Type::String)
		{
			((NerdCore::Class::String*)data.ptr)->value += (std::string)_v1;
		}
		else 
		{
			std::string _s = (std::string)*this;
			type = NerdCore::Enum::Type::String;
			data.ptr = new NerdCore::Class::String("");
			((NerdCore::Class::String*)data.ptr)->value += _s + (std::string)_v1;
			
		}
		return *this;
	}
	
	VAR VAR::operator-(const VAR &_v1)
	{	
		if (type < NerdCore::Enum::Type::String ) return data.number - _v1;
		else return NerdCore::Global::NaN;
	}
	
	VAR& VAR::operator-=(const VAR &_v1)
	{
		if(type < NerdCore::Enum::Type::String) data.number -= _v1;
		else 
		{
			return NerdCore::Global::NaN;
		}
		return *this;
	}
	VAR VAR::operator*(const VAR &_v1)
	{
		if(type < NerdCore::Enum::Type::String) return data.number * _v1;
		return NerdCore::Global::NaN;
	}

	VAR& VAR::operator*=(const VAR &_v1)
	{
		if(type < NerdCore::Enum::Type::String) data.number *= _v1;
		return *this;
	}
	VAR VAR::operator/(const VAR &_v1)
	{
		if (type < NerdCore::Enum::Type::String) return data.number / _v1;
		return NerdCore::Global::NaN;
	}

	VAR& VAR::operator/=(const VAR &_v1)
	{
		if(type < NerdCore::Enum::Type::String) data.number /= _v1;
		return *this;
	}
	VAR VAR::operator%(const VAR &_v1)
	{
		if (type < NerdCore::Enum::Type::String && _v1.type < NerdCore::Enum::Type::String)
		{
			int _left = (int)_v1;
			if(_left == 0) return NerdCore::Global::NaN;
			return (int)data.number % _left;
		}
		else
		{
			double _left = (double)_v1;
			if(_left == 0) return NerdCore::Global::NaN;
			return remainder((double)*this, _left);
		}
	}
	VAR& VAR::operator%=(const VAR &_v1)
	{
		if (type < NerdCore::Enum::Type::String)
		{
			int _left = (int)data.number;
			_left %= (int)_v1;
			if(_left == 0) data.number = std::numeric_limits<double>::quiet_NaN();
			data.number = _left;
		}
		else
		{
			return NerdCore::Global::NaN;
		}
		return *this;
	}
	// TODO: "**" and "**=" VAR::operators
	// var++
	/*
	inline VAR& VAR::operator++(const int _v1)
	{
		if (type < NerdCore::Enum::Type::String)
		{
			data.number++;
		}
		return *this;
	}
	
	// ++var
	VAR& VAR::operator++()
	{
		if (type < NerdCore::Enum::Type::String)
		{
			++data.number;
		}
		return *this;
	}
	// var--
	VAR& VAR::operator--(const int _v1)
	{
		if (type < NerdCore::Enum::Type::String)
		{
			data.number--;
		}
		return *this;
	}
	// --var
	VAR& VAR::operator--()
	{
		if (type < NerdCore::Enum::Type::String)
		{
			--data.number;
		}
		return *this;
	}
	*/
	
	/// Comparison VAR::operators
	VAR VAR::operator==(const VAR &_v1) const
	{
		if (type == _v1.type)
		{
			switch (type)
			{
			case NerdCore::Enum::Type::Number:
				return (bool)(data.number == _v1);
			case NerdCore::Enum::Type::Boolean:
				return __NERD_Create_Boolean((bool)data.number == (bool)_v1);
			case NerdCore::Enum::Type::String:
				return __NERD_Create_Boolean((((NerdCore::Class::String*)data.ptr)->value).compare((std::string)_v1) == 0);
			case NerdCore::Enum::Type::Null:
			case NerdCore::Enum::Type::Array:
			case NerdCore::Enum::Type::Native:
			case NerdCore::Enum::Type::Function:
			case NerdCore::Enum::Type::Object:
			default:
				return _v1.data.ptr == this->data.ptr;
			}
		}
		else
		{
			if (type == NerdCore::Enum::Type::String || _v1.type == NerdCore::Enum::Type::String)
			{
				return __NERD_Create_Boolean((std::string) * this == (std::string)_v1);
			}
			else
				return __NERD_Create_Boolean((double)*this == (double)_v1);
		}
	}
	// === emulated with __NERD_EQUAL_VALUE_AND_TYPE
	VAR VAR::operator!=(const VAR &_v1)
	{
		return !(*this == _v1);
	}
	
	// !== emulated with __NERD_NOT_EQUAL_VALUE_AND_TYPE
	
	VAR VAR::operator<(const VAR &_v1)
	{
		return data.number < (double)_v1;
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
	VAR& VAR::operator&=(const VAR &_v1)
	{
		type = NerdCore::Enum::Type::Number;
		data.number = (int)*this & (int)_v1;
		return *this;
	}
	
	VAR VAR::operator|(const VAR &_v1)
	{ 
		return (int)*this | (int)_v1;
	}
	VAR VAR::operator|=(const VAR &_v1)
	{
		if (type < NerdCore::Enum::Type::String)
		{
			data.number = (int)data.number | (int)_v1;
		}
		else
		{
			return NerdCore::Global::NaN;
		}
		return *this;
	}
	VAR VAR::operator^(const VAR &_v1) { return (int)*this ^ (int)_v1; }
	VAR VAR::operator^=(const VAR &_v1)
	{
		if (type < NerdCore::Enum::Type::String)
		{
			data.number = (int)data.number ^ (int)_v1;
		}
		else
		{
			return NerdCore::Global::NaN;
		}
		return *this;
	}
	VAR VAR::operator~() { return ~(int)*this; }
	VAR VAR::operator>>(const VAR &_v1) { return (int)*this >> (int)_v1; }
	VAR VAR::operator>>=(const VAR &_v1)
	{
		if (type < NerdCore::Enum::Type::String)
		{
			data.number = (int)data.number >> (int)_v1;
		}
		else
		{
			return NerdCore::Global::NaN;
		}
		return *this;
	}
	VAR VAR::operator<<(const VAR &_v1) 
	{ 
		return (int)*this << (int)_v1; 
	}
	VAR VAR::operator<<=(const VAR &_v1)
	{
		if (type < NerdCore::Enum::Type::String)
		{
			data.number = (int)data.number << (int)_v1;
		}
		else
		{
			return NerdCore::Global::NaN;
		}
		return *this;
	}

	VAR::operator int() const
	{
		if(type < NerdCore::Enum::Type::String) return data.number;
		return (int)(*(NerdCore::Class::Base*)data.ptr);
	}
	
	VAR::operator int()
	{
		if(type < NerdCore::Enum::Type::String) return data.number;
		return (int)(*(NerdCore::Class::Base*)data.ptr);
	}

	VAR::operator double() const
	{
		if(type < NerdCore::Enum::Type::String) return data.number;
		return (double)(*(NerdCore::Class::Base*)data.ptr);
	}
	
	VAR::operator double()
	{
		if(type < NerdCore::Enum::Type::String) return data.number;
		return (double)(*(NerdCore::Class::Base*)data.ptr);
	}

	VAR::operator bool() const
	{
		if(type == NerdCore::Enum::Type::Null) return false;
		else if(type == NerdCore::Enum::Type::Boolean || type == NerdCore::Enum::Type::Number) return data.number;
		else return (bool)(*(NerdCore::Class::Base*)data.ptr);
	}
	
	VAR::operator bool()
	{
		if(type == NerdCore::Enum::Type::Null) return false;
		else if(type == NerdCore::Enum::Type::Boolean || type == NerdCore::Enum::Type::Number) return data.number;
		else return (bool)(*(NerdCore::Class::Base*)data.ptr);
	}
	
	VAR::operator const char*() const
	{
		if(type == NerdCore::Enum::Type::String)
		{
			return ((NerdCore::Class::String*)this->data.ptr)->value.c_str();
		}
		else 
		{
			throw(NerdCore::VAR("Char* conversion error: variable is not a string"));
		}
	}

	VAR::operator std::string() const
	{
		if(type < NerdCore::Enum::Type::String) return __NERD_DOUBLE_TO_STRING(data.number);
		return (std::string)(*(NerdCore::Class::Base*)data.ptr);
	}
	
	VAR::operator std::string()
	{
		if(type < NerdCore::Enum::Type::String) return __NERD_DOUBLE_TO_STRING(data.number);
		return (std::string)(*(NerdCore::Class::Base*)data.ptr);
	}

	VAR::operator long long()
	{
		if(type < NerdCore::Enum::Type::String) return data.number;
		return (long long)((double)*this);
	}

	VAR::operator long long() const
	{
		if(type < NerdCore::Enum::Type::String) return data.number;
		return (long long)((double)*this);
	}

	VAR::operator std::string_view() const
	{
		if(type == NerdCore::Enum::Type::String)
		{
			return std::string_view(((NerdCore::Class::String*)this->data.ptr)->value.c_str());
		}
		else 
		{
			throw(NerdCore::VAR("string_view conversion error: variable is not a string"));
		}
	}

		
} // namespace NerdCore