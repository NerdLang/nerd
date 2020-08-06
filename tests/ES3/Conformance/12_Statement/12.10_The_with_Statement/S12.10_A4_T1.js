// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S12.10_A4_T1;
 * @section: 12.10;
 * @assertion: Changing property using "eval" statement containing "with" statement;
 * @description: Changing string property;
 */
 
this.p1 = 1;
var myObj = {
  p1: 'a', 
}
eval("with(myObj){p1='b'}");

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if(myObj.p1 !== 'b'){
  $ERROR('#1: myObj.p1 === "b". Actual:  myObj.p1 ==='+ myObj.p1  );
}
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//CHECK#2
if(myObj.p1 === 1){
  $ERROR('#2: myObj.p1 !== 1');
}
//
//////////////////////////////////////////////////////////////////////////////
