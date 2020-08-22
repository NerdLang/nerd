#pragma once

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
#include "values.h"
#include "classes.h"

#define __NJS_VAR NJS::VAR
#define var __NJS_VAR
#define let __NJS_VAR
#define __NJS_Create_Ptr_Scoped_Anon(__CONTENT__) new function<__NJS_VAR (vector<VAR>)>([&](vector<VAR> __NJS_VARARGS){ __CONTENT__ })
#define __NJS_Create_Ptr_Unscoped_Anon(__CONTENT__) new function<__NJS_VAR (vector<VAR>)>([](vector<VAR> __NJS_VARARGS){ __CONTENT__ })
#define __NJS_Create_Var_Scoped_Anon(__CONTENT__) __NJS_VAR(NJS::Enum::Type::FUNCTION, __NJS_Create_Ptr_Scoped_Anon(__CONTENT__))
#define __NJS_Create_Var_Unscoped_Anon(__CONTENT__) __NJS_VAR(NJS::Enum::Type::FUNCTION, __NJS_Create_Ptr_Unscoped_Anon(__CONTENT__))

union __NJS_VAL {
	int i;
	double d;
	bool b;
	NJS::Class::String *s;
	NJS::Class::Array *a;
	NJS::Class::Object *o;
	NJS::Class::Function *f;
	NJS::Class::Native *n;
};

/*** REGISTER ***/

/*** END REGISTER ***/
