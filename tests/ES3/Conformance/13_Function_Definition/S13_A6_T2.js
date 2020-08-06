// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S13_A6_T2;
* @section: 13;
* @assertion: FunctionDeclaration can be overrided by other FunctionDeclaration with the same Identifier;
* @description: Calling a function before it is declared one more time;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
try{
    var __result = __func();
} catch(e) {
    $FAIL("#1: Function call can appears in the program before the FunctionDeclaration appears");
}
if (__result !== "SECOND") {
	$ERROR('#1.1: __result === "SECOND". Actual: __result ==='+__result);
}
//
//////////////////////////////////////////////////////////////////////////////

function __func(){return "FIRST";};

//////////////////////////////////////////////////////////////////////////////
//CHECK#2
__result = __func();
if (__result !== "SECOND") {
	$ERROR('#2: __result === "SECOND". Actual: __result ==='+__result);
}
//
//////////////////////////////////////////////////////////////////////////////

function __func(){return "SECOND";};
