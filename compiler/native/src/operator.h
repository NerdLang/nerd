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

NectarCore::VAR __Nectar_Boolean_Result(NectarCore::VAR _v)
{
	if (_v.type == NectarCore::Enum::Type::Number)
		return _v.data.number;
	else if (_v.type == NectarCore::Enum::Type::Boolean)
		return _v.data.number;
	else if (_v.type == NectarCore::Enum::Type::String)
	{
		if (strlen(((NectarCore::Class::String*)_v.data.ptr)->value.c_str()) > 0)
			return true;
		else
			return false;
	}
	else if (_v.type == NectarCore::Enum::Type::Array)
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

std::ostream &operator<<(std::ostream &os, const NectarCore::VAR &_v)
{
	switch (_v.type)
	{
	case NectarCore::Enum::Type::Undefined:
		os << (std::string)(*(NectarCore::Class::Undefined*)_v.data.ptr);
		break;
	case NectarCore::Enum::Type::Boolean:
		if(_v.data.number) os << "true";
		else os << "false";
		break;
	case NectarCore::Enum::Type::Number:
		os << (std::string)_v;
		break;
	case NectarCore::Enum::Type::String:
		os << (std::string)(*(NectarCore::Class::String*)_v.data.ptr);
		break;
	case NectarCore::Enum::Type::Object:
		os << __Nectar_Object_Stringify(_v);
		break;
	case NectarCore::Enum::Type::FixedArray:
		os << __Nectar_Object_Stringify(_v);
		break;
	case NectarCore::Enum::Type::Array:
		os << __Nectar_Object_Stringify(_v);
		break;
	case NectarCore::Enum::Type::Struct:
		os << (std::string)(*(NectarCore::Class::Struct*)_v.data.ptr);
		break;
	case NectarCore::Enum::Type::Native:
		os << (std::string)(*(NectarCore::Class::Native*)_v.data.ptr);
		break;
	case NectarCore::Enum::Type::Function:
		os << (std::string)(*(NectarCore::Class::Function*)_v.data.ptr);
		break;
	case NectarCore::Enum::Type::Null:
		os << "null";
		break;
	default:
		os << "undefined";
		break;
	}
	return os;
}

NectarCore::VAR parseInt(NectarCore::VAR _str)
{
	if (_str.type == NectarCore::Enum::Type::String)
	{
#ifdef __Nectar_ENV_ARDUINO
		return NectarCore::Global::undefined;
#else
		return __Nectar_Create_Number((double)(*(NectarCore::Class::String*)_str.data.ptr));
#endif
	}
	else
		return __Nectar_Create_Undefined();
}

NectarCore::VAR __Nectar_Log_Console(NectarCore::VAR _var)
{
#ifdef __Nectar_ENV_ARDUINO

#else
	std::cout << _var;
	std::cout << std::endl;
#endif

	return NectarCore::Global::undefined;
}

NectarCore::VAR __Nectar_Log_Console(NectarCore::VAR* _var, int _length)
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

	return NectarCore::Global::undefined;
}

NectarCore::VAR __Nectar_Object_Keys(NectarCore::VAR _var)
{
	NectarCore::VAR _res = new NectarCore::Class::Array();
	
	if (_var.type != NectarCore::Enum::Type::Object && _var.type != NectarCore::Enum::Type::Array)
	{
		return _res;
	}

	if(_var.type == NectarCore::Enum::Type::Array)
	{
		NectarCore::Type::vector_t *_arr = &((NectarCore::Class::Array*)_var.data.ptr)->value;
		int _j = (*_arr).size();
		for (int _i = 0; _i < _j; _i++)
		{

			if(!(*_arr)[_i].property[1])
			{
				_res["push"](std::to_string(_i));
			}
		}
	}

	NectarCore::Type::object_t *_obj;
	if(_var.type == NectarCore::Enum::Type::Array) _obj = &((NectarCore::Class::Array*)_var.data.ptr)->object;
	else _obj = &((NectarCore::Class::Object*)_var.data.ptr)->object;
	
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

NectarCore::VAR __Nectar_Object_Stringify(NectarCore::VAR _var)
{
	return __Nectar_Object_Stringify(_var, true);
}

NectarCore::VAR __Nectar_Object_Stringify(NectarCore::VAR _var, bool _bracket)
{
	if(_var.property[1]) return "";
	NectarCore::Enum::Type _t = _var.type;

	if (_t == NectarCore::Enum::Type::Undefined)
		return "\e[90mundefined\e[0m";
	else if (_t == NectarCore::Enum::Type::Number)
		return NectarCore::VAR("\e[33m") + _var + "\e[0m";
	else if (_t == NectarCore::Enum::Type::String)
		return NectarCore::VAR("\e[32m'") + _var + "'\e[0m";
	else if (_t == NectarCore::Enum::Type::Function)
		return NectarCore::VAR("'") + (std::string)(*(NectarCore::Class::Function*)_var.data.ptr) + "'";
	else if (_t == NectarCore::Enum::Type::FixedArray)
	{
		NectarCore::VAR _res = "";
		NectarCore::VAR *_arr = ((NectarCore::Class::FixedArray*)_var.data.ptr)->value;
		NectarCore::Type::object_t *_obj = &((NectarCore::Class::FixedArray*)_var.data.ptr)->object;
		if(_bracket) _res += " [ ";
		int j = ((NectarCore::Class::FixedArray*)_var.data.ptr)->length;
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
	else if (_t == NectarCore::Enum::Type::Array)
	{
		NectarCore::VAR _res = "";
		NectarCore::Type::vector_t *_arr = &((NectarCore::Class::Array*)_var.data.ptr)->value;
		NectarCore::Type::object_t *_obj = &((NectarCore::Class::Array*)_var.data.ptr)->object;
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
	else if (_t == NectarCore::Enum::Type::Object)
	{
		NectarCore::VAR _res = "";
		NectarCore::Type::object_t *_obj = &((NectarCore::Class::Object*)_var.data.ptr)->object;
		_res = "{";
		#ifndef __Nectar__OBJECT_VECTOR
		int _i = 0;
		for (auto _el: *_obj)
		{
			if(!_el.second.property[1])
			{
				if (_i > 0) _res += ", ";
				_res += NectarCore::VAR("\"") + _el.first + "\"";
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
				_res += NectarCore::VAR("\"") + (*_obj)[_i].first + "\"";
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

NectarCore::VAR __Nectar_Object_Clone(NectarCore::VAR& _var)
{
	NectarCore::Enum::Type _t = _var.type;
	switch(_t)
	{
		case NectarCore::Enum::Type::Undefined:
		case NectarCore::Enum::Type::Number:
		case NectarCore::Enum::Type::String:
		case NectarCore::Enum::Type::Function:
			return _var;
		case NectarCore::Enum::Type::Array:
		{
			NectarCore::VAR _res = new NectarCore::Class::Array();
			std::vector<NectarCore::VAR> *_arr = &((NectarCore::Class::Array*)_var.data.ptr)->value;

			int j = (*_arr).size();
			for (int i = 0; i < j; i++)
			{
				_res[i] = __Nectar_Object_Clone((*_arr)[i]);
			}
			return _res;
		}
		case NectarCore::Enum::Type::Object:
		{
			const NectarCore::VAR _res = new NectarCore::Class::Object();
			NectarCore::Type::object_t *_obj = &((NectarCore::Class::Object*)_var.data.ptr)->object;
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
			return NectarCore::Global::undefined;
	}
}

void __Nectar_Object_Construct(NectarCore::VAR _this, NectarCore::VAR _prototype)
{
	if(_this.type == NectarCore::Enum::Type::Object && _prototype.type == NectarCore::Enum::Type::Object)
	{
		NectarCore::Type::object_t *_obj = &((NectarCore::Class::Object*)_prototype.data.ptr)->object;
		
		#ifndef __Nectar__OBJECT_VECTOR
		for (auto _el: *_obj)
		{
			NectarCore::VAR _tmp =  _this[_el.first];
			if(_tmp.type == NectarCore::Enum::Type::Undefined)
			{
				_this[_el.first] = _el.second;
			}
		}
		#else
		int j = (*_obj).size();
		for (int _i = 0; _i < j; _i++)
		{
			NectarCore::VAR _tmp =  _this[(*_obj)[_i].first];
			if(_tmp.type == NectarCore::Enum::Type::Undefined)
			{
				_this[(*_obj)[_i].first] = (*_obj)[_i].second;
			}
		}
		#endif
	}
	
}

NectarCore::VAR __Nectar_CREATE_Function(void *_fn)
{
	return NectarCore::VAR(NectarCore::Enum::Type::Function, _fn);
}

NectarCore::VAR __Nectar_Create_Native(void *_native)
{
	return NectarCore::VAR(NectarCore::Enum::Type::Undefined, _native);
}

void *__Nectar_Get_Native(NectarCore::VAR _native)
{
	return ((NectarCore::Class::Function*)_native.data.ptr);
}

__Nectar_Create_Lambda(__IMPL_EVAL)
{
	__Nectar_Log_Console("eval not implemented, return NectarCore::Global::undefined");
	return NectarCore::VAR();
});

NectarCore::VAR eval = __Nectar_Create_Function(__IMPL_EVAL);

std::function<NectarCore::VAR(NectarCore::Type::vector_t)> *__Nectar_IS_NAN = new std::function<NectarCore::VAR(NectarCore::Type::vector_t)>([](NectarCore::Type::vector_t _Nectar_VARARGS) {
	NectarCore::VAR _test;
	if (_Nectar_VARARGS.size() > 0)
		_test = _Nectar_VARARGS[0];
	else
		return __Nectar_Create_Boolean(0);

	if (_test.type == NectarCore::Enum::Type::Number)
	{
		return __Nectar_Create_Boolean(1);
	}

	return __Nectar_Create_Boolean(0);
});

NectarCore::VAR isNaN = NectarCore::VAR(NectarCore::Enum::Type::Function, __Nectar_IS_NAN);

NectarCore::VAR __Nectar_EQUAL_VALUE_AND_TYPE(NectarCore::VAR _left, NectarCore::VAR _right)
{
	if (_left.type == _right.type && (NectarCore::VAR)_left == (NectarCore::VAR)_right)
	{
		return __Nectar_Create_Boolean(1);
	}

	return __Nectar_Create_Boolean(0);
}

NectarCore::VAR __Nectar_NOT_EQUAL_VALUE_AND_TYPE(NectarCore::VAR _left, NectarCore::VAR _right)
{
	if (_left.type != _right.type || (bool)(_left != _right))
	{
		return __Nectar_Create_Boolean(1);
	}

	return __Nectar_Create_Boolean(0);
}

NectarCore::VAR operator+ (NectarCore::VAR _left, int right)
{
	if (_left.type == NectarCore::Enum::Type::String) return (std::string)_left + __Nectar_DOUBLE_TO_STRING(right);
	else return (double)_left + right;
}

NectarCore::VAR operator+ (NectarCore::VAR _left, double right)
{
	if (_left.type == NectarCore::Enum::Type::String) return (std::string)_left + __Nectar_DOUBLE_TO_STRING(right);
	else return (double)_left + right;
}

NectarCore::VAR operator+ (NectarCore::VAR _left, const char* right)
{
	return (std::string)_left + std::string(right);
}

void operator+= (NectarCore::VAR& _left, std::string right)
{
	std::string _str = (std::string)_left;
	_str += right;
	_left = _str;
}

void operator+= (NectarCore::VAR& _left, const char* right)
{
	std::string _str = (std::string)_left;
	_str += right;
	_left = _str;
}

void operator+= (NectarCore::VAR& _left, int right)
{
	if(_left.type == NectarCore::Enum::Type::Number) _left.data.number += right;
	else
	{
		std::string _str = (std::string)_left;
		_str += right;
		_left = _str;
	}
}

void operator+= (NectarCore::VAR& _left, double right)
{
	if(_left.type == NectarCore::Enum::Type::Number) _left.data.number += right;
	else
	{
		std::string _str = (std::string)_left;
		_str += right;
		_left.data.ptr = new NectarCore::Class::String(_str);
		_left.type = NectarCore::Enum::Type::String;
	}
}

NectarCore::VAR operator* (NectarCore::VAR _left, const char* right)
{
	return _left * std::string(right);
}

NectarCore::VAR operator- (NectarCore::VAR _left, const char* right)
{
	return _left - std::string(right);
}

NectarCore::VAR operator/ (NectarCore::VAR _left, const char* right)
{
	return _left / std::string(right);
}

NectarCore::VAR operator|| (NectarCore::VAR _left, int right)
{
	if(_left.type != NectarCore::Enum::Type::Undefined) return _left;
	else return right;
}

NectarCore::VAR operator|| (NectarCore::VAR _left, double right)
{
	if(_left.type != NectarCore::Enum::Type::Undefined) return _left;
	else return right;
}

NectarCore::VAR operator|| (NectarCore::VAR _left, std::string right)
{
	if(_left.type != NectarCore::Enum::Type::Undefined) return _left;
	else return right;
}

NectarCore::VAR operator|| (NectarCore::VAR _left, NectarCore::VAR right)
{
	if(_left.type != NectarCore::Enum::Type::Undefined) return _left;
	else return right;
}
