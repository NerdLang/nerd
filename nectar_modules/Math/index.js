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
 
"!_ffi_include lib/math.h";

var _Math = 
{
    /*** PROPERTIES ***/
    
    E: __Nectar_MATH_E,
    LN2: __Nectar_MATH_LN2,
    LOG2E: __Nectar_MATH_LOG2E,
    LOG10E: __Nectar_MATH_LOG10E,
    PI: __Nectar_MATH_PI,
    SQRT1_2: __Nectar_MATH_SQRT1_2,
    SQRT2: __Nectar_MATH_SQRT2,

    /*** END PROPERTIES ***/

    /*** METHODS ***/

    abs: __Nectar_MATH_ABS,
	acos: __Nectar_MATH_ACOS,
	acosh: __Nectar_MATH_ACOSH,
	asin: __Nectar_MATH_ASIN,
	asinh: __Nectar_MATH_ASINH,
	atan: __Nectar_MATH_ATAN,
	atanh: __Nectar_MATH_ATANH,
	atan2: __Nectar_MATH_ATAN2,
	cbrt: __Nectar_MATH_CBRT,
	ceil: __Nectar_MATH_CEIL,
	clz32: __Nectar_MATH_CLZ32,
	cos: __Nectar_MATH_COS,
	cosh: __Nectar_MATH_COSH,
	exp: __Nectar_MATH_EXP,
	expm1: __Nectar_MATH_EXPM1,
	floor: __Nectar_MATH_FLOOR,
	fround: __Nectar_MATH_FROUND,
    hypot: __Nectar_MATH_HYPOT,
    imul: __Nectar_MATH_IMUL,
	log: __Nectar_MATH_LOG,
	log1p: __Nectar_MATH_LOG1P,
	log10: __Nectar_MATH_LOG10,
	log2: __Nectar_MATH_LOG2,
	max: __Nectar_MATH_MAX,
    min: __Nectar_MATH_MIN,
    pow: __Nectar_MATH_POW,
	random: __Nectar_MATH_RANDOM,
	round: __Nectar_MATH_ROUND,
	sign: __Nectar_MATH_SIGN,
	sin: __Nectar_MATH_SIN,
	sinh: __Nectar_MATH_SINH,
	sqrt: __Nectar_MATH_SQRT,
	tan: __Nectar_MATH_TAN,
	tanh: __Nectar_MATH_TANH,
    trunc: __Nectar_MATH_TRUNC,
    
    /*** END METHODS ***/
    toString: function () { return "[object Math]"; }
};


module.exports = _Math;
