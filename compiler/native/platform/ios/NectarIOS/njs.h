#ifdef __cplusplus

 #include <iostream>
 #include <string>
 #include <cstring>
 #include <stdio.h>
 #include <stdlib.h>
 #include <sstream>
 #include <memory>
 #include <vector>
 #include<stdarg.h>
 #include <functional>


#ifdef __NJS_ARDUINO
 #include <util/delay.h>
 #include <string.h>
 #include <WString.h>
 #include <new.h>
 #include <time.h>
 #include <nonstd-function.h>
 using namespace nonstd;
#endif
 
 using namespace std;

enum NJS::Enum::Type
{
	NJS::Enum::Type::UNDEFINED = 1,
	NJS::Enum::Type::NUMBER,
	NJS::Enum::Type::DOUBLE,
	NJS::Enum::Type::OBJECT,
	NJS::Enum::Type::BIGNUMBER,
	NJS::Enum::Type::BOOLEAN,
	NJS::Enum::Type::STRING,
	NJS::Enum::Type::NATIVE,
	NJS::Enum::Type::FUNCTION,
	NJS::Enum::Type::ARRAY,
	NJS::Enum::Type::ISNAN,
	NJS::Enum::Type::ISINFINITY,
	NJS::Enum::Type::ISNULL
	
};

/*** HELPERS ***/
#define __NJS_GET_STRING(_var) _var.get().s->__NJS_VALUE.c_str()
#define var NJS::VAR
#define let NJS::VAR
#define __NJS_Create_Boolean(_value) NJS::VAR(NJS::Enum::Type::BOOLEAN, _value)
#define __NJS_Create_Number(_value) NJS::VAR( _value)
#define __NJS_Create_Function(_value) NJS::VAR(NJS::Enum::Type::FUNCTION, _value)
#define __NJS_Create_Undefined() NJS::VAR()
#define __NJS_DECL_FUNCTION function
#define __NJS_RETURN_UNDEFINED var __undef = NJS::VAR(); return __undef;
#define __NJS_Create_String(_value) NJS::VAR(_value)
#define __NJS_Create_Infinity() NJS::VAR(NJS::Enum::Type::ISINFINITY, 0)
#define Infinity __NJS_Create_Infinity()
#define __NJS_Create_Null() NJS::VAR(NJS::Enum::Type::ISNULL, 0)
//#define __NJS_Init_Null NJS::VAR(NJS::Enum::Type::ISNULL, 0)
//#define null __NJS_Create_Null()
#define __NJS_Create_Lambda(name) function<NJS::VAR (vector<var>)>* name = new function<NJS::VAR (vector<var>)>([](vector<var> NJS::VARARGS)
/*** END HELPERS ***/



struct NJS::VAR;

class __NJS_Class_Object
{
  public:
  int cnt = 0;
  void Delete();
	__NJS_Class_Object();
	vector<pair<char*, NJS::VAR>> __OBJECT;

};

class __NJS_Class_String
{
  public:
	int cnt = 0;
	void Delete();
    __NJS_Class_String(char* _str);
    string __NJS_VALUE;
	vector<pair<char*, NJS::VAR>> __OBJECT;
};


class __NJS_Class_Array
{
  public:
	int cnt = 0;
	void Delete();
    __NJS_Class_Array();
    vector<NJS::VAR> __NJS_VALUE = vector<NJS::VAR>();
	vector<pair<char*, NJS::VAR>> __OBJECT;
};

class __NJS_Class_Function
{
  public:
	int cnt = 0;
	void Delete();
  	__NJS_Class_Function(void* _f);
	void* __NJS_VALUE;
	vector<pair<char*, NJS::VAR>> __OBJECT;
};

class __NJS_Class_Native
{
  public:
	int cnt = 0;
	void Delete();
  	__NJS_Class_Native(void* _n);
	void* __NJS_VALUE;
	vector<pair<char*, NJS::VAR>> __OBJECT;
};

union NJS::VAL
{
	int i;
	double d;
	bool b;
	__NJS_Class_String* s;
	__NJS_Class_Array* a;
	__NJS_Class_Object* o;
	__NJS_Class_Function* f;
	__NJS_Class_Native* n;
};

/*** REGISTER ***/

int FREE_PTR = -1;
int REGISTER_PTR = 0;
#ifdef CL_WINDOWS
	NJS::VAL REGISTER[1000000];
#else
	NJS::VAL REGISTER[1000000]{(NJS::VAL){.i=0}};
#endif
int FREE[1000000] = {0};


/*** END REGISTER ***/

NJS::VAR __NJS_Log_Console(NJS::VAR _var);
NJS::VAR __NJS_Object_Keys(NJS::VAR _var);
NJS::VAR __NJS_Object_Stringify(NJS::VAR _var);

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

char* __NJS_Concat_Str_To_Int(int _left, char* _right)
{
	std::stringstream output;
	output << _left << _right;
	return strdup(output.str().c_str());
}

char* __NJS_Concat_Str_To_Int(double _left, char* _right)
{
	std::stringstream output;
	output << _left << _right;
	return strdup(output.str().c_str());
}

char* __NJS_Concat_Int_To_Str(char* _left, int _right)
{
	std::stringstream output;
	output << _left << _right;
	return strdup(output.str().c_str());
}

char* __NJS_Concat_Int_To_Str(char* _left, double _right)
{
	std::stringstream output;
	output << _left << _right;
	return strdup(output.str().c_str());
}

char* __NJS_Concat_Str_To_Str(const char* _left, const char* _right)
{
	char* _result = (char*)malloc(strlen(_left) + strlen(_right) + 1);
	strcpy(_result, _left);
	strcat(_result, _right);
	strcat(_result, "\0");
	return _result;
}

struct NJS::VAR
{   	
	private:
	
		void setPtr()
		{
			if(_ptr > -1) 
			{
				return;
			}
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
		NJS::Enum::Type type;
		int _ptr = -1;
		
		inline NJS::VAL get() const
		{
			return REGISTER[_ptr];
		}
	
		NJS::VAR()
		{
		  setPtr();
		  type = NJS::Enum::Type::UNDEFINED;
		  REGISTER[_ptr].i = 0;
		}
		
		~NJS::VAR()
		{	
			if(type ==  NJS::Enum::Type::OBJECT)
			{
				REGISTER[_ptr].o->Delete();
			}
			else if(type ==  NJS::Enum::Type::STRING)
			{
				REGISTER[_ptr].s->Delete();
			}
			else if(type ==  NJS::Enum::Type::FUNCTION)
			{
				REGISTER[_ptr].f->Delete();
			}
			else if(type ==  NJS::Enum::Type::ARRAY)
			{
				REGISTER[_ptr].a->Delete();
			}
			else if(type ==  NJS::Enum::Type::NATIVE)
			{
				REGISTER[_ptr].a->Delete();
			}
			FREE[++FREE_PTR] = _ptr;
		}
		
		/**/
		NJS::VAR(NJS::VAR const& _v) 
		{ 
			setPtr();
			type = _v.type;
			
			if(_v.type == NJS::Enum::Type::OBJECT)
			{
				REGISTER[_ptr] = REGISTER[_v._ptr];
				REGISTER[_ptr].o->cnt++;
			}
			else if(_v.type == NJS::Enum::Type::STRING)
			{
				
				REGISTER[_ptr].s = new __NJS_Class_String(strdup(REGISTER[_v._ptr].s->__NJS_VALUE.c_str()));

			}
			else if(_v.type == NJS::Enum::Type::FUNCTION)
			{
				REGISTER[_ptr] = REGISTER[_v._ptr];
				REGISTER[_ptr].f->cnt++;
			}
			else if(_v.type == NJS::Enum::Type::ARRAY)
			{
				REGISTER[_ptr] = REGISTER[_v._ptr];
				REGISTER[_ptr].a->cnt++;
			}
			else if(_v.type == NJS::Enum::Type::NATIVE)
			{
				REGISTER[_ptr] = REGISTER[_v._ptr];
				REGISTER[_ptr].n->cnt++;
			}
			else
			{
				REGISTER[_ptr] = REGISTER[_v._ptr];
			}

		}
		/**/
		
		/*** CONSTRUCTOR ***/
		
		NJS::VAR (NJS::Enum::Type _type, int _value)
		{
			setPtr();
			this->type = _type;
			REGISTER[_ptr].i = _value;
		}
		
		NJS::VAR (int _value)
		{
			setPtr();
			this->type = NJS::Enum::Type::NUMBER;
			REGISTER[_ptr].i = _value;
		}

		NJS::VAR (double _value)
		{
			setPtr();
			this->type = NJS::Enum::Type::DOUBLE;
			REGISTER[_ptr].d = _value;
		}

		NJS::VAR (char* _value)
		{
			setPtr();
			type = NJS::Enum::Type::STRING;
			REGISTER[_ptr].s = new __NJS_Class_String(_value);
		}
		
		NJS::VAR (string _value)
		{
			setPtr();
			type = NJS::Enum::Type::STRING;
			REGISTER[_ptr].s = new __NJS_Class_String((char*)_value.c_str());
		}
		
		NJS::VAR (const char* _value)
		{
			setPtr();
			type = NJS::Enum::Type::STRING;
			REGISTER[_ptr].s = new __NJS_Class_String((char*)_value);
		}
		
		NJS::VAR (__NJS_Class_Array* _value)
		{
			setPtr();
			type = NJS::Enum::Type::ARRAY;
			REGISTER[_ptr].a = _value;
		}
		NJS::VAR (__NJS_Class_Object* _value)
		{
			setPtr();
			type = NJS::Enum::Type::OBJECT;
			REGISTER[_ptr].o = _value;
		}
		NJS::VAR (__NJS_Class_Native* _value)
		{
			setPtr();
			type = NJS::Enum::Type::NATIVE;
			REGISTER[_ptr].n = _value;
		}
		NJS::VAR (NJS::Enum::Type _type, void* _value)
		{
			setPtr();
			type = _type;
			REGISTER[_ptr].f = new __NJS_Class_Function(_value);
		}


		NJS::VAR (function<NJS::VAR (vector<var>)>& _value)
		{
			setPtr();
			type = NJS::Enum::Type::FUNCTION;
			REGISTER[_ptr].f = new __NJS_Class_Function(&_value);
		}

		/*** VARIADIC LAMBDAS ***/
		template<class... Args>
		NJS::VAR (function<NJS::VAR (Args...)>& _value)
		{
			setPtr();
			type = NJS::Enum::Type::FUNCTION;
			REGISTER[_ptr].f = new __NJS_Class_Function(&_value);
		}
		/*** END VARIADIC LAMBDAS ***/
		

		/*** END CONSTRUCTOR ***/

		/*** OPERATOR ***/

		/*** EQUAL ***/
		NJS::VAR operator=(const NJS::VAR _v)
		{
			if(type == NJS::Enum::Type::OBJECT) REGISTER[_ptr].o->Delete();
			else if(type == NJS::Enum::Type::STRING) REGISTER[_ptr].s->Delete();
			else if(type == NJS::Enum::Type::FUNCTION) REGISTER[_ptr].f->Delete();
			else if(type == NJS::Enum::Type::ARRAY) REGISTER[_ptr].a->Delete();
			else if(type == NJS::Enum::Type::NATIVE) REGISTER[_ptr].n->Delete();

			type = _v.type;;
			if(_v.type == NJS::Enum::Type::OBJECT)
			{
				REGISTER[_ptr] = REGISTER[_v._ptr];
				REGISTER[_ptr].o->cnt++;
			}
			else if(_v.type == NJS::Enum::Type::STRING)
			{
				REGISTER[_ptr].s = new __NJS_Class_String(strdup(REGISTER[_v._ptr].s->__NJS_VALUE.c_str()));
			}
			else if(_v.type == NJS::Enum::Type::FUNCTION)
			{
				REGISTER[_ptr] = REGISTER[_v._ptr];
				REGISTER[_ptr].f->cnt++;
			}
			else if(_v.type == NJS::Enum::Type::ARRAY)
			{
				REGISTER[_ptr] = REGISTER[_v._ptr];
				REGISTER[_ptr].a->cnt++;
			}
			else if(_v.type == NJS::Enum::Type::NATIVE)
			{
				REGISTER[_ptr] = REGISTER[_v._ptr];
				REGISTER[_ptr].n->cnt++;
			}
			else REGISTER[_ptr] = REGISTER[_v._ptr];
			
			return *this;
		}
		/*** END EQUAL ***/
		
		NJS::VAR operator+(const NJS::VAR& _v1)
		{
			if(type == NJS::Enum::Type::NUMBER && _v1.type == NJS::Enum::Type::NUMBER)
			{
				return REGISTER[_ptr].i + REGISTER[_v1._ptr].i;
			}
			else if(type == NJS::Enum::Type::NUMBER && _v1.type == NJS::Enum::Type::DOUBLE)
			{
				return REGISTER[_ptr].i + REGISTER[_v1._ptr].d;
			}
			else if(type == NJS::Enum::Type::DOUBLE && _v1.type == NJS::Enum::Type::DOUBLE)
			{
				return REGISTER[_ptr].d + REGISTER[_v1._ptr].d;
			}
			else if(type == NJS::Enum::Type::DOUBLE && _v1.type == NJS::Enum::Type::NUMBER)
			{
				return REGISTER[_ptr].d + REGISTER[_v1._ptr].i;
			}
			else if(type == NJS::Enum::Type::NUMBER && _v1.type == NJS::Enum::Type::STRING)
			{
				return __NJS_Create_String(__NJS_Concat_Str_To_Int(get().i, (char*)_v1.get().s->__NJS_VALUE.c_str()));
			}
			else if(type == NJS::Enum::Type::DOUBLE && _v1.type == NJS::Enum::Type::STRING)
			{
				return __NJS_Create_String(__NJS_Concat_Str_To_Int(get().d, (char*)_v1.get().s->__NJS_VALUE.c_str()));
			}
			else if(type == NJS::Enum::Type::STRING && _v1.type == NJS::Enum::Type::NUMBER)
			{
				return __NJS_Create_String(__NJS_Concat_Int_To_Str((char*)get().s->__NJS_VALUE.c_str(), _v1.get().i));
			}
			else if(type == NJS::Enum::Type::STRING && _v1.type == NJS::Enum::Type::DOUBLE)
			{
				return __NJS_Create_String(__NJS_Concat_Int_To_Str((char*)get().s->__NJS_VALUE.c_str(), _v1.get().d));
			}
			else if(type == NJS::Enum::Type::STRING && _v1.type == NJS::Enum::Type::BOOLEAN)
			{
				if(_v1.get().b)
				{
				  return __NJS_Create_String(__NJS_Concat_Str_To_Str((char*)get().s->__NJS_VALUE.c_str(), (char*)"true"));
				}
				return __NJS_Create_String(__NJS_Concat_Str_To_Str((char*)get().s->__NJS_VALUE.c_str(), (char*)"false"));
			}
			else if(type == NJS::Enum::Type::STRING && _v1.type == NJS::Enum::Type::STRING)
			{
				return __NJS_Create_String(__NJS_Concat_Str_To_Str(get().s->__NJS_VALUE.c_str(), (char*)_v1.get().s->__NJS_VALUE.c_str()));
			}
			else
			{
				return NJS::VAR(0);
			}
		}
		NJS::VAR operator-(const NJS::VAR& _v1)
		{
			if(type == NJS::Enum::Type::NUMBER && _v1.type == NJS::Enum::Type::NUMBER) return NJS::VAR( get().i - _v1.get().i );
			else if(type == NJS::Enum::Type::NUMBER && _v1.type == NJS::Enum::Type::DOUBLE) return NJS::VAR( get().i - _v1.get().d );
			else if(type == NJS::Enum::Type::DOUBLE && _v1.type == NJS::Enum::Type::NUMBER) return NJS::VAR( get().d - _v1.get().i );
			else if(type == NJS::Enum::Type::DOUBLE && _v1.type == NJS::Enum::Type::DOUBLE) return NJS::VAR( get().d - _v1.get().d );
			return NJS::VAR();
		}

		NJS::VAR operator-()
		{
			if(type == NJS::Enum::Type::NUMBER) return NJS::VAR( -get().i);
			else if(type == NJS::Enum::Type::DOUBLE) return NJS::VAR( -get().d);
			return NJS::VAR();
		}

		NJS::VAR operator+()
		{
			if(type == NJS::Enum::Type::NUMBER) return NJS::VAR( get().i);
			else if(type == NJS::Enum::Type::DOUBLE) return NJS::VAR( get().d);
			return NJS::VAR();
		}


		NJS::VAR operator+=(const NJS::VAR _v1)
		{
			if(type == NJS::Enum::Type::NUMBER && _v1.type == NJS::Enum::Type::NUMBER) REGISTER[_ptr].i += _v1.get().i;
			else if(type == NJS::Enum::Type::NUMBER && _v1.type == NJS::Enum::Type::DOUBLE) REGISTER[_ptr].i += _v1.get().d;
			else if(type == NJS::Enum::Type::DOUBLE && _v1.type == NJS::Enum::Type::NUMBER) REGISTER[_ptr].d += _v1.get().i;
			else if(type == NJS::Enum::Type::DOUBLE && _v1.type == NJS::Enum::Type::DOUBLE) REGISTER[_ptr].d += _v1.get().d;
			else if(type == NJS::Enum::Type::STRING && _v1.type == NJS::Enum::Type::STRING) REGISTER[_ptr].s->__NJS_VALUE += _v1.get().s->__NJS_VALUE;
			else if(type == NJS::Enum::Type::STRING && _v1.type == NJS::Enum::Type::DOUBLE) REGISTER[_ptr].s->__NJS_VALUE += _v1.get().d;
			else if(type == NJS::Enum::Type::STRING && _v1.type == NJS::Enum::Type::NUMBER) REGISTER[_ptr].s->__NJS_VALUE += _v1.get().i;
			return NJS::VAR();
		}
	
   	 NJS::VAR operator++(const int _v1)
		{
			if(type == NJS::Enum::Type::NUMBER) REGISTER[_ptr].i++;
			else if(type == NJS::Enum::Type::DOUBLE) REGISTER[_ptr].d++;
			return *this;
		}
    	NJS::VAR operator--(const int _v1)
		{
			if(type == NJS::Enum::Type::NUMBER) REGISTER[_ptr].i--;
			else if(type == NJS::Enum::Type::DOUBLE) REGISTER[_ptr].d--;
			return *this;
		}

    	NJS::VAR operator*(const NJS::VAR& _v1)
		{
			if(type == NJS::Enum::Type::NUMBER && _v1.type == NJS::Enum::Type::NUMBER) return NJS::VAR( get().i * _v1.get().i );
			else if(type == NJS::Enum::Type::NUMBER && _v1.type == NJS::Enum::Type::DOUBLE) return NJS::VAR( get().i * _v1.get().d );
			else if(type == NJS::Enum::Type::DOUBLE && _v1.type == NJS::Enum::Type::NUMBER) return NJS::VAR( get().d * _v1.get().i );
			else if(type == NJS::Enum::Type::DOUBLE && _v1.type == NJS::Enum::Type::DOUBLE) return NJS::VAR( get().d * _v1.get().d );
			return NJS::VAR();
		}
		NJS::VAR operator*= (const NJS::VAR& _v1)
		{
			if(type == NJS::Enum::Type::NUMBER && _v1.type == NJS::Enum::Type::NUMBER) REGISTER[_ptr].i *= _v1.get().i;
			else if(type == NJS::Enum::Type::NUMBER && _v1.type == NJS::Enum::Type::DOUBLE) REGISTER[_ptr].i *= _v1.get().d;
			else if(type == NJS::Enum::Type::DOUBLE && _v1.type == NJS::Enum::Type::NUMBER) REGISTER[_ptr].d *= _v1.get().i;
			else if(type == NJS::Enum::Type::DOUBLE && _v1.type == NJS::Enum::Type::DOUBLE) REGISTER[_ptr].d *= _v1.get().d;
			return NJS::VAR();
		}
		NJS::VAR operator/= (const NJS::VAR& _v1)
		{
			if(type == NJS::Enum::Type::NUMBER && _v1.type == NJS::Enum::Type::NUMBER) REGISTER[_ptr].i /= _v1.get().i;
			else if(type == NJS::Enum::Type::NUMBER && _v1.type == NJS::Enum::Type::DOUBLE) REGISTER[_ptr].i /= _v1.get().d;
			else if(type == NJS::Enum::Type::DOUBLE && _v1.type == NJS::Enum::Type::NUMBER) REGISTER[_ptr].d /= _v1.get().i;
			else if(type == NJS::Enum::Type::DOUBLE && _v1.type == NJS::Enum::Type::DOUBLE) REGISTER[_ptr].d /= _v1.get().d;
			return NJS::VAR();
		}
    NJS::VAR operator/(const NJS::VAR& _v1)
		{
			if(type == NJS::Enum::Type::NUMBER && _v1.type == NJS::Enum::Type::NUMBER) return NJS::VAR( get().i / _v1.get().i );
			else if(type == NJS::Enum::Type::NUMBER && _v1.type == NJS::Enum::Type::DOUBLE) return NJS::VAR( get().i / _v1.get().d );
			else if(type == NJS::Enum::Type::DOUBLE && _v1.type == NJS::Enum::Type::NUMBER) return NJS::VAR( get().d / _v1.get().i );
			else if(type == NJS::Enum::Type::DOUBLE && _v1.type == NJS::Enum::Type::DOUBLE) return NJS::VAR( get().d / _v1.get().d );
			return NJS::VAR();
		}
    NJS::VAR operator%(const NJS::VAR& _v1)
		{
			return NJS::VAR( get().i % _v1.get().i );
		}
		
    NJS::VAR const operator! () const
    {
      if(type == NJS::Enum::Type::NUMBER)
      {
        return __NJS_Create_Number(!get().i);
      }
      else if(type == NJS::Enum::Type::UNDEFINED)
      {
			return true;
	  }
      else return false;
    };
		
    NJS::VAR operator==(const NJS::VAR& _v1)
		{
			if(type == _v1.type )
			{
				if(type == NJS::Enum::Type::NUMBER) return NJS::VAR(NJS::Enum::Type::BOOLEAN, get().i == _v1.get().i);
				else if(type == NJS::Enum::Type::STRING)
				{
					if(strcmp(get().s->__NJS_VALUE.c_str(),_v1.get().s->__NJS_VALUE.c_str()) == 0) return true;
					else return false;
				}
				else if(type == NJS::Enum::Type::UNDEFINED) return true;
			}
			return false;
		}
		
		NJS::VAR operator<(const NJS::VAR& _v1)
		{
			if(type == _v1.type )
			{
				if(type == NJS::Enum::Type::NUMBER) return NJS::VAR(NJS::Enum::Type::BOOLEAN, get().i < _v1.get().i);
				else if(type == NJS::Enum::Type::STRING)
				{
					return false;
				}
			}
			return false;
			
		}
		
    NJS::VAR operator<=(const NJS::VAR& _v1)
		{
			if(type == _v1.type )
			{
				if(type == NJS::Enum::Type::NUMBER) return NJS::VAR(NJS::Enum::Type::BOOLEAN, get().i <= _v1.get().i);
				else if(type == NJS::Enum::Type::STRING)
				{
					return false;
				}
			}
			return false;
		}

		NJS::VAR operator>(const NJS::VAR& _v1)
		{
			if(type == _v1.type )
			{
				if(type == NJS::Enum::Type::NUMBER) return NJS::VAR(NJS::Enum::Type::BOOLEAN, get().i > _v1.get().i);
				else if(type == NJS::Enum::Type::STRING)
				{
					return false;
				}
			}
			return false;
		}
		
    NJS::VAR operator>=(const NJS::VAR& _v1)
		{
			if(type == _v1.type )
			{
				if(type == NJS::Enum::Type::NUMBER) return NJS::VAR(NJS::Enum::Type::BOOLEAN, get().i >= _v1.get().i);
				else if(type == NJS::Enum::Type::STRING)
				{
					return false;
				}
			}
			return false;
		}
    NJS::VAR operator>>(const NJS::VAR& _v1)
		{
			if(type == _v1.type )
			{
				if(type == NJS::Enum::Type::NUMBER) return NJS::VAR( get().i >> _v1.get().i);
			}
			return 0;
			
		}
    NJS::VAR operator<<(const NJS::VAR& _v1)
		{
			if(type == _v1.type )
			{
				if(type == NJS::Enum::Type::NUMBER) return NJS::VAR( get().i << _v1.get().i);
			}
			return 0;
		}
	

	explicit operator bool() const 
	{ 
		if(type == NJS::Enum::Type::UNDEFINED) return 0;
		else if(type == NJS::Enum::Type::NUMBER || type == NJS::Enum::Type::BOOLEAN) return this->get().i; 
		else if(type == NJS::Enum::Type::DOUBLE) return this->get().d;
		else if(type == NJS::Enum::Type::STRING) return 1;
		else if(type == NJS::Enum::Type::FUNCTION) return 1;
		else if(type == NJS::Enum::Type::OBJECT) return 1;
		else if(type == NJS::Enum::Type::ARRAY) return 1;
		else if(type == NJS::Enum::Type::NATIVE) return 1;
		else if(type == NJS::Enum::Type::ISNAN) return 0;
		return 0;
	}
};


namespace NECTAR
{
	NJS::VAR null = __NJS_Create_Null();
	NJS::VAR undefined = NJS::VAR();
}

/*** VARIADIC CALLS ***/
template<class... Args>
NJS::VAR __NJS_Back_Var_Call_Function(NJS::VAR _obj, Args... args)
{
	vector<var> _args = vector<var>{(var)args...};
	return (*static_cast<function<NJS::VAR ( vector<var> )>*>(_obj.get().f->__NJS_VALUE))( _args );
}


template<class... Args>
NJS::VAR __NJS_Call_Function(NJS::VAR _obj, Args... args)
{
	if(_obj.type != NJS::Enum::Type::FUNCTION)
	{
		#ifndef __NJS_ARDUINO
			cout << "[!] Fatal error, object is not a function" << endl;
		#endif
		exit(1);
	}
	return __NJS_Back_Var_Call_Function(_obj, (NJS::VAR)(args)...);
}
/*** END VARIADIC CALLS ***/

/*** FIXED CALLS ***/
template<class... Args>
NJS::VAR __NJS_Back_Var_Call_Fixed_Function(NJS::VAR _obj, Args... args)
{
	return (*static_cast<function<NJS::VAR ( Args... )>*>(_obj.get().f->__NJS_VALUE))( args... );
}


template<class... Args>
NJS::VAR __NJS_Call_Fixed_Function(NJS::VAR _obj, Args... args)
{
	if(_obj.type != NJS::Enum::Type::FUNCTION)
	{
		#ifndef __NJS_ARDUINO
			cout << "[!] Fatal error, object is not a function" << endl;
		#endif
		exit(1);
	}
	return __NJS_Back_Var_Call_Fixed_Function(_obj, (NJS::VAR)(args)...);
}
/*** END FIXED CALLS ***/

/*** FAST CALLS ***/
#define __NJS_Call_Fast_Function(_name, __VA_ARGS__) _name(__VA_ARGS__)
/*** END FAST CALLS ***/


NJS::VAR __create_Array()
{
  __NJS_Class_Array* _a = new __NJS_Class_Array();
  return NJS::VAR(NJS::Enum::Type::ARRAY, _a);
}

NJS::VAR __NJS_Create_Array()
{
  __NJS_Class_Array* _a = new __NJS_Class_Array();
  return NJS::VAR(_a);
}

int __NJS_Get_Int(NJS::VAR _v)
{
  return _v.get().i;
}

char* __NJS_Get_String(NJS::VAR _v)
{
  return (char*)_v.get().s->__NJS_VALUE.c_str();
}

NJS::VAR __NJS_Typeof(NJS::VAR _var)
{
  char* _array[] = {(char*)"", (char*)"undefined", (char*)"number", (char*)"number", (char*)"object", (char*)"number", (char*)"boolean", (char*)"string", (char*)"native", (char*)"function", (char*)"array", (char*) "NaN", (char*) "number", (char*) "object"};
  return __NJS_Create_String(_array[_var.type]);
}

/*** ***/
NJS::VAR __NJS_Object_Set(char* _index, NJS::VAR _value, vector<pair<char*, NJS::VAR>>* _obj)
{
  int _j = (*_obj).size();
  for(int _i = 0; _i < _j; _i++)
  {
    if(strcmp(_index, (*_obj)[_i].first) == 0)
    {

      if(_value.type == NJS::Enum::Type::STRING)
	{
		REGISTER[(*_obj)[_i].second._ptr].s = new __NJS_Class_String(strdup(REGISTER[_value._ptr].s->__NJS_VALUE.c_str()));
	}
	else REGISTER[(*_obj)[_i].second._ptr] = REGISTER[_value._ptr];

	  return NJS::VAR();
    }
  }

  (*_obj).push_back(pair<char*, NJS::VAR>( _index, _value));
  return NJS::VAR();

}
/**/



NJS::VAR __NJS_Object_Set(NJS::VAR _index, NJS::VAR _value, NJS::VAR _array)
{
  if(_array.type == NJS::Enum::Type::ARRAY && _index.type == NJS::Enum::Type::NUMBER)
  {
	 if(_array.get().a->__NJS_VALUE.size() <= _index.get().i) _array.get().a->__NJS_VALUE.resize(_index.get().i + 1);
    _array.get().a->__NJS_VALUE[_index.get().i].type = _value.type;

	if(_value.type == NJS::Enum::Type::STRING)
	{
		REGISTER[_array.get().a->__NJS_VALUE[_index.get().i]._ptr].s = new __NJS_Class_String(strdup(REGISTER[_value._ptr].s->__NJS_VALUE.c_str()));
	}
	else REGISTER[_array.get().a->__NJS_VALUE[_index.get().i]._ptr] = REGISTER[_value._ptr];
	
	__NJS_Object_Set((char*)"length", NJS::VAR((int)_array.get().a->__NJS_VALUE.size()), _array);
	return NJS::VAR();
    
  }
  else if(_array.type == NJS::Enum::Type::OBJECT || _array.type == NJS::Enum::Type::STRING || _array.type == NJS::Enum::Type::FUNCTION || _array.type == NJS::Enum::Type::ARRAY || _array.type == NJS::Enum::Type::NATIVE)
  {
    vector<pair<char*, NJS::VAR>>* _obj;
    if(_array.type == NJS::Enum::Type::OBJECT) _obj = &_array.get().o->__OBJECT;
	else if(_array.type == NJS::Enum::Type::ARRAY) _obj = &_array.get().a->__OBJECT;
    else if(_array.type == NJS::Enum::Type::STRING) _obj = &_array.get().s->__OBJECT;
	else if(_array.type == NJS::Enum::Type::FUNCTION) _obj = &_array.get().f->__OBJECT;
    else return NJS::VAR();
	
	_index.get().s->cnt++;
	return __NJS_Object_Set((char*)_index.get().s->__NJS_VALUE.c_str(), _value, _obj);

  }

  return NJS::VAR();
}


NJS::VAR __NJS_Object_Get(NJS::VAR _index, NJS::VAR _array)
{
  if(_array.type != NJS::Enum::Type::ARRAY && _array.type != NJS::Enum::Type::OBJECT && _array.type != NJS::Enum::Type::STRING && _array.type != NJS::Enum::Type::FUNCTION && _array.type != NJS::Enum::Type::NATIVE) 
  {
	  __NJS_RETURN_UNDEFINED;
  }
  if(_array.type == NJS::Enum::Type::ARRAY && _index.type == NJS::Enum::Type::NUMBER)
  {
    if(_index.get().i > _array.get().a->__NJS_VALUE.size())
    {
      __NJS_RETURN_UNDEFINED;
    }
    return _array.get().a->__NJS_VALUE[_index.get().i];
  }
  else
  {
    if(_index.type != NJS::Enum::Type::STRING)
	{
		__NJS_RETURN_UNDEFINED;
	}
    vector<pair<char*, NJS::VAR>>* _obj;
    if(_array.type == NJS::Enum::Type::OBJECT) _obj = &_array.get().o->__OBJECT;
	else if(_array.type == NJS::Enum::Type::ARRAY) _obj = &_array.get().a->__OBJECT;
    else if(_array.type == NJS::Enum::Type::STRING) _obj = &_array.get().s->__OBJECT;
	else if(_array.type == NJS::Enum::Type::FUNCTION) _obj = &_array.get().f->__OBJECT;
    else
	{
		__NJS_RETURN_UNDEFINED;
	}
    int _j = (*_obj).size();
    for(int _i = 0; _i < _j; _i++)
    {
      if(strcmp(strdup(_index.get().s->__NJS_VALUE.c_str()), (*_obj)[_i].first) == 0)
      {
        return (*_obj)[_i].second;
      }
    }
  }

  __NJS_RETURN_UNDEFINED;
}

__NJS_Class_String::__NJS_Class_String(char* _value)
{
	cnt++;
	/*** toString ***/
  function<NJS::VAR ()>* __OBJ_TO_NJS_STRING = new function<NJS::VAR ()>([&](){ return __NJS_Create_String((char*)this->__NJS_VALUE.c_str()); });
  NJS::VAR toString = NJS::VAR(NJS::Enum::Type::FUNCTION, __OBJ_TO_NJS_STRING);
  __NJS_Object_Set((char*)"toString", toString, &this->__OBJECT);
	/*** end to string ***/
	
	/*** length ***/
  __NJS_Object_Set((char*)"length", NJS::VAR((int)strlen(_value)), &this->__OBJECT);
	/*** end length ***/
	
  /*** split ***/
  function<NJS::VAR (vector<var>)>* __OBJ_TO___NJS_SPLIT = new function<NJS::VAR (vector<var>)>([&](vector<var> NJS::VARARGS)
  { 
	  var _needle;
	  if(NJS::VARARGS.size() > 0) _needle = NJS::VARARGS[0];
	  else return NJS::VAR(this->__NJS_VALUE.c_str());

	NJS::VAR _arr = __NJS_Create_Array();
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
  
  NJS::VAR __split = NJS::VAR(NJS::Enum::Type::FUNCTION, __OBJ_TO___NJS_SPLIT);
  __NJS_Object_Set((char*)"split", __split, &this->__OBJECT);
	/*** end split ***/

 #ifndef __NJS_ARDUINO
	/*** indexOf ***/
  function<NJS::VAR (vector<var>)>* __OBJ_TO___NJS_INDEXOF = new function<NJS::VAR (vector<var>)>([&](vector<var> NJS::VARARGS)
  { 
	  var _needle;
	  if(NJS::VARARGS.size() > 0) _needle = NJS::VARARGS[0];
	  else return NJS::VAR(-1);

	string::size_type loc = this->__NJS_VALUE.find( _needle.get().s->__NJS_VALUE, 0 );
	if( loc != string::npos ) 
	{
		return NJS::VAR((int)loc);
	} 
	return NJS::VAR(-1);
  });
  
  NJS::VAR __indexof = NJS::VAR(NJS::Enum::Type::FUNCTION, __OBJ_TO___NJS_INDEXOF);

  __NJS_Object_Set((char*)"indexOf", __indexof, &this->__OBJECT);
	/*** end indexOf ***/

	/*** lastIndexOf ***/
  function<NJS::VAR (vector<var>)>* __OBJ_TO___NJS_LASTINDEXOF = new function<NJS::VAR (vector<var>)>([&](vector<var> NJS::VARARGS)
  { 
	  var _needle;
	  if(NJS::VARARGS.size() > 0) _needle = NJS::VARARGS[0];
	  else return NJS::VAR(-1);

	string::size_type loc = this->__NJS_VALUE.find_last_of( _needle.get().s->__NJS_VALUE, 0 );
	if( loc != string::npos ) 
	{
		return NJS::VAR((int)loc);
	} 
	return NJS::VAR(-1);
  });
  
  NJS::VAR __lastindexof = NJS::VAR(NJS::Enum::Type::FUNCTION, __OBJ_TO___NJS_LASTINDEXOF);

  __NJS_Object_Set((char*)"lastIndexOf", __lastindexof, &this->__OBJECT);
	/*** end lastIndexOf ***/

  /*** search ***/
  function<NJS::VAR (vector<var>)>* __OBJ_TO___NJS_SEARCH = new function<NJS::VAR (vector<var>)>([&](vector<var> NJS::VARARGS)
  { 
	  var _needle;
	  if(NJS::VARARGS.size() > 0) _needle = NJS::VARARGS[0];
	  else return NJS::VAR(-1);

	string::size_type loc = this->__NJS_VALUE.find( _needle.get().s->__NJS_VALUE, 0 );
	if( loc != string::npos ) 
	{
		return NJS::VAR((int)loc);
	} 
	return NJS::VAR(-1);
  });
  
  NJS::VAR __search = NJS::VAR(NJS::Enum::Type::FUNCTION, __OBJ_TO___NJS_SEARCH);

  __NJS_Object_Set((char*)"search", __search, &this->__OBJECT);
	/*** end search ***/

  /*** slice ***/
  function<NJS::VAR (vector<var>)>* __OBJ_TO___NJS_SLICE = new function<NJS::VAR (vector<var>)>([&](vector<var> NJS::VARARGS)
  { 
	var _start; var _end;
	if(NJS::VARARGS.size() > 0) _start = NJS::VARARGS[0];
	else return  NJS::VAR(this->__NJS_VALUE.c_str());
	if(NJS::VARARGS.size() > 1) _end = NJS::VARARGS[1];

	if(_end.type == NJS::Enum::Type::UNDEFINED) return NJS::VAR(this->__NJS_VALUE.substr( _start.get().i, string::npos).c_str());
	int _endIndex = _end.get().i - _start.get().i;
	return NJS::VAR(this->__NJS_VALUE.substr( _start.get().i, _endIndex).c_str());
  });
  
  NJS::VAR __slice = NJS::VAR(NJS::Enum::Type::FUNCTION, __OBJ_TO___NJS_SLICE);

  __NJS_Object_Set((char*)"slice", __slice, &this->__OBJECT);
  __NJS_Object_Set((char*)"substring", __slice, &this->__OBJECT);
	/*** end slice ***/

	  /*** substr ***/
  function<NJS::VAR (vector<var>)>* __OBJ_TO___NJS_SUBSTR = new function<NJS::VAR (vector<var>)>([&](vector<var> NJS::VARARGS)
  { 
	var _start; var _end;
	if(NJS::VARARGS.size() > 0) _start = NJS::VARARGS[0];
	else return  NJS::VAR(this->__NJS_VALUE.c_str());
	if(NJS::VARARGS.size() > 1) _end = NJS::VARARGS[1];

	if(_end.type == NJS::Enum::Type::UNDEFINED) return NJS::VAR(this->__NJS_VALUE.substr( _start.get().i, string::npos).c_str());
	return NJS::VAR(this->__NJS_VALUE.substr( _start.get().i, _end.get().i ).c_str());
  });
  
  NJS::VAR __substr = NJS::VAR(NJS::Enum::Type::FUNCTION, __OBJ_TO___NJS_SUBSTR);

  __NJS_Object_Set((char*)"substr", __substr, &this->__OBJECT);
	/*** end substr ***/

	/*** replace ***/
  function<NJS::VAR (vector<var>)>* __OBJ_TO___NJS_REPLACE = new function<NJS::VAR (vector<var>)>([&](vector<var> NJS::VARARGS)
  { 
	var _search; var _replace;
	if(NJS::VARARGS.size() > 0) _search = NJS::VARARGS[0];
	else return  NJS::VAR(this->__NJS_VALUE.c_str());
	if(NJS::VARARGS.size() > 1) _replace = NJS::VARARGS[1];

	size_t start_pos = this->__NJS_VALUE.find(_search.get().s->__NJS_VALUE);
    if(start_pos == std::string::npos)
	{
        return var(this->__NJS_VALUE.c_str());
	}
    return var(this->__NJS_VALUE.replace(start_pos, _search.get().s->__NJS_VALUE.length(), _replace.get().s->__NJS_VALUE).c_str());
  });
  
  NJS::VAR __replace = NJS::VAR(NJS::Enum::Type::FUNCTION, __OBJ_TO___NJS_REPLACE);

  __NJS_Object_Set((char*)"replace", __replace, &this->__OBJECT);
	/*** end replace ***/
#endif

  __NJS_VALUE = _value;
}

__NJS_Class_Array::__NJS_Class_Array()
{
	cnt++;
  function<NJS::VAR ()>* __OBJ_TO_NJS_STRING = new function<NJS::VAR ()>([&](){ return __NJS_Create_String((char*)"Array"); });
  NJS::VAR toString = NJS::VAR(NJS::Enum::Type::FUNCTION, __OBJ_TO_NJS_STRING);
  __NJS_Object_Set((char*)"toString", toString, &this->__OBJECT);
  
  __NJS_Object_Set((char*)"length", NJS::VAR(0), &this->__OBJECT);
}

__NJS_Class_Object::__NJS_Class_Object()
{
	cnt++;
}


__NJS_Class_Function::__NJS_Class_Function(void* _f)
{
	cnt++;
  __NJS_VALUE = _f;

}

__NJS_Class_Native::__NJS_Class_Native(void* _n)
{
	cnt++;
  __NJS_VALUE = _n;

}


void __NJS_Class_String::Delete()
{
	this->cnt --;
	if(this->cnt < 1)
	{
		delete this;
	}	
}

void __NJS_Class_Array::Delete()
{
	this->cnt --;
	if(this->cnt < 1)
	{
		delete this;
	}	
}

void __NJS_Class_Object::Delete()
{
	this->cnt --;
	if(this->cnt < 1)
	{
		delete this;
	}	
}

void __NJS_Class_Function::Delete()
{
	this->cnt --;
	if(this->cnt < 1)
	{
		delete this;
	}	
}

void __NJS_Class_Native::Delete()
{
	this->cnt --;
	if(this->cnt < 1)
	{
		delete this;
	}	
}

NJS::VAR Array()
{
  vector<NJS::VAR>* _arr = new vector<NJS::VAR>();
  return NJS::VAR(NJS::Enum::Type::ARRAY, _arr);
}

NJS::VAR __NJS_Boolean_Result(NJS::VAR _v)
{
  if(_v.type == NJS::Enum::Type::NUMBER) return _v.get().i;
  else if(_v.type == NJS::Enum::Type::BOOLEAN) return _v.get().b;
  else if(_v.type == NJS::Enum::Type::STRING)
  {
    if(strlen(_v.get().s->__NJS_VALUE.c_str()) > 0) return true;
    else return false;
  }
  else if(_v.type == NJS::Enum::Type::ARRAY) return true;
  else return false;
}

ostream& operator << (ostream& os, const NJS::VAR& _v)
{
  switch(_v.type)
  {
    case NJS::Enum::Type::BOOLEAN:
		if(_v.get().b) os << (char*)"true";
		else os << (char*)"false";
		break;
	case NJS::Enum::Type::NUMBER:
		os << _v.get().i;
		break;
	case NJS::Enum::Type::DOUBLE:
		os << _v.get().d;
		break;
	case NJS::Enum::Type::STRING:
		os << _v.get().s->__NJS_VALUE;
		break;
	case NJS::Enum::Type::OBJECT:
		os << __NJS_Object_Stringify(_v);
		break;
	case NJS::Enum::Type::ARRAY:
		os << __NJS_Object_Stringify(_v);
		break;
	case NJS::Enum::Type::NATIVE:
		os << "[Native]";
		break;
	case NJS::Enum::Type::ISNAN:
		os << "NaN";
		break;
	case NJS::Enum::Type::FUNCTION:
		os << "[Function]";
		break;
	case NJS::Enum::Type::ISINFINITY:
		os << "Infinity";
		break;
	case NJS::Enum::Type::ISNULL:
		os << "null";
		break;
	default:
		os << "undefined";
		break;
  }
  return os;
}

NJS::VAR parseInt(NJS::VAR _str)
{
  if(_str.type == NJS::Enum::Type::STRING)
  {
	#ifdef __NJS_ARDUINO
		return NJS::VAR();
	#else
		return __NJS_Create_Number(stoi(_str.get().s->__NJS_VALUE));
	#endif
  }
  else return __NJS_Create_Undefined();
}


NJS::VAR  __NJS_Log_Console(NJS::VAR _var)
{
	#ifdef __NJS_ARDUINO
	
	#else
		cout << _var;
		cout << endl;
	#endif
	
  return NJS::VAR();
}

NJS::VAR  __NJS_Object_Keys(NJS::VAR _var)
{
	if(_var.type != NJS::Enum::Type::OBJECT) return 0;
	var _res = __NJS_Create_Array();
	
	vector<pair<char*, NJS::VAR>>* _obj = &_var.get().o->__OBJECT;
    int _j = (*_obj).size();
    for(int _i = 0; _i < _j; _i++)
    {
		__NJS_Object_Set(_i, (*_obj)[_i].first, _res);
    }
	return _res;
}

NJS::VAR  __NJS_Object_Stringify(NJS::VAR _var)
{

	NJS::Enum::Type _t = _var.type;

	if(_t == NJS::Enum::Type::UNDEFINED) return "undefined";
	else if(_t == NJS::Enum::Type::ISNAN) return "NaN";
	else if(_t ==  NJS::Enum::Type::NUMBER) return var("") + _var;
	else if(_t == NJS::Enum::Type::DOUBLE) return _var;
	else if(_t == NJS::Enum::Type::STRING) return var("\"") + _var + "\"";
	else if(_t == NJS::Enum::Type::FUNCTION) return var("\"") + "[Function]" + "\"";
	else if(_t == NJS::Enum::Type::ARRAY)
	{
		var _res = "";
		vector<NJS::VAR>* _arr = &_var.get().a->__NJS_VALUE;
		_res += "[";
		int j = (*_arr).size();
		for(int i = 0; i < j; i++)
		{
			if(i > 0) _res += ", ";
			_res += __NJS_Object_Stringify((*_arr)[i]);
		}
		_res += "]";
		return _res;
	}
	else if(_t == NJS::Enum::Type::OBJECT)
	{
		var _res = "";
		vector<pair<char*, NJS::VAR>>* _obj = &_var.get().o->__OBJECT;
		_res = "{";
		int j = (*_obj).size();
		for(int _i = 0; _i < j; _i++)
		{
			if(_i > 0) _res += ", ";
			_res += var("\"") + (*_obj)[_i].first + "\"";
			_res += ":";
			_res += __NJS_Object_Stringify((*_obj)[_i].second);
		}
		_res += "}";
		return _res;
    }
    else return "";
}

NJS::VAR __NJS_Create_Object()
{
  __NJS_Class_Object* _obj = new __NJS_Class_Object();
  return NJS::VAR(_obj);
}

NJS::VAR __NJS_CREATE_FUNCTION(void* _fn)
{
  return NJS::VAR(NJS::Enum::Type::FUNCTION, _fn);
}

NJS::VAR __NJS_Create_Native(void* _native)
{
  return NJS::VAR(NJS::Enum::Type::UNDEFINED, _native);
}

/*
void* __NJS_Get_Function(NJS::VAR _fn)
{
  return _fn.get().f;
}
*/

function<var (vector<var>)>* __NJS_Get_Function(NJS::VAR _v)
{
  return (function<var (vector<var>)>*)_v.get().f->__NJS_VALUE;
}

void* __NJS_Get_Native(NJS::VAR _native)
{
  return _native.get().f;
}

/*** REDIFINING STD OPERATORS ***/


template<typename t>
NJS::VAR operator+(t _left, const NJS::VAR& _right)
{
	return NJS::VAR(_left) + _right;
}

template<typename t>
NJS::VAR operator-(t _left, const NJS::VAR& _right)
{
	return NJS::VAR(_left) - _right;
}

template<typename t>
NJS::VAR operator*(t _left, const NJS::VAR& _right)
{
	return NJS::VAR(_left) * _right;
}

template<typename t>
NJS::VAR operator/(t _left, const NJS::VAR& _right)
{
	return NJS::VAR(_left) / _right;
}

/*** END REDIFINING STD OPERATORS ***/

__NJS_Create_Lambda(__IMPL_EVAL)
{ 
	__NJS_Log_Console("eval not implemented, return undefined");
	return var();
});
var eval = __NJS_Create_Function(__IMPL_EVAL);

#endif
