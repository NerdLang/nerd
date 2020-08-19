/*
 * This file is part of NectarJS
 * Copyright (c) 2017 - 2020 Adrien THIERRY
 * http://nectarjs.com - https://seraum.com/
 *
 * sources : https://github.com/nectarjs/nectarjs
 * 
 * NectarJS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NectarJS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NectarJS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
 
__NJS_DECL_FUNCTION<__NJS_VAR (vector<var> __NJS_VARARGS)>* __NJS_FN_NATIVE_LOG_CONSOLE = new __NJS_DECL_FUNCTION<__NJS_VAR (vector<var> __NJS_VARARGS)>([]( vector<var> __NJS_VARARGS ) -> __NJS_VAR 
{
	if(__NJS_VARARGS.size() == 0) __NJS_Log_Console("");
	else __NJS_Log_Console(__NJS_VARARGS[0]);
	return var();
});

var __NJS_NATIVE_LOG_CONSOLE = __NJS_Create_Function(__NJS_FN_NATIVE_LOG_CONSOLE);
