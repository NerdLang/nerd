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
#include <string>
#include <limits>

#define __NJS_INIT_RAND_SEED
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

namespace NJS::Builtins {
	
	class Math {
		static const NJS::VAR E;
		static const NJS::VAR LN2;
		static const NJS::VAR LOG2E;
		static const NJS::VAR LOG10E;
		static const NJS::VAR PI;
		static const NJS::VAR SQRT1_2;
		static const NJS::VAR SQRT2;
		
			#ifdef __NJS__OBJECT_HASHMAP
	NJS::VAR &String::operator[](const char* key)
	{
		std::string _str = key;
		std::string_view _sview = _str;
		
		NJS::VAR& _obj = object[_str];
		if(_obj) return _obj; 
		
		__NJS_Method_Lazy_Loader("toString", toString);
		__NJS_Method_Lazy_Loader("split", split);
		__NJS_Method_Lazy_Loader("indexOf", indexOf);
		__NJS_Method_Lazy_Loader("lastIndexOf", lastIndexOf);
		__NJS_Method_Lazy_Loader("search", search);
		__NJS_Method_Lazy_Loader("slice", slice);
		__NJS_Method_Lazy_Loader("substr", substr);
		__NJS_Method_Lazy_Loader("replace", replace);
		
		if(_sview.compare("length") == 0)
			{
				_length = (int)value.size();
				return _length;
			}
			return _obj;
		}
		#else
		NJS::VAR &String::operator[](const char* key)
		{		
			std::string _str = key;
			std::string_view _sview = _str;
			for (auto & search : object)
			{
				if (_sview.compare(search.first) == 0)
				{
					return search.second;
				}
			}
			__NJS_Method_Lazy_Loader("toString", toString);
			__NJS_Method_Lazy_Loader("split", split);
			__NJS_Method_Lazy_Loader("indexOf", indexOf);
			__NJS_Method_Lazy_Loader("lastIndexOf", lastIndexOf);
			__NJS_Method_Lazy_Loader("search", search);
			__NJS_Method_Lazy_Loader("slice", slice);
			__NJS_Method_Lazy_Loader("substr", substr);
			__NJS_Method_Lazy_Loader("replace", replace);
			if(_sview.compare("length") == 0)
			{
				_length = (int)value.size();
				return _length;
			}
			object.push_back(NJS::Type::pair_t(((std::string)*this), undefined));
			return object[object.size() - 1].second;
		}
		#endif
		
		// NJS::VAR* _args, int _len
		NJS::VAR abs (NJS::VAR* _args, int _len) { return std::abs((double)_args[0]); }
		NJS::VAR acos (NJS::VAR* _args, int _len) { return std::acos((double)_args[0]); }
		NJS::VAR acosh (NJS::VAR* _args, int _len) { return std::acosh((double)_args[0]); }
		NJS::VAR asin (NJS::VAR* _args, int _len) { return std::asin((double)_args[0]); }
		NJS::VAR asinh (NJS::VAR* _args, int _len) { return std::asinh((double)_args[0]); }
		NJS::VAR atan (NJS::VAR* _args, int _len) { return std::atan((double)_args[0]); }
		NJS::VAR atan2(NJS::VAR* _args, int len) {
			return std::atan2((double)_args[0], (double)_args[1]);
		}
		NJS::VAR atanh (NJS::VAR* _args, int _len) { return std::atanh((double)_args[0]); }
		NJS::VAR cbrt (NJS::VAR* _args, int _len) { return std::cbrt((double)_args[0]); }
		NJS::VAR ceil (NJS::VAR* _args, int _len) { return std::ceil((double)_args[0]); }
		NJS::VAR clz32 (NJS::VAR* _args, int _len) {
			int n = (int)_args[0];
			return n > 0 ? (int)(31 - std::log2(n >> 0)) : 32;
		}
		NJS::VAR cos (NJS::VAR* _args, int _len) { return std::cos((double)_args[0]); }
		NJS::VAR cosh (NJS::VAR* _args, int _len) { return std::cosh((double)_args[0]); }
		NJS::VAR exp (NJS::VAR* _args, int _len) { return std::exp((double)_args[0]); }
		NJS::VAR exmp11 (NJS::VAR* _args, int _len) { return std::expm1((double)_args[0]); }
		NJS::VAR floor (NJS::VAR* _args, int _len) { return (int)(std::floor((double)_args[0])); }
		NJS::VAR fround (NJS::VAR* _args, int _len) { return (double)((double)_args[0]); }
		NJS::VAR hypot (NJS::VAR* _args, int _len)
		{
			double max = 0;
			double s = 0;
			for (int i = 0; i < _len; i++) {
				double x = std::abs((double)_args[i]);
				if (x > max) {
					s *= (max / x) * (max / x);
					max = x;
				}
				s += (x == 0 && max == 0) ? 0 : (x / max) * (x / max);
			}
			return max == INFINITY ? INFINITY : max * std::sqrt(s);
		}
		NJS::VAR imul (NJS::VAR* _args, int _len) { return (int)_args[0] * (int)_args[1]; }
		NJS::VAR log (NJS::VAR* _args, int _len) { return std::log((double)_args[0]); }
		NJS::VAR log1p (NJS::VAR* _args, int _len) { return std::log1p((double)_args[0]); }
		NJS::VAR log2 (NJS::VAR* _args, int _len) { return std::log2((double)_args[0]); }
		NJS::VAR log10 (NJS::VAR* _args, int _len) { return std::log10((double)_args[0]); }
		NJS::VAR max (NJS::VAR* _args, int _len) {
			double max = -INFINITY;
			for (int i = 0; i < _len; i++) {
				double n = (double)_args[i];
				if (n > max) {
					max = n;
				}
			}
			return max;
		}
		NJS::VAR min (NJS::VAR* _args, int _len)
		{
			double min = INFINITY;
			for (int i = 0; i < _len; i++) {
				double n = (double)_args[i];
				if (n < min) {
					min = n;
				}
			}
			return min;
		}
		NJS::VAR pow(NJS::VAR* _args, int _len) {
			return std::pow((double)_args[0], (double)_args[1]);
		}
		NJS::VAR random (NJS::VAR* _args, int _len) {
			return (double)(std::rand()) / (double)(RAND_MAX);
		}
		NJS::VAR round (NJS::VAR* _args, int _len) { return (int)(std::round((double)_args[0])); }
		NJS::VAR sign (NJS::VAR* _args, int _len) {
			double n = (double)_args[0];
			return (n == 0) ? 0 : (n > 0 ? 1 : -1);
		}
		NJS::VAR sin (NJS::VAR* _args, int _len) {	return std::sin((double)_args[0]); }
		NJS::VAR sinh (NJS::VAR* _args, int _len) { return std::sinh((double)_args[0]); }
		NJS::VAR sqrt (NJS::VAR* _args, int _len) { return std::sqrt((double)_args[0]); }
		NJS::VAR tan (NJS::VAR* _args, int _len) { return std::tan((double)_args[0]); }
		NJS::VAR tanh (NJS::VAR* _args, int _len) { return std::tanh((double)_args[0]); }
		NJS::VAR trunc (NJS::VAR* _args, int _len) { return (int)_args[0]; }
	}
	
	const NJS::VAR Math::E = M_E;
	const NJS::VAR Math::LN2 = M_LN2;
	const NJS::VAR Math::LOG2E = M_LOG2E;
	const NJS::VAR Math::LOG10E = M_LOG10E;
	const NJS::VAR Math::PI = M_PI;
	const NJS::VAR Math::SQRT1_2 = M_SQRT1_2;
	const NJS::VAR Math::SQRT2 = M_SQRT2;
}
