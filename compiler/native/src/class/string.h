__NJS_Class_String::__NJS_Class_String(string _value)
{
	cnt++;
	/*** toString ***/
	function<__NJS_VAR(vector<var>)> *__OBJ_TO___NJS_STRING = new function<__NJS_VAR(vector<var>)>([&](vector<var> __NJS_VARARGS) { return __NJS_Create_String(this->__NJS_VALUE); });
	__NJS_VAR toString = __NJS_VAR(__NJS_FUNCTION, __OBJ_TO___NJS_STRING);
	__NJS_Object_Set("toString", toString, &this->__OBJECT);
	/*** end to string ***/

	/*** length ***/
	__NJS_Object_Set("length", __NJS_VAR((int)_value.size()), &this->__OBJECT);
	/*** end length ***/

	/*** split ***/
	function<__NJS_VAR(vector<var>)> *__OBJ_TO___NJS_SPLIT = new function<__NJS_VAR(vector<var>)>([&](vector<var> __NJS_VARARGS) {
		var _needle;
		if (__NJS_VARARGS.size() > 0)
			_needle = __NJS_VARARGS[0];
		else
			return __NJS_VAR(this->__NJS_VALUE);

		__NJS_VAR _arr = __NJS_Create_Array();
		char *_v = (char *)malloc(strlen(this->__NJS_VALUE.c_str()) + 1);
		strcpy(_v, this->__NJS_VALUE.c_str());
		char *delim = (char *)malloc(strlen(_needle.get().s->__NJS_VALUE.c_str()) + 1);
		strcpy(delim, _needle.get().s->__NJS_VALUE.c_str());

		char *ptr = strtok(_v, delim);
		int i = 0;
		char *_new;
		while (ptr != NULL)
		{
			_new = (char *)malloc(strlen(ptr) + 1);
			strcpy(_new, ptr);
			__NJS_Object_Set(i, _new, _arr);
			free(_new);
			ptr = strtok(NULL, delim);
			i++;
		}

		free(delim);
		return _arr;
	});

	__NJS_VAR __split = __NJS_VAR(__NJS_FUNCTION, __OBJ_TO___NJS_SPLIT);
	__NJS_Object_Set("split", __split, &this->__OBJECT);
	/*** end split ***/

#ifndef __NJS_ARDUINO
	/*** indexOf ***/
	function<__NJS_VAR(vector<var>)> *__OBJ_TO___NJS_INDEXOF = new function<__NJS_VAR(vector<var>)>([&](vector<var> __NJS_VARARGS) {
		var _needle;
		if (__NJS_VARARGS.size() > 0)
			_needle = __NJS_VARARGS[0];
		else
			return __NJS_VAR(-1);

		string::size_type loc = this->__NJS_VALUE.find(_needle.get().s->__NJS_VALUE, 0);
		if (loc != string::npos)
		{
			return __NJS_VAR((int)loc);
		}
		return __NJS_VAR(-1);
	});

	__NJS_VAR __indexof = __NJS_VAR(__NJS_FUNCTION, __OBJ_TO___NJS_INDEXOF);

	__NJS_Object_Set("indexOf", __indexof, &this->__OBJECT);
	/*** end indexOf ***/

	/*** lastIndexOf ***/
	function<__NJS_VAR(vector<var>)> *__OBJ_TO___NJS_LASTINDEXOF = new function<__NJS_VAR(vector<var>)>([&](vector<var> __NJS_VARARGS) {
		var _needle;
		if (__NJS_VARARGS.size() > 0)
			_needle = __NJS_VARARGS[0];
		else
			return __NJS_VAR(-1);

		string::size_type loc = this->__NJS_VALUE.find_last_of(_needle.get().s->__NJS_VALUE, 0);
		if (loc != string::npos)
		{
			return __NJS_VAR((int)loc);
		}
		return __NJS_VAR(-1);
	});

	__NJS_VAR __lastindexof = __NJS_VAR(__NJS_FUNCTION, __OBJ_TO___NJS_LASTINDEXOF);

	__NJS_Object_Set("lastIndexOf", __lastindexof, &this->__OBJECT);
	/*** end lastIndexOf ***/

	/*** search ***/
	function<__NJS_VAR(vector<var>)> *__OBJ_TO___NJS_SEARCH = new function<__NJS_VAR(vector<var>)>([&](vector<var> __NJS_VARARGS) {
		var _needle;
		if (__NJS_VARARGS.size() > 0)
			_needle = __NJS_VARARGS[0];
		else
			return __NJS_VAR(-1);

		string::size_type loc = this->__NJS_VALUE.find(_needle.get().s->__NJS_VALUE, 0);
		if (loc != string::npos)
		{
			return __NJS_VAR((int)loc);
		}
		return __NJS_VAR(-1);
	});

	__NJS_VAR __search = __NJS_VAR(__NJS_FUNCTION, __OBJ_TO___NJS_SEARCH);

	__NJS_Object_Set("search", __search, &this->__OBJECT);
	/*** end search ***/

	/*** slice ***/
	function<__NJS_VAR(vector<var>)> *__OBJ_TO___NJS_SLICE = new function<__NJS_VAR(vector<var>)>([&](vector<var> __NJS_VARARGS) {
		var _start;
		var _end;
		if (__NJS_VARARGS.size() > 0)
			_start = __NJS_VARARGS[0];
		else
			return __NJS_VAR(this->__NJS_VALUE);
		if (__NJS_VARARGS.size() > 1)
			_end = __NJS_VARARGS[1];

		if (_end.type == __NJS_UNDEFINED)
			return __NJS_VAR(this->__NJS_VALUE.substr(_start.get().i, string::npos));
		int _endIndex = _end.get().i - _start.get().i;
		return __NJS_VAR(this->__NJS_VALUE.substr(_start.get().i, _endIndex));
	});

	__NJS_VAR __slice = __NJS_VAR(__NJS_FUNCTION, __OBJ_TO___NJS_SLICE);

	__NJS_Object_Set("slice", __slice, &this->__OBJECT);
	__NJS_Object_Set("substring", __slice, &this->__OBJECT);
	/*** end slice ***/

	/*** substr ***/
	function<__NJS_VAR(vector<var>)> *__OBJ_TO___NJS_SUBSTR = new function<__NJS_VAR(vector<var>)>([&](vector<var> __NJS_VARARGS) {
		var _start;
		var _end;
		if (__NJS_VARARGS.size() > 0)
			_start = __NJS_VARARGS[0];
		else
			return __NJS_VAR(this->__NJS_VALUE);
		if (__NJS_VARARGS.size() > 1)
			_end = __NJS_VARARGS[1];

		if (_end.type == __NJS_UNDEFINED)
			return __NJS_VAR(this->__NJS_VALUE.substr(_start.get().i, string::npos));
		return __NJS_VAR(this->__NJS_VALUE.substr(_start.get().i, _end.get().i));
	});

	__NJS_VAR __substr = __NJS_VAR(__NJS_FUNCTION, __OBJ_TO___NJS_SUBSTR);

	__NJS_Object_Set("substr", __substr, &this->__OBJECT);
	/*** end substr ***/

	/*** replace ***/
	function<__NJS_VAR(vector<var>)> *__OBJ_TO___NJS_REPLACE = new function<__NJS_VAR(vector<var>)>([&](vector<var> __NJS_VARARGS) {
		var _search;
		var _replace;
		if (__NJS_VARARGS.size() > 0)
			_search = __NJS_VARARGS[0];
		else
			return __NJS_VAR(this->__NJS_VALUE);
		if (__NJS_VARARGS.size() > 1)
			_replace = __NJS_VARARGS[1];

		size_t start_pos = this->__NJS_VALUE.find(_search.get().s->__NJS_VALUE);
		if (start_pos == std::string::npos)
		{
			return var(this->__NJS_VALUE);
		}
		return var(this->__NJS_VALUE.replace(start_pos, _search.get().s->__NJS_VALUE.length(), _replace.get().s->__NJS_VALUE));
	});

	__NJS_VAR __replace = __NJS_VAR(__NJS_FUNCTION, __OBJ_TO___NJS_REPLACE);

	__NJS_Object_Set("replace", __replace, &this->__OBJECT);
	/*** end replace ***/
#endif

	__NJS_VALUE = _value;
}

void __NJS_Class_String::Delete()
{
	this->cnt--;
	if (this->cnt < 1)
	{
		delete this;
	}
}