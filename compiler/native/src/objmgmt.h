int __NJS_Get_Int(NJS::VAR _v)
{
	return (int)(*(NJS::Class::Number*)_v._ptr);
}

const char *__NJS_Get_String(NJS::VAR _v)
{
	if (_v.type != NJS::Enum::Type::STRING)
		return "";
	return ((NJS::Class::String*)_v._ptr)->value.c_str();
}

NJS::VAR __NJS_Typeof(NJS::VAR _var)
{
	const char *_array[] = {"", "undefined", "number", "object", "boolean", "string", "native", "function", "array", "NaN", "number", "object"};
	return __NJS_Create_String(_array[_var.type]);
}

/*** ***/
NJS::VAR __NJS_Object_Set(const char *_index, NJS::VAR _value, vector<pair<const char *, NJS::VAR>> *_obj)
{
	int _j = (*_obj).size();
	for (int _i = 0; _i < _j; _i++)
	{
		if (strcmp(_index, (*_obj)[_i].first) == 0)
		{

			if (_value.type == NJS::Enum::Type::STRING)
			{
				(*_obj)[_i].second = new NJS::Class::String((string)_value);
			}
			else
			{
				(*_obj)[_i].second._ptr = _value._ptr;
			}

			return NJS::VAR();
		}
	}

	(*_obj).push_back(pair<const char *, NJS::VAR>(_index, _value));
	return NJS::VAR();
}
/**/

NJS::VAR __NJS_Object_Set(NJS::VAR _index, NJS::VAR _value, NJS::VAR _array)
{
	if (_array.type == NJS::Enum::Type::ARRAY && _index.type == NJS::Enum::Type::NUMBER)
	{

		if (((NJS::Class::Array*)_array._ptr)->value.size() <= (int)(*(NJS::Class::Number*)_index._ptr))
		{

			((NJS::Class::Array*)_array._ptr)->value.reserve( (int)(*(NJS::Class::Number*)_index._ptr) + 1);
			((NJS::Class::Array*)_array._ptr)->value.resize( (int)(*(NJS::Class::Number*)_index._ptr) + 1);
		}

		((NJS::Class::Array*)_array._ptr)->value.at( (int)(*(NJS::Class::Number*)_index._ptr) ) = _value;

		__NJS_Object_Set("length", (int)((NJS::Class::Array*)_array._ptr)->value.size(), &((NJS::Class::Array*)_array._ptr)->object);
		
		return NJS::VAR();
	}
	else if (_array.type == NJS::Enum::Type::OBJECT || _array.type == NJS::Enum::Type::STRING || _array.type == NJS::Enum::Type::FUNCTION || _array.type == NJS::Enum::Type::ARRAY || _array.type == NJS::Enum::Type::NATIVE)
	{
		vector<pair<const char *, NJS::VAR>> *_obj;
		if (_array.type == NJS::Enum::Type::OBJECT)
			_obj = &((NJS::Class::Object*)_array._ptr)->object;
		else if (_array.type == NJS::Enum::Type::ARRAY)
			_obj = &((NJS::Class::Array*)_array._ptr)->object;
		else if (_array.type == NJS::Enum::Type::STRING)
			_obj = &((NJS::Class::String*)_array._ptr)->object;
		else if (_array.type == NJS::Enum::Type::FUNCTION)
			_obj = &((NJS::Class::Function*)_array._ptr)->object;
		else
			return NJS::VAR();

		((NJS::Class::String*)_index._ptr)->counter++;
		return __NJS_Object_Set(((NJS::Class::String*)_index._ptr)->value.c_str(), _value, _obj);
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
		if ((bool)(*(NJS::Class::Number*)_index._ptr) > (int)((NJS::Class::Array*)_array._ptr)->value.size())
		{
			__NJS_RETURN_UNDEFINED;
		}
		return ((NJS::Class::Array*)_array._ptr)->value[(int)(*(NJS::Class::Number*)_index._ptr)];
	}
	else
	{
		if (_index.type != NJS::Enum::Type::STRING)
		{
			__NJS_RETURN_UNDEFINED;
		}
		vector<pair<const char *, NJS::VAR>> *_obj;
		if (_array.type == NJS::Enum::Type::OBJECT)
			_obj = &((NJS::Class::Object*)_array._ptr)->object;
		else if (_array.type == NJS::Enum::Type::ARRAY)
			_obj = &((NJS::Class::Array*)_array._ptr)->object;
		else if (_array.type == NJS::Enum::Type::STRING)
			_obj = &((NJS::Class::String*)_array._ptr)->object;
		else if (_array.type == NJS::Enum::Type::FUNCTION)
			_obj = &((NJS::Class::Function*)_array._ptr)->object;
		else
		{
			__NJS_RETURN_UNDEFINED;
		}
		int _j = (*_obj).size();
		for (int _i = 0; _i < _j; _i++)
		{
			if (strcmp(((NJS::Class::String*)_index._ptr)->value.c_str(), (*_obj)[_i].first) == 0)
			{
				return (*_obj)[_i].second;
			}
		}
	}

	__NJS_RETURN_UNDEFINED;
}