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
 
int __Nectar_Get_Int(Nectar::VAR _v);
const char *__Nectar_Get_String(Nectar::VAR _v);
extern const std::string _array[11];
Nectar::VAR __Nectar_typeof(Nectar::VAR _var);
Nectar::VAR __Nectar_instanceof(Nectar::VAR _left, Nectar::VAR _right);
Nectar::VAR __Nectar_delete(Nectar::VAR _left, std::string _right);
Nectar::VAR __Nectar_Object_Set(std::string _index, Nectar::VAR _value, Nectar::Type::object_t *_obj);
Nectar::VAR __Nectar_Object_Set(Nectar::VAR _index, Nectar::VAR _value, Nectar::VAR _array);
