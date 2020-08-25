__NJS_VAR __create_Array()
{
	__NJS_Class_Array *_a = new __NJS_Class_Array();
	return __NJS_VAR(NJS::Enum::Type::ARRAY, _a);
}

__NJS_VAR __NJS_Create_Array()
{
	__NJS_Class_Array *_a = new __NJS_Class_Array();
	return __NJS_VAR(_a);
}

int __NJS_Get_Int(__NJS_VAR _v)
{
	return _v.get().i;
}

const char *__NJS_Get_String(__NJS_VAR _v)
{
	if (_v.type != NJS::Enum::Type::STRING)
		return "";
	return _v.get().s->__NJS_VALUE.c_str();
}

__NJS_VAR __NJS_Typeof(__NJS_VAR _var)
{
	const char *_array[] = {"", "undefined", "number", "number", "object", "number", "boolean", "string", "native", "function", "array", "NaN", "number", "object"};
	return __NJS_Create_String(_array[_var.type]);
}

/*** ***/
__NJS_VAR __NJS_Object_Set(const char *_index, __NJS_VAR _value, vector<pair<const char *, __NJS_VAR>> *_obj)
{
	int _j = (*_obj).size();
	for (int _i = 0; _i < _j; _i++)
	{
		if (strcmp(_index, (*_obj)[_i].first) == 0)
		{

			if (_value.type == NJS::Enum::Type::STRING)
			{
				REGISTER[(*_obj)[_i].second._ptr].s = new __NJS_Class_String((string)_value);
			}
			else
				REGISTER[(*_obj)[_i].second._ptr] = REGISTER[_value._ptr];

			return __NJS_VAR();
		}
	}

	(*_obj).push_back(pair<const char *, __NJS_VAR>(_index, _value));
	return __NJS_VAR();
}
/**/

__NJS_VAR __NJS_Object_Set(__NJS_VAR _index, __NJS_VAR _value, __NJS_VAR _array)
{
	if (_array.type == NJS::Enum::Type::ARRAY && _index.type == NJS::Enum::Type::NUMBER)
	{

		if (_array.get().a->__NJS_VALUE.size() <= _index.get().i)
		{
			_array.get().a->__NJS_VALUE.reserve(_index.get().i + 1);
			_array.get().a->__NJS_VALUE.resize(_index.get().i + 1);
		}

		_array.get().a->__NJS_VALUE.at(_index.get().i) = _value;

		__NJS_Object_Set("length", (int)_array.get().a->__NJS_VALUE.size(), &_array.get().a->__OBJECT);
		return __NJS_VAR();
	}
	else if (_array.type == NJS::Enum::Type::OBJECT || _array.type == NJS::Enum::Type::STRING || _array.type == NJS::Enum::Type::FUNCTION || _array.type == NJS::Enum::Type::ARRAY || _array.type == NJS::Enum::Type::NATIVE)
	{
		vector<pair<const char *, __NJS_VAR>> *_obj;
		if (_array.type == NJS::Enum::Type::OBJECT)
			_obj = &_array.get().o->__OBJECT;
		else if (_array.type == NJS::Enum::Type::ARRAY)
			_obj = &_array.get().a->__OBJECT;
		else if (_array.type == NJS::Enum::Type::STRING)
			_obj = &_array.get().s->__OBJECT;
		else if (_array.type == NJS::Enum::Type::FUNCTION)
			_obj = &_array.get().f->__OBJECT;
		else
			return __NJS_VAR();

		_index.get().s->cnt++;
		return __NJS_Object_Set(_index.get().s->__NJS_VALUE.c_str(), _value, _obj);
	}

	return __NJS_VAR();
}

__NJS_VAR __NJS_Object_Get(__NJS_VAR _index, __NJS_VAR _array)
{
	if (_array.type != NJS::Enum::Type::ARRAY && _array.type != NJS::Enum::Type::OBJECT && _array.type != NJS::Enum::Type::STRING && _array.type != NJS::Enum::Type::FUNCTION && _array.type != NJS::Enum::Type::NATIVE)
	{
		__NJS_RETURN_UNDEFINED;
	}
	if (_array.type == NJS::Enum::Type::ARRAY && _index.type == NJS::Enum::Type::NUMBER)
	{
		if (_index.get().i > _array.get().a->__NJS_VALUE.size())
		{
			__NJS_RETURN_UNDEFINED;
		}
		return _array.get().a->__NJS_VALUE[_index.get().i];
	}
	else
	{
		if (_index.type != NJS::Enum::Type::STRING)
		{
			__NJS_RETURN_UNDEFINED;
		}
		vector<pair<const char *, __NJS_VAR>> *_obj;
		if (_array.type == NJS::Enum::Type::OBJECT)
			_obj = &_array.get().o->__OBJECT;
		else if (_array.type == NJS::Enum::Type::ARRAY)
			_obj = &_array.get().a->__OBJECT;
		else if (_array.type == NJS::Enum::Type::STRING)
			_obj = &_array.get().s->__OBJECT;
		else if (_array.type == NJS::Enum::Type::FUNCTION)
			_obj = &_array.get().f->__OBJECT;
		else
		{
			__NJS_RETURN_UNDEFINED;
		}
		int _j = (*_obj).size();
		for (int _i = 0; _i < _j; _i++)
		{
			if (strcmp(_index.get().s->__NJS_VALUE.c_str(), (*_obj)[_i].first) == 0)
			{
				return (*_obj)[_i].second;
			}
		}
	}

	__NJS_RETURN_UNDEFINED;
}