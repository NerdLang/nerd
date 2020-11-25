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
 
namespace Nectar
{
	
	VAR::VAR()
	{
		property.set(1,1);
		type = Nectar::Enum::Type::Undefined;
		data.ptr = Nectar::Global::undefined.data.ptr;
	}

	VAR::~VAR()
	{
		if(type > Nectar::Enum::Type::Number) ((Nectar::Class::Base*)data.ptr)->Delete();
	}

	/*** COPY ***/
	 VAR::VAR(VAR const &_v)
	{
		if(property[0] != 0) return;
		
		property = _v.property;
		type = _v.type;
		if(type < Nectar::Enum::Type::String)
		{
			data.number = (double)_v;
		}
		else data.ptr = ((Nectar::Class::Base*)_v.data.ptr)->Copy();
		
	}
	/* END COPY */
	
	/*** MOVE ***/
	VAR::VAR(VAR const &&_v)
	{
		property = _v.property;
		type = _v.type;
		if(type < Nectar::Enum::Type::String)
		{
			data.number = _v.data.number;
		}
		else data.ptr = ((Nectar::Class::Base*)_v.data.ptr)->Copy();
	}
	/* END MOVE */
	
	/*** CONSTRUCTOR ***/

	VAR::VAR(Nectar::Enum::Type _type, int _value)
	{
		this->type = _type;
		data.number = _value;
	}
	
	VAR::VAR(Nectar::Enum::Type _type, double _value)
	{
		this->type = _type;
		data.number = _value;
	}

	VAR::VAR(int _value)
	{
		this->type = Nectar::Enum::Type::Number;
		data.number = _value;
	}

	VAR::VAR(double _value)
	{
		this->type = Nectar::Enum::Type::Number;
		data.number = _value;
	}
	
	VAR::VAR(long long _value)
	{
		this->type = Nectar::Enum::Type::Number;
		data.number = _value;
	}

	VAR::VAR(char *_value)
	{
		type = Nectar::Enum::Type::String;
		data.ptr = new Nectar::Class::String(_value);
	}

	VAR::VAR(std::string _value)
	{
		type = Nectar::Enum::Type::String;
		data.ptr = new Nectar::Class::String(_value);
	}

	VAR::VAR(const char *_value)
	{
		type = Nectar::Enum::Type::String;
		data.ptr = new Nectar::Class::String(_value);
	}

	VAR::VAR(Nectar::Class::FixedArray *_value)
	{
		type = Nectar::Enum::Type::FixedArray;
		_value->counter++;
		data.ptr = _value;
	}

	VAR::VAR(Nectar::Class::Array *_value)
	{
		type = Nectar::Enum::Type::Array;
		_value->counter++;
		data.ptr = _value;
	}
	
	VAR::VAR(const Nectar::Class::Array *_value)
	{
		type = Nectar::Enum::Type::Array;
		data.ptr = (Nectar::Class::Array *)_value;
		((Nectar::Class::Array*)data.ptr)->counter++;
	}
	
	VAR::VAR(bool _value)
	{
		type = Nectar::Enum::Type::Boolean;
		data.number =_value;
	}
	
	VAR::VAR(Nectar::Class::Function *_value)
	{
		type = Nectar::Enum::Type::Function;
		_value->counter++;
		data.ptr = _value;
	}
	
	VAR::VAR(Nectar::Class::Object *_value)
	{
		type = Nectar::Enum::Type::Object;
		_value->counter++;
		data.ptr = _value;
	}
	
	VAR::VAR(Nectar::Class::String *_value)
	{
		type = Nectar::Enum::Type::String;
		data.ptr = new Nectar::Class::String(_value->value);
	}
	
	VAR::VAR(Nectar::Class::Native *_value)
	{
		type = Nectar::Enum::Type::Native;
		_value->counter++;
		data.ptr = _value;
	}
	
	VAR::VAR(Nectar::Class::Undefined *_value)
	{
		property.set(1, 1);
		type = Nectar::Enum::Type::Undefined;
		data.ptr = _value;
	}
	VAR::VAR(void *_value, void* fn)
	{
		type = Nectar::Enum::Type::Struct;
		data.ptr = new Nectar::Class::Struct(_value, (Nectar::Type::clean_struct*)fn);
	}
	VAR::VAR(Nectar::Enum::Type _type, void *_value)
	{
		type = _type;
		data.ptr = new Nectar::Class::Function(_value);
	}
	
	VAR::VAR(Nectar::Enum::Type _type, void *_value, Nectar::VAR _this)
	{
		type = _type;
		data.ptr = new Nectar::Class::Function(_value);
		if(_this.data.ptr == Nectar::Global::__Nectar_THIS.data.ptr) ((Nectar::Class::Object*)_this.data.ptr)->counter++;

		((Nectar::Class::Function*)data.ptr)->This.data.ptr = _this.data.ptr;
		((Nectar::Class::Function*)data.ptr)->This.type = _this.type;

	}
	
	/* END CALL OVERLOAD */

	VAR & VAR::operator[] (VAR _index)
	{
		if(type < Nectar::Enum::Type::String) return Nectar::Class::NUMBER::Accessor(*this, _index);
		return (*(Nectar::Class::Base*)data.ptr)[_index];
	}
	
	VAR & VAR::operator[] (VAR _index) const
	{
		if(type < Nectar::Enum::Type::String) return Nectar::Class::NUMBER::Accessor(*this, _index);
		return (*(Nectar::Class::Base*)data.ptr)[_index];
	}
	
	VAR & VAR::operator[] (int _index) const
	{
		if(type < Nectar::Enum::Type::String) return Nectar::Global::undefined;
		return (*(Nectar::Class::Base*)data.ptr)[_index];
	}
	
	VAR & VAR::operator[] (int _index)
	{
		if(type < Nectar::Enum::Type::String) return Nectar::Global::undefined;
		return (*(Nectar::Class::Base*)data.ptr)[_index];
	}
	
	VAR & VAR::operator[] (double _index)
	{
		if(type < Nectar::Enum::Type::String) return Nectar::Global::undefined;
		return (*(Nectar::Class::Base*)data.ptr)[_index];
	}
	
	VAR & VAR::operator[] (const char* _index)
	{
		if(type < Nectar::Enum::Type::String) return Nectar::Class::NUMBER::Accessor(*this, VAR(_index));
		return (*(Nectar::Class::Base*)data.ptr)[_index];
	}
	
	/* END ACCESS OVERLOAD */

	/*** END CONSTRUCTOR ***/

	/*** OPERATOR ***/
	void VAR::operator=(const VAR &_v)
	{
		if(property[0] != 0) return;
		if(type > Nectar::Enum::Type::Number) 
		{
			((Nectar::Class::Base*)data.ptr)->Delete();
		}
		property = _v.property;
		type = _v.type;
		if(type < Nectar::Enum::Type::String)
		{
			data.number = (double)_v;
		}
		else
		{
			data.ptr = ((Nectar::Class::Base*)_v.data.ptr)->Copy();
		}
	}

	/// Unary VAR::operators
	VAR VAR::operator+()
	{
		if(type < Nectar::Enum::Type::String) return data.number;
		return (double)*this;
	}
	
	VAR VAR::operator-()
	{
		if(type < Nectar::Enum::Type::String) return -data.number;
		return -(double)*this;
	}
	VAR VAR::operator!() 
	{ 
		if(type < Nectar::Enum::Type::String) return !data.number;
		return !(bool)*this; 
	};

	/// Logical VAR::operators
	VAR VAR::operator&&(const VAR &_v1) { return (bool)*this && (bool)_v1; }
	VAR VAR::operator||(const VAR &_v1) { return (bool)*this || (bool)_v1; }

	/// Arithmetic VAR::operators
	VAR VAR::operator+(const VAR &_v1)
	{
		if (type < Nectar::Enum::Type::String)
		{
			return data.number + _v1;
		}
		else if (type == Nectar::Enum::Type::String || type == Nectar::Enum::Type::Array || type == Nectar::Enum::Type::Object || _v1.type == Nectar::Enum::Type::String)
		{
			if(_v1.type == Nectar::Enum::Type::Null) return ((std::string)*this) + "null";
			else return __Nectar_Concat_To_Str((std::string)*this, (std::string)_v1);
		}
		else
		{
			return Nectar::Global::NaN;
		}
		
	}
	VAR VAR::operator+(const char _v1[])
	{
		return __Nectar_Concat_To_Str((std::string)*this, _v1);
	}
	
	VAR& VAR::operator+=(const VAR &_v1)
	{
		if(type < Nectar::Enum::Type::String)
		{
			data.number += _v1;
		}
		else if(type == Nectar::Enum::Type::String)
		{
			((Nectar::Class::String*)data.ptr)->value += (std::string)_v1;
		}
		else 
		{
			std::string _s = (std::string)*this;
			type = Nectar::Enum::Type::String;
			data.ptr = new Nectar::Class::String("");
			((Nectar::Class::String*)data.ptr)->value += _s + (std::string)_v1;
			
		}
		return *this;
	}
	VAR VAR::operator-(const VAR &_v1)
	{	
		if (type < Nectar::Enum::Type::String ) return data.number - _v1;
		else return Nectar::Global::NaN;
	}
	
	VAR& VAR::operator-=(const VAR &_v1)
	{
		if(type < Nectar::Enum::Type::String) data.number -= _v1;
		else 
		{
			return Nectar::Global::NaN;
		}
		return *this;
	}
	VAR VAR::operator*(const VAR &_v1)
	{
		if(type < Nectar::Enum::Type::String) return data.number * _v1;
		return Nectar::Global::NaN;
	}

	VAR& VAR::operator*=(const VAR &_v1)
	{
		if(type < Nectar::Enum::Type::String) data.number *= _v1;
		return *this;
	}
	VAR VAR::operator/(const VAR &_v1)
	{
		if (type < Nectar::Enum::Type::String) return data.number / _v1;
		return Nectar::Global::NaN;
	}

	VAR& VAR::operator/=(const VAR &_v1)
	{
		if(type < Nectar::Enum::Type::String) data.number /= _v1;
		return *this;
	}
	VAR VAR::operator%(const VAR &_v1)
	{
		if (type < Nectar::Enum::Type::String && _v1.type < Nectar::Enum::Type::String)
		{
			int _left = (int)_v1;
			if(_left == 0) return Nectar::Global::NaN;
			return (int)data.number % _left;
		}
		else
		{
			double _left = (double)_v1;
			if(_left == 0) return Nectar::Global::NaN;
			return remainder((double)*this, _left);
		}
	}
	VAR& VAR::operator%=(const VAR &_v1)
	{
		if (type < Nectar::Enum::Type::String)
		{
			int _left = (int)data.number;
			_left %= (int)_v1;
			if(_left == 0) data.number = std::numeric_limits<double>::quiet_NaN();
			data.number = _left;
		}
		else
		{
			return Nectar::Global::NaN;
		}
		return *this;
	}
	// TODO: "**" and "**=" VAR::operators
	// var++
	VAR& VAR::operator++(const int _v1)
	{
		if (type < Nectar::Enum::Type::String)
		{
			data.number++;
		}
		return *this;
	}
	// ++var
	VAR& VAR::operator++()
	{
		if (type < Nectar::Enum::Type::String)
		{
			++data.number;
		}
		return *this;
	}
	// var--
	VAR& VAR::operator--(const int _v1)
	{
		if (type < Nectar::Enum::Type::String)
		{
			data.number--;
		}
		return *this;
	}
	// --var
	VAR& VAR::operator--()
	{
		if (type < Nectar::Enum::Type::String)
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
			case Nectar::Enum::Type::Number:
				return (bool)(data.number == _v1);
			case Nectar::Enum::Type::Boolean:
				return __Nectar_Create_Boolean((bool)data.number == (bool)_v1);
			case Nectar::Enum::Type::String:
				return __Nectar_Create_Boolean((((Nectar::Class::String*)data.ptr)->value).compare((std::string)_v1) == 0);
			case Nectar::Enum::Type::Null:
			case Nectar::Enum::Type::Undefined:
				return __Nectar_Create_Boolean(true);
			case Nectar::Enum::Type::Array:
			case Nectar::Enum::Type::Native:
			case Nectar::Enum::Type::Function:
			case Nectar::Enum::Type::Object:
			default:
				return __Nectar_Create_Boolean(false);
			}
		}
		else
		{
			if (type == Nectar::Enum::Type::String || _v1.type == Nectar::Enum::Type::String)
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
		type = Nectar::Enum::Type::Number;
		data.number = (int)*this & (int)_v1;
		return *this;
	}
	
	VAR VAR::operator|(const VAR &_v1)
	{ 
		return (int)*this | (int)_v1;
	}
	VAR VAR::operator|=(const VAR &_v1)
	{
		if (type < Nectar::Enum::Type::String)
		{
			data.number = (int)data.number | (int)_v1;
		}
		else
		{
			return Nectar::Global::NaN;
		}
		return *this;
	}
	VAR VAR::operator^(const VAR &_v1) { return (int)*this ^ (int)_v1; }
	VAR VAR::operator^=(const VAR &_v1)
	{
		if (type < Nectar::Enum::Type::String)
		{
			data.number = (int)data.number ^ (int)_v1;
		}
		else
		{
			return Nectar::Global::NaN;
		}
		return *this;
	}
	VAR VAR::operator~() { return ~(int)*this; }
	VAR VAR::operator>>(const VAR &_v1) { return (int)*this >> (int)_v1; }
	VAR VAR::operator>>=(const VAR &_v1)
	{
		if (type < Nectar::Enum::Type::String)
		{
			data.number = (int)data.number >> (int)_v1;
		}
		else
		{
			return Nectar::Global::NaN;
		}
		return *this;
	}
	VAR VAR::operator<<(const VAR &_v1) 
	{ 
		return (int)*this << (int)_v1; 
	}
	VAR VAR::operator<<=(const VAR &_v1)
	{
		if (type < Nectar::Enum::Type::String)
		{
			data.number = (int)data.number << (int)_v1;
		}
		else
		{
			return Nectar::Global::NaN;
		}
		return *this;
	}

	VAR::operator int() const
	{
		if(type < Nectar::Enum::Type::String) return data.number;
		return (int)(*(Nectar::Class::Base*)data.ptr);
	}
	
	VAR::operator int()
	{
		if(type < Nectar::Enum::Type::String) return data.number;
		return (int)(*(Nectar::Class::Base*)data.ptr);
	}

	VAR::operator double() const
	{
		if(type < Nectar::Enum::Type::String) return data.number;
		return (double)(*(Nectar::Class::Base*)data.ptr);
	}
	
	VAR::operator double()
	{
		if(type < Nectar::Enum::Type::String) return data.number;
		return (double)(*(Nectar::Class::Base*)data.ptr);
	}

	VAR::operator bool() const
	{
		if(type == Nectar::Enum::Type::Undefined) return false;
		else if(type == Nectar::Enum::Type::Boolean || type == Nectar::Enum::Type::Number) return data.number;
		else return (bool)(*(Nectar::Class::Base*)data.ptr);
	}
	
	VAR::operator bool()
	{
		if(type == Nectar::Enum::Type::Undefined) return false;
		else if(type == Nectar::Enum::Type::Boolean || type == Nectar::Enum::Type::Number) return data.number;
		else return (bool)(*(Nectar::Class::Base*)data.ptr);
	}

	VAR::operator std::string() const
	{
		if(type < Nectar::Enum::Type::String) return __Nectar_DOUBLE_TO_STRING(data.number);
		return (std::string)(*(Nectar::Class::Base*)data.ptr);
	}
	
	VAR::operator std::string()
	{
		if(type < Nectar::Enum::Type::String) return __Nectar_DOUBLE_TO_STRING(data.number);
		return (std::string)(*(Nectar::Class::Base*)data.ptr);
	}

	VAR::operator long long()
	{
		if(type < Nectar::Enum::Type::String) return data.number;
		return (long long)((double)*this);
	}

	VAR::operator long long() const
	{
		if(type < Nectar::Enum::Type::String) return data.number;
		return (long long)((double)*this);
	}

		
} // namespace Nectar