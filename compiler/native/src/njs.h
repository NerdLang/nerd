 #include <iostream>
 #include <string>
 #include <cstring>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <sstream>
 #include <memory>
 #include <vector>

#ifdef __NJS_ARDUINO
 #include <util/delay.h>
 #include <string.h>
 #include <WString.h>
 #include <new.h>
 #include <time.h>
 #include <nonstd-function.h>
	using namespace nonstd;
#else
	 #include <functional>
#endif
 
 using namespace std;

enum __NJS_TYPE
{
	__NJS_UNDEFINED = 1,
	__NJS_NUMBER,
	__NJS_OBJECT,
	__NJS_BIGNUMBER,
	__NJS_BOOLEAN,
	__NJS_STRING,
	//__NJS_NATIVE,
	__NJS_FUNCTION,
	__NJS_ARRAY,
	//__NJS_NAN,
	
};

/*** HELPERS ***/
#ifdef __NJS_ARDUINO
	#define __NJS_FFI_FUNCTION(_name, ...) function<var (__VA_ARGS__)>  _name   = [&](__VA_ARGS__) -> var
#else 
	#define __NJS_FFI_FUNCTION(_name, ...) function<var (__VA_ARGS__)> _name   = [&](__VA_ARGS__) -> var
#endif
#define __NJS_GET_STRING(_var) _var.get().s->__NJS_VALUE.c_str()
#define let var
#define __NJS_VAR var
#define __NJS_Create_Boolean(_value) var(__NJS_BOOLEAN, _value)
#define __NJS_Create_Number(_value) var( _value)
#define true __NJS_Create_Boolean(true)
#define false __NJS_Create_Boolean(false)
#define __NJS_Create_Undefined() var()
#define __NJS_VAR var
#define __NJS_DECL_FUNCTION function

struct var;

class __NJS_Class_Object
{
  public:
	int cnt = 0;
	__NJS_Class_Object();
    vector<pair<char*, var>> __OBJECT;
    var Get(char* _index);
	void Delete();
};

class __NJS_Class_String : public __NJS_Class_Object
{
  public:
    __NJS_Class_String(char* _str);
    var Get(char* _index);
    string __NJS_VALUE;
};


class __NJS_Class_Array : public __NJS_Class_Object
{
  public:
    __NJS_Class_Array();
    var Get(char* _index);
    vector<var> __NJS_VALUE;
};

class __NJS_Class_Function : public __NJS_Class_Object
{
  public:
  __NJS_Class_Function(void* _f);
    var Get(char* _index);
    void* __NJS_VALUE;
	//void Delete();
};

union val
{
	int i;
	bool b;
	__NJS_Class_String* s;
	__NJS_Class_Array* a;
	__NJS_Class_Object* o;
	__NJS_Class_Function* f;
};

/*** REGISTER ***/

int FREE_PTR = -1;
int REGISTER_PTR = 0;
val REGISTER[{{REGISTER}}]{(val){.i=0}};
int FREE[{{REGISTER}}] = {0};


/*** END REGISTER ***/

var __create_Array(vector<var>  _value);
var __NJS_Log_Console(var _var);
var __NJS_Create_String(char* _value);
inline var __NJS_Object_Get(char* _index, var _array);
inline var __NJS_Object_Get(int _index, var _array);
inline var __NJS_Object_Get(var _index, var _array);
inline var __NJS_Object_Set(var _index, var _value, var _object);


/*** STRDUP ***/
char* strdup (const char* s)
{
  size_t slen = strlen(s);
  char* result = (char*)malloc(slen + 1);
  if(result == NULL)
  {
    return NULL;
  }

  memcpy(result, s, slen+1);
  return result;
}

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



struct var
{   	
	private:
	
		void setPtr()
		{
			if(_ptr > -1) return;
			if(FREE_PTR > -1)
			{
				_ptr = FREE[FREE_PTR--];
			}
			else 
			{
				_ptr = REGISTER_PTR++;
			}
			
		}

	public:
		__NJS_TYPE type;
		int _ptr = -1;
	
		inline val get() const
		{
			return REGISTER[_ptr];
		}
	
		inline var()
		{
		  setPtr();
		  type = __NJS_UNDEFINED;
		  REGISTER[_ptr].i = 0;
		}
		
		~var()
		{	
			if(type ==  __NJS_OBJECT)
			{
				REGISTER[_ptr].o->Delete();
			}
			FREE[++FREE_PTR] = _ptr;
		}
		
		/**/
		var(var const& _v) 
		{ 
			setPtr();
			type = _v.type;
			REGISTER[_ptr] = REGISTER[_v._ptr];
			if(_v.type == __NJS_OBJECT)
			{
				REGISTER[_ptr].o->cnt++;
			}
			return;
		}
		/**/
		
		/*** CONSTRUCTOR ***/
		
		inline var (__NJS_TYPE _type, int _value)
		{
			setPtr();
			this->type = _type;
			REGISTER[_ptr].i = _value;
		}
		
		inline var (int _value)
		{
			setPtr();
			this->type = __NJS_NUMBER;
			REGISTER[_ptr].i = _value;
		}

		var (char* _value)
		{
			setPtr();
			type = __NJS_STRING;
			REGISTER[_ptr].s = new __NJS_Class_String(_value);
		}
		
		var (const char* _value)
		{
			setPtr();
			type = __NJS_STRING;
			REGISTER[_ptr].s = new __NJS_Class_String((char*)_value);
		}
		
		var (__NJS_Class_String* _value)
		{
			setPtr();
			type = __NJS_STRING;
			REGISTER[_ptr].s = _value;
		}
		var (__NJS_Class_Array* _value)
		{
			setPtr();
			type = __NJS_ARRAY;
			REGISTER[_ptr].a = _value;
		}
		var (__NJS_Class_Object* _value)
		{
			setPtr();
			type = __NJS_OBJECT;
			REGISTER[_ptr].o = _value;
		}
		var (__NJS_TYPE _type, void* _value)
		{
			setPtr();
			type = _type;
			REGISTER[_ptr].f = new __NJS_Class_Function(_value);
		}

		/*** VARIADIC LAMBDAS ***/
		template<class... Args>
		var::var (function<var (Args...)>& _value)
		{
			setPtr();
			type = __NJS_FUNCTION;
			REGISTER[_ptr].f = new __NJS_Class_Function(&_value);
		}
		/*** END VARIADIC LAMBDAS ***/
		

		/*** END CONSTRUCTOR ***/

		/*** OPERATOR ***/

		/*** EQUAL ***/
		var& operator=(const var& _v)
		{
			if(type == __NJS_OBJECT) REGISTER[_ptr].o->Delete();
			type = _v.type;;
			REGISTER[_ptr] = REGISTER[_v._ptr];
			if(_v.type == __NJS_OBJECT)
			{
				REGISTER[_ptr].o->cnt++;
			}
			return;
		}
		/*** END EQUAL ***/
		
		inline var operator+(const var& _v1)
		{
			if(type == __NJS_NUMBER && _v1.type == __NJS_NUMBER)
			{
				return REGISTER[_ptr].i + REGISTER[_v1._ptr].i;
			}
			else if(type == __NJS_NUMBER && _v1.type == __NJS_STRING)
			{
				return __NJS_Create_String(__NJS_Concat_Str_To_Int(get().i, _v1.get().s->__NJS_VALUE.c_str()));
			}
			else if(type == __NJS_STRING && _v1.type == __NJS_NUMBER)
			{
				return __NJS_Create_String(__NJS_Concat_Int_To_Str(get().s->__NJS_VALUE.c_str(), _v1.get().i));
			}
			else if(type == __NJS_STRING && _v1.type == __NJS_BOOLEAN)
			{
				if(_v1.get().b)
				{
				  return __NJS_Create_String(__NJS_Concat_Str_To_Str(get().s->__NJS_VALUE.c_str(), (char*)"true"));
				}
				return __NJS_Create_String(__NJS_Concat_Str_To_Str(get().s->__NJS_VALUE.c_str(), (char*)"false"));
			}
			else if(type == __NJS_STRING && _v1.type == __NJS_STRING)
			{
				return __NJS_Create_String(__NJS_Concat_Str_To_Str(get().s->__NJS_VALUE.c_str(), _v1.get().s->__NJS_VALUE.c_str()));
			}
			else
			{
				return var(0);
			}
		}
		inline var operator-(const var& _v1)
		{
			return REGISTER[_ptr].i - REGISTER[_v1._ptr].i;
		}
    	var operator*(const var& _v1)
		{
			return var( get().i * _v1.get().i );
		}
		var operator*= (const var& _v1)
		{
			REGISTER[_ptr].i *= _v1.get().i;
			return var();
		}
		var operator/= (const var& _v1)
		{
			REGISTER[_ptr].i /= _v1.get().i;
			return var();
		}
    var operator/(const var& _v1)
		{
			return var( get().i / _v1.get().i );
		}
    var operator%(const var& _v1)
		{
			return var( get().i % _v1.get().i );
		}
		
    var const operator! () const
    {
      if(type == __NJS_NUMBER)
      {
        return __NJS_Create_Number(!get().i);
      }
      else return(false);
    };
	
	var operator+=(const var _v1)
		{
			REGISTER[_ptr].i += _v1.get().i;
			return var();
		}
	
    var operator++(const int _v1)
		{
			REGISTER[_ptr].i++;
			return *this;
		}
    var operator--(const int _v1)
		{
			REGISTER[_ptr].i--;
			return *this;
		}
		
    var operator==(const var& _v1)
		{
			return var(__NJS_BOOLEAN, get().i == _v1.get().i);
		}
		
		var operator<(const var& _v1)
		{
			return var(__NJS_BOOLEAN, get().i < _v1.get().i);
		}
		
    var operator<=(const var& _v1)
		{
			return var(__NJS_BOOLEAN, get().i <= _v1.get().i);
		}

		var operator>(const var& _v1)
		{
			return var(__NJS_BOOLEAN, get().i > _v1.get().i);
		}
		
    var operator>=(const var& _v1)
		{
			return var(__NJS_BOOLEAN, get().i >= _v1.get().i);
		}
    var operator>>(const var& _v1)
		{
			return var( get().i >> _v1.get().i);
		}
    var operator<<(const var& _v1)
		{
			return var( get().i << _v1.get().i);
		}
	

	explicit operator bool() const 
	{ 
		return this->get().i; 
	}
};

/*** VARIADIC CALLS ***/
template<class... Args>
inline var __NJS_Back_Var_Call_Function(var _obj, Args... args)
{
	return (*static_cast<function<var ( Args... )>*>(_obj.get().f->__NJS_VALUE))( args... );
}

template<class... Args>
inline var __NJS_Call_Function(var _obj, Args... args)
{
	return __NJS_Back_Var_Call_Function(_obj, (var)(args)...);
}
/*** END VARIADIC CALLS ***/


inline var __create_Array()
{
  __NJS_Class_Array* _a = new __NJS_Class_Array();
  return var(__NJS_ARRAY, _a);
}

inline var __NJS_Create_Array()
{
  __NJS_Class_Array* _a = new __NJS_Class_Array();
  return var(_a);
}

inline int __NJS_Get_Int(var _v)
{
  return _v.get().i;
}

inline char* __NJS_Get_String(var _v)
{
  return _v.get().s->__NJS_VALUE.c_str();
}

inline var __NJS_Typeof(var _var)
{
  char* _array[] = {(char*)"", (char*)"undefined", (char*)"number", (char*)"object", (char*)"number", (char*)"boolean", (char*)"string", (char*)"function", (char*)"array"};
  return __NJS_Create_String(_array[_var.type]);
}

/*** ***/
inline var __NJS_Object_Set(char* _index, var _value, vector<pair<char*, var>>* _obj)
{
  int _j = (*_obj).size();
  for(int _i = 0; _i < _j; _i++)
  {
    if(strcmp(_index, (*_obj)[_i].first) == 0)
    {
      (*_obj)[_i].second.type = _value.type;
	  
      REGISTER[(*_obj)[_i].second._ptr] = REGISTER[_value._ptr];
      
	  return var();
    }
  }
  (*_obj).push_back(pair<char*, var>( _index, _value));
  return var();
}

inline var __NJS_Object_Set(var _index, var _value, vector<pair<char*, var>>* _obj)
{
  int _j = (*_obj).size();
  for(int _i = 0; _i < _j; _i++)
  {
    if(strcmp(_index.get().s->__NJS_VALUE.c_str(), (*_obj)[_i].first) == 0)
    {
      (*_obj)[_i].second.type = _value.type;
      
	  REGISTER[(*_obj)[_i].second._ptr] = REGISTER[_value._ptr];
      
	  return var();
    }
  }
  (*_obj).push_back(pair<char*, var>( (char*)_index.get().s->__NJS_VALUE.c_str(), _value));
  return var();
}

inline var __NJS_Object_Set(char* _index, var _value, var _array)
{

  vector<pair<char*, var>>* _obj;
  if(_array.type == __NJS_OBJECT) _obj = &_array.get().o->__OBJECT;
  else if(_array.type == __NJS_STRING) _obj = &_array.get().s->__OBJECT;
  else if(_array.type == __NJS_FUNCTION) _obj = &_array.get().f->__OBJECT;
  else return var();

  int _j = (*_obj).size();

  for(int _i = 0; _i < _j; _i++)
  {
    if(strcmp(_index, (*_obj)[_i].first) == 0)
    {
      (*_obj)[_i].second.type = _value.type;
	  
	  REGISTER[(*_obj)[_i].second._ptr] = REGISTER[_value._ptr];
	  
      return var();
    }
  }
  (*_obj).push_back(pair<char*, var>( _index, _value));
  return var();
}

inline var __NJS_Object_Set(var _index, var _value, var _array)
{

  if(_array.type == __NJS_ARRAY)
  {
    if(_index.type != __NJS_NUMBER) return var (__NJS_UNDEFINED, 0);

    if(_array.get().a->__NJS_VALUE.size() <= _index.get().i) _array.get().a->__NJS_VALUE.resize(_index.get().i + 1);

    _array.get().a->__NJS_VALUE[_index.get().i].type = _value.type;
    
	REGISTER[_array.get().a->__NJS_VALUE[_index.get().i]._ptr] = REGISTER[_value._ptr];

    __NJS_Object_Set(__NJS_Create_String((char*)"length"), __NJS_Create_Number(_array.get().a->__NJS_VALUE.size()), &_array.get().a->__OBJECT);
  }
  else if(_array.type == __NJS_OBJECT || _array.type == __NJS_STRING || _array.type == __NJS_FUNCTION)
  {
    vector<pair<char*, var>>* _obj;
    if(_array.type == __NJS_OBJECT) _obj = &_array.get().o->__OBJECT;
    else if(_array.type == __NJS_STRING) _obj = &_array.get().s->__OBJECT;
	else if(_array.type == __NJS_FUNCTION) _obj = &_array.get().f->__OBJECT;
    else return var();

    int _j = (*_obj).size();

    for(int _i = 0; _i < _j; _i++)
    {
      if(strcmp(_index.get().s->__NJS_VALUE.c_str(), (*_obj)[_i].first) == 0)
      {
        (*_obj)[_i].second.type = _value.type;
		
        REGISTER[(*_obj)[_i].second._ptr] = REGISTER[_value._ptr];
		
        return var();
      }
    }
    (*_obj).push_back(pair<char*, var>( (char*)_index.get().s->__NJS_VALUE.c_str(), _value));
  }
  return var();
}

inline var __NJS_Object_Set(int _index, var _value, var _array)
{

  if(_array.type == __NJS_ARRAY)
  {
    if(_array.get().a->__NJS_VALUE.size() <= _index) _array.get().a->__NJS_VALUE.resize(_index + 1);
    _array.get().a->__NJS_VALUE[_index].type = _value.type;
	REGISTER[_array.get().a->__NJS_VALUE[_index]._ptr] = REGISTER[_value._ptr];
	__NJS_Object_Set(__NJS_Create_String((char*)"length"), __NJS_Create_Number(_array.get().a->__NJS_VALUE.size()), &_array.get().a->__OBJECT);
  }
  return var();
}


inline var __NJS_Object_Get(int _index, var _array)
{
  if(_array.type != __NJS_ARRAY && _array.type != __NJS_OBJECT && _array.type != __NJS_FUNCTION) return var();
  if(_array.type == __NJS_ARRAY)
  {
    if(_index > _array.get().a->__NJS_VALUE.size())
    {
      return var();
    }
	 
    return _array.get().a->__NJS_VALUE[_index];
  }
  return var();
}


inline var __NJS_Object_Get(char* _index, var _array)
{
	return __NJS_Object_Get(var(_index), _array);
}

inline var __NJS_Object_Get(var _index, var _array)
{
  if(_array.type != __NJS_ARRAY && _array.type != __NJS_OBJECT && _array.type != __NJS_STRING && _array.type != __NJS_FUNCTION) return var();
  if(_array.type == __NJS_ARRAY)
  {
    if(_index.type == __NJS_STRING)
    {
      return _array.get().a->Get(__NJS_Get_String(_index));
    }
    else if(_index.type != __NJS_NUMBER || _index.get().i > _array.get().a->__NJS_VALUE.size())
    {
      return var();
    }
    return _array.get().a->__NJS_VALUE[_index.get().i];
  }
  else
  {
    if(_index.type != __NJS_STRING) return var();
    vector<pair<char*, var>>* _obj;
    if(_array.type == __NJS_OBJECT) _obj = &_array.get().o->__OBJECT;
    else if(_array.type == __NJS_STRING) _obj = &_array.get().s->__OBJECT;
	else if(_array.type == __NJS_FUNCTION) _obj = &_array.get().f->__OBJECT;
    else return var();
    int _j = (*_obj).size();
    for(int _i = 0; _i < _j; _i++)
    {
      if(strcmp(_index.get().s->__NJS_VALUE.c_str(), (*_obj)[_i].first) == 0)
      {
        return (*_obj)[_i].second;
      }
    }
  }
  return var();
}


__NJS_Class_String::__NJS_Class_String(char* _value)
{
	/*** toString ***/
  function<var ()>* __OBJ_TO___NJS_STRING = new function<var ()>([&](){ return __NJS_Create_String(this->__NJS_VALUE.c_str()); });
  var toString = var(__NJS_FUNCTION, __OBJ_TO___NJS_STRING);
  __NJS_Object_Set((char*)"toString", toString, &this->__OBJECT);
	/*** end to string ***/
	
	/*** length ***/
  __NJS_Object_Set((char*)"length", var(strlen(_value)), &this->__OBJECT);
	/*** end length ***/
	
  /*** split ***/
  function<var (var)>* __OBJ_TO___NJS_SPLIT = new function<var (var)>([&](var _needle)
  { 
	var _arr = __NJS_Create_Array();
    char* _v = (char*)malloc(strlen(this->__NJS_VALUE.c_str()) + 1);
	strcpy(_v, this->__NJS_VALUE.c_str());	
	char* delim = (char*)malloc(strlen(_needle.get().s->__NJS_VALUE.c_str()) + 1);
	strcpy(delim, _needle.get().s->__NJS_VALUE.c_str());

	char *ptr = strtok(_v, delim);
	int i = 0;
	char* _new;
	while (ptr != NULL)
	{
		char* _new = (char*)malloc(strlen(ptr));
		strcpy(_new, ptr);
		__NJS_Object_Set(i, _new, _arr);
		
		ptr = strtok(NULL, delim);
		i++;
	}
	
	return _arr; 
  });
  
  var __split = var(__NJS_FUNCTION, __OBJ_TO___NJS_SPLIT);
  __NJS_Object_Set((char*)"split", __split, &this->__OBJECT);
	/*** end split ***/


  __NJS_VALUE = _value;
}

inline var __NJS_Class_String::Get(char* _index)
{
  return __NJS_Object_Get(_index, this);
}

__NJS_Class_Array::__NJS_Class_Array()
{

  function<var ()>* __OBJ_TO___NJS_STRING = new function<var ()>([&](){ return __NJS_Create_String((char*)"Array"); });
  var toString = var(__NJS_FUNCTION, __OBJ_TO___NJS_STRING);
  __NJS_Object_Set((char*)"toString", toString, &this->__OBJECT);

  __NJS_Object_Set((char*)"length", var(0), this);

}

__NJS_Class_Object::__NJS_Class_Object()
{
  cnt++;
}


__NJS_Class_Function::__NJS_Class_Function(void* _f)
{
  cnt = 1;
  __NJS_VALUE = _f;

}

void __NJS_Class_Object::Delete()
{
	this->cnt --;
	if(this->cnt < 1)
	{
		#ifdef __NJS_ARDUINO
			// quick fix to change
		#else
			delete this;
		#endif
	}	
}

inline var __NJS_Class_Array::Get(char* _index)
{
  return __NJS_Object_Get(_index, this);
}


inline var Array()
{
  vector<var>* _arr = new vector<var>();
  return var(__NJS_ARRAY, _arr);
}

inline var __NJS_Boolean_Result(var _v)
{
  if(_v.type == __NJS_NUMBER) return _v.get().i;
  else if(_v.type == __NJS_BOOLEAN) return _v.get().b;
  else if(_v.type == __NJS_STRING)
  {
    if(strlen(_v.get().s->__NJS_VALUE.c_str()) > 0) return true;
    else return false;
  }
  else if(_v.type == __NJS_ARRAY) return true;
  else return false;
}

ostream& operator << (ostream& os, const var& _v)
{
  switch(_v.type)
	{
    case __NJS_UNDEFINED:
      os << "undefined";
      break;
    case __NJS_BOOLEAN:
      if(_v.get().b) os << (char*)"true";
      else os << (char*)"false";
      break;
		case __NJS_NUMBER:
			os << _v.get().i;
			break;
		case __NJS_STRING:
			os << _v.get().s->__NJS_VALUE;
			break;
		default:
			os << "undefined";
	}
	return os;
}

inline var parseInt(var _str)
{
  if(_str.type == __NJS_STRING)
  {
	#ifdef __NJS_ARDUINO
		return var();
	#else
		return __NJS_Create_Number(stoi(_str.get().s->__NJS_VALUE));
	#endif
  }
  else return __NJS_Create_Undefined();
}


inline var  __NJS_Log_Console(var _var)
{
	#ifdef __NJS_ARDUINO
	
	#else
		cout << _var;
		cout << endl;
	#endif
	
  return var();
}


inline var __NJS_Create_String(char* _value)
{
  __NJS_Class_String* _s = new __NJS_Class_String(_value);
  return var(_s);
}

inline var __NJS_Create_Object()
{
  __NJS_Class_Object* _obj = new __NJS_Class_Object();
  return var(_obj);
}


inline var Object()
{
  return __NJS_Create_Object();
}

inline var __NJS_CREATE_FUNCTION(void* _fn)
{
  return var(__NJS_FUNCTION, _fn);
}

inline var __NJS_Create_Native(void* _native)
{
  return var(__NJS_UNDEFINED, _native);
}

inline void* __NJS_Get_Function(var _fn)
{
  return _fn.get().f;
}

inline void* __NJS_Get_Native(var _native)
{
  return _native.get().f;
}

/*** REDIFINING STD OPERATORS ***/

inline var operator+(char* _left, const var& _right)
{
	return var(_left) + _right;
}

inline var operator+(int _left, const var& _right)
{
	return var(_left) + _right;
}
/*** END REDIFINING STD OPERATORS ***/