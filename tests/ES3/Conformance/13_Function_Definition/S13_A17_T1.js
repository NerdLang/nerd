// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S13_A17_T1;
* @section: 13;
* @assertion: Function call cannot appear in the program before the FunctionExpression appears;
* @description: Trying to call a function before the FunctionExpression appears; 
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
try{
    var __result = __func();
	$FAIL("#1: var __result = __func() lead to throwing exception");
} catch(e) {
}
//
//////////////////////////////////////////////////////////////////////////////

var __func = function (){return "ONE";};

//////////////////////////////////////////////////////////////////////////////
//CHECK#2
var __result = __func();
if (__result !== "ONE") {
	$ERROR('#2: __result === "ONE". Actual: __result ==='+__result);
}
//
//////////////////////////////////////////////////////////////////////////////

__func = function (){return "TWO";};

//////////////////////////////////////////////////////////////////////////////
//CHECK#3
var __result = __func();
if (__result !== "TWO") {
	$ERROR('#3: __result === "TWO". Actual: __result ==='+__result);
}
//
//////////////////////////////////////////////////////////////////////////////
