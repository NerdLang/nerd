//!_c_include "lib/main-nana.h"

var NANA_GUI = {};

NANA_GUI.createForm = function(_title, _text, _button)
{
	__NJS_CreateForm(__NJS_Get_String(_title), __NJS_Get_String(_text), __NJS_Get_String(_button));
}

module.exports = NANA_GUI;
