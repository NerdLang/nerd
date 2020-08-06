// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S12.4_A2_T1;
* @section: 12.4;
* @assertion: The production ExpressionStatement : [lookahead \notin {{, function}] Expression; is evaluated as follows: 
* 1. Evaluate Expression. 
* 2. Call GetValue(Result(1)). 
* 3. Return (normal, Result(2), empty);
* @description: Checking by using eval "(eval("x+1+x==1"))";
*/

x=1;

__evaluated = eval("x+1+x==1");

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (__evaluated !== false) {
	$ERROR('#1: __evaluated === false. Actual:  __evaluated ==='+ __evaluated  );
}
//
//////////////////////////////////////////////////////////////////////////////

__evaluated = eval("1+1+1==1");

//////////////////////////////////////////////////////////////////////////////
//CHECK#2
if (__evaluated !== false) {
	$ERROR('#2: __evaluated === false. Actual:  __evaluated ==='+ __evaluated  );
}
//
//////////////////////////////////////////////////////////////////////////////
