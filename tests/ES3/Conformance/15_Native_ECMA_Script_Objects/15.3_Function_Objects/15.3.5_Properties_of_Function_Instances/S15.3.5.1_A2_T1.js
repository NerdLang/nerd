// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.3.5.1_A2_T1;
* @section: 15.3.5.1;
* @assertion: the length property has the attributes { DontDelete };
* @description: Checking if deleting the length property of Function("arg1,arg2,arg3", null) fails;
*/

f = new Function("arg1,arg2,arg3", null);

//CHECK#1
if (!(f.hasOwnProperty('length'))) {
  $FAIL('#1: the function has length property.');
}

//CHECK#2
if(delete f.length){
  $ERROR('#2: the function.length property has the attributes DontDelete.');
}

//CHECK#3
if (!(f.hasOwnProperty('length'))) {
  $ERROR('#3: the function.length property has the attributes DontDelete.');
}

//CHECK#4
if (f.length !== 3) {
  $ERROR('#4: the length property has the attributes { DontDelete }');
}
