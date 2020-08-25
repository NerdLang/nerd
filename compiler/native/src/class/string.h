__NJS_Class_String::__NJS_Class_String(string _value)
{
	cnt++;
	/*** toString ***/
	function<NJS::VAR(vector<var>)> *__OBJ_TO_NJS_STRING = new function<NJS::VAR(vector<var>)>([&](vector<var> _NJS_VARARGS) { return __NJS_Create_String(this->__NJS_VALUE); });
	NJS::VAR toString = NJS::VAR(NJS::Enum::Type::FUNCTION, __OBJ_TO_NJS_STRING);
	__NJS_Object_Set("toString", toString, &this->__OBJECT);
	/*** end to string ***/

	/*** length ***/
	__NJS_Object_Set("length", NJS::VAR((int)_value.size()), &this->__OBJECT);
	/*** end length ***/

	/*** split ***/
	function<NJS::VAR(vector<var>)> *__OBJ_TO___NJS_SPLIT = new function<NJS::VAR(vector<var>)>([&](vector<var> _NJS_VARARGS) {
		var _needle;
		if (_NJS_VARARGS.size() > 0)
			_needle = _NJS_VARARGS[0];
		else
			return NJS::VAR(this->__NJS_VALUE);

		NJS::VAR _arr = __NJS_Create_Array();
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

	NJS::VAR __split = NJS::VAR(NJS::Enum::Type::FUNCTION, __OBJ_TO___NJS_SPLIT);
	__NJS_Object_Set("split", __split, &this->__OBJECT);
	/*** end split ***/

#ifndef __NJS_ARDUINO
	/*** indexOf ***/
	function<NJS::VAR(vector<var>)> *__OBJ_TO___NJS_INDEXOF = new function<NJS::VAR(vector<var>)>([&](vector<var> _NJS_VARARGS) {
		var _needle;
		if (_NJS_VARARGS.size() > 0)
			_needle = _NJS_VARARGS[0];
		else
			return NJS::VAR(-1);

		string::size_type loc = this->__NJS_VALUE.find(_needle.get().s->__NJS_VALUE, 0);
		if (loc != string::npos)
		{
			return NJS::VAR((int)loc);
		}
		return NJS::VAR(-1);
	});

	NJS::VAR __indexof = NJS::VAR(NJS::Enum::Type::FUNCTION, __OBJ_TO___NJS_INDEXOF);

	__NJS_Object_Set("indexOf", __indexof, &this->__OBJECT);
	/*** end indexOf ***/

	/*** lastIndexOf ***/
	function<NJS::VAR(vector<var>)> *__OBJ_TO___NJS_LASTINDEXOF = new function<NJS::VAR(vector<var>)>([&](vector<var> _NJS_VARARGS) {
		var _needle;
		if (_NJS_VARARGS.size() > 0)
			_needle = _NJS_VARARGS[0];
		else
			return NJS::VAR(-1);

		string::size_type loc = this->__NJS_VALUE.find_last_of(_needle.get().s->__NJS_VALUE, 0);
		if (loc != string::npos)
		{
			return NJS::VAR((int)loc);
		}
		return NJS::VAR(-1);
	});

	NJS::VAR __lastindexof = NJS::VAR(NJS::Enum::Type::FUNCTION, __OBJ_TO___NJS_LASTINDEXOF);

	__NJS_Object_Set("lastIndexOf", __lastindexof, &this->__OBJECT);
	/*** end lastIndexOf ***/

	/*** search ***/
	function<NJS::VAR(vector<var>)> *__OBJ_TO___NJS_SEARCH = new function<NJS::VAR(vector<var>)>([&](vector<var> _NJS_VARARGS) {
		var _needle;
		if (_NJS_VARARGS.size() > 0)
			_needle = _NJS_VARARGS[0];
		else
			return NJS::VAR(-1);

		string::size_type loc = this->__NJS_VALUE.find(_needle.get().s->__NJS_VALUE, 0);
		if (loc != string::npos)
		{
			return NJS::VAR((int)loc);
		}
		return NJS::VAR(-1);
	});

	NJS::VAR __search = NJS::VAR(NJS::Enum::Type::FUNCTION, __OBJ_TO___NJS_SEARCH);

	__NJS_Object_Set("search", __search, &this->__OBJECT);
	/*** end search ***/

	/*** slice ***/
	function<NJS::VAR(vector<var>)> *__OBJ_TO___NJS_SLICE = new function<NJS::VAR(vector<var>)>([&](vector<var> _NJS_VARARGS) {
		var _start;
		var _end;
		if (_NJS_VARARGS.size() > 0)
			_start = _NJS_VARARGS[0];
		else
			return NJS::VAR(this->__NJS_VALUE);
		if (_NJS_VARARGS.size() > 1)
			_end = _NJS_VARARGS[1];

		if (_end.type == NJS::Enum::Type::UNDEFINED)
			return NJS::VAR(this->__NJS_VALUE.substr(_start.get().i, string::npos));
		int _endIndex = _end.get().i - _start.get().i;
		return NJS::VAR(this->__NJS_VALUE.substr(_start.get().i, _endIndex));
	});

	NJS::VAR __slice = NJS::VAR(NJS::Enum::Type::FUNCTION, __OBJ_TO___NJS_SLICE);

	__NJS_Object_Set("slice", __slice, &this->__OBJECT);
	__NJS_Object_Set("substring", __slice, &this->__OBJECT);
	/*** end slice ***/

	/*** substr ***/
	function<NJS::VAR(vector<var>)> *__OBJ_TO___NJS_SUBSTR = new function<NJS::VAR(vector<var>)>([&](vector<var> _NJS_VARARGS) {
		var _start;
		var _end;
		if (_NJS_VARARGS.size() > 0)
			_start = _NJS_VARARGS[0];
		else
			return NJS::VAR(this->__NJS_VALUE);
		if (_NJS_VARARGS.size() > 1)
			_end = _NJS_VARARGS[1];

		if (_end.type == NJS::Enum::Type::UNDEFINED)
			return NJS::VAR(this->__NJS_VALUE.substr(_start.get().i, string::npos));
		return NJS::VAR(this->__NJS_VALUE.substr(_start.get().i, _end.get().i));
	});

	NJS::VAR __substr = NJS::VAR(NJS::Enum::Type::FUNCTION, __OBJ_TO___NJS_SUBSTR);

	__NJS_Object_Set("substr", __substr, &this->__OBJECT);
	/*** end substr ***/

	/*** replace ***/
	function<NJS::VAR(vector<var>)> *__OBJ_TO___NJS_REPLACE = new function<NJS::VAR(vector<var>)>([&](vector<var> _NJS_VARARGS) {
		var _search;
		var _replace;
		if (_NJS_VARARGS.size() > 0)
			_search = _NJS_VARARGS[0];
		else
			return NJS::VAR(this->__NJS_VALUE);
		if (_NJS_VARARGS.size() > 1)
			_replace = _NJS_VARARGS[1];

		size_t start_pos = this->__NJS_VALUE.find(_search.get().s->__NJS_VALUE);
		if (start_pos == std::string::npos)
		{
			return var(this->__NJS_VALUE);
		}
		return var(this->__NJS_VALUE.replace(start_pos, _search.get().s->__NJS_VALUE.length(), _replace.get().s->__NJS_VALUE));
	});

	NJS::VAR __replace = NJS::VAR(NJS::Enum::Type::FUNCTION, __OBJ_TO___NJS_REPLACE);

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