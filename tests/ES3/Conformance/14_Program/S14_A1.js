// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S14_A1;
* @section: 14;
* @assertion: FunctionExpression must be localed in a reacheable fragment of the program;
* @description: Declaring a function within an "if" Expression;
*/

THERE = "I'm there";
HERE = "I'm here";

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if ( __func !== undefined) {
	$ERROR('#1: __func === undefined. Actual:  __func ==='+ __func  );
}
//
//////////////////////////////////////////////////////////////////////////////

if (true){
    var __func = function(){return HERE;};
} else {
    var __func = function (){return THERE;};
};

//////////////////////////////////////////////////////////////////////////////
//CHECK#2
if (__func() !== HERE) {
	$ERROR('#2: __func() === HERE. Actual:  __func() ==='+ __func()  );
}
//
//////////////////////////////////////////////////////////////////////////////
