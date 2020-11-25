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
#define __Nectar_INIT_RAND_SEED
#if defined(_USE_MATH_DEFINES) && !defined(M_E)
#define _MATH_DEFINES_DEFINED

/* Define _USE_MATH_DEFINES before including math.h to expose these macro
 * definitions for common math constants.  These are placed under an #ifdef
 * since these commonly-defined names are not part of the C/C++ standards.
 */

/* Definitions of useful mathematical constants
 * M_E        - e
 * M_LOG2E    - log2(e)
 * M_LOG10E   - log10(e)
 * M_LN2      - ln(2)
 * M_LN10     - ln(10)
 * M_PI       - pi
 * M_PI_2     - pi/2
 * M_PI_4     - pi/4
 * M_1_PI     - 1/pi
 * M_2_PI     - 2/pi
 * M_2_SQRTPI - 2/sqrt(pi)
 * M_SQRT2    - sqrt(2)
 * M_SQRT1_2  - 1/sqrt(2)
 */

#define M_E        2.71828182845904523536
#define M_LOG2E    1.44269504088896340736
#define M_LOG10E   0.434294481903251827651
#define M_LN2      0.693147180559945309417
#define M_LN10     2.30258509299404568402
#define M_PI       3.14159265358979323846
#define M_PI_2     1.57079632679489661923
#define M_PI_4     0.785398163397448309616
#define M_1_PI     0.318309886183790671538
#define M_2_PI     0.636619772367581343076
#define M_2_SQRTPI 1.12837916709551257390
#define M_SQRT2    1.41421356237309504880
#define M_SQRT1_2  0.707106781186547524401

#endif  /* _USE_MATH_DEFINES */



var __Nectar_MATH_E = NectarCore::VAR(M_E);
var __Nectar_MATH_LN2 = NectarCore::VAR(M_LN2);
var __Nectar_MATH_LOG2E = NectarCore::VAR(M_LOG2E);
var __Nectar_MATH_LOG10E = NectarCore::VAR(M_LOG10E);
var __Nectar_MATH_PI = NectarCore::VAR(M_PI);
var __Nectar_MATH_SQRT1_2 = NectarCore::VAR(M_SQRT1_2);
var __Nectar_MATH_SQRT2 = NectarCore::VAR(M_SQRT2);

function __Nectar_MATH_ABS(x) 
{ 
	return NectarCore::VAR(std::abs((double)(x))); 
};

function __Nectar_MATH_ACOS(x) 
{ 
	return NectarCore::VAR(std::acos((double)(x))); 
};

function __Nectar_MATH_ACOSH(x)
{ 
	return NectarCore::VAR(std::acosh((double)(x))); 
};

function __Nectar_MATH_ASIN(x) 
{ 
	return NectarCore::VAR(std::asin((double)(x))); 
};

function __Nectar_MATH_ASINH(x) 
{
	return NectarCore::VAR(std::asinh((double)(x))); 
};
function __Nectar_MATH_ATAN(x) 
{ 
	return NectarCore::VAR(std::atan((double)(x))); 
};
function __Nectar_MATH_ATAN2(x, y) 
{ 
	return NectarCore::VAR(std::atan2((double)(x), (double)(y))); 
};
function __Nectar_MATH_ATANH(x) 
{ 
	return NectarCore::VAR(std::atanh((double)(x))); 
};
function __Nectar_MATH_CBRT(x) 
{ 
	return NectarCore::VAR(std::cbrt((double)(x))); 
};
function __Nectar_MATH_CEIL(x) 
{ 
	return NectarCore::VAR(std::ceil((double)(x))); 
};

function __Nectar_MATH_CLZ32(x) 
{
	int n = (int)(x);
	return NectarCore::VAR(n > 0 ? (int)(31 - std::log2(n >> 0)) : 32);
};

function __Nectar_MATH_COS(x) 
{ 
	return NectarCore::VAR(std::cos((double)(x))); 
};

function __Nectar_MATH_COSH(x) 
{ 
	return NectarCore::VAR(std::cosh((double)(x))); 
};

function __Nectar_MATH_EXP(x) 
{ 
	return std::exp((double)(x)); 
};

function __Nectar_MATH_EXPM1(x) 
{ 
	return NectarCore::VAR(std::expm1((double)(x))); 
};

function __Nectar_MATH_FLOOR(x) 
{ 
	return NectarCore::VAR((int)(std::floor((double)(x))));
};

function __Nectar_MATH_FROUND(x) 
{ 
	return NectarCore::VAR((double)((double)(x))); 
};

function __Nectar_MATH_HYPOT()
{
	double max = 0;
	double s = 0;
	for (int i = 0; i < __Nectar_VARLENGTH; i++) {
		double x = std::abs((double)(__Nectar_VARARGS[i]));
		if (x > max) {
			s *= (max / x) * (max / x);
			max = x;
		}
		s += (x == 0 && max == 0) ? 0 : (x / max) * (x / max);
	}
	return NectarCore::VAR(max == INFINITY ? INFINITY : max * std::sqrt(s));
};

function __Nectar_MATH_IMUL(x, y)
{
	return NectarCore::VAR((int)(x) * (int)(y));
};

function __Nectar_MATH_LOG(x) 
{ 
	return NectarCore::VAR(std::log((double)(x))); 
};

function __Nectar_MATH_LOG1P(x) 
{ 
	return NectarCore::VAR(std::log1p((double)(x))); 
};

function __Nectar_MATH_LOG2(x) 
{ 
	return NectarCore::VAR(std::log2((double)(x))); 
};

function __Nectar_MATH_LOG10(x) 
{ 
	return NectarCore::VAR(std::log10((double)(x))); 
};

function __Nectar_MATH_MAX()
{
	double max = -INFINITY;
	for (int i = 0; i < __Nectar_VARLENGTH; i++) {
		double n = (double)(__Nectar_VARARGS[i]);
		if (n > max) {
			max = n;
		}
	}
	return NectarCore::VAR(max);
};

function __Nectar_MATH_MIN()
{
	double min = INFINITY;
	for (int i = 0; i < __Nectar_VARLENGTH; i++) {
		double n = (double)(__Nectar_VARARGS[i]);
		if (n < min) {
			min = n;
		}
	}
	return NectarCore::VAR(min);
};

function __Nectar_MATH_POW(x, x2) 
{ 
	return NectarCore::VAR(std::pow((double)(x), (double)(x2))); 
};

function __Nectar_MATH_RANDOM() 
{ 
	return NectarCore::VAR((double)(std::rand()) / (double)(RAND_MAX));
};

function __Nectar_MATH_ROUND(x) 
{ 
	return NectarCore::VAR((int)(std::round((double)(x))));
};

function __Nectar_MATH_SIGN(x) 
{
	double n = (double)(x);
	if (n == 0) { return NectarCore::VAR(0); }
	else { return NectarCore::VAR(n > 0 ? 1 : -1); };
};

function __Nectar_MATH_SIN(x) 
{ 
	return NectarCore::VAR(std::sin((double)(x))); 
};

function __Nectar_MATH_SINH(x) 
{ 
	return NectarCore::VAR(std::sinh((double)(x))); 
};

function __Nectar_MATH_SQRT(x) 
{ 
	return NectarCore::VAR(std::sqrt((double)(x))); 
};

function __Nectar_MATH_TAN(x) 
{ 
	return NectarCore::VAR(std::tan((double)(x))); 
};

function __Nectar_MATH_TANH(x) 
{ 
	return NectarCore::VAR(std::tanh((double)(x))); 
};

function __Nectar_MATH_TRUNC(x) 
{ 
	return NectarCore::VAR((int)(x)); 
};
