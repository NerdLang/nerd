#include "jsmn.h"

int to_int(char const *s)
{
     if ( s == NULL || *s == '\0' )
        throw std::invalid_argument("null or empty JSON argument");

     bool negate = (s[0] == '-');
     if ( *s == '+' || *s == '-' ) 
         ++s;

     if ( *s == '\0')
        throw std::invalid_argument("sign character only.");

     int result = 0;
     while(*s)
     {
		 if ( *s >= '0' && *s <= '9' )
          {
              result = result * 10  - (*s - '0'); 
          }
          else
              throw std::invalid_argument("invalid JSON input string");
          ++s;
     }
     return negate ? result : -result;
} 

static inline void *realloc_it(void *ptrmem, size_t size) {
  void *p = realloc(ptrmem, size);
  if (!p) {
    free(ptrmem);
    fprintf(stderr, "realloc(): errno=%d\n", errno);
  }
  return p;
}



char* substr(const char* arr, int begin, int len)
{
    char* res = new char[len];
    for (int i = 0; i < len; i++) res[i] = *(arr + begin + i);
    res[len] = 0;
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
	  string _s = substr(js, t->start, t->end - t->start);
	if(_s[0] == 't') _res = true;
	else if(_s[0] == 'f') _res = false;
	else if(_s[0] == 'n') _res = var();
	else _res = to_int(_s.c_str());

    return 1;
  } 
  else if (t->type == JSMN_STRING) 
  {
	_res = substr(js, t->start, t->end - t->start);

    return 1;
  } 
  else if (t->type == JSMN_OBJECT) 
  {
    j = 0;
    _res = __NJS_Create_Object();
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
      __NJS_Object_Set(_key, _value, _res);
    }
    return j+1;
  } 
  else if (t->type == JSMN_ARRAY) 
  {
    j = 0;
    _res = __NJS_Create_Array();
    for (i = 0; i < t->size; i++) 
    {
      var _value;
      j += dump(js, t + 1 + j, count - j, indent + 1, _value);
      __NJS_Object_Set(i, _value, _res);
    }
    return j+1;
  }
  return 0;
}

function __NJS_JSON_PARSE(__json)
{
	size_t tokcount = 32;
	int r;
	int j = 0;
	var __RESULT;
	char* JSON_STRING = (char*)__json.get().s->__NJS_VALUE.c_str();
	jsmn_parser p;
	jsmntok_t *tok = (jsmntok_t*)malloc(sizeof(*tok) * tokcount);

	jsmn_init(&p);
	
	int _again = 1;
	while(_again)
	{
		r = jsmn_parse(&p, JSON_STRING, strlen(JSON_STRING), tok, tokcount);
		if (r < 0) 
		{
			if (r == JSMN_ERROR_NOMEM) 
			{
				tokcount = tokcount * 2;
				tok = (jsmntok_t *)realloc_it(tok, sizeof(*tok) * tokcount);
			}
			else
			{
				printf("Failed to parse JSON: %d\n", r);
				return __RESULT;
			}
		}
		else 
		{
			dump(JSON_STRING, tok, p.toknext, 0, __RESULT);
			_again = 0;
		}
	}
	free(tok);
	return __RESULT;
};


function __NJS_JSON_STRINGIFY(__object)
{
	return "Not implemented yet";
};
