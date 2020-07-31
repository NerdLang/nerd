// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S13.2_A1_T1;
* @section: 13.2;
* @assertion: A "prototype" property is automatically created for every function;
* @description: Using "function __func(){}" as a FunctionDeclaration; 
*/

function __func(){};

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (__func.prototype === undefined) {
	$ERROR('#1: __func.prototype !== undefined');
}
//
//////////////////////////////////////////////////////////////////////////////
