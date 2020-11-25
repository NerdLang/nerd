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
 
namespace NectarCore
{
	
	VAR::VAR()
	{
		property.set(1,1);
		type = NectarCore::Enum::Type::Undefined;
		data.ptr = NectarCore::Global::undefined.data.ptr;
	}

	VAR::~VAR()
	{
		if(type > NectarCore::Enum::Type::Number) ((NectarCore::Class::Base*)data.ptr)->Delete();
	}

	/*** COPY ***/
	 VAR::VAR(VAR const &_v)
	{
		if(property[0] != 0) return;
		
		property = _v.property;
		type = _v.type;
		if(type < NectarCore::Enum::Type::String)
		{
			data.number = (double)_v;
		}
		else data.ptr = ((NectarCore::Class::Base*)_v.data.ptr)->Copy();
		
	}
	/* END COPY */
	
	/*** MOVE ***/
	VAR::VAR(VAR const &&_v)
	{
		property = _v.property;
		type = _v.type;
		if(type < NectarCore::Enum::Type::String)
		{
			data.number = _v.data.number;
		}
		else data.ptr = ((NectarCore::Class::Base*)_v.data.ptr)->Copy();
	}
	/* END MOVE */
	
	/*** CONSTRUCTOR ***/

	VAR::VAR(NectarCore::Enum::Type _type, int _value)
	{
		this->type = _type;
		data.number = _value;
	}
	
	VAR::VAR(NectarCore::Enum::Type _type, double _value)
	{
		this->type = _type;
		data.number = _value;
	}

	VAR::VAR(int _value)
	{
		this->type = NectarCore::Enum::Type::Number;
		data.number = _value;
	}

	VAR::VAR(double _value)
	{
		this->type = NectarCore::Enum::Type::Number;
		data.number = _value;
	}
	
	VAR::VAR(long long _value)
	{
		this->type = NectarCore::Enum::Type::Number;
		data.number = _value;
	}

	VAR::VAR(char *_value)
	{
		type = NectarCore::Enum::Type::String;
		data.ptr = new NectarCore::Class::String(_value);
	}

	VAR::VAR(std::string _value)
	{
		type = NectarCore::Enum::Type::String;
		data.ptr = new NectarCore::Class::String(_value);
	}

	VAR::VAR(const char *_value)
	{
		type = NectarCore::Enum::Type::String;
		data.ptr = new NectarCore::Class::String(_value);
	}

	VAR::VAR(NectarCore::Class::FixedArray *_value)
	{
		type = NectarCore::Enum::Type::FixedArray;
		_value->counter++;
		data.ptr = _value;
	}

	VAR::VAR(NectarCore::Class::Array *_value)
	{
		type = NectarCore::Enum::Type::Array;
		_value->counter++;
		data.ptr = _value;
	}
	
	VAR::VAR(const NectarCore::Class::Array *_value)
	{
		type = NectarCore::Enum::Type::Array;
		data.ptr = (NectarCore::Class::Array *)_value;
		((NectarCore::Class::Array*)data.ptr)->counter++;
	}
	
	VAR::VAR(bool _value)
	{
		type = NectarCore::Enum::Type::Boolean;
		data.number =_value;
	}
	
	VAR::VAR(NectarCore::Class::Function *_value)
	{
		type = NectarCore::Enum::Type::Function;
		_value->counter++;
		data.ptr = _value;
	}
	
	VAR::VAR(NectarCore::Class::Object *_value)
	{
		type = NectarCore::Enum::Type::Object;
		_value->counter++;
		data.ptr = _value;
	}
	
	VAR::VAR(NectarCore::Class::String *_value)
	{
		type = NectarCore::Enum::Type::String;
		data.ptr = new NectarCore::Class::String(_value->value);
	}
	
	VAR::VAR(NectarCore::Class::Native *_value)
	{
		type = NectarCore::Enum::Type::Native;
		_value->counter++;
		data.ptr = _value;
	}
	
	VAR::VAR(NectarCore::Class::Undefined *_value)
	{
		property.set(1, 1);
		type = NectarCore::Enum::Type::Undefined;
		data.ptr = _value;
	}
	VAR::VAR(void *_value, void* fn)
	{
		type = NectarCore::Enum::Type::Struct;
		data.ptr = new NectarCore::Class::Struct(_value, (NectarCore::Type::clean_struct*)fn);
	}
	VAR::VAR(NectarCore::Enum::Type _type, void *_value)
	{
		type = _type;
		data.ptr = new NectarCore::Class::Function(_value);
	}
	
	VAR::VAR(NectarCore::Enum::Type _type, void *_value, NectarCore::VAR _this)
	{
		type = _type;
		data.ptr = new NectarCore::Class::Function(_value);
		if(_this.data.ptr == NectarCore::Global::__Nectar_THIS.data.ptr) ((NectarCore::Class::Object*)_this.data.ptr)->counter++;

		((NectarCore::Class::Function*)data.ptr)->This.data.ptr = _this.data.ptr;
		((NectarCore::Class::Function*)data.ptr)->This.type = _this.type;

	}
	
	/* END CALL OVERLOAD */

	VAR & VAR::operator[] (VAR _index)
	{
		if(type < NectarCore::Enum::Type::String) return NectarCore::Class::NUMBER::Accessor(*this, _index);
		return (*(NectarCore::Class::Base*)data.ptr)[_index];
	}
	
	VAR & VAR::operator[] (VAR _index) const
	{
		if(type < NectarCore::Enum::Type::String) return NectarCore::Class::NUMBER::Accessor(*this, _index);
		return (*(NectarCore::Class::Base*)data.ptr)[_index];
	}
	
	VAR & VAR::operator[] (int _index) const
	{
		if(type < NectarCore::Enum::Type::String) return NectarCore::Global::undefined;
		return (*(NectarCore::Class::Base*)data.ptr)[_index];
	}
	
	VAR & VAR::operator[] (int _index)
	{
		if(type < NectarCore::Enum::Type::String) return NectarCore::Global::undefined;
		return (*(NectarCore::Class::Base*)data.ptr)[_index];
	}
	
	VAR & VAR::operator[] (double _index)
	{
		if(type < NectarCore::Enum::Type::String) return NectarCore::Global::undefined;
		return (*(NectarCore::Class::Base*)data.ptr)[_index];
	}
	
	VAR & VAR::operator[] (const char* _index)
	{
		if(type < NectarCore::Enum::Type::String) return NectarCore::Class::NUMBER::Accessor(*this, VAR(_index));
		return (*(NectarCore::Class::Base*)data.ptr)[_index];
	}
	
	/* END ACCESS OVERLOAD */

	/*** END CONSTRUCTOR ***/

	/*** OPERATOR ***/
	void VAR::operator=(const VAR &_v)
	{
		if(property[0] != 0) return;
		if(type > NectarCore::Enum::Type::Number) 
		{
			((NectarCore::Class::Base*)data.ptr)->Delete();
		}
		property = _v.property;
		type = _v.type;
		if(type < NectarCore::Enum::Type::String)
		{
			data.number = (double)_v;
		}
		else
		{
			data.ptr = ((NectarCore::Class::Base*)_v.data.ptr)->Copy();
		}
	}

	/// Unary VAR::operators
	VAR VAR::operator+()
	{
		if(type < NectarCore::Enum::Type::String) return data.number;
		return (double)*this;
	}
	
	VAR VAR::operator-()
	{
		if(type < NectarCore::Enum::Type::String) return -data.number;
		return -(double)*this;
	}
	VAR VAR::operator!() 
	{ 
		if(type < NectarCore::Enum::Type::String) return !data.number;
		return !(bool)*this; 
	};

	/// Logical VAR::operators
	VAR VAR::operator&&(const VAR &_v1) { return (bool)*this && (bool)_v1; }
	VAR VAR::operator||(const VAR &_v1) { return (bool)*this || (bool)_v1; }

	/// Arithmetic VAR::operators
	VAR VAR::operator+(const VAR &_v1)
	{
		if (type < NectarCore::Enum::Type::String)
		{
			return data.number + _v1;
		}
		else if (type == NectarCore::Enum::Type::String || type == NectarCore::Enum::Type::Array || type == NectarCore::Enum::Type::Object || _v1.type == NectarCore::Enum::Type::String)
		{
			if(_v1.type == NectarCore::Enum::Type::Null) return ((std::string)*this) + "null";
			else return __Nectar_Concat_To_Str((std::string)*this, (std::string)_v1);
		}
		else
		{
			return NectarCore::Global::NaN;
		}
		
	}
	VAR VAR::operator+(const char _v1[])
	{
		return __Nectar_Concat_To_Str((std::string)*this, _v1);
	}
	
	VAR& VAR::operator+=(const VAR &_v1)
	{
		if(type < NectarCore::Enum::Type::String)
		{
			data.number += _v1;
		}
		else if(type == NectarCore::Enum::Type::String)
		{
			((NectarCore::Class::String*)data.ptr)->value += (std::string)_v1;
		}
		else 
		{
			std::string _s = (std::string)*this;
			type = NectarCore::Enum::Type::String;
			data.ptr = new NectarCore::Class::String("");
			((NectarCore::Class::String*)data.ptr)->value += _s + (std::string)_v1;
			
		}
		return *this;
	}
	VAR VAR::operator-(const VAR &_v1)
	{	
		if (type < NectarCore::Enum::Type::String ) return data.number - _v1;
		else return NectarCore::Global::NaN;
	}
	
	VAR& VAR::operator-=(const VAR &_v1)
	{
		if(type < NectarCore::Enum::Type::String) data.number -= _v1;
		else 
		{
			return NectarCore::Global::NaN;
		}
		return *this;
	}
	VAR VAR::operator*(const VAR &_v1)
	{
		if(type < NectarCore::Enum::Type::String) return data.number * _v1;
		return NectarCore::Global::NaN;
	}

	VAR& VAR::operator*=(const VAR &_v1)
	{
		if(type < NectarCore::Enum::Type::String) data.number *= _v1;
		return *this;
	}
	VAR VAR::operator/(const VAR &_v1)
	{
		if (type < NectarCore::Enum::Type::String) return data.number / _v1;
		return NectarCore::Global::NaN;
	}

	VAR& VAR::operator/=(const VAR &_v1)
	{
		if(type < NectarCore::Enum::Type::String) data.number /= _v1;
		return *this;
	}
	VAR VAR::operator%(const VAR &_v1)
	{
		if (type < NectarCore::Enum::Type::String && _v1.type < NectarCore::Enum::Type::String)
		{
			int _left = (int)_v1;
			if(_left == 0) return NectarCore::Global::NaN;
			return (int)data.number % _left;
		}
		else
		{
			double _left = (double)_v1;
			if(_left == 0) return NectarCore::Global::NaN;
			return remainder((double)*this, _left);
		}
	}
	VAR& VAR::operator%=(const VAR &_v1)
	{
		if (type < NectarCore::Enum::Type::String)
		{
			int _left = (int)data.number;
			_left %= (int)_v1;
			if(_left == 0) data.number = std::numeric_limits<double>::quiet_NaN();
			data.number = _left;
		}
		else
		{
			return NectarCore::Global::NaN;
		}
		return *this;
	}
	// TODO: "**" and "**=" VAR::operators
	// var++
	VAR& VAR::operator++(const int _v1)
	{
		if (type < NectarCore::Enum::Type::String)
		{
			data.number++;
		}
		return *this;
	}
	// ++var
	VAR& VAR::operator++()
	{
		if (type < NectarCore::Enum::Type::String)
		{
			++data.number;
		}
		return *this;
	}
	// var--
	VAR& VAR::operator--(const int _v1)
	{
		if (type < NectarCore::Enum::Type::String)
		{
			data.number--;
		}
		return *this;
	}
	// --var
	VAR& VAR::operator--()
	{
		if (type < NectarCore::Enum::Type::String)
		{
			--data.number;
		}
		return *this;
	}

	/// Comparison VAR::operators
	VAR VAR::operator==(const VAR &_v1)
	{
		if (type == _v1.type)
		{
			switch (type)
			{
			case NectarCore::Enum::Type::Number:
				return (bool)(data.number == _v1);
			case NectarCore::Enum::Type::Boolean:
				return __Nectar_Create_Boolean((bool)data.number == (bool)_v1);
			case NectarCore::Enum::Type::String:
				return __Nectar_Create_Boolean((((NectarCore::Class::String*)data.ptr)->value).compare((std::string)_v1) == 0);
			case NectarCore::Enum::Type::Null:
			case NectarCore::Enum::Type::Undefined:
				return __Nectar_Create_Boolean(true);
			case NectarCore::Enum::Type::Array:
			case NectarCore::Enum::Type::Native:
			case NectarCore::Enum::Type::Function:
			case NectarCore::Enum::Type::Object:
			default:
				return __Nectar_Create_Boolean(false);
			}
		}
		else
		{
			if (type == NectarCore::Enum::Type::String || _v1.type == NectarCore::Enum::Type::String)
			{
				return __Nectar_Create_Boolean((std::string) * this == (std::string)_v1);
			}
			else
				return __Nectar_Create_Boolean((double)*this == (double)_v1);
		}
	}
	// === emulated with __Nectar_EQUAL_VALUE_AND_TYPE
	VAR VAR::operator!=(const VAR &_v1)
	{
		return !(*this == _v1);
	}
	
	// !== emulated with __Nectar_NOT_EQUAL_VALUE_AND_TYPE
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
	VAR& VAR::operator&=(const VAR &_v1)
	{
		type = NectarCore::Enum::Type::Number;
		data.number = (int)*this & (int)_v1;
		return *this;
	}
	
	VAR VAR::operator|(const VAR &_v1)
	{ 
		return (int)*this | (int)_v1;
	}
	VAR VAR::operator|=(const VAR &_v1)
	{
		if (type < NectarCore::Enum::Type::String)
		{
			data.number = (int)data.number | (int)_v1;
		}
		else
		{
			return NectarCore::Global::NaN;
		}
		return *this;
	}
	VAR VAR::operator^(const VAR &_v1) { return (int)*this ^ (int)_v1; }
	VAR VAR::operator^=(const VAR &_v1)
	{
		if (type < NectarCore::Enum::Type::String)
		{
			data.number = (int)data.number ^ (int)_v1;
		}
		else
		{
			return NectarCore::Global::NaN;
		}
		return *this;
	}
	VAR VAR::operator~() { return ~(int)*this; }
	VAR VAR::operator>>(const VAR &_v1) { return (int)*this >> (int)_v1; }
	VAR VAR::operator>>=(const VAR &_v1)
	{
		if (type < NectarCore::Enum::Type::String)
		{
			data.number = (int)data.number >> (int)_v1;
		}
		else
		{
			return NectarCore::Global::NaN;
		}
		return *this;
	}
	VAR VAR::operator<<(const VAR &_v1) 
	{ 
		return (int)*this << (int)_v1; 
	}
	VAR VAR::operator<<=(const VAR &_v1)
	{
		if (type < NectarCore::Enum::Type::String)
		{
			data.number = (int)data.number << (int)_v1;
		}
		else
		{
			return NectarCore::Global::NaN;
		}
		return *this;
	}

	VAR::operator int() const
	{
		if(type < NectarCore::Enum::Type::String) return data.number;
		return (int)(*(NectarCore::Class::Base*)data.ptr);
	}
	
	VAR::operator int()
	{
		if(type < NectarCore::Enum::Type::String) return data.number;
		return (int)(*(NectarCore::Class::Base*)data.ptr);
	}

	VAR::operator double() const
	{
		if(type < NectarCore::Enum::Type::String) return data.number;
		return (double)(*(NectarCore::Class::Base*)data.ptr);
	}
	
	VAR::operator double()
	{
		if(type < NectarCore::Enum::Type::String) return data.number;
		return (double)(*(NectarCore::Class::Base*)data.ptr);
	}

	VAR::operator bool() const
	{
		if(type == NectarCore::Enum::Type::Undefined) return false;
		else if(type == NectarCore::Enum::Type::Boolean || type == NectarCore::Enum::Type::Number) return data.number;
		else return (bool)(*(NectarCore::Class::Base*)data.ptr);
	}
	
	VAR::operator bool()
	{
		if(type == NectarCore::Enum::Type::Undefined) return false;
		else if(type == NectarCore::Enum::Type::Boolean || type == NectarCore::Enum::Type::Number) return data.number;
		else return (bool)(*(NectarCore::Class::Base*)data.ptr);
	}

	VAR::operator std::string() const
	{
		if(type < NectarCore::Enum::Type::String) return __Nectar_DOUBLE_TO_STRING(data.number);
		return (std::string)(*(NectarCore::Class::Base*)data.ptr);
	}
	
	VAR::operator std::string()
	{
		if(type < NectarCore::Enum::Type::String) return __Nectar_DOUBLE_TO_STRING(data.number);
		return (std::string)(*(NectarCore::Class::Base*)data.ptr);
	}

	VAR::operator long long()
	{
		if(type < NectarCore::Enum::Type::String) return data.number;
		return (long long)((double)*this);
	}

	VAR::operator long long() const
	{
		if(type < NectarCore::Enum::Type::String) return data.number;
		return (long long)((double)*this);
	}

		
} // namespace NectarCore