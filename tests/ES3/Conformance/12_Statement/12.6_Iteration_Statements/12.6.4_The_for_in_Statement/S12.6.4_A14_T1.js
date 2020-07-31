// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S12.6.4_A14_T1;
* @section: 12.6.4;
* @assertion: FunctionExpession within a "for-in" Expression is allowed;
* @description: Using "function __func(){return 0;}" as Expession;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#
for(x in function __func(){return 0;}){
    if (x=="prototype") 
        var __reached = 1;
};
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//CHECK#2
if (__reached !== 1) {
	$ERROR('#2: function expession inside of for-in expression is allowed');
}
//
//////////////////////////////////////////////////////////////////////////////
