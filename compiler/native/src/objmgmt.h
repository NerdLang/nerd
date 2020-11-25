/*
 * This file is part of NectarCPP
 * Copyright (c) 2020 - 2020 Adrien THIERRY
 * https://nectar-lang.org - https://seraum.com/
 *
 * sources : https://github.com/nectar-lang/NectarCPP
 * 
 * NectarCPP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NectarCPP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NectarCPP.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
 
int __Nectar_Get_Int(Nectar::VAR _v)
{
	return (int)_v.data.number;
}

const char *__Nectar_Get_String(Nectar::VAR _v)
{
	if (_v.type != Nectar::Enum::Type::String)
		return "";
	return ((Nectar::Class::String*)_v.data.ptr)->value.c_str();
}

const std::string _array[] = {"object", "boolean", "number", "string", "native", "struct", "fixed_array", "array", "object", "function", "Nectar::Global::undefined" };
Nectar::VAR __Nectar_typeof(Nectar::VAR _var)
{
	return __Nectar_Create_String(_array[_var.type]);
}

Nectar::VAR __Nectar_instanceof(Nectar::VAR _left, Nectar::VAR _right)
{
	if(_left.type < Nectar::Enum::Type::Object) return __Nectar_Boolean_FALSE;
	
	Nectar::VAR protoRight = _right["prototype"];
	if(!protoRight) return __Nectar_Boolean_FALSE;
	
	Nectar::Type::vector_p vLeft = ((Nectar::Class::Object*)_left.data.ptr)->instance;
		
	for (auto searchLeft : vLeft)
	{
		if(searchLeft == protoRight.data.ptr) return __Nectar_Boolean_TRUE;
	}
	return __Nectar_Boolean_FALSE;
}

Nectar::VAR __Nectar_delete(Nectar::VAR _left, std::string _right)
{
	if(_left.type == Nectar::Enum::Type::Object)
	{
		((Nectar::Class::Object*)_left.data.ptr)->jsDelete(_right);
		return __Nectar_Boolean_TRUE;
	}
	else if(_left.type == Nectar::Enum::Type::Function)
	{
		((Nectar::Class::Function*)_left.data.ptr)->jsDelete(_right);
		return __Nectar_Boolean_TRUE;
	}
	return __Nectar_Boolean_FALSE;
}

/*** ***/
#ifndef __Nectar__OBJECT_VECTOR
Nectar::VAR __Nectar_Object_Set(std::string _index, Nectar::VAR _value, Nectar::Type::object_t *_obj)
{
	
	if (_value.type == Nectar::Enum::Type::String)
	{
		(*_obj)[_index] = new Nectar::Class::String((std::string)_value);
	}
	else
	{
		(*_obj)[_index].data.ptr = _value.data.ptr;
	}
		
	return Nectar::Global::undefined;
}
#else
Nectar::VAR __Nectar_Object_Set(std::string _index, Nectar::VAR _value, Nectar::Type::object_t *_obj)
{
	int _j = (*_obj).size();
	for (int _i = 0; _i < _j; _i++)
	{
		if (_index.compare((*_obj)[_i].first) == 0)
		{

			if (_value.type == Nectar::Enum::Type::String)
			{
				(*_obj)[_i].second = new Nectar::Class::String((std::string)_value);
			}
			else
			{
				(*_obj)[_i].second.data.ptr = _value.data.ptr;
			}

			return Nectar::Global::undefined;
		}
	}

	(*_obj).push_back(Nectar::Type::pair_t(_index, _value));
	return Nectar::Global::undefined;
}
#endif
/**/

Nectar::VAR __Nectar_Object_Set(Nectar::VAR _index, Nectar::VAR _value, Nectar::VAR _array)
{
	if (_array.type == Nectar::Enum::Type::Array && _index.type == Nectar::Enum::Type::Number)
	{

		if (((Nectar::Class::Array*)_array.data.ptr)->value.size() <= (int)_index.data.number)
		{
			((Nectar::Class::Array*)_array.data.ptr)->value.resize( (int)_index.data.number + 1);
		}

		((Nectar::Class::Array*)_array.data.ptr)->value.at( (int)_index.data.number ) = _value;
		
		return Nectar::Global::undefined;
	}
	else if (_array.type == Nectar::Enum::Type::Object || _array.type == Nectar::Enum::Type::String || _array.type == Nectar::Enum::Type::Function || _array.type == Nectar::Enum::Type::Array || _array.type == Nectar::Enum::Type::Native)
	{
		Nectar::Type::object_t *_obj;
		if (_array.type == Nectar::Enum::Type::Object)
			_obj = &((Nectar::Class::Object*)_array.data.ptr)->object;
		else if (_array.type == Nectar::Enum::Type::Array)
			_obj = &((Nectar::Class::Array*)_array.data.ptr)->object;
		else if (_array.type == Nectar::Enum::Type::String)
			_obj = &((Nectar::Class::String*)_array.data.ptr)->object;
		else if (_array.type == Nectar::Enum::Type::Function)
			_obj = &((Nectar::Class::Function*)_array.data.ptr)->object;
		else
			return Nectar::Global::undefined;

		return __Nectar_Object_Set((std::string)_index, _value, _obj);
	}

	return Nectar::Global::undefined;
}
