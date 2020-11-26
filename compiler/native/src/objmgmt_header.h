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
 
int __Nectar_Get_Int(NectarCore::VAR _v);
const char *__Nectar_Get_String(NectarCore::VAR _v);
extern const std::string _array[11];
NectarCore::VAR __Nectar_typeof(NectarCore::VAR _var);
NectarCore::VAR __Nectar_instanceof(NectarCore::VAR _left, NectarCore::VAR _right);
NectarCore::VAR __Nectar_delete(NectarCore::VAR _left, NectarCore::VAR _right);
NectarCore::VAR __Nectar_Object_Set(std::string _index, NectarCore::VAR _value, NectarCore::Type::object_t *_obj);
NectarCore::VAR __Nectar_Object_Set(NectarCore::VAR _index, NectarCore::VAR _value, NectarCore::VAR _array);
