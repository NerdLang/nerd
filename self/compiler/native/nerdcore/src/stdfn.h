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

namespace NerdCore::Functions
{
	NerdCore::VAR println()
	{
		#ifndef __NERD_ENV_ARDUINO
		std::cout << std::endl;
		#endif
		return NerdCore::Global::null;
	}
	NerdCore::VAR println(NerdCore::VAR _var)
	{
		#ifndef __NERD_ENV_ARDUINO
		std::cout << _var << std::endl;
		#endif
		return NerdCore::Global::null;
	}
	
	NerdCore::VAR print()
	{
		return NerdCore::Global::null;
	}
	
	NerdCore::VAR print(NerdCore::VAR _var)
	{
		#ifndef __NERD_ENV_ARDUINO
		std::cout << _var;
		#endif
		return NerdCore::Global::null;
	}
	
	
}

	// no namespace
	NerdCore::VAR length_of(NerdCore::VAR _var)
	{
		switch( _var.type)
		{
			case NerdCore::Enum::Type::Null:
				return 0;
			break;
			case NerdCore::Enum::Type::Boolean:
				return 1;
			break;
			case NerdCore::Enum::Type::Number:
				return 1;
			break;
			case NerdCore::Enum::Type::String:
				return (double)((std::string)_var).size();
			break;
			case NerdCore::Enum::Type::Array:
				return (double)((NerdCore::Class::Array*)_var.data.ptr)->Size();
			break;
			case NerdCore::Enum::Type::FixedArray:
				return (double)((NerdCore::Class::FixedArray*)_var.data.ptr)->length;
			break;
			case NerdCore::Enum::Type::Object:
				return (double)((NerdCore::Class::Object*)_var.data.ptr)->Size();
			break;
			case NerdCore::Enum::Type::Native:
				return (double)((NerdCore::Class::Native*)_var.data.ptr)->length;
			break;
			default:
				return 0;
			break;
		}
		return 0;
	}

	NerdCore::VAR size_of(NerdCore::VAR _var)
	{
		return (double)sizeof(_var);
	}