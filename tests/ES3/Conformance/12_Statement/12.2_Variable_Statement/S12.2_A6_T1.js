// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S12.2_A6_T1;
* @section: 12.2;
* @assertion: VariableDeclaration within "try-catch" statement is allowed;
* @description: Declaring variable within "try-catch" statement;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
try{
	intry__var=intry__var;
}catch(e){
	$ERROR('#1: Variable declaration inside "try" block is admitted');
};
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//CHECK#2
try{
	incatch__var=incatch__var;
}catch(e){
	$ERROR('#2: Variable declaration inside "catch" block is admitted');
};
//
//////////////////////////////////////////////////////////////////////////////

try{
  var intry__var;
}catch(e){
    var incatch__var;
};
