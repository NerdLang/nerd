// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.4.5.2_A2_T1;
 * @section: 15.4.5.2, 15.4;
 * @assertion: If a property is added whose name is an array index, 
 * the length property is changed;
 * @description: Checking length property;
*/

//CHECK#1
x = [];
if (x.length !== 0) {  
  $ERROR('#1: x = []; x.length === 0. Actual: ' + (x.length));    
}

//CHECK#2
x[0] = 1;
if (x.length !== 1) {      
  $ERROR('#2: x = []; x[1] = 1; x.length === 1. Actual: ' + (x.length));
}

//CHECK#3
x[1] = 1;
if (x.length !== 2) {      
  $ERROR('#3: x = []; x[0] = 1; x[1] = 1; x.length === 2. Actual: ' + (x.length));
}

//CHECK#4
x[9] = 1;
if (x.length !== 10) {      
  $ERROR('#4: x = []; x[0] = 1; x[1] = 1; x[9] = 1; x.length === 10. Actual: ' + (x.length));
}
