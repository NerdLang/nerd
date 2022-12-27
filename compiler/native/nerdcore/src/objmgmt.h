/*
	Copyright (c) 2021 NerdLang - Adrien THIERRY and contributors

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

*/

NerdCore::VAR __NERD_delete(NerdCore::VAR _left, NerdCore::VAR _right)
{
	if(_left.type == NerdCore::Enum::Type::Object)
	{
		((NerdCore::Class::Object*)_left.data.ptr)->jsDelete(_right);
		return __NERD_Boolean_TRUE;
	}
	else if(_left.type == NerdCore::Enum::Type::Array)
	{
		((NerdCore::Class::Array*)_left.data.ptr)->jsDelete(_right);
		return __NERD_Boolean_TRUE;
	}
	else if(_left.type == NerdCore::Enum::Type::Function)
	{
		((NerdCore::Class::Function*)_left.data.ptr)->jsDelete(_right);
		return __NERD_Boolean_TRUE;
	}
	return __NERD_Boolean_FALSE;
}

/*** ***/
#ifndef __NERD__OBJECT_VECTOR
NerdCore::VAR __NERD_Object_Set(std::string _index, NerdCore::VAR _value, NerdCore::Type::object_t *_obj)
{
	
	if (_value.type == NerdCore::Enum::Type::String)
	{
		(*_obj)[_index] = new NerdCore::Class::String((std::string)_value);
	}
	else
	{
		(*_obj)[_index].data.ptr = _value.data.ptr;
	}
		
	return NerdCore::Global::null;
}
#else
NerdCore::VAR __NERD_Object_Set(std::string _index, NerdCore::VAR _value, NerdCore::Type::object_t *_obj)
{
	int _j = (*_obj).size();
	for (int _i = 0; _i < _j; _i++)
	{
		if (_index.compare((*_obj)[_i].first) == 0)
		{

			if (_value.type == NerdCore::Enum::Type::String)
			{
				(*_obj)[_i].second = new NerdCore::Class::String((std::string)_value);
			}
			else
			{
				(*_obj)[_i].second.data.ptr = _value.data.ptr;
			}

			return NerdCore::Global::null;
		}
	}

	(*_obj).push_back(NerdCore::Type::pair_t(_index, _value));
	return NerdCore::Global::null;
}
#endif
/**/

NerdCore::VAR __NERD_Object_Set(NerdCore::VAR _index, NerdCore::VAR _value, NerdCore::VAR _array)
{
	if (_array.type == NerdCore::Enum::Type::Array && _index.type == NerdCore::Enum::Type::Number)
	{

		if (((NerdCore::Class::Array*)_array.data.ptr)->value.size() <= (int)_index.data.number)
		{
			((NerdCore::Class::Array*)_array.data.ptr)->value.resize( (int)_index.data.number + 1);
		}

		((NerdCore::Class::Array*)_array.data.ptr)->value.at( (int)_index.data.number ) = _value;
		
		return NerdCore::Global::null;
	}
	else if (_array.type == NerdCore::Enum::Type::Object || _array.type == NerdCore::Enum::Type::String || _array.type == NerdCore::Enum::Type::Function || _array.type == NerdCore::Enum::Type::Array || _array.type == NerdCore::Enum::Type::Native)
	{
		NerdCore::Type::object_t *_obj;
		if (_array.type == NerdCore::Enum::Type::Object)
			_obj = &((NerdCore::Class::Object*)_array.data.ptr)->object;
		else
			return NerdCore::Global::null;

		return __NERD_Object_Set((std::string)_index, _value, _obj);
	}

	return NerdCore::Global::null;
}



/* typeof */
const std::string _array[] = {"null", "boolean", "number", "string", "native", "native", "struct", "fixed_array", "array", "object", "function" };
std::string type_of(NerdCore::Global::var _var)
{
	return _array[_var.type];
}
std::string typeof(NerdCore::Global::var _var)
{
	return _array[_var.type];
}