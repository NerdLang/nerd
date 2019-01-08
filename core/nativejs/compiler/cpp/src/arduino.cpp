/*
 * This file is part of NectarJS
 * Copyright (c) 2019 Adrien THIERRY
 * http://nectarjs.com - https://nectrium.com
 *
 * sources : https://github.com/nectarjs/nectarjs
 *
 * NectarJS
 * Copyright (C) 2019 Adrien THIERRY - Necrium
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

 #include <avr/io.h>
 #include <wiring_digital.c>
 #include <Arduino.h>
 #include <wiring.c>
 #include <hooks.c>
 #include <util/delay.h>
 #include <string.h>
 #include <WString.h>
 #include <WString.cpp>
 #include <new.h>
 #include <new.cpp>
 #include <time.h>


#define UNDEFINED 0
#define NUMBER 1
#define UINT 2
#define STRING 3
#define BOOLEAN 4
#define ARRAY 5


#define __create_Boolean(_value) var(BOOLEAN, _value)
#define __create_Number(_value) var(NUMBER, _value)
#define __create_String(_value) var(STRING,(char*)_value)
#define __create_Undefined() var(UNDEFINED, 0)


template<typename Data>
class vector {
  size_t d_size; // Stores no. of actually stored objects
  size_t d_capacity; // Stores allocated capacity
  Data *d_data; // Stores data
  public:
    vector() : d_size(0), d_capacity(0), d_data(0) {}; // Default constructor
    vector(vector const &other) : d_size(other.d_size), d_capacity(other.d_capacity), d_data(0) { d_data = (Data *)malloc(d_capacity*sizeof(Data)); memcpy(d_data, other.d_data, d_size*sizeof(Data)); }; // Copy constuctor
    ~vector() { free(d_data); }; // Destructor
    vector &operator=(vector const &other) { free(d_data); d_size = other.d_size; d_capacity = other.d_capacity; d_data = (Data *)malloc(d_capacity*sizeof(Data)); memcpy(d_data, other.d_data, d_size*sizeof(Data)); return *this; }; // Needed for memory management
    void push_back(Data const &x) { if (d_capacity == d_size) resize(); d_data[d_size++] = x; }; // Adds new  If needed, allocates more space
    size_t size() const { return d_size; }; // Size getter
    Data const &operator[](size_t idx) const { return d_data[idx]; }; // Const getter
    Data &operator[](size_t idx) { return d_data[idx]; }; // Changeable getter
  private:
    void resize() { d_capacity = d_capacity ? d_capacity*2 : 1; Data *newdata = (Data *)malloc(d_capacity*sizeof(Data)); memcpy(newdata, d_data, d_size * sizeof(Data)); free(d_data); d_data = newdata; };// Allocates double the old space
};

struct var
{
		unsigned int type;
    int u;
  	unsigned int i;
    unsigned int p;
  	bool b;
  	String s;
    vector<var>* a;
    var(){}
    var (int _type, unsigned int _value): type(_type), p(_value){}

		var (int _type, int _value): type(_type), i(_value){}
		var (int _value): type(NUMBER), i(_value){}

		var (int _type, String _value): type(_type), s(String(_value)){}
		var (String _value): type(STRING), s(String(_value)){}

    var (int _type, vector<var>* _value): type(_type), a(_value){}
		var (vector<var>* _value): type(ARRAY), a(_value){}

		var operator+(const var& _v1)
		{
			if(type == NUMBER && _v1.type == NUMBER)
			{
				return var(NUMBER, i + _v1.i);
			}
      else if(type == UINT && _v1.type == NUMBER)
			{
				return var(NUMBER, p + _v1.i);
			}
			else if(type == STRING && _v1.type == NUMBER)
			{
        String _r = String(s);
        _r.concat(_v1.i);
        return var(STRING, _r);
			}
      else if(type == STRING && _v1.type == UINT)
			{
        String _r = String(s);
        _r.concat(String(_v1.p));
        return var(STRING, _r);
			}
			else if(type == STRING && _v1.type == STRING)
			{
        String _r = String(s);
        _r.concat(_v1.s);
        return var(STRING, _r);
			}
			else
			{
				return var(NUMBER,0);
			}
		}
		var operator-(const var& _v1)
		{
      if(type == NUMBER && _v1.type == NUMBER)
			{
				return var(NUMBER, i - _v1.i);
			}
      else if(type == UINT && _v1.type == NUMBER)
			{
				return var(NUMBER, p - _v1.i);
			}
		}
    var operator*(const var& _v1)
		{
      if(type == NUMBER && _v1.type == NUMBER)
			{
				return var(NUMBER, i * _v1.i);
			}
      else if(type == UINT && _v1.type == NUMBER)
			{
				return var(UINT, p * _v1.i);
			}
		}
    var operator/(const var& _v1)
		{
      if(type == NUMBER && _v1.type == NUMBER)
			{
				return var(NUMBER, i / _v1.i);
			}
      else if(type == UINT && _v1.type == NUMBER)
			{
				return var(NUMBER, p / (unsigned int) _v1.i);
		  }
    }
    var operator%(const var& _v1)
		{
      if(type == NUMBER && _v1.type == NUMBER)
			{
				return var(NUMBER, i % _v1.i);
			}
      else if(type == UINT && _v1.type == NUMBER)
			{
				return var(NUMBER, p % _v1.i);
			}
		}
    var const operator ! () const
    {
      if(type == NUMBER)
      {
        return __create_Number(!i);
      }
      else return(__create_Boolean(false));
    };
    var operator++(const int _v1)
		{
			return var(NUMBER, i++ );
		}
    var operator--(const int _v1)
		{
			return var(NUMBER, i-- );
		}
    var operator==(const var& _v1)
		{
			return var(BOOLEAN, i == _v1.i);
		}
		var operator<(const var& _v1)
		{
			return var(BOOLEAN, i < _v1.i);
		}
    var operator<=(const var& _v1)
		{
			return var(BOOLEAN, i <= _v1.i);
		}
		var operator>(const var& _v1)
		{
			return var(BOOLEAN, i > _v1.i);
		}
    var operator>=(const var& _v1)
		{
			return var(BOOLEAN, i >= _v1.i);
		}
    var operator[] (const int index)
    {
      if(type == ARRAY)
      {
        if(index > (*a).size() - 1)
        {
          return var(UNDEFINED, 0);
        }
        return (*a)[index];
      }
      else if(type == STRING)
      {
        return var((char*)String(String(s).charAt(index)).c_str());
      }
      return var(UNDEFINED, 0);
    }
    ~var()
    {
      if(type == ARRAY) delete [] a;
    }
};

var Array()
{
  vector<var>* _arr;
  return var(ARRAY, _arr);
}

inline int __NJS_Get_Int(var _v)
{
  return _v.i;
}

inline String __NJS_Get_String(var _v)
{
  return _v.s;
}

bool __NJS_Boolean_Result(var _v)
{
  if(_v.type == NUMBER) return _v.i;
  else if(_v.type == BOOLEAN) return _v.b;
  else if(_v.type == STRING)
  {
    if(_v.s.length() > 0) return true;
    else return false;
  }
  else if(_v.type == ARRAY) return true;
  else return false;
}

var parseInt(var _str)
{
  if(_str.type == STRING)
  {
    return var(NUMBER, (int)String(_str.s).toInt());
  }
  else return __create_Undefined();
}

var __NJS_Typeof(var _var)
{
  const char* _array[] = {"undefined", "number", "number", "string", "boolean", "array"};
  return __create_String(_array[_var.type]);
}


static var NECTARJS = var(BOOLEAN, 1);

__GLOBAL_VAR__

__NECTAR_LIB__



// Declared weak in Arduino.h to allow user redefinitions.
int atexit(void (* /*func*/ )()) { return 0; }
// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));
void initVariant() { }

void setupUSB() __attribute__((weak));
void setupUSB() { }

var setup() __attribute__((weak));
var loop() __attribute__((weak));

__DECLARATION__

__CODE__

int main(void)
{
  init();

  initVariant();

  #if defined(USBCON)
  USBDevice.attach();
  #endif

  __MAIN__

  setup();

	while(true)
  {
    loop();
  }
  return 0;
}
