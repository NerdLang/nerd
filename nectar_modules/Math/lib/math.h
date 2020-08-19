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
 
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>

using namespace std;

var __NJS_MATH_E = __NJS_VAR(M_E);
var __NJS_MATH_LN2 = __NJS_VAR(M_LN2);
var __NJS_MATH_LOG2E = __NJS_VAR(M_LOG2E);
var __NJS_MATH_LOG10E = __NJS_VAR(M_LOG10E);
var __NJS_MATH_PI = __NJS_VAR(M_PI);
var __NJS_MATH_SQRT1_2 = __NJS_VAR(M_SQRT1_2);
var __NJS_MATH_SQRT2 = __NJS_VAR(M_SQRT2);

function __NJS_MATH_ABS(x) 
{ 
	return __NJS_VAR(abs(static_cast<double>(x))); 
};

function __NJS_MATH_ACOS(x) 
{ 
	return __NJS_VAR(acos(static_cast<double>(x))); 
};

function __NJS_MATH_ACOSH(x)
{ 
	return __NJS_VAR(acosh(static_cast<double>(x))); 
};

function __NJS_MATH_ASIN(x) 
{ 
	return __NJS_VAR(asin(static_cast<double>(x))); 
};

function __NJS_MATH_ASINH(x) 
{
	return __NJS_VAR(asinh(static_cast<double>(x))); 
};
function __NJS_MATH_ATAN(x) 
{ 
	return __NJS_VAR(atan(static_cast<double>(x))); 
};
function __NJS_MATH_ATAN2(x, y) 
{ 
	return __NJS_VAR(atan2(static_cast<double>(x), static_cast<double>(y))); 
};
function __NJS_MATH_ATANH(x) 
{ 
	return __NJS_VAR(atanh(static_cast<double>(x))); 
};
function __NJS_MATH_CBRT(x) 
{ 
	return __NJS_VAR(cbrt(static_cast<double>(x))); 
};
function __NJS_MATH_CEIL(x) 
{ 
	return __NJS_VAR(ceil(static_cast<double>(x))); 
};

function __NJS_MATH_CLZ32(x) 
{
	int n = static_cast<int>(x);
    return __NJS_VAR(n > 0 ? (int)(31 - log2(n >> 0)) : 32);
};

function __NJS_MATH_COS(x) 
{ 
	return __NJS_VAR(cos(static_cast<double>(x))); 
};

function __NJS_MATH_COSH(x) 
{ 
	return __NJS_VAR(cosh(static_cast<double>(x))); 
};

function __NJS_MATH_EXP(x) 
{ 
	return __NJS_VAR(exp(static_cast<double>(x))); 
};

function __NJS_MATH_EXPM1(x) 
{ 
	return __NJS_VAR(expm1(static_cast<double>(x))); 
};

function __NJS_MATH_FLOOR(x) 
{ 
	return __NJS_VAR(static_cast<int>(floor(static_cast<double>(x))));
};

function __NJS_MATH_FROUND(x) 
{ 
	return __NJS_VAR(static_cast<double>(static_cast<double>(x))); 
};

__NJS_DECL_FUNCTION<__NJS_VAR (vector<var> __NJS_VARARGS)>* __NJS_MATH_NATIVE_HYPOT = new __NJS_DECL_FUNCTION<__NJS_VAR (vector<var> __NJS_VARARGS)>([]( vector<var> __NJS_VARARGS ) -> __NJS_VAR 
{
	double max = 0;
	double s = 0;
	for (var arg : __NJS_VARARGS) {
		double x = abs(static_cast<double>(arg));
		if (x > max) {
			s *= (max / x) * (max / x);
			max = x;
		}
		s += (x == 0 && max == 0) ? 0 : (x / max) * (x / max);
	}
	return __NJS_VAR(max == INFINITY ? INFINITY : max * sqrt(s));
});
var __NJS_MATH_HYPOT = __NJS_Create_Function(__NJS_MATH_NATIVE_HYPOT);

function __NJS_MATH_IMUL(x, y)
{
	return __NJS_VAR(static_cast<int>(x) * static_cast<int>(y));
};

function __NJS_MATH_LOG(x) 
{ 
	return __NJS_VAR(log(static_cast<double>(x))); 
};

function __NJS_MATH_LOG1P(x) 
{ 
	return __NJS_VAR(log1p(static_cast<double>(x))); 
};

function __NJS_MATH_LOG2(x) 
{ 
	return __NJS_VAR(log2(static_cast<double>(x))); 
};

function __NJS_MATH_LOG10(x) 
{ 
	return __NJS_VAR(log10(static_cast<double>(x))); 
};

__NJS_DECL_FUNCTION<__NJS_VAR (vector<var> __NJS_VARARGS)>* __NJS_MATH_NATIVE_MAX = new __NJS_DECL_FUNCTION<__NJS_VAR (vector<var> __NJS_VARARGS)>([]( vector<var> __NJS_VARARGS ) -> __NJS_VAR 
{
	double max = -INFINITY;
	for (var x : __NJS_VARARGS) {
		double n = static_cast<double>(x);
		if (n > max) {
			max = n;
		}
	}
	return __NJS_VAR(max);
});
var __NJS_MATH_MAX = __NJS_Create_Function(__NJS_MATH_NATIVE_MAX);

__NJS_DECL_FUNCTION<__NJS_VAR (vector<var> __NJS_VARARGS)>* __NJS_MATH_NATIVE_MIN = new __NJS_DECL_FUNCTION<__NJS_VAR (vector<var> __NJS_VARARGS)>([]( vector<var> __NJS_VARARGS ) -> __NJS_VAR 
{
	double min = INFINITY;
	for (var x : __NJS_VARARGS) {
		double n = static_cast<double>(x);
		if (n < min) {
			min = n;
		}
	}
	return __NJS_VAR(min);
});
var __NJS_MATH_MIN = __NJS_Create_Function(__NJS_MATH_NATIVE_MIN);

function __NJS_MATH_POW(x, x2) 
{ 
	return __NJS_VAR(pow(static_cast<double>(x), static_cast<double>(x2))); 
};

function __NJS_MATH_RANDOM() 
{ 
	return __NJS_VAR(static_cast<double>(rand()) / static_cast<double>(RAND_MAX));
};

function __NJS_MATH_ROUND(x) 
{ 
	return __NJS_VAR(static_cast<int>(round(static_cast<double>(x))));
};

function __NJS_MATH_SIGN(x) 
{
	double n = static_cast<double>(x);
	if (n == 0) { return __NJS_VAR(0); }
	else { return __NJS_VAR(n > 0 ? 1 : -1); };
};

function __NJS_MATH_SIN(x) 
{ 
	return __NJS_VAR(sin(static_cast<double>(x))); 
};

function __NJS_MATH_SINH(x) 
{ 
	return __NJS_VAR(sinh(static_cast<double>(x))); 
};

function __NJS_MATH_SQRT(x) 
{ 
	return __NJS_VAR(sqrt(static_cast<double>(x))); 
};

function __NJS_MATH_TAN(x) 
{ 
	return __NJS_VAR(tan(static_cast<double>(x))); 
};

function __NJS_MATH_TANH(x) 
{ 
	return __NJS_VAR(tanh(static_cast<double>(x))); 
};

function __NJS_MATH_TRUNC(x) 
{ 
	return __NJS_VAR(static_cast<int>(x)); 
};
