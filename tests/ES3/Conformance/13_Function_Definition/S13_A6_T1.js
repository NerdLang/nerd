// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S13_A6_T1;
* @section: 13;
* @assertion: FunctionDeclaration can be overrided by other FunctionDeclaration with the same Identifier;
* @description: Duplicating function declaration;
*/

function __func(){return 1};
 
__store__func = __func;
 
 __1 = __func();
 
 function __func(){return 'A'};
 
 __A = __func();
 
//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (__store__func !== __func) {
	$ERROR('#1: __store__func === __func. Actual: __store__func ==='+__store__func);
}
//
////////////////////////////////////////////////////////////////////////////// 
 
//////////////////////////////////////////////////////////////////////////////
//CHECK#2
if (__1 !== __A) {
	$ERROR('#2: __1 === __A. Actual: __1 ==='+__1);
}
//
//////////////////////////////////////////////////////////////////////////////
