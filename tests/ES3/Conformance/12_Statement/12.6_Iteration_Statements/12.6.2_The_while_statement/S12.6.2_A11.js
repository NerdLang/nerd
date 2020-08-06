// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S12.6.2_A11;
* @section: 12.6.2;
* @assertion: "{}" Block within a "while" Expression is evaluated to true;
* @description: Checking if execution of "while({}){}" passes;
*/

while({}){
    var __in__do=1;
    if(__in__do)break;
};

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (__in__do !== 1) {
	$ERROR('#1: "{}" in while expression evaluates to true');
}
//
//////////////////////////////////////////////////////////////////////////////
