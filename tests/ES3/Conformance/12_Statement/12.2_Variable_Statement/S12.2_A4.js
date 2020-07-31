// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S12.2_A4;
* @section: 12.2;
* @assertion: Unicode characters in variable Identifier are allowed;
* @description: Create and use unicode characters in variable Identifier;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
try {
	__var=__var;
} catch (e) {
	$ERROR('#1: Unicode characters in variable Identifier allowed');
}
//
//////////////////////////////////////////////////////////////////////////////

var \u005f\u005f\u0076\u0061\u0072 = 1;

//////////////////////////////////////////////////////////////////////////////
//CHECK#2
if (__var !== 1) {
	$ERROR('#2: __var === 1. Actual:  __var ==='+ __var  );
}
//
//////////////////////////////////////////////////////////////////////////////
