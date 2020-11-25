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
 #define __NJS_ENV_NODE
 #include "uv.h"
 #include "nectar.hpp"
 
 using namespace NectarCore::Global;
 using namespace NectarCore::Functions;
 
 var __NJS_ENV = "node";
 var __NJS_PLATFORM = "{{__PLATFORM__}}"; 
 #define __NJS_Create_Object() new NectarCore::Class::Object()
 #define __NJS_Create_Array(_arr) new NectarCore::Class::Array(_arr)
 #define __NJS_InitVar() NectarCore::VAR()
 
 uv_loop_t *__NJS_UV_DEFAULT_LOOP = (uv_loop_t *)malloc(sizeof(uv_loop_t));
 
 {INCLUDE}
 
 {DECL}

int main(int argc, char* argv[])
{
	uv_loop_init(__NJS_UV_DEFAULT_LOOP);
	var __NJS_ARGS = __NJS_Create_Array();
	for( int i = 0; i < argc; i++)
	{
		__NJS_ARGS[i] = argv[i];
	}

	{INIT}

	{
		{CODE};
	}
	
    uv_run(__NJS_UV_DEFAULT_LOOP, UV_RUN_DEFAULT);

    uv_loop_close(__NJS_UV_DEFAULT_LOOP);
    free(__NJS_UV_DEFAULT_LOOP);
    return 0;
	
	return 0;
}
