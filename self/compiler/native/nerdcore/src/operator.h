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

NerdCore::VAR operator+ (const char* _left, const NerdCore::VAR &_right)
{
	return NerdCore::VAR(_left) + _right;
}
NerdCore::VAR operator+ (std::string _left, const NerdCore::VAR &_right)
{
	return NerdCore::VAR(_left) + _right;
}

NerdCore::VAR operator* (const char* _left, const NerdCore::VAR &_right)
{
	return NerdCore::Global::NaN;
}
NerdCore::VAR operator* (std::string _left, const NerdCore::VAR &_right)
{
	return NerdCore::Global::NaN;
}

NerdCore::VAR operator- (const char* _left, const NerdCore::VAR &_right)
{
	return NerdCore::Global::NaN;
}
NerdCore::VAR operator- (std::string _left, const NerdCore::VAR &_right)
{
	return NerdCore::Global::NaN;
}

NerdCore::VAR operator/ (const char* _left, const NerdCore::VAR &_right)
{
	return NerdCore::Global::NaN;
}
NerdCore::VAR operator/ (std::string _left, const NerdCore::VAR &_right)
{
	return NerdCore::Global::NaN;
}

/*** operator== ***/
NerdCore::VAR operator== (NerdCore::VAR _left, int right)
{
	return (double)_left == right;
}

NerdCore::VAR operator== (NerdCore::VAR _left, double right)
{
	return (double)_left == right;
}

NerdCore::VAR operator== (NerdCore::VAR _left, std::string right)
{
	return (std::string)_left == right;
}

NerdCore::VAR operator== (NerdCore::VAR _left, const char* right)
{
	return (std::string)_left == std::string(right);
}
/* end operator== */

/*** operator!= ***/
NerdCore::VAR operator!= (NerdCore::VAR _left, int right)
{
	return (double)_left != right;
}

NerdCore::VAR operator!= (NerdCore::VAR _left, double right)
{
	return (double)_left != right;
}

NerdCore::VAR operator!= (NerdCore::VAR _left, std::string right)
{
	return (std::string)_left != right;
}

NerdCore::VAR operator!= (NerdCore::VAR _left, const char* right)
{
	return (std::string)_left != std::string(right);
}
/* end operator!= */

/*** operator| ***/
NerdCore::VAR operator| (NerdCore::VAR _left, int right)
{
	return (int)_left | right;
}

NerdCore::VAR operator| (NerdCore::VAR _left, double right)
{
	return (int)_left | (int)right;
}

NerdCore::VAR operator| (NerdCore::VAR _left, std::string right)
{
	return (double)_left;
}

NerdCore::VAR operator| (NerdCore::VAR _left, const char* right)
{
	return (double)_left;
}
/* end operator| */

/*** operator^ ***/
NerdCore::VAR operator^ (NerdCore::VAR _left, int right)
{
	return (int)_left ^ right;
}

NerdCore::VAR operator^ (NerdCore::VAR _left, double right)
{
	return (int)_left ^ (int)right;
}

NerdCore::VAR operator^ (NerdCore::VAR _left, std::string right)
{
	return (double)_left;
}

NerdCore::VAR operator^ (NerdCore::VAR _left, const char* right)
{
	return (double)_left;
}
/* end operator^ */

/*** operator& ***/
NerdCore::VAR operator& (NerdCore::VAR _left, int right)
{
	return (int)_left & right;
}

NerdCore::VAR operator& (NerdCore::VAR _left, double right)
{
	return (int)_left & (int)right;
}

NerdCore::VAR operator& (NerdCore::VAR _left, std::string right)
{
	return (double)_left;
}

NerdCore::VAR operator& (NerdCore::VAR _left, const char* right)
{
	return (double)_left;
}
/* end operator& */

/*** operator< **
inline NerdCore::VAR operator< (NerdCore::VAR _left, int right)
{
	return _left.data.number < right;
}


inline NerdCore::VAR operator< (NerdCore::VAR _left, double right)
{
	return _left.data.number < right;
}
*/
NerdCore::VAR operator< (NerdCore::VAR _left, std::string right)
{
	return (std::string)_left < right;
}

NerdCore::VAR operator< (NerdCore::VAR _left, const char* right)
{
	return (std::string)_left < std::string(right);
}
/* end operator< */

/*** operator<< ***/
NerdCore::VAR operator<< (NerdCore::VAR _left, int right)
{
	return (int)_left << right;
}

NerdCore::VAR operator<< (NerdCore::VAR _left, double right)
{
	return (int)_left << (int)right;
}

NerdCore::VAR operator<< (NerdCore::VAR _left, std::string right)
{
	return (std::string)_left << right;
}

NerdCore::VAR operator<< (NerdCore::VAR _left, const char* right)
{
	return (std::string)_left << std::string(right);
}
/* end operator<< */

/*** operator>= ***/
NerdCore::VAR operator<= (NerdCore::VAR _left, std::string right)
{
	return (std::string)_left <= right;
}

NerdCore::VAR operator<= (NerdCore::VAR _left, const char* right)
{
	return (std::string)_left < std::string(right);
}
/* end operator<= */

/*** operator> ***/

NerdCore::VAR operator> (NerdCore::VAR _left, std::string right)
{
	return (std::string)_left > right;
}

NerdCore::VAR operator> (NerdCore::VAR _left, const char* right)
{
	return (std::string)_left > std::string(right);
}
/* end operator> */

/*** operator>> ***/
NerdCore::VAR operator>> (NerdCore::VAR _left, int right)
{
	return (int)_left >> right;
}

NerdCore::VAR operator>> (NerdCore::VAR _left, double right)
{
	return (int)_left >> (int)right;
}

NerdCore::VAR operator>> (NerdCore::VAR _left, std::string right)
{
	return (std::string)_left >> right;
}

NerdCore::VAR operator>> (NerdCore::VAR _left, const char* right)
{
	return (std::string)_left >> std::string(right);
}
/* end operator>> */

/*** operator>= ***/

NerdCore::VAR operator>= (NerdCore::VAR _left, std::string right)
{
	return (std::string)_left >= right;
}

NerdCore::VAR operator>= (NerdCore::VAR _left, const char* right)
{
	return (std::string)_left > std::string(right);
}

/* end operator>= */

NerdCore::VAR __NERD_Boolean_Result(NerdCore::VAR _v)
{
	if (_v.type == NerdCore::Enum::Type::Number)
		return _v.data.number;
	else if (_v.type == NerdCore::Enum::Type::Boolean)
		return _v.data.number;
	else if (_v.type == NerdCore::Enum::Type::String)
	{
		if (strlen(((NerdCore::Class::String*)_v.data.ptr)->value.c_str()) > 0)
			return true;
		else
			return false;
	}
	else if (_v.type == NerdCore::Enum::Type::Array)
		return true;
	else
		return false;
}

std::string __NERD_DOUBLE_TO_STRING(double _var)
{
	std::ostringstream strout ;
	strout << std::fixed << std::setprecision(14) << _var;
	std::string str = strout.str() ;
	
	size_t end = str.find_last_not_of( '0' ) + 1 ;
	str = str.erase( end ) ;
	
	end = str.find_last_not_of( '.' ) + 1 ;
	str = str.erase( end ) ;
	
	int exp = str.length();
	if(exp > 21)
	{
		std::string first = str.substr(0, 1);
		std::string second = str.substr(1, 15);
		str = first + "." + second + "e+" + std::to_string(exp-1);
	}
	return str;
}

std::ostream &operator<<(std::ostream &os, const NerdCore::VAR &_v)
{
	switch (_v.type)
	{
	case NerdCore::Enum::Type::Boolean:
		if(_v.data.number) os << "true";
		else os << "false";
		break;
	case NerdCore::Enum::Type::Number:
			os << std::setprecision(14) << _v.data.number;
		break;
	case NerdCore::Enum::Type::String:
		os << (std::string)(*(NerdCore::Class::String*)_v.data.ptr);
		break;
	case NerdCore::Enum::Type::Object:
		os << __NERD_Object_Stringify(_v);
		break;
	case NerdCore::Enum::Type::FixedArray:
		os << __NERD_Object_Stringify(_v);
		break;
	case NerdCore::Enum::Type::Array:
		os << __NERD_Object_Stringify(_v);
		break;
	case NerdCore::Enum::Type::Struct:
		os << (std::string)(*(NerdCore::Class::Struct*)_v.data.ptr);
		break;
	case NerdCore::Enum::Type::Native:
		os << (std::string)(*(NerdCore::Class::Native*)_v.data.ptr);
		break;
	case NerdCore::Enum::Type::Function:
		os << (std::string)(*(NerdCore::Class::Function*)_v.data.ptr);
		break;
	case NerdCore::Enum::Type::Null:
		os << "null";
		break;
	default:
		os << "null";
		break;
	}
	return os;
	
}

NerdCore::VAR parseInt(NerdCore::VAR _str)
{
	if (_str.type == NerdCore::Enum::Type::String)
	{
#ifdef __NERD_ENV_ARDUINO
		return NerdCore::Global::null;
#else
		return __NERD_Create_Number((double)(*(NerdCore::Class::String*)_str.data.ptr));
#endif
	}
	else
		return NerdCore::Global::null;
}

NerdCore::VAR __NERD_Log_Console(NerdCore::VAR _var)
{
#ifdef __NERD_ENV_ARDUINO

#else
	std::cout << _var;
	std::cout << std::endl;
#endif

	return NerdCore::Global::null;
}

NerdCore::VAR __NERD_Log_Console(NerdCore::VAR* _var, int _length)
{
#ifdef __NERD_ENV_ARDUINO

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

	return NerdCore::Global::null;
}

NerdCore::VAR __NERD_Object_Keys(NerdCore::VAR _var)
{
	NerdCore::VAR _res = new NerdCore::Class::Array();
	
	if (_var.type != NerdCore::Enum::Type::Object && _var.type != NerdCore::Enum::Type::Array)
	{
		return _res;
	}

	if(_var.type == NerdCore::Enum::Type::Array)
	{
		NerdCore::Type::vector_t *_arr = &((NerdCore::Class::Array*)_var.data.ptr)->value;
		int _j = (*_arr).size();
		for (int _i = 0; _i < _j; _i++)
		{
			_res[_i] = std::to_string(_i);
		}
	}
	else 
	{
		NerdCore::Type::object_t *_obj;
		if(_var.type == NerdCore::Enum::Type::Object) _obj = &((NerdCore::Class::Object*)_var.data.ptr)->object;
		
		#ifndef __NERD__OBJECT_VECTOR
		int _k = 0;
		for (auto _el: *_obj)
		{
			_res[_k] = _el.first;
			_k++;
		}
		#else
		int _j = (*_obj).size();
		for (int _k = 0; _k < _j; _k++)
		{
			_res[_k] = (*_obj)[_k].first;
		}
		#endif
	}
	return _res;
}

NerdCore::VAR __NERD_Object_Stringify(NerdCore::VAR _var)
{
	return __NERD_Object_Stringify(_var, true);
}

NerdCore::VAR __NERD_Object_Stringify(NerdCore::VAR _var, bool _bracket)
{
	NerdCore::Enum::Type _t = _var.type;
	if (_t == NerdCore::Enum::Type::Number)
	{
		return "\e[33m" + _var + "\e[0m";
	}
	else if (_t == NerdCore::Enum::Type::String)
	{
		return "\e[32m'" + ((NerdCore::Class::String*)_var.data.ptr)->value + "'\e[0m";
	}
	else if (_t == NerdCore::Enum::Type::Function)
	{
		return "'" + (std::string)(*(NerdCore::Class::Function*)_var.data.ptr) + "'";
	}
	else if (_t == NerdCore::Enum::Type::FixedArray)
	{
		NerdCore::VAR _res = "";
		NerdCore::VAR *_arr = ((NerdCore::Class::FixedArray*)_var.data.ptr)->value;

		if(_bracket) _res += " [ ";
		int j = ((NerdCore::Class::FixedArray*)_var.data.ptr)->length;
		int k = 0;
		int l = 0;
		for (int i = 0; i < j; i++)
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
			_res += __NERD_Object_Stringify((*_arr)[i], _bracket);
			l++;
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
		
		if(_bracket) _res += " ] ";

		return _res;
	}
	else if (_t == NerdCore::Enum::Type::Array)
	{
		NerdCore::VAR _res = NerdCore::Global::var("");
		NerdCore::Type::vector_t *_arr = &((NerdCore::Class::Array*)_var.data.ptr)->value;
		if(_bracket) _res += " [ ";
		int j = (*_arr).size();
		int k = 0;
		int l = 0;
		for (int i = 0; i < j; i++)
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

			NerdCore::Global::var test = 
			_res += __NERD_Object_Stringify((*_arr)[i], _bracket);
			
			l++;
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

		if(_bracket) _res += " ] ";

		return _res;
	}
	else if (_t == NerdCore::Enum::Type::Object)
	{
		NerdCore::VAR _res = "";
		NerdCore::Type::object_t *_obj = &((NerdCore::Class::Object*)_var.data.ptr)->object;
		_res = "{";
		#ifndef __NERD__OBJECT_VECTOR
		int _i = 0;
		int _comma = 0;
		for (auto _el: *_obj)
		{
			if(_el.second.type != NerdCore::Enum::Type::Null && _el.first != "__proto__" && _el.first != "prototype")
			{
				if (_comma > 0) _res += ", ";
				_res += NerdCore::VAR("\"") + _el.first + "\"";
				_res += ":";
				_res += __NERD_Object_Stringify(_el.second);
				_comma++;
			}
			_i++;
		}
		#else
		int j = (*_obj).size();
		for (int _i = 0; _i < j; _i++)
		{
			if (_i > 0) _res += ", ";
			_res += NerdCore::VAR("\"") + (*_obj)[_i].first + "\"";
			_res += ":";
			_res += __NERD_Object_Stringify((*_obj)[_i].second);
		}
		#endif
		_res += "}";
		return _res;
	}
	else
		return "";
}

NerdCore::VAR __NERD_Object_Clone(NerdCore::VAR& _var)
{
	NerdCore::Enum::Type _t = _var.type;
	switch(_t)
	{
		case NerdCore::Enum::Type::Null:
		case NerdCore::Enum::Type::Number:
		case NerdCore::Enum::Type::String:
		case NerdCore::Enum::Type::Function:
			return _var;
		case NerdCore::Enum::Type::Array:
		{
			NerdCore::VAR _res = new NerdCore::Class::Array();
			std::vector<NerdCore::VAR> *_arr = &((NerdCore::Class::Array*)_var.data.ptr)->value;

			int j = (*_arr).size();
			for (int i = 0; i < j; i++)
			{
				_res[i] = __NERD_Object_Clone((*_arr)[i]);
			}
			return _res;
		}
		case NerdCore::Enum::Type::Object:
		{
			const NerdCore::VAR _res = new NerdCore::Class::Object();
			NerdCore::Type::object_t *_obj = &((NerdCore::Class::Object*)_var.data.ptr)->object;
			#ifndef __NERD__OBJECT_VECTOR
			for (auto _el: *_obj)
			{
				_res[_el.first] = __NERD_Object_Clone(_el.second);
			}
			#else
			int j = (*_obj).size();
			for (int _i = 0; _i < j; _i++)
			{
				_res[(*_obj)[_i].first] = __NERD_Object_Clone((*_obj)[_i].second);
			}
			#endif
			return _res;
		}
		default:
			return NerdCore::Global::null;
	}
}

void __NERD_Object_Construct(NerdCore::VAR _this, NerdCore::VAR _prototype)
{
	if(_this.type == NerdCore::Enum::Type::Object && _prototype.type == NerdCore::Enum::Type::Object)
	{
		NerdCore::Type::object_t *_obj = &((NerdCore::Class::Object*)_prototype.data.ptr)->object;
		
		#ifndef __NERD__OBJECT_VECTOR
		for (auto _el: *_obj)
		{
			NerdCore::VAR _tmp =  _this[_el.first];
			if(_tmp.type == NerdCore::Enum::Type::Null)
			{
				_this[_el.first] = _el.second;
			}
		}
		#else
		int j = (*_obj).size();
		for (int _i = 0; _i < j; _i++)
		{
			NerdCore::VAR _tmp =  _this[(*_obj)[_i].first];
			if(_tmp.type == NerdCore::Enum::Type::Null)
			{
				_this[(*_obj)[_i].first] = (*_obj)[_i].second;
			}
		}
		#endif
	}
	
}

NerdCore::VAR __NERD_CREATE_Function(void *_fn)
{
	return NerdCore::VAR(NerdCore::Enum::Type::Function, _fn);
}

NerdCore::VAR __NERD_Create_Native(void *_native)
{
	return NerdCore::VAR(NerdCore::Enum::Type::Null, _native);
}

void *__NERD_Get_Native(NerdCore::VAR _native)
{
	return ((NerdCore::Class::Function*)_native.data.ptr);
}

__NERD_Create_Lambda(__IMPL_EVAL)
{
	__NERD_Log_Console("eval not implemented, return NerdCore::Global::null");
	return NerdCore::VAR();
});

NerdCore::VAR eval = __NERD_Create_Function(__IMPL_EVAL);

std::function<NerdCore::VAR(NerdCore::Type::vector_t)> *__NERD_IS_NAN = new std::function<NerdCore::VAR(NerdCore::Type::vector_t)>([](NerdCore::Type::vector_t _Nerd_VARARGS) {
	NerdCore::VAR _test;
	if (_Nerd_VARARGS.size() > 0)
		_test = _Nerd_VARARGS[0];
	else
		return __NERD_Create_Boolean(0);

	if (_test.type == NerdCore::Enum::Type::Number)
	{
		return __NERD_Create_Boolean(1);
	}

	return __NERD_Create_Boolean(0);
});

NerdCore::VAR isNaN = NerdCore::VAR(NerdCore::Enum::Type::Function, __NERD_IS_NAN);

NerdCore::VAR __NERD_EQUAL_VALUE_AND_TYPE(NerdCore::VAR _left, NerdCore::VAR _right)
{
	if (_left.type == _right.type && (NerdCore::VAR)_left == (NerdCore::VAR)_right)
	{
		return __NERD_Create_Boolean(1);
	}

	return __NERD_Create_Boolean(0);
}

NerdCore::VAR __NERD_NOT_EQUAL_VALUE_AND_TYPE(NerdCore::VAR _left, NerdCore::VAR _right)
{
	if (_left.type != _right.type || (bool)(_left != _right))
	{
		return __NERD_Create_Boolean(1);
	}

	return __NERD_Create_Boolean(0);
}

NerdCore::VAR operator+ (NerdCore::VAR _left, int right)
{
	if (_left.type == NerdCore::Enum::Type::String) return (std::string)_left + __NERD_DOUBLE_TO_STRING(right);
	else return (double)_left + right;
}

NerdCore::VAR operator+ (NerdCore::VAR _left, double right)
{
	if (_left.type == NerdCore::Enum::Type::String) return (std::string)_left + __NERD_DOUBLE_TO_STRING(right);
	else return (double)_left + right;
}

NerdCore::VAR operator+ (NerdCore::VAR _left, const char* right)
{
	return (std::string)_left + std::string(right);
}

void operator+= (NerdCore::VAR& _left, std::string right)
{
	std::string _str = (std::string)_left;
	_str += right;
	_left = _str;
}

void operator+= (NerdCore::VAR& _left, const char* right)
{
	std::string _str = (std::string)_left;
	_str += right;
	_left = _str;
}

void operator+= (NerdCore::VAR& _left, int right)
{
	if(_left.type == NerdCore::Enum::Type::Number) _left.data.number += right;
	else
	{
		std::string _str = (std::string)_left;
		_str += right;
		_left = _str;
	}
}

void operator+= (NerdCore::VAR& _left, double right)
{
	if(_left.type == NerdCore::Enum::Type::Number) _left.data.number += right;
	else
	{
		std::string _str = (std::string)_left;
		_str += right;
		_left.data.ptr = new NerdCore::Class::String(_str);
		_left.type = NerdCore::Enum::Type::String;
	}
}


NerdCore::VAR operator|| (NerdCore::VAR _left, int right)
{
	if(_left.type != NerdCore::Enum::Type::Null) return _left;
	else return right;
}

NerdCore::VAR operator|| (NerdCore::VAR _left, double right)
{
	if(_left.type != NerdCore::Enum::Type::Null) return _left;
	else return right;
}

NerdCore::VAR operator|| (NerdCore::VAR _left, std::string right)
{
	if(_left.type != NerdCore::Enum::Type::Null) return _left;
	else return right;
}

NerdCore::VAR operator|| (NerdCore::VAR _left, const char* right)
{
	if(_left.type != NerdCore::Enum::Type::Null) return _left;
	else return right;
}

/*** op* ***/
NerdCore::VAR operator* (NerdCore::VAR _left, int right)
{
	return (double)_left * right;
}

NerdCore::VAR operator* (NerdCore::VAR _left, double right)
{
	return (double)_left * right;
}

NerdCore::VAR operator* (NerdCore::VAR _left, std::string right)
{
	return (double)_left * (double)(NerdCore::VAR(right));
}

NerdCore::VAR operator* (NerdCore::VAR _left, const char* right)
{
	return (double)_left * (double)(NerdCore::VAR(right));
}
/* end op* */

/*** op- ***/
NerdCore::VAR operator- (NerdCore::VAR _left, int right)
{
	return (double)_left - right;
}

NerdCore::VAR operator- (NerdCore::VAR _left, double right)
{
	return (double)_left - right;
}

NerdCore::VAR operator- (NerdCore::VAR _left, std::string right)
{
	return (double)_left - (double)(NerdCore::VAR(right));
}

NerdCore::VAR operator- (NerdCore::VAR _left, const char* right)
{
	return (double)_left - (double)(NerdCore::VAR(right));
}
/* end op- */

/*** op/ ***/
NerdCore::VAR operator/ (NerdCore::VAR _left, int right)
{
	return (double)_left / right;
}

NerdCore::VAR operator/ (NerdCore::VAR _left, double right)
{
	return (double)_left / right;
}

NerdCore::VAR operator/ (NerdCore::VAR _left, std::string right)
{
	return (double)_left / (double)(NerdCore::VAR(right));
}

NerdCore::VAR operator/ (NerdCore::VAR _left, const char* right)
{
	return (double)_left / (double)(NerdCore::VAR(right));
}
/* end op/ */

/*** op% ***/
NerdCore::VAR operator% (NerdCore::VAR _left, int right)
{
	return (int)_left % right;
}

NerdCore::VAR operator% (NerdCore::VAR _left, double right)
{
	return (int)_left % (int)right;
}

NerdCore::VAR operator% (NerdCore::VAR _left, std::string right)
{
	return (int)_left % (int)(NerdCore::VAR(right));
}

NerdCore::VAR operator% (NerdCore::VAR _left, const char* right)
{
	return (int)_left % (int)(NerdCore::VAR(right));
}
/* end op% */