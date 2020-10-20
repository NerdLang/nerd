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
#pragma once
#include <emscripten.h>
#include <emscripten/bind.h>

std::vector<std::pair<std::string, __NJS_VAR>> __NJS_INTERNAL_BIND;

function __NJS_WASM_RUN_SCRIPT(_script)
{
	emscripten_run_script(__NJS_Get_String(_script));
}

function __NJS_WASM_BIND(_name, _function)
{
	__NJS_INTERNAL_BIND.push_back(std::make_pair(__NJS_Get_String(_name), _function));
}

std::string __NJS_EM_BIND(std::string _name, std::string _data) 
{
    for (auto it = begin (__NJS_INTERNAL_BIND); it != end (__NJS_INTERNAL_BIND); ++it) 
	{
		if(it->first.compare(_name) == 0)
		{
			return (std::string)(it->second(_data));
			break;
		}
	}
	return "undefined";
}

int __NJS_EM_BIND_INT(std::string _name, int _data) 
{
    for (auto it = begin (__NJS_INTERNAL_BIND); it != end (__NJS_INTERNAL_BIND); ++it) 
	{
		if(it->first.compare(_name) == 0)
		{
			return (int)(it->second(_data));
			break;
		}
	}
	return 0;
}


EMSCRIPTEN_BINDINGS(nectar_module) 
{
    emscripten::function("callNectar", &__NJS_EM_BIND);
	emscripten::function("callNectarInt", &__NJS_EM_BIND_INT);
}
