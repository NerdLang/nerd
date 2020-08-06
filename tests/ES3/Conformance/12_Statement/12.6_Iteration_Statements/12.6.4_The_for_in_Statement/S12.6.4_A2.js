// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S12.6.4_A2;
* @section: 12.6.4;
* @assertion: "for(key in null)" Expression is allowed;
* @description: Checking if execution of "for(key in null)" passes;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#
try {
	for(__key in null){
	    var key=__key;
	};
} catch (e) {
	$ERROR('#1: "for(__key in null){}" does not lead to throwing exception');
}
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//CHECK#2
if (key!==undefined) {
	$ERROR('#2: key === undefined. Actual: key ==='+key);
}
//
//////////////////////////////////////////////////////////////////////////////



