int __NJS_Get_Int(NJS::VAR _v)
{
	return (int)(*(NJS::Class::Number*)_v._ptr);
}

const char *__NJS_Get_String(NJS::VAR _v)
{
	if (_v.type != NJS::Enum::Type::String)
		return "";
	return ((NJS::Class::String*)_v._ptr)->value.c_str();
}

NJS::VAR __NJS_typeof(NJS::VAR _var)
{
	const char *_array[] = {"", "undefined", "number", "object", "boolean", "string", "native", "function", "array", "NaN", "number", "object"};
	return __NJS_Create_String(_array[_var.type]);
}

NJS::VAR __NJS_instanceof(NJS::VAR _left, NJS::VAR _right)
{
	if(_left.type != NJS::Enum::Type::Object || _right.type != NJS::Enum::Type::Function) return __NJS_Boolean_FALSE;
	
	var protoRight = _right["prototype"];
	if(!protoRight) return __NJS_Boolean_FALSE;
	
	NJS::Type::vector_p vLeft = ((NJS::Class::Object*)_left._ptr)->instance;
		
	for (auto searchLeft : vLeft)
	{
		if(searchLeft == protoRight._ptr) return __NJS_Boolean_TRUE;
	}
	return __NJS_Boolean_FALSE;
}

NJS::VAR __NJS_delete(NJS::VAR _left, std::string _right)
{
	if(_left.type == NJS::Enum::Type::Object)
	{
		((NJS::Class::Object*)_left._ptr)->jsDelete(_right);
		return __NJS_Boolean_TRUE;
	}
	else if(_left.type == NJS::Enum::Type::Function)
	{
		((NJS::Class::Function*)_left._ptr)->jsDelete(_right);
		return __NJS_Boolean_TRUE;
	}
	return __NJS_Boolean_FALSE;
}

/*** ***/
#ifdef __NJS__OBJECT_HASHMAP
NJS::VAR __NJS_Object_Set(std::string _index, NJS::VAR _value, NJS::Type::object_t *_obj)
{
	
	if (_value.type == NJS::Enum::Type::String)
	{
		(*_obj)[_index] = new NJS::Class::String((std::string)_value);
	}
	else
	{
		(*_obj)[_index]._ptr = _value._ptr;
	}
		
	return undefined;
}
#else
NJS::VAR __NJS_Object_Set(std::string _index, NJS::VAR _value, NJS::Type::object_t *_obj)
{
	int _j = (*_obj).size();
	for (int _i = 0; _i < _j; _i++)
	{
		if (_index.compare((*_obj)[_i].first) == 0)
		{

			if (_value.type == NJS::Enum::Type::String)
			{
				(*_obj)[_i].second = new NJS::Class::String((std::string)_value);
			}
			else
			{
				(*_obj)[_i].second._ptr = _value._ptr;
			}

			return undefined;
		}
	}

	(*_obj).push_back(NJS::Type::pair_t(_index, _value));
	return undefined;
}
#endif
/**/

NJS::VAR __NJS_Object_Set(NJS::VAR _index, NJS::VAR _value, NJS::VAR _array)
{
	if (_array.type == NJS::Enum::Type::Array && _index.type == NJS::Enum::Type::Number)
	{

		if (((NJS::Class::Array*)_array._ptr)->value.size() <= (int)(*(NJS::Class::Number*)_index._ptr))
		{

			((NJS::Class::Array*)_array._ptr)->value.reserve( (int)(*(NJS::Class::Number*)_index._ptr) + 1);
			((NJS::Class::Array*)_array._ptr)->value.resize( (int)(*(NJS::Class::Number*)_index._ptr) + 1);
		}

		((NJS::Class::Array*)_array._ptr)->value.at( (int)(*(NJS::Class::Number*)_index._ptr) ) = _value;
		
		return undefined;
	}
	else if (_array.type == NJS::Enum::Type::Object || _array.type == NJS::Enum::Type::String || _array.type == NJS::Enum::Type::Function || _array.type == NJS::Enum::Type::Array || _array.type == NJS::Enum::Type::Native)
	{
		NJS::Type::object_t *_obj;
		if (_array.type == NJS::Enum::Type::Object)
			_obj = &((NJS::Class::Object*)_array._ptr)->object;
		else if (_array.type == NJS::Enum::Type::Array)
			_obj = &((NJS::Class::Array*)_array._ptr)->object;
		else if (_array.type == NJS::Enum::Type::String)
			_obj = &((NJS::Class::String*)_array._ptr)->object;
		else if (_array.type == NJS::Enum::Type::Function)
			_obj = &((NJS::Class::Function*)_array._ptr)->object;
		else
			return undefined;

		return __NJS_Object_Set((std::string)_index, _value, _obj);
	}

	return undefined;
}
