/*
 * This file is part of NectarJS
 * Copyright (c) 2017 - 2020 Adrien THIERRY
 * http://nectarjs.com - https://seraum.com/
 *
 * sources : https://github.com/nectarjs/nectarjs
 * 
 * NectarJS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NectarJS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NectarJS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
 
#define JSMN_STRICT
#ifndef __Nectar_ARDUINO
  #define JSMN_PARENT_LINK
#endif

#include "jsmn.h"

NerdCore::VAR to_int(char const *s)
{
	bool _float = false;
	if(strchr(s, '.'))
	{
		return NerdCore::VAR(std::stod(s));
	}
	else 
	{
		return NerdCore::VAR(std::stoi(s));
	}
} 

static inline void *realloc_it(void *ptrmem, size_t size) {
  void *p = std::realloc(ptrmem, size);
  if (!p) {
    std::free(ptrmem);
    std::fprintf(stderr, "realloc(): errno=%d\n", errno);
  }
  return p;
}

char* substr(const char* arr, int begin, int len)
{
    char* res = new char[len];
    for (int i = 0; i < len - 1; i++) res[i] = *(arr + begin + i);
    res[len - 1] = 0;
    return res;
}



int dump(const char *js, jsmntok_t *t, size_t count, int indent, var& _res) 
{
  int i, j, k;
  jsmntok_t *key;
  if (count == 0) 
  {
    return 0;
  }
  if (t->type == JSMN_PRIMITIVE) 
  {
	std::string _s = substr(js, t->start, t->end - t->start);
	if(_s[0] == 't') _res = true;
	else if(_s[0] == 'f') _res = false;
	else if(_s[0] == 'n') _res = var();
	else _res = to_int(_s.c_str());

    return 1;
  } 
  else if (t->type == JSMN_STRING) 
  {
	_res = substr(js, t->start, t->end - t->start + 1);

    return 1;
  } 
  else if (t->type == JSMN_OBJECT) 
  {
    j = 0;
    _res = new NerdCore::Class::Object();
    for (i = 0; i < t->size; i++) 
    {
      key = t + 1 + j;
      var _key;
      j += dump(js, key, count - j, indent + 1, _key);
      var _value;
      if (key->size > 0) 
      {
        j += dump(js, t + 1 + j, count - j, indent + 1, _value);
      }
	  _res[_key] = _value;
      //__NERD_Object_Set(_key, _value, _res);
    }
    return j+1;
  } 
  else if (t->type == JSMN_ARRAY) 
  {
    j = 0;
    _res = new NerdCore::Class::Array();
    std::vector<var> _arr;

    for (i = 0; i < t->size; i++) 
    {
      var _value;  
      j += dump(js, t + 1 + j, count - j, indent + 1, _value);
	  _res[i] = _value;
      //__NERD_Object_Set(i, _value, _res);
    }
    return j+1;
  }
  return 0;
}
