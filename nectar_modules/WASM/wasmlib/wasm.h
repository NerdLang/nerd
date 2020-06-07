#include <emscripten.h>
#include <emscripten/bind.h>

vector<pair<string, __NJS_VAR>> __NJS_INTERNAL_BIND;

function __NJS_WASM_RUN_SCRIPT(_script)
{
	emscripten_run_script(__NJS_Get_String(_script));
}

function __NJS_WASM_BIND(_name, _function)
{
	__NJS_INTERNAL_BIND.push_back(std::make_pair(__NJS_Get_String(_name), _function));
}

string __NJS_EM_BIND(string _name, string _data) 
{
    for (auto it = begin (__NJS_INTERNAL_BIND); it != end (__NJS_INTERNAL_BIND); ++it) 
	{
		if(it->first.compare(_name) == 0)
		{
			return __NJS_Get_String(__NJS_Call_Function(it->second, _data));
			break;
		}
	}
	return "undefined";
}


EMSCRIPTEN_BINDINGS(nectar_module) 
{
    emscripten::function("callNectar", &__NJS_EM_BIND);
}
