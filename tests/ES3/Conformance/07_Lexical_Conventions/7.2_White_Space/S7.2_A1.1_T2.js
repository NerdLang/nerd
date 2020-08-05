// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S7.2_A1.1_T2;
 * @section: 7.2, 7.5;
 * @assertion: HORIZONTAL TAB (U+0009) between any two tokens is allowed;
 * @description: Insert real HORIZONTAL TAB between tokens of var x=1;  
*/

	var  x	=	1	;
if (x !== 1) {
  $ERROR('#1: 	var	x	=	1	; x === 1. Actual: ' + (x));
}
