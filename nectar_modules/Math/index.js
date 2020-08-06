"!_ffi_include lib/math.h";

var _Math = 
{
    /*** PROPERTIES ***/
    
    E: __NJS_M_E,
    LN2: __NJS_M_LN2,
    LOG2E: __NJS_M_LOG2E,
    LOG10E: __NJS_M_LOG10E,
    PI: __NJS_M_PI,
    SQRT1_2: __NJS_M_SQRT1_2,
    SQRT2: __NJS_M_SQRT2,

    /*** END PROPERTIES ***/

    /*** METHODS ***/

    //abs: __NJS_M_ABS,
	abs: function(i)
    {
        if(i < 0) return -i;
        return i;
    },
	acos: __NJS_M_ACOS,
	acosh: __NJS_M_ACOSH,
	asin: __NJS_M_ASIN,
	asinh: __NJS_M_ASINH,
	atan: __NJS_M_ATAN,
	atanh: __NJS_M_ATANH,
	atan2: __NJS_M_ATAN2,
	cbrt: __NJS_M_CBRT,
	ceil: __NJS_M_CEIL,
	clz32: __NJS_M_CLZ32,
	cos: __NJS_M_COS,
	cosh: __NJS_M_COSH,
	exp: __NJS_M_EXP,
	expm1: __NJS_M_EXPM1,
	floor: __NJS_M_FLOOR,
	fround: __NJS_M_FROUND,
    //hypot: __NJS_M_HYPOT,
    hypot: function (_array) {
        var max = 0;
        var s = 0;
        for (var i = 0; i < _array.length; i += 1) {
            if(typeof _array[i] == "number")
            {
                var arg = Math.abs(Number(_array[i]));
                if (arg > max) {
                    s *= (max / arg) * (max / arg);
                    max = arg;
                }
                s += arg === 0 && max === 0 ? 0 : (arg / max) * (arg / max);
            }
        }
        return max === 1 / 0 ? 1 / 0 : max * Math.sqrt(s);
    },
    //imul: __NJS_M_IMUL,
    imul: function(x, y)
    {
        var _res = 0;
        _res = (x * y);
        return _res;
    },
	log: __NJS_M_LOG,
	log1p: __NJS_M_LOG1P,
	log10: __NJS_M_LOG10,
	log2: __NJS_M_LOG2,
	//max: __NJS_M_MAX,
    max: function(_array)
    {
        var _res;
        for(var i = 0; i < _array.length; i++)
        {
            if(typeof _array[i] == "number")
            {
                if(typeof _res == "undefined") _res = _array[i];
                if(_array[i] > _res) _res = _array[i];
            } 
        }
        if(typeof _res == "undefined") _res = 0;
        return _res;
    },
    //min: __NJS_M_MIN,
    min: function(_array)
    {
        var _res;
        for(var i = 0; i < _array.length; i++)
        {
            if(typeof _array[i] == "number")
            {
                if(typeof _res == "undefined") _res = _array[i];
                if(_array[i] < _res) _res = _array[i];
            } 
        }
        if(typeof _res == "undefined") _res = 0;
        return _res;
    },
    pow: __NJS_M_POW,
	random: __NJS_M_RANDOM,
	round: __NJS_M_ROUND,
	sign: __NJS_M_SIGN,
	sin: __NJS_M_SIN,
	sinh: __NJS_M_SINH,
	sqrt: __NJS_M_SQRT,
	tan: __NJS_M_TAN,
	tanh: __NJS_M_TANH,
    trunc: __NJS_M_TRUNC,
    
    /*** END METHODS ***/
    toString: function () { return "[object Math]"; }
};


module.exports = _Math;
