/* Date std module */
"!_ffi_include libdate/date.h";

function _date()
{
	
};

_date.now = __NJS_NATIVE_DATE_NOW;

module.exports = _date;