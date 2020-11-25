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

Nectar::VAR __Nectar_Boolean_Result(Nectar::VAR _v)
{
	if (_v.type == Nectar::Enum::Type::Number)
		return _v.data.number;
	else if (_v.type == Nectar::Enum::Type::Boolean)
		return _v.data.number;
	else if (_v.type == Nectar::Enum::Type::String)
	{
		if (strlen(((Nectar::Class::String*)_v.data.ptr)->value.c_str()) > 0)
			return true;
		else
			return false;
	}
	else if (_v.type == Nectar::Enum::Type::Array)
		return true;
	else
		return false;
}

std::string __Nectar_DOUBLE_TO_STRING(double _var)
{
	std::ostringstream strout ;
	strout << std::fixed << std::setprecision(14) << _var;
	std::string str = strout.str() ;
	
	size_t end = str.find_last_not_of( '0' ) + 1 ;
	str = str.erase( end ) ;
	
	end = str.find_last_not_of( '.' ) + 1 ;
	str = str.erase( end ) ;
	
	int exp = str.length();
	if(exp > 20)
	{
		std::string first = str.substr(0, 1);
		std::string second = str.substr(1, 15);
		str = first + "." + second + "e+" + std::to_string(exp-1);
	}
	return str;
}

std::ostream &operator<<(std::ostream &os, const Nectar::VAR &_v)
{
	switch (_v.type)
	{
	case Nectar::Enum::Type::Undefined:
		os << (std::string)(*(Nectar::Class::Undefined*)_v.data.ptr);
		break;
	case Nectar::Enum::Type::Boolean:
		if(_v.data.number) os << "true";
		else os << "false";
		break;
	case Nectar::Enum::Type::Number:
		os << (std::string)_v;
		break;
	case Nectar::Enum::Type::String:
		os << (std::string)(*(Nectar::Class::String*)_v.data.ptr);
		break;
	case Nectar::Enum::Type::Object:
		os << __Nectar_Object_Stringify(_v);
		break;
	case Nectar::Enum::Type::FixedArray:
		os << __Nectar_Object_Stringify(_v);
		break;
	case Nectar::Enum::Type::Array:
		os << __Nectar_Object_Stringify(_v);
		break;
	case Nectar::Enum::Type::Struct:
		os << (std::string)(*(Nectar::Class::Struct*)_v.data.ptr);
		break;
	case Nectar::Enum::Type::Native:
		os << (std::string)(*(Nectar::Class::Native*)_v.data.ptr);
		break;
	case Nectar::Enum::Type::Function:
		os << (std::string)(*(Nectar::Class::Function*)_v.data.ptr);
		break;
	case Nectar::Enum::Type::Null:
		os << "null";
		break;
	default:
		os << "undefined";
		break;
	}
	return os;
}

Nectar::VAR parseInt(Nectar::VAR _str)
{
	if (_str.type == Nectar::Enum::Type::String)
	{
#ifdef __Nectar_ENV_ARDUINO
		return Nectar::Global::undefined;
#else
		return __Nectar_Create_Number((double)(*(Nectar::Class::String*)_str.data.ptr));
#endif
	}
	else
		return __Nectar_Create_Undefined();
}

Nectar::VAR __Nectar_Log_Console(Nectar::VAR _var)
{
#ifdef __Nectar_ENV_ARDUINO

#else
	std::cout << _var;
	std::cout << std::endl;
#endif

	return Nectar::Global::undefined;
}

Nectar::VAR __Nectar_Log_Console(Nectar::VAR* _var, int _length)
{
#ifdef __Nectar_ENV_ARDUINO

#else
	bool first = false;
	for(int i = 0; i < _length; i++)
	{
		if(first) std::cout << " ";
		std::cout << _var[i];
		if(!first) first = true;
	}
	std::cout << std::endl;
#endif

	return Nectar::Global::undefined;
}

Nectar::VAR __Nectar_Object_Keys(Nectar::VAR _var)
{
	Nectar::VAR _res = new Nectar::Class::Array();
	
	if (_var.type != Nectar::Enum::Type::Object && _var.type != Nectar::Enum::Type::Array)
	{
		return _res;
	}

	if(_var.type == Nectar::Enum::Type::Array)
	{
		Nectar::Type::vector_t *_arr = &((Nectar::Class::Array*)_var.data.ptr)->value;
		int _j = (*_arr).size();
		for (int _i = 0; _i < _j; _i++)
		{

			if(!(*_arr)[_i].property[1])
			{
				_res["push"](std::to_string(_i));
			}
		}
	}

	Nectar::Type::object_t *_obj;
	if(_var.type == Nectar::Enum::Type::Array) _obj = &((Nectar::Class::Array*)_var.data.ptr)->object;
	else _obj = &((Nectar::Class::Object*)_var.data.ptr)->object;
	
	#ifndef __Nectar__OBJECT_VECTOR
	for (auto _el: *_obj)
	{
		if(!_var.property[1])
		{
			_res["push"](_el.first);
		}
	}
	#else
	int _j = (*_obj).size();
	for (int _k = 0; _k < _j; _k++)
	{
		if(!_var.property[1])
		{
			_res["push"]((*_obj)[_k].first);
		}
	}
	#endif
	return _res;
}

Nectar::VAR __Nectar_Object_Stringify(Nectar::VAR _var)
{
	return __Nectar_Object_Stringify(_var, true);
}

Nectar::VAR __Nectar_Object_Stringify(Nectar::VAR _var, bool _bracket)
{
	if(_var.property[1]) return "";
	Nectar::Enum::Type _t = _var.type;

	if (_t == Nectar::Enum::Type::Undefined)
		return "\e[90mundefined\e[0m";
	else if (_t == Nectar::Enum::Type::Number)
		return Nectar::VAR("\e[33m") + _var + "\e[0m";
	else if (_t == Nectar::Enum::Type::String)
		return Nectar::VAR("\e[32m'") + _var + "'\e[0m";
	else if (_t == Nectar::Enum::Type::Function)
		return Nectar::VAR("'") + (std::string)(*(Nectar::Class::Function*)_var.data.ptr) + "'";
	else if (_t == Nectar::Enum::Type::FixedArray)
	{
		Nectar::VAR _res = "";
		Nectar::VAR *_arr = ((Nectar::Class::FixedArray*)_var.data.ptr)->value;
		Nectar::Type::object_t *_obj = &((Nectar::Class::FixedArray*)_var.data.ptr)->object;
		if(_bracket) _res += " [ ";
		int i = 0;
		int j = ((Nectar::Class::FixedArray*)_var.data.ptr)->length;
		int k = 0;
		int l = 0;
		for (int i = 0; i < j; i++)
		{
			if((*_arr)[i].property[1])
			{
				k++;
			}
			else
			{
				if (l > 0) _res += ", ";
				if(k > 0)
				{
					if(k == 1)
						_res += "\e[90m<1 empty item>\e[0m, ";
					else
						_res += "\e[90m<" + std::to_string(k) + " empty items>\e[0m, ";
					k = 0;
				}
				_res += __Nectar_Object_Stringify((*_arr)[i], _bracket);
				l++;
			}
		}
		
		if(k > 0)
		{
			if (l > 0) _res += ", ";
			if(k == 1)
				_res += "\e[90m<1 empty item>\e[0m";
			else
				_res += "\e[90m<" + std::to_string(k) + " empty items>\e[0m";
			l++;
		}
		
		for(auto& o: (*_obj))
		{
			if(!o.second.property[1])
			{
				if (l > 0) _res += ", ";
			
				_res += o.first + ":" + ((std::string)__Nectar_Object_Stringify(o.second, _bracket));
				l++;
			}
		}
		
		if(_bracket) _res += " ] ";

		return _res;
	}
	else if (_t == Nectar::Enum::Type::Array)
	{
		Nectar::VAR _res = "";
		Nectar::Type::vector_t *_arr = &((Nectar::Class::Array*)_var.data.ptr)->value;
		Nectar::Type::object_t *_obj = &((Nectar::Class::Array*)_var.data.ptr)->object;
		if(_bracket) _res += " [ ";
		int j = (*_arr).size();
		int k = 0;
		int l = 0;
		for (int i = 0; i < j; i++)
		{
			if((*_arr)[i].property[1])
			{
				k++;
			}
			else
			{
				if (l > 0) _res += ", ";
				if(k > 0)
				{
					if(k == 1)
						_res += "\e[90m<1 empty item>\e[0m, ";
					else
						_res += "\e[90m<" + std::to_string(k) + " empty items>\e[0m, ";
					k = 0;
				}
				_res += __Nectar_Object_Stringify((*_arr)[i], _bracket);
				l++;
			}
		}
		if(k > 0)
		{
			if (l > 0) _res += ", ";
			if(k == 1)
				_res += "\e[90m<1 empty item>\e[0m";
			else
				_res += "\e[90m<" + std::to_string(k) + " empty items>\e[0m";
			l++;
		}
		for(auto& o: (*_obj))
		{
			if(!o.second.property[1])
			{
				if (l > 0) _res += ", ";
			
				_res += o.first + ":" + ((std::string)__Nectar_Object_Stringify(o.second, _bracket));
				l++;
			}
		}
		
		if(_bracket) _res += " ] ";

		return _res;
	}
	else if (_t == Nectar::Enum::Type::Object)
	{
		Nectar::VAR _res = "";
		Nectar::Type::object_t *_obj = &((Nectar::Class::Object*)_var.data.ptr)->object;
		_res = "{";
		#ifndef __Nectar__OBJECT_VECTOR
		int _i = 0;
		for (auto _el: *_obj)
		{
			if(!_el.second.property[1])
			{
				if (_i > 0) _res += ", ";
				_res += Nectar::VAR("\"") + _el.first + "\"";
				_res += ":";
				_res += __Nectar_Object_Stringify(_el.second);
				_i++;
			}
		}
		#else
		int j = (*_obj).size();
		for (int _i = 0; _i < j; _i++)
		{
			if(!(*_obj)[_i].second.property[1])
			{
				if (_i > 0) _res += ", ";
				_res += Nectar::VAR("\"") + (*_obj)[_i].first + "\"";
				_res += ":";
				_res += __Nectar_Object_Stringify((*_obj)[_i].second);
			}
		}
		#endif
		_res += "}";
		return _res;
	}
	else
		return "";
}

Nectar::VAR __Nectar_Object_Clone(Nectar::VAR& _var)
{
	Nectar::Enum::Type _t = _var.type;
	switch(_t)
	{
		case Nectar::Enum::Type::Undefined:
		case Nectar::Enum::Type::Number:
		case Nectar::Enum::Type::String:
		case Nectar::Enum::Type::Function:
			return _var;
		case Nectar::Enum::Type::Array:
		{
			Nectar::VAR _res = new Nectar::Class::Array();
			std::vector<Nectar::VAR> *_arr = &((Nectar::Class::Array*)_var.data.ptr)->value;

			int j = (*_arr).size();
			for (int i = 0; i < j; i++)
			{
				_res[i] = __Nectar_Object_Clone((*_arr)[i]);
			}
			return _res;
		}
		case Nectar::Enum::Type::Object:
		{
			const Nectar::VAR _res = new Nectar::Class::Object();
			Nectar::Type::object_t *_obj = &((Nectar::Class::Object*)_var.data.ptr)->object;
			#ifndef __Nectar__OBJECT_VECTOR
			for (auto _el: *_obj)
			{
				_res[_el.first] = __Nectar_Object_Clone(_el.second);
			}
			#else
			int j = (*_obj).size();
			for (int _i = 0; _i < j; _i++)
			{
				_res[(*_obj)[_i].first] = __Nectar_Object_Clone((*_obj)[_i].second);
			}
			#endif
			return _res;
		}
		default:
			return Nectar::Global::undefined;
	}
}

void __Nectar_Object_Construct(Nectar::VAR _this, Nectar::VAR _prototype)
{
	if(_this.type == Nectar::Enum::Type::Object && _prototype.type == Nectar::Enum::Type::Object)
	{
		Nectar::Type::object_t *_obj = &((Nectar::Class::Object*)_prototype.data.ptr)->object;
		
		#ifndef __Nectar__OBJECT_VECTOR
		for (auto _el: *_obj)
		{
			Nectar::VAR _tmp =  _this[_el.first];
			if(_tmp.type == Nectar::Enum::Type::Undefined)
			{
				_this[_el.first] = _el.second;
			}
		}
		#else
		int j = (*_obj).size();
		for (int _i = 0; _i < j; _i++)
		{
			Nectar::VAR _tmp =  _this[(*_obj)[_i].first];
			if(_tmp.type == Nectar::Enum::Type::Undefined)
			{
				_this[(*_obj)[_i].first] = (*_obj)[_i].second;
			}
		}
		#endif
	}
	
}

Nectar::VAR __Nectar_CREATE_Function(void *_fn)
{
	return Nectar::VAR(Nectar::Enum::Type::Function, _fn);
}

Nectar::VAR __Nectar_Create_Native(void *_native)
{
	return Nectar::VAR(Nectar::Enum::Type::Undefined, _native);
}

void *__Nectar_Get_Native(Nectar::VAR _native)
{
	return ((Nectar::Class::Function*)_native.data.ptr);
}

__Nectar_Create_Lambda(__IMPL_EVAL)
{
	__Nectar_Log_Console("eval not implemented, return Nectar::Global::undefined");
	return Nectar::VAR();
});

Nectar::VAR eval = __Nectar_Create_Function(__IMPL_EVAL);

std::function<Nectar::VAR(Nectar::Type::vector_t)> *__Nectar_IS_NAN = new std::function<Nectar::VAR(Nectar::Type::vector_t)>([](Nectar::Type::vector_t _Nectar_VARARGS) {
	Nectar::VAR _test;
	if (_Nectar_VARARGS.size() > 0)
		_test = _Nectar_VARARGS[0];
	else
		return __Nectar_Create_Boolean(0);

	if (_test.type == Nectar::Enum::Type::Number)
	{
		return __Nectar_Create_Boolean(1);
	}

	return __Nectar_Create_Boolean(0);
});

Nectar::VAR isNaN = Nectar::VAR(Nectar::Enum::Type::Function, __Nectar_IS_NAN);

Nectar::VAR __Nectar_EQUAL_VALUE_AND_TYPE(Nectar::VAR _left, Nectar::VAR _right)
{
	if (_left.type == _right.type && (Nectar::VAR)_left == (Nectar::VAR)_right)
	{
		return __Nectar_Create_Boolean(1);
	}

	return __Nectar_Create_Boolean(0);
}

Nectar::VAR __Nectar_NOT_EQUAL_VALUE_AND_TYPE(Nectar::VAR _left, Nectar::VAR _right)
{
	if (_left.type != _right.type || (bool)(_left != _right))
	{
		return __Nectar_Create_Boolean(1);
	}

	return __Nectar_Create_Boolean(0);
}

Nectar::VAR operator+ (Nectar::VAR _left, int right)
{
	if (_left.type == Nectar::Enum::Type::String) return (std::string)_left + __Nectar_DOUBLE_TO_STRING(right);
	else return (double)_left + right;
}

Nectar::VAR operator+ (Nectar::VAR _left, double right)
{
	if (_left.type == Nectar::Enum::Type::String) return (std::string)_left + __Nectar_DOUBLE_TO_STRING(right);
	else return (double)_left + right;
}

Nectar::VAR operator+ (Nectar::VAR _left, const char* right)
{
	return (std::string)_left + std::string(right);
}

void operator+= (Nectar::VAR& _left, std::string right)
{
	std::string _str = (std::string)_left;
	_str += right;
	_left = _str;
}

void operator+= (Nectar::VAR& _left, const char* right)
{
	std::string _str = (std::string)_left;
	_str += right;
	_left = _str;
}

void operator+= (Nectar::VAR& _left, int right)
{
	if(_left.type == Nectar::Enum::Type::Number) _left.data.number += right;
	else
	{
		std::string _str = (std::string)_left;
		_str += right;
		_left = _str;
	}
}

void operator+= (Nectar::VAR& _left, double right)
{
	if(_left.type == Nectar::Enum::Type::Number) _left.data.number += right;
	else
	{
		std::string _str = (std::string)_left;
		_str += right;
		_left.data.ptr = new Nectar::Class::String(_str);
		_left.type = Nectar::Enum::Type::String;
	}
}

Nectar::VAR operator* (Nectar::VAR _left, const char* right)
{
	return _left * std::string(right);
}

Nectar::VAR operator- (Nectar::VAR _left, const char* right)
{
	return _left - std::string(right);
}

Nectar::VAR operator/ (Nectar::VAR _left, const char* right)
{
	return _left / std::string(right);
}

Nectar::VAR operator|| (Nectar::VAR _left, int right)
{
	if(_left.type != Nectar::Enum::Type::Undefined) return _left;
	else return right;
}

Nectar::VAR operator|| (Nectar::VAR _left, double right)
{
	if(_left.type != Nectar::Enum::Type::Undefined) return _left;
	else return right;
}

Nectar::VAR operator|| (Nectar::VAR _left, std::string right)
{
	if(_left.type != Nectar::Enum::Type::Undefined) return _left;
	else return right;
}

Nectar::VAR operator|| (Nectar::VAR _left, Nectar::VAR right)
{
	if(_left.type != Nectar::Enum::Type::Undefined) return _left;
	else return right;
}
