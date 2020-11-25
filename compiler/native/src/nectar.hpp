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

#ifdef __Nectar_ENV_ARDUINO
#include <util/delay.h>
#include <WString.h>
#include <new.h>
#include <time.h>
#include <nonstd-function.h>
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

namespace NectarCore
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
	}
} // namespace NectarCore

#include "var_header.h"
#include "type_header.h"
#include "values_header.h"
#include "functions_header.h"
#include "classes_header.h"
#include "native_header.h"
#include "this_header.h"
#include "class/number_header.h"
#include "objmgmt_header.h"
#include "event_header.h"
#include "operator_header.h"
#include "std_global_js_header.h"
#include "stdfn_header.h"
