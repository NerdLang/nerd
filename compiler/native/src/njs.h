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
 
#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <memory>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdarg.h>

#ifdef __NJS_ARDUINO
#include <util/delay.h>
#include <string.h>
#include <WString.h>
#include <new.h>
#include <time.h>
#include <nonstd-function.h>
using namespace nonstd;
#else
#include <functional>
#endif

#include "enum.h"

using namespace std;
using namespace NJS;


#include "macro.h"

struct __NJS_VAR;

#include "class.h"

#include "memory.h"

#include "functions.h"

#include "var.h"

namespace NECTAR
{
	__NJS_VAR null = __NJS_Create_Null();
	__NJS_VAR undefined = __NJS_VAR();
} // namespace NECTAR


#include "objmgmt.h"

#include "class/object.h"
#include "class/string.h"
#include "class/array.h"
#include "class/function.h"
#include "class/native.h"

#include "operator.h"
