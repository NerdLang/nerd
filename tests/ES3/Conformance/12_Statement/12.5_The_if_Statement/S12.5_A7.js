// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S12.5_A7;
* @section: 12.5;
* @assertion: In the "if" statement empty statement is allowed and is evaluated to "undefined";
* @description: Checking by using eval "eval("if(1);"))";
*/


//////////////////////////////////////////////////////////////////////////////
//CHECK#1
try {
	__evaluated = eval("if(1);");
	if (__evaluated !== undefined) {
		$ERROR('#1: __evaluated === undefined. Actual:  __evaluated ==='+ __evaluated  );
	}
	
} catch (e) {
	$ERROR('#1.1: "__evaluated = eval("if(1);")" does not lead to throwing exception');

}
//
//////////////////////////////////////////////////////////////////////////////
