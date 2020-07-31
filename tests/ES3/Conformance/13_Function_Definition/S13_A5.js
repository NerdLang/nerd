// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S13_A5;
* @section: 13, 10.1.2;
* @assertion: Only FormalParameterList as arguments list is allowed;
* @description: Trying to use [arg1, arg2, arg3], (arg1, arg2, arg3), etc. as a FormalParameterList; 
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
try{
	eval("function __func([arg1, arg2, arg3]){return arguments.length;}");
	$ERROR('#1: eval("function __func([arg1, arg2, arg3]){return arguments.length;}") lead to throwing exception');
} catch(e){
	if(!(e instanceof SyntaxError)){
		$ERROR('#1.1: eval("function __func([arg1, arg2, arg3]){return arguments.length;}") lead to throwing exception of SyntaxError. Actual: exception is '+e);
	}
}
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//CHECK#2
try{
	eval("function __func((arg1, arg2, arg3)){return arguments.length;}");
	$ERROR('#2: eval("function __func((arg1, arg2, arg3)){return arguments.length;}") lead to throwing exception')
} catch(e){
	if(!(e instanceof SyntaxError)){
		$ERROR('#2.1: eval("function __func((arg1, arg2, arg3)){return arguments.length;}") lead to throwing exception of SyntaxError. Actual: exception is '+e);
	}
}
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//CHECK#3
try{
	eval("function __func(arg1, arg2, arg3,){return arguments.length;}");
	$ERROR('#3: eval("function __func(arg1, arg2, arg3,){return arguments.length;}") lead to throwing exception')
} catch(e){
	if(!(e instanceof SyntaxError)){
		$ERROR('#3.1: eval("function __func(arg1, arg2, arg3,){return arguments.length;}") lead to throwing exception of SyntaxError. Actual: exception is '+e);
	}
}
//
//////////////////////////////////////////////////////////////////////////////
