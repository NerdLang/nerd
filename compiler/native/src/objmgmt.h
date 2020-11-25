int __NJS_Get_Int(NJS::VAR _v)
{
	return (int)_v.data.number;
}

const char *__NJS_Get_String(NJS::VAR _v)
{
	if (_v.type != NJS::Enum::Type::String)
		return "";
	return ((NJS::Class::String*)_v.data.ptr)->value.c_str();
}

const std::string _array[] = {"object", "boolean", "number", "string", "native", "struct", "fixed_array", "array", "object", "function", "NJS::Global::undefined" };
NJS::VAR __NJS_typeof(NJS::VAR _var)
{
	return __NJS_Create_String(_array[_var.type]);
}

NJS::VAR __NJS_instanceof(NJS::VAR _left, NJS::VAR _right)
{
	if(_left.type < NJS::Enum::Type::Object) return __NJS_Boolean_FALSE;
	
	NJS::VAR protoRight = _right["prototype"];
	if(!protoRight) return __NJS_Boolean_FALSE;
	
	NJS::Type::vector_p vLeft = ((NJS::Class::Object*)_left.data.ptr)->instance;
		
	for (auto searchLeft : vLeft)
	{
		if(searchLeft == protoRight.data.ptr) return __NJS_Boolean_TRUE;
	}
	return __NJS_Boolean_FALSE;
}

NJS::VAR __NJS_delete(NJS::VAR _left, std::string _right)
{
	if(_left.type == NJS::Enum::Type::Object)
	{
		((NJS::Class::Object*)_left.data.ptr)->jsDelete(_right);
		return __NJS_Boolean_TRUE;
	}
	else if(_left.type == NJS::Enum::Type::Function)
	{
		((NJS::Class::Function*)_left.data.ptr)->jsDelete(_right);
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
		(*_obj)[_index].data.ptr = _value.data.ptr;
	}
		
	return NJS::Global::undefined;
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
				(*_obj)[_i].second.data.ptr = _value.data.ptr;
			}

			return NJS::Global::undefined;
		}
	}

	(*_obj).push_back(NJS::Type::pair_t(_index, _value));
	return NJS::Global::undefined;
}
#endif
/**/

NJS::VAR __NJS_Object_Set(NJS::VAR _index, NJS::VAR _value, NJS::VAR _array)
{
	if (_array.type == NJS::Enum::Type::Array && _index.type == NJS::Enum::Type::Number)
	{

		if (((NJS::Class::Array*)_array.data.ptr)->value.size() <= (int)_index.data.number)
		{
			((NJS::Class::Array*)_array.data.ptr)->value.resize( (int)_index.data.number + 1);
		}

		((NJS::Class::Array*)_array.data.ptr)->value.at( (int)_index.data.number ) = _value;
		
		return NJS::Global::undefined;
	}
	else if (_array.type == NJS::Enum::Type::Object || _array.type == NJS::Enum::Type::String || _array.type == NJS::Enum::Type::Function || _array.type == NJS::Enum::Type::Array || _array.type == NJS::Enum::Type::Native)
	{
		NJS::Type::object_t *_obj;
		if (_array.type == NJS::Enum::Type::Object)
			_obj = &((NJS::Class::Object*)_array.data.ptr)->object;
		else if (_array.type == NJS::Enum::Type::Array)
			_obj = &((NJS::Class::Array*)_array.data.ptr)->object;
		else if (_array.type == NJS::Enum::Type::String)
			_obj = &((NJS::Class::String*)_array.data.ptr)->object;
		else if (_array.type == NJS::Enum::Type::Function)
			_obj = &((NJS::Class::Function*)_array.data.ptr)->object;
		else
			return NJS::Global::undefined;

		return __NJS_Object_Set((std::string)_index, _value, _obj);
	}

	return NJS::Global::undefined;
}
