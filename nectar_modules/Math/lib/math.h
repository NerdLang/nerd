// #define JSMN_STRICT
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>

using namespace std;

var __NJS_M_E = __NJS_VAR(M_E);
var __NJS_M_LN2 = __NJS_VAR(M_LN2);
var __NJS_M_LOG2E = __NJS_VAR(M_LOG2E);
var __NJS_M_LOG10E = __NJS_VAR(M_LOG10E);
var __NJS_M_PI = __NJS_VAR(M_PI);
var __NJS_M_SQRT1_2 = __NJS_VAR(M_SQRT1_2);
var __NJS_M_SQRT2 = __NJS_VAR(M_SQRT2);

function __GET_VALUE (_var)
{
	if (_var.type == __NJS_NUMBER) {
		return _var.get().i;
	} else if (_var.type == __NJS_DOUBLE) {
		return _var.get().d;
	} else if (_var.type == __NJS_STRING) {
		return stod(_var.get().s->__NJS_VALUE);
	}
};

function __NJS_MATH_ABS(_var) { return __NJS_VAR(abs(__GET_VALUE(_var))); };
function __NJS_MATH_ACOS(_var) { return __NJS_VAR(acos(__GET_VALUE(_var))); };
function __NJS_MATH_ACOSH(_var) { return __NJS_VAR(acosh(__GET_VALUE(_var))); };
function __NJS_MATH_ASIN(_var) { return __NJS_VAR(asin(__GET_VALUE(_var))); };
function __NJS_MATH_ASINH(_var) { return __NJS_VAR(asinh(__GET_VALUE(_var))); };
function __NJS_MATH_ATAN(_var) { return __NJS_VAR(atan(__GET_VALUE(_var))); };
function __NJS_MATH_ATAN2(_var) { return __NJS_VAR(atan2(__GET_VALUE(_var))); };
function __NJS_MATH_ATANH(_var) { return __NJS_VAR(atanh(__GET_VALUE(_var))); };
function __NJS_MATH_CBRT(_var) { return __NJS_VAR(cbrt(__GET_VALUE(_var))); };
function __NJS_MATH_CEIL(_var) { return __NJS_VAR(ceil(__GET_VALUE(_var))); };
function __NJS_MATH_CLZ32(_var) {
	auto x = (int)__GET_VALUE(_var);
    if (x == 0) {
      return __NJS_VAR(32);
    }
    return __NJS_VAR((int)(31 - log(x >> 0) / M_LN2));
};
function __NJS_MATH_COS(_var) { return __NJS_VAR(cos(__GET_VALUE(_var))); };
function __NJS_MATH_COSH(_var) { return __NJS_VAR(cosh(__GET_VALUE(_var))); };
function __NJS_MATH_EXP(_var) { return __NJS_VAR(exp(__GET_VALUE(_var))); };
function __NJS_MATH_EXPM1(_var) { return __NJS_VAR(expm1(__GET_VALUE(_var))); };
function __NJS_MATH_FLOOR(_var) { return __NJS_VAR((int)floor(__GET_VALUE(_var))); };
function __NJS_MATH_FROUND(_var) { return __NJS_VAR((float)__GET_VALUE(_var))); };
//function __NJS_MATH_HYPOT(_var) {
//	return __NJS_VAR(cos(__GET_VALUE(_var)));
//};
//function __NJS_MATH_IMUL(_var) {
//	return __NJS_VAR(imul(__GET_VALUE(_var)));
//};
function __NJS_MATH_LOG(_var) { return __NJS_VAR(log(__GET_VALUE(_var))); };
function __NJS_MATH_LOG1P(_var) { return __NJS_VAR(log1p(__GET_VALUE(_var))); };
function __NJS_MATH_LOG2(_var) { return __NJS_VAR(log2(__GET_VALUE(_var))); };
function __NJS_MATH_LOG10(_var) { return __NJS_VAR(log10(__GET_VALUE(_var))); };
//function __NJS_MATH_MAX(_var) {	
//	return __NJS_VAR(log2(__GET_VALUE(_var)));
//};
//function __NJS_MATH_MIN(_var) {
//	return __NJS_VAR(log2(__GET_VALUE(_var)));
//};
function __NJS_MATH_POW(_var, _var2) { return __NJS_VAR(pow(__GET_VALUE(_var), __GET_VALUE(_var2))); };
function __NJS_MATH_RANDOM() { return __NJS_VAR(static_cast<float>(rand()) / static_cast<float>(RAND_MAX)); };
function __NJS_MATH_ROUND(_var) { return __NJS_VAR((int)round(__GET_VALUE(_var))); };
function __NJS_MATH_SIGN(_var) {
	auto x = __GET_VALUE(_var);
	if (x == 0) { return __NJS_VAR(0); }
	else { return __NJS_VAR(x > 0 ? 1 : -1); };
};
function __NJS_MATH_SIN(_var) { return __NJS_VAR(sin(__GET_VALUE(_var))); };
function __NJS_MATH_SINH(_var) { return __NJS_VAR(sinh(__GET_VALUE(_var))); };
function __NJS_MATH_SQRT(_var) { return __NJS_VAR(sqrt(__GET_VALUE(_var))); };
function __NJS_MATH_TAN(_var) { return __NJS_VAR(tan(__GET_VALUE(_var))); };
function __NJS_MATH_TANH(_var) { return __NJS_VAR(tanh(__GET_VALUE(_var))); };
function __NJS_MATH_TRUNC(_var) { return __NJS_VAR((int)(__GET_VALUE(_var))); };
