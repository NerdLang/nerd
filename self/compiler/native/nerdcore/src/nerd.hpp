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

#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <vector>
#include <memory>
#include <iomanip>
#define _USE_MATH_DEFINES
#include <stdarg.h>
#include <tuple>
#include <bitset>


#ifdef __NERD_ENV_ARDUINO
#include <util/delay.h>
#include <WString.h>
#include <new.h>
#include <time.h>
#include <nonstd-function.h>
#include <string_view>
#include <math.h>
#undef max
#undef min
#include <limits>
#else
#include <functional>
#include <cmath>
#include <limits>
#include <mutex>
#include <chrono>
#include <thread>
#endif

#include "enum.h"
#include "macro.h"

namespace NerdCore
{
	struct VAR;
	
	namespace Class
	{
		class Base;
		class Undefined;
		class Boolean;
		class String;
		class Array;
		class Object;
		class Function;
		class Native;
		class Struct;
		class FixedArray;
		
		
		//template<typename T>
		//class NativeTPL;
	}
} // namespace NerdCore
#include "type_header.h"
#include "var_header.h"
#include "values_header.h"
#include "functions_header.h"
#include "classes_header.h"
#include "native_header.h"
#include "class/number_header.h"
#include "objmgmt_header.h"
#include "operator_header.h"
#include "stdfn_header.h"
