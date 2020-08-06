// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S12.6.4_A3;
* @section: 12.6.4;
* @assertion: The production IterationStatement: "for (var VariableDeclarationNoIn in Expression) Statement";
* @description: Using an array as an Expression is appropriate. Here Expression is an array of numbers. Eval is used;
*/

__str="";

__evaluated = eval("for(ind in (arr=[2,1,4,3]))__str+=arr[ind]");

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (__evaluated !== __str) {
	$ERROR('#1: __evaluated === __str. Actual:  __evaluated ==='+ __evaluated  );
}
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//CHECK#2
if (!( (__str.indexOf("2")!==-1)&&(__str.indexOf("1")!==-1)&&(__str.indexOf("4")!==-1)&&(__str.indexOf("3")!==-1) )) {
	$ERROR('#2: (__str.indexOf("2")!==-1)&&(__str.indexOf("1")!==-1)&&(__str.indexOf("4")!==-1)&&(__str.indexOf("3")!==-1)');
}
//
//////////////////////////////////////////////////////////////////////////////



