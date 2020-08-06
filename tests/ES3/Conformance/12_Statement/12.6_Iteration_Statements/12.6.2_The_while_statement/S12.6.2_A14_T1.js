// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S12.6.2_A14_T1;
* @section: 12.6.2;
* @assertion: FunctionExpression within a "while" Expression is allowed;
* @description: Using "function __func(){return 0;}" as an Expression;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#
while(function __func(){return 0;}){
   var __reached = 1;
   break;
};
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//CHECK#2
if (__reached !== 1) {
	$ERROR('#2: function expression inside of while expression is allowed');
}
//
//////////////////////////////////////////////////////////////////////////////
