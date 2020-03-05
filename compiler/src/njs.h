 #include <iostream>
 #include <functional>
 #include <string>
 #include <cstring>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <sstream>
 #include <vector>
 #include <memory>

using namespace std;
 
enum
{
	OBJECT = 1,
	NUMBER,
	BIGNUMBER,
	BOOLEAN,
	STRING,
	//NATIVE,
	FUNCTION,
	ARRAY,
	//NAN,
	UNDEFINED
};

struct var;
union val;

var __create_String(char* _value);
var __create_Array(vector<var>*  _value);
var __NJS_Log_Console(var _var);

#define __NJS_Create_Boolean(_value) var(BOOLEAN, _value)
#define __NJS_Create_Number(_value) var(NUMBER, _value)
#define __NJS_Create_Undefined() var(UNDEFINED, 0)

var __NJS_Create_String(char* _str);

class __NJS_Class_Object
{
  public:
    vector<shared_ptr<pair<char*, var>>>* __OBJECT = new vector<shared_ptr<pair<char*, var>>>();
    var Get(char* _index);
};

class __NJS_Class_String : public __NJS_Class_Object
{
  public:
    __NJS_Class_String(char* _str);
    var Get(char* _index);
    char* __NJS_VALUE;
};

class __NJS_Class_Array : public __NJS_Class_Object
{
  public:
    __NJS_Class_Array(vector<var>* _arr);
    var Get(char* _index);
    vector<var>* __NJS_VALUE;
};

inline char* __NJS_Concat_Str_To_Int(int _left, char* _right)
{
	std::stringstream output;
	output << _left << _right;
	return strdup(output.str().c_str());
}

inline char* __NJS_Concat_Int_To_Str(char* _left, int _right)
{
	std::stringstream output;
	output << _left << _right;
	return strdup(output.str().c_str());
}

inline char* __NJS_Concat_Str_To_Str(const char* _left, const char* _right)
{
	char* _result = (char*)malloc(strlen(_left) + strlen(_right) + 1);
	strcpy(_result, _left);
	strcat(_result, _right);
	strcat(_result, "\0");
	return _result;
}

union val
{
	int i;
	bool b;
	__NJS_Class_String* s;
	__NJS_Class_Array* a;
	vector<shared_ptr<pair<char*, var>>>* o;
	void* f;
};

inline var __NJS_Object_Get(char* _index, var _array);
inline var __NJS_Object_Get(int _index, var _array);
inline var __NJS_Object_Get(var _index, var _array);
inline var __NJS_Object_Set(var _index, var _value, var _object);

struct var
{   	
	unsigned int type;
	val value;

    var()
    {
      type = UNDEFINED;
      value = (val){.i = 0};
    }

	var (int _type, int _value): type(_type), value((val){.i=_value}){}
	var (int _value): type(NUMBER), value((val){.i=_value}){}
	var (char* _value): type(STRING), value((val){.s=new __NJS_Class_String(_value)}){}
	var (int _type, __NJS_Class_String* _value): type(_type), value((val){.s=_value}){}
	var (__NJS_Class_String* _value): type(STRING), value((val){.s=_value}){}

    var (int _type, vector<var>* _value): type(_type)
    {
      __NJS_Class_Array* _a = new __NJS_Class_Array(_value);
      value = (val){.a = _a };
    }
	
	var (vector<var>* _value): type(ARRAY)
    {
      __NJS_Class_Array* _a = new __NJS_Class_Array(_value);
      value = (val){.a = _a };
    }

    var (int _type, vector<shared_ptr<pair<char*, var>>>* _value): type(_type), value((val){.o=_value}){}
		var (vector<shared_ptr<pair<char*, var>>>* _value): type(OBJECT), value((val){.o=_value}){}

    var (int _type, void* _value): type(_type), value((val){.f=_value}){}


		/*** OPERATOR ***/
		var operator+(const var& _v1)
		{
			if(type == NUMBER && _v1.type == NUMBER)
			{
				return var(NUMBER, value.i + _v1.value.i);
			}
			else if(type == NUMBER && _v1.type == STRING)
			{
				return __create_String(__NJS_Concat_Str_To_Int(value.i, _v1.value.s->__NJS_VALUE));
			}
			else if(type == STRING && _v1.type == NUMBER)
			{
				return __create_String(__NJS_Concat_Int_To_Str(value.s->__NJS_VALUE, _v1.value.i));
			}
			else if(type == STRING && _v1.type == BOOLEAN)
			{
				if(_v1.value.b)
				{
				  return __create_String(__NJS_Concat_Str_To_Str(value.s->__NJS_VALUE, (char*)"true"));
				}
				return __create_String(__NJS_Concat_Str_To_Str(value.s->__NJS_VALUE, (char*)"false"));
			}
			else if(type == STRING && _v1.type == STRING)
			{
				return __create_String(__NJS_Concat_Str_To_Str(value.s->__NJS_VALUE, _v1.value.s->__NJS_VALUE));
			}
			else
			{
				return var(NUMBER,0);
			}
		}
		var operator-(const var& _v1)
		{
			return var(NUMBER, value.i - _v1.value.i );
		}
    var operator*(const var& _v1)
		{
			return var(NUMBER, value.i * _v1.value.i );
		}
    var operator/(const var& _v1)
		{
			return var(NUMBER, value.i / _v1.value.i );
		}
    var operator%(const var& _v1)
		{
			return var(NUMBER, value.i % _v1.value.i );
		}
		
    var const operator! () const
    {
      if(type == NUMBER)
      {
        return __NJS_Create_Number(!value.i);
      }
      else return(__NJS_Create_Boolean(false));
    };
	
    var operator++(const int _v1)
		{
			return var(NUMBER, value.i++ );
		}
    var operator--(const int _v1)
		{
			return var(NUMBER, value.i-- );
		}
		
    var operator==(const var& _v1)
		{
			return var(BOOLEAN, value.i == _v1.value.i);
		}
		
		var operator<(const var& _v1)
		{
			return var(BOOLEAN, value.i < _v1.value.i);
		}
		
    var operator<=(const var& _v1)
		{
			return var(BOOLEAN, value.i <= _v1.value.i);
		}

		var operator>(const var& _v1)
		{
			return var(BOOLEAN, value.i > _v1.value.i);
		}
		
    var operator>=(const var& _v1)
		{
			return var(BOOLEAN, value.i >= _v1.value.i);
		}
    var operator>>(const var& _v1)
		{
			return var(NUMBER, value.i >> _v1.value.i);
		}
    var operator<<(const var& _v1)
		{
			return var(NUMBER, value.i << _v1.value.i);
		}
    var operator[] (const int index)
    {
      if(type == ARRAY)
      {
        if(index > (*value.a->__NJS_VALUE).size() - 1)
        {
          return var(UNDEFINED, 0);
        }
        return (*value.a->__NJS_VALUE)[index];
      }
      else if(type == STRING)
      {
        return var(value.s+index);
      }
      else if(type == OBJECT)
      {
        return var(UNDEFINED, 0);
      }
      return var(UNDEFINED, 0);
    }
	explicit operator bool() const 
	{ 
		return this->value.i; 
	}
	
	var __NJS_Get(var _param)
	{
		return __NJS_Object_Get(_param, *this);
	}
	
	var __NJS_Get(char* _param)
	{
		return __NJS_Object_Get(_param, *this);
	}
	
	var __NJS_Set(char* _index, var _value)
	{
		return __NJS_Object_Set(_index, _value, *this);
	}
	
	var __NJS_Set(var _index, var _value)
	{
		return __NJS_Object_Set(_index, _value, *this);
	}
	
	var __NJS_Set(int _index, var _value)
	{
		return __NJS_Object_Set(_index, _value, *this);
	}
	
	var __NJS_Self_Call()
	{
		return (*static_cast<function<var ()>*>(this->value.f))();
	}
	
	var __NJS_Self_Call(var _a1)
	{
		return (*static_cast<function<var (var _a1)>*>(this->value.f))(_a1);
	}
	
	var __NJS_Self_Call(var _a1, var _a2)
	{
		return (*static_cast<function<var (var _a1, var _a2)>*>(this->value.f))(_a1, _a2);
	}
	
	var __NJS_Self_Call(var _a1, var _a2, var _a3)
	{
		return (*static_cast<function<var (var _a1, var _a2, var _a3)>*>(this->value.f))(_a1, _a2, _a3);
	}

	var __NJS_Call(char* _fn)
	{
		return (*static_cast<function<var ()>*>((this->__NJS_Get(_fn)).value.f))();
	}
	
	var __NJS_Call(char* _fn, var _arg)
	{
		return (*static_cast<function<var (var _arg)>*>((this->__NJS_Get(_fn)).value.f))(_arg);
	}
	
	var __NJS_Call(char* _fn, var _arg, var _arg2)
	{
		return (*static_cast<function<var (var __arg, var __arg2)>*>((this->__NJS_Get(_fn)).value.f))(_arg, _arg2);
	}
	
	var __NJS_Call(char* _fn, var _arg, var _arg2, var _arg3)
	{
		return (*static_cast<function<var (var __arg, var __arg2, var __arg3)>*>((this->__NJS_Get(_fn)).value.f))(_arg, _arg2, _arg3);
	}
	
};

inline var __create_String(char* _value)
{
  __NJS_Class_String* _s = new __NJS_Class_String(_value);
  return var(STRING, _s);
}

inline var __create_Array(vector<var>* _value)
{
  __NJS_Class_Array* _a = new __NJS_Class_Array(_value);
  return var(ARRAY, _a);
}

inline int __NJS_Get_Int(var _v)
{
  return _v.value.i;
}

inline char* __NJS_Get_String(var _v)
{
  return _v.value.s->__NJS_VALUE;
}

inline var __NJS_Typeof(var _var)
{
  char* _array[] = {(char*)"", (char*)"object", (char*)"number", (char*)"number", (char*)"boolean", (char*)"string", (char*)"function", (char*)"array", (char*)"undefined"};
  return __create_String(_array[_var.type]);
}


inline var __NJS_Object_Set(char* _index, var _value, var _array)
{
  vector<shared_ptr<pair<char*, var>>>* _obj;
  if(_array.type == OBJECT) _obj = _array.value.o;
  else if(_array.type == STRING) _obj = _array.value.s->__OBJECT;
  else return var(UNDEFINED, 0);

  int _j = (*_obj).size();

  for(int _i = 0; _i < _j; _i++)
  {
    if(strcmp(_index, (*_obj)[_i]->first) == 0)
    {
      (*_obj)[_i]->second.type = _value.type;
      (*_obj)[_i]->second.value = _value.value;
      return var(UNDEFINED, 0);
    }
  }
  (*_obj).push_back(shared_ptr<pair<char*, var>>(new pair<char*, var>( _index, _value)));
  return var(UNDEFINED, 0);
}

inline var __NJS_Object_Set(var _index, var _value, var _array)
{
  if(_array.type == ARRAY)
  {
    if(_index.type != NUMBER) return var (UNDEFINED, 0);
    vector<var>* _obj = _array.value.a->__NJS_VALUE;
    if(_obj->size() <= _index.value.i) _obj->resize(_index.value.i + 1);

    _obj->at(_index.value.i).type = _value.type;
    _obj->at(_index.value.i).value = _value.value;

    __NJS_Object_Set(__create_String((char*)"length"), __NJS_Create_Number(_obj->size()), _array.value.a->__OBJECT);
  }
  else if(_array.type == OBJECT || _array.type == STRING)
  {
    vector<shared_ptr<pair<char*, var>>>* _obj;
    if(_array.type == OBJECT) _obj = _array.value.o;
    else if(_array.type == STRING) _obj = _array.value.s->__OBJECT;
    else return var(UNDEFINED, 0);

    int _j = (*_obj).size();

    for(int _i = 0; _i < _j; _i++)
    {
      if(strcmp(_index.value.s->__NJS_VALUE, (*_obj)[_i]->first) == 0)
      {
        (*_obj)[_i]->second.type = _value.type;
        (*_obj)[_i]->second.value = _value.value;
        return var(UNDEFINED, 0);
      }
    }
    (*_obj).push_back(shared_ptr<pair<char*, var>>(new pair<char*, var>( _index.value.s->__NJS_VALUE, _value)));
  }
  return var(UNDEFINED, 0);
}

inline var __NJS_Object_Set(char* _index, var _value, vector<shared_ptr<pair<char*, var>>>* _obj)
{
  int _j = (*_obj).size();
  for(int _i = 0; _i < _j; _i++)
  {
    if(strcmp(_index, (*_obj)[_i]->first) == 0)
    {
      (*_obj)[_i]->second.type = _value.type;
      (*_obj)[_i]->second.value = _value.value;
      return var(UNDEFINED, 0);
    }
  }
  (*_obj).push_back(shared_ptr<pair<char*, var>>(new pair<char*, var>( _index, _value)));
  return var(UNDEFINED, 0);
}

inline var __NJS_Object_Set(var _index, var _value, vector<shared_ptr<pair<char*, var>>>* _obj)
{
  int _j = (*_obj).size();
  for(int _i = 0; _i < _j; _i++)
  {
    if(strcmp(_index.value.s->__NJS_VALUE, (*_obj)[_i]->first) == 0)
    {
      (*_obj)[_i]->second.type = _value.type;
      (*_obj)[_i]->second.value = _value.value;
      return var(UNDEFINED, 0);
    }
  }
  (*_obj).push_back(shared_ptr<pair<char*, var>>(new pair<char*, var>( _index.value.s->__NJS_VALUE, _value)));
  return var(UNDEFINED, 0);
}

inline var __NJS_Object_Get(var _index, var _array)
{
  if(_array.type != ARRAY && _array.type != OBJECT && _array.type != STRING) return var(UNDEFINED, 0);
  if(_array.type == ARRAY)
  {
    if(_index.type == STRING)
    {
      return _array.value.a->Get(__NJS_Get_String(_index));
    }
    else if(_index.type != NUMBER || _index.value.i > _array.value.a->__NJS_VALUE->size())
    {
      return var(UNDEFINED, 0);
    }
    return (*_array.value.a->__NJS_VALUE)[_index.value.i];
  }
  else
  {
    if(_index.type != STRING) return var(UNDEFINED, 0);
    vector<shared_ptr<pair<char*, var>>>* _obj;
    if(_array.type == OBJECT) _obj = _array.value.o;
    else if(_array.type == STRING) _obj = _array.value.s->__OBJECT;
    else return var(UNDEFINED, 0);
    int _j = (*_obj).size();
    for(int _i = 0; _i < _j; _i++)
    {
      if(strcmp(_index.value.s->__NJS_VALUE, (*_obj)[_i]->first) == 0)
      {
        return (*_obj)[_i]->second;
      }
    }
  }
  return var(UNDEFINED, 0);
}

inline var __NJS_Object_Get(int _index, var _array)
{
  if(_array.type != ARRAY && _array.type != OBJECT) return var(UNDEFINED, 0);
  if(_array.type == ARRAY)
  {
    if(_index > _array.value.a->__NJS_VALUE->size())
    {
      return var(UNDEFINED, 0);
    }
    return (*_array.value.a->__NJS_VALUE)[_index];
  }
  return var(UNDEFINED, 0);
}

inline var __NJS_Object_Get(char* _index, var _array)
{
  vector<shared_ptr<pair<char*, var>>>* _obj;
  if(_array.type == OBJECT) _obj = _array.value.o;
  else if(_array.type == STRING) _obj = _array.value.s->__OBJECT;
  else return var(UNDEFINED, 0);
  int _j = (*_obj).size();
  for(int _i = 0; _i < _j; _i++)
  {
    if(strcmp(_index, (*_obj)[_i]->first) == 0)
    {
      return (*_obj)[_i]->second;
    }
  }
  return var(UNDEFINED, 0);
}

__NJS_Class_String::__NJS_Class_String(char* _value)
{
  std::function<var ()> __OBJ_TO_STRING = [&](){ return __NJS_Create_String(this->__NJS_VALUE); };
  var toString = var(FUNCTION, &__OBJ_TO_STRING);
  __NJS_Object_Set((char*)"toString", toString, this->__OBJECT);

  __NJS_Object_Set((char*)"length", var(strlen(_value)), this->__OBJECT);

  __NJS_VALUE = _value;
}

var __NJS_Class_String::Get(char* _index)
{
  return __NJS_Object_Get(_index, this->__OBJECT);
}

__NJS_Class_Array::__NJS_Class_Array(vector<var>* _value)
{
  std::function<var ()> __OBJ_TO_STRING = [&](){ return __NJS_Create_String((char*)"Array"); };
  var toString = var(FUNCTION, &__OBJ_TO_STRING);
  __NJS_Object_Set((char*)"toString", toString, this->__OBJECT);

  __NJS_Object_Set((char*)"length", __NJS_Create_Number(_value->size()), this->__OBJECT);

  __NJS_VALUE = _value;
}

var __NJS_Class_Array::Get(char* _index)
{
  return __NJS_Object_Get(_index, this->__OBJECT);
}


inline var Array()
{
  vector<var>* _arr = new vector<var>();
  return var(ARRAY, _arr);
}

inline __NJS_Boolean_Result(var _v)
{
  if(_v.type == NUMBER) return _v.value.i;
  else if(_v.type == BOOLEAN) return _v.value.b;
  else if(_v.type == STRING)
  {
    if(strlen(_v.value.s->__NJS_VALUE) > 0) return true;
    else return false;
  }
  else if(_v.type == ARRAY) return true;
  else return false;
}

ostream& operator << (ostream& os, const var& _v)
{
  switch(_v.type)
	{
    case UNDEFINED:
      os << "undefined";
      break;
    case BOOLEAN:
      if(_v.value.b) os << (char*)"true";
      else os << (char*)"false";
      break;
		case NUMBER:
			os << _v.value.i;
			break;
		case STRING:
			os << _v.value.s->__NJS_VALUE;
			break;
		default:
			os << "undefined";
	}
	return os;
}

inline var parseInt(var _str)
{
  if(_str.type == STRING)
  {
    return __NJS_Create_Number(stoi(_str.value.s->__NJS_VALUE));
  }
  else return __NJS_Create_Undefined();
}


inline var  __NJS_Log_Console(var _var)
{
	cout << _var;
	cout << endl;
  return var(UNDEFINED, 0);
}


inline var __NJS_Create_String(char* _str)
{
  __NJS_Class_String* _s = new __NJS_Class_String(_str);
  return var(STRING, _s);
}

inline var __NJS_Create_Object()
{
  vector<shared_ptr<pair<char*, var>>>* __obj = new vector<shared_ptr<pair<char*, var>>>();
  return var(OBJECT, __obj);
}

inline var Object()
{
  vector<shared_ptr<pair<char*, var>>>* __obj = new vector<shared_ptr<pair<char*, var>>>();
  return var(OBJECT, __obj);
}

inline var __NJS_Create_Function(void* _fn)
{
  return var(FUNCTION, _fn);
}

inline var __NJS_Create_Native(void* _native)
{
  return var(UNDEFINED, _native);
}

inline void* __NJS_Get_Function(var _fn)
{
  return _fn.value.f;
}

inline void* __NJS_Get_Native(var _native)
{
  return _native.value.f;
}

#define __NJS_FUNCTION_MACRO std::function

/*** REDIFINING STD OPERATORS ***/

var operator+(char* _left, const var& _right)
{
	return var(_left) + _right;
}

var operator+(int _left, const var& _right)
{
	return var(_left) + _right;
}
