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

 #include <iostream>
 #include <string>
 #include <cstring>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <sstream>
 #include <vector>
 #include <memory>


 #include "nerdcore/src/nerd.hpp"
 using namespace NerdCore::Global;
 
 var __NJS_ENV = "std";
 var __NJS_PLATFORM = "{{__PLATFORM__}}";
 NerdCore::Global::var __NERD_ARGS = new NerdCore::Class::Array();
 NerdCore::Global::var _ = new NerdCore::Class::Object();
 NerdCore::Global::var __dirname;
 {INCLUDE}
 

	std::string ToFixed(double number, size_t digits)
	{
		char format[10];
		char str[64];
		sprintf_s(format, "%%0.%zdf", digits);
		return std::string(str, sprintf_s(str, format, number));
	}


int main(int __NERD_VARLENGTH, char* __Nerd_Argv[])
{
	global["__NERD__"] = true;
	std::string argv_str(__Nerd_Argv[0]);
	
	#ifdef _WIN32
		std::string __NERD_DIRNAME = argv_str.substr(0, argv_str.find_last_of("\\"));
	#elif _WIN64
		std::string __NERD_DIRNAME = argv_str.substr(0, argv_str.find_last_of("\\"));
	#else
		std::string __NERD_DIRNAME = argv_str.substr(0, argv_str.find_last_of("/"));
	#endif
	if(__NERD_DIRNAME.size() == argv_str.size())
	{
		__dirname = "";
	}
	else
	{
		__dirname = __NERD_DIRNAME;
	}
	NerdCore::VAR __NERD_VARARGS[__NERD_VARLENGTH];
	for( int i = 0; i < __NERD_VARLENGTH; i++)
	{
		__NERD_ARGS[i] = __Nerd_Argv[i];
		__NERD_VARARGS[i] = __Nerd_Argv[i];
	}
	
	//NerdCore::VAR Object = __NERD_Create_Var_Scoped_Copy_Anon( return __NERD_THIS; );
	//NerdCore::VAR String = __NERD_Create_Var_Scoped_Copy_Anon( return __NERD_THIS; );
	{DECL}
	
	
	Object["prototype"] = new NerdCore::Class::Object();
	Object["prototype"]["valueOf"] = __NERD_Create_Var_Scoped_Copy_Anon({
		return __NERD_THIS;
	});
	
	Object["prototype"]["toString"] = __NERD_Create_Var_Scoped_Copy_Anon({
		return __NERD_THIS;
	});
	
	String["prototype"] = new NerdCore::Class::Object();
	String["prototype"]["__proto__"] = Object["prototype"];
	String["prototype"]["valueOf"] = __NERD_Create_Var_Scoped_Copy_Anon({
		return ((char*)__NERD_OBJECT(__NERD_THIS)->bind);
	});
	String["prototype"]["toString"] = __NERD_Create_Var_Scoped_Copy_Anon({
		return ((char*)__NERD_OBJECT(__NERD_THIS)->bind);
	});
	
	Array["prototype"] = new NerdCore::Class::Object();
	Array["prototype"]["__proto__"] = Object["prototype"];
	Array["prototype"]["indexOf"] = __NERD_Create_Var_Scoped_Copy_Anon({

		if(__NERD_VARLENGTH == 0)
		{
			return -1;
		}
		else
		{
			int i = -1;
			int _max = __NERD_ARRAY(__NERD_THIS)->value.size();
			while(++i < _max)
			{
				if(__NERD_ARRAY(__NERD_THIS)->value[i] == __NERD_VARARGS[0])
				{
					return i;
				}
			}
			return -1;
		}
	});
	Array["prototype"]["push"] = __NERD_Create_Var_Scoped_Copy_Anon({
		
		if(__NERD_VARLENGTH == 0)
		{
			return 0;
		}
		else
		{
			for(int i = 0; i < __NERD_VARLENGTH; i++)
			{
				__NERD_ARRAY(__NERD_THIS)->value.push_back(__NERD_VARARGS[i]);
			}
			return __NERD_VARLENGTH;
		}
	});
	
	Array["isArray"] = __NERD_Create_Var_Scoped_Copy_Anon({
		
		if(__NERD_VARLENGTH == 0)
		{
			return false;
		}
		else
		{
			if(__NERD_VARARGS[0].type == NerdCore::Enum::Type::Array)
			{
				return true;
			}
			return false;
		}
	});

	try 
	{
		{INIT}
		
		#ifdef __NERD_INIT_RAND_SEED
		srand (time(NULL));
		#endif
		
		{
			{CODE}
		}
	}
	catch(NerdCore::VAR __NERD_Global_Exception)
	{
		__NERD_Log_Console(__NERD_Global_Exception);
		exit(1);
	}
	return 0;
}
