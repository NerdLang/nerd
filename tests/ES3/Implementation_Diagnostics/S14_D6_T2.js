// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S14_D6_T2;
* @section: 14;
* @assertion: Function declaration may be inside of while block ;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (typeof __func !== "function") {
	$ERROR('1: Function declaration may be inside of while block');
}
//
//////////////////////////////////////////////////////////////////////////////

while(1){
    break;
    function __func(){return BANNER;};
}

BANNER="union jack";

//////////////////////////////////////////////////////////////////////////////
//CHECK#2
if (__func() !== "union jack") {
	$ERROR('2: Function declaration may be inside of while block');
}
//
//////////////////////////////////////////////////////////////////////////////
