// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.4.4.3_A3_T1;
 * @section: 15.4.4.3, 8.6.2.1;
 * @assertion: [[Get]] from not an inherited property;
 * @description: [[Prototype]] of Array instance is Array.prototype;
*/

//CHECK#1
var n = 0;
var obj = {toLocaleString: function() {n++}};
Array.prototype[1] = obj;
x = [obj];
x.length = 2;
x.toLocaleString();
if (n !== 2) {  
  $ERROR('#1: var n = 0; var obj = {toLocaleString: function() {n++}}; Array.prototype[1] = obj; x = [obj]; x.length = 2; x.toLocaleString(); n === 2. Actual: ' + (n));    
}
