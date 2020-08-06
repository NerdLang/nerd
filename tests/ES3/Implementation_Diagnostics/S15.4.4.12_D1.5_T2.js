// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.4.4.12_D1.5_T2;
 * @section: 15.4.4.12;
 * @assertion: If a function is given fewer arguments than the function is 
 * specified to require, the function shall behave exactly as if it had been 
 * given sufficient additional arguments, each such argument being the
 * undefined value;
 * @description: one argument;
*/

var x = [0,1,2,3];
var arr = x.splice(1);

//CHECK#1
arr.getClass = Object.prototype.toString;
if (arr.getClass() !== "[object " + "Array" + "]") {
  $ERROR('#1: var x = [0,1,2,3]; var arr = x.splice(1); arr is Array object');
}

//CHECK#2
if (arr.length !== 0) {
  $ERROR('#2: var x = [0,1,2,3]; var arr = x.splice(1); arr.length === 0');
}      

//CHECK#3
if (x.length !== 4) {
  $ERROR('#3: var x = [0,1,2,3]; var arr = x.splice(1); x.length === 4');
} 

//CHECK#4
if (x[0] !== 0) {
  $ERROR('#4: var x = [0,1,2,3]; var arr = x.splice(1); x[0] === 0');
}

//CHECK#5
if (x[1] !== 1) {
  $ERROR('#5: var x = [0,1,2,3]; var arr = x.splice(1); x[1] === 1');
} 

//CHECK#6
if (x[2] !== 2) {
  $ERROR('#6: var x = [0,1,2,3]; var arr = x.splice(1); x[2] === 2');
}

//CHECK#7
if (x[3] !== 3) {
  $ERROR('#7: var x = [0,1,2,3]; var arr = x.splice(1); x[3] === 3');
}    
