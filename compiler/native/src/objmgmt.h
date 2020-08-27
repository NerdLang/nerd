NJS::VAR __create_Array()
{
	NJS::Class::Array *_a = new NJS::Class::Array();
	return NJS::VAR(NJS::Enum::Type::ARRAY, _a);
}

NJS::VAR __NJS_Create_Array()
{
	NJS::Class::Array *_a = new NJS::Class::Array();
	return NJS::VAR(_a);
}

int __NJS_Get_Int(NJS::VAR _v)
{
	return _v.get().i;
}

const char *__NJS_Get_String(NJS::VAR _v)
{
	if (_v.type != NJS::Enum::Type::STRING)
		return "";
	return _v.get().s->value.c_str();
}

NJS::VAR __NJS_Typeof(NJS::VAR _var)
{
	const char *_array[] = {"", "undefined", "number", "number", "object", "number", "boolean", "string", "native", "function", "array", "NaN", "number", "object"};
	return __NJS_Create_String(_array[_var.type]);
}

/*** ***/
NJS::VAR __NJS_Object_Set(const char *_index, NJS::VAR _value, vector<pair<const char *, NJS::VAR>> *_obj)
{
	//std::cout << _index << endl;
	int _j = (*_obj).size();
	for (int _i = 0; _i < _j; _i++)
	{
		if (strcmp(_index, (*_obj)[_i].first) == 0)
		{

			if (_value.type == NJS::Enum::Type::STRING)
			{
				NJS::MEMORY::REGISTER[(*_obj)[_i].second._ptr].s = new NJS::Class::String((string)_value);
			}
			else
				NJS::MEMORY::REGISTER[(*_obj)[_i].second._ptr] = NJS::MEMORY::REGISTER[_value._ptr];

			return NJS::VAR();
		}
	}

	(*_obj).push_back(pair<const char *, NJS::VAR>(_index, _value));
	return NJS::VAR();
}
/**/

NJS::VAR __NJS_Object_Set(NJS::VAR _index, NJS::VAR _value, NJS::VAR _array)
{
	//cout << "SECOND" << endl;
	if (_array.type == NJS::Enum::Type::ARRAY && _index.type == NJS::Enum::Type::NUMBER)
	{

		if (_array.get().a->value.size() <= _index.get().i)
		{
			_array.get().a->value.reserve(_index.get().i + 1);
			_array.get().a->value.resize(_index.get().i + 1);
		}

		_array.get().a->value.at(_index.get().i) = _value;

		__NJS_Object_Set("length", (int)_array.get().a->value.size(), &_array.get().a->object);
		return NJS::VAR();
	}
	else if (_array.type == NJS::Enum::Type::OBJECT || _array.type == NJS::Enum::Type::STRING || _array.type == NJS::Enum::Type::FUNCTION || _array.type == NJS::Enum::Type::ARRAY || _array.type == NJS::Enum::Type::NATIVE)
	{
		vector<pair<const char *, NJS::VAR>> *_obj;
		if (_array.type == NJS::Enum::Type::OBJECT)
			_obj = &_array.get().o->object;
		else if (_array.type == NJS::Enum::Type::ARRAY)
			_obj = &_array.get().a->object;
		else if (_array.type == NJS::Enum::Type::STRING)
			_obj = &_array.get().s->object;
		else if (_array.type == NJS::Enum::Type::FUNCTION)
			_obj = &_array.get().f->object;
		else
			return NJS::VAR();

		_index.get().s->cnt++;
		return __NJS_Object_Set(_index.get().s->value.c_str(), _value, _obj);
	}

	return NJS::VAR();
}

NJS::VAR __NJS_Object_Get(NJS::VAR _index, NJS::VAR _array)
{
	if (_array.type != NJS::Enum::Type::ARRAY && _array.type != NJS::Enum::Type::OBJECT && _array.type != NJS::Enum::Type::STRING && _array.type != NJS::Enum::Type::FUNCTION && _array.type != NJS::Enum::Type::NATIVE)
	{
		__NJS_RETURN_UNDEFINED;
	}
	if (_array.type == NJS::Enum::Type::ARRAY && _index.type == NJS::Enum::Type::NUMBER)
	{
		if (_index.get().i > _array.get().a->value.size())
		{
			__NJS_RETURN_UNDEFINED;
		}
		return _array.get().a->value[_index.get().i];
	}
	else
	{
		if (_index.type != NJS::Enum::Type::STRING)
		{
			__NJS_RETURN_UNDEFINED;
		}
		vector<pair<const char *, NJS::VAR>> *_obj;
		if (_array.type == NJS::Enum::Type::OBJECT)
			_obj = &_array.get().o->object;
		else if (_array.type == NJS::Enum::Type::ARRAY)
			_obj = &_array.get().a->object;
		else if (_array.type == NJS::Enum::Type::STRING)
			_obj = &_array.get().s->object;
		else if (_array.type == NJS::Enum::Type::FUNCTION)
			_obj = &_array.get().f->object;
		else
		{
			__NJS_RETURN_UNDEFINED;
		}
		int _j = (*_obj).size();
		for (int _i = 0; _i < _j; _i++)
		{
			if (strcmp(_index.get().s->value.c_str(), (*_obj)[_i].first) == 0)
			{
				return (*_obj)[_i].second;
			}
		}
	}

	__NJS_RETURN_UNDEFINED;
}