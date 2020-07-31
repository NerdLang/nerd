// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.3.4.1_A1_T2;
* @section: 15.3.4.1;
* @assertion: The initial value of Function.prototype.constructor is the built-in Function constructor;
* @description: Create new Function.prototype.constructor object;
*/

constr = Function.prototype.constructor;

f = new constr;

// CHECK#0
if (f === undefined) {
  $ERROR('#0: new Function() return the newly created function object.');
}

// CHECK#1
if (f.constructor !== Function) {
  $ERROR('#1: new Function() create a new function object');
}

// CHECK#2
if (!(Function.prototype.isPrototypeOf(f))) {
  $ERROR('#2: when new Function() calls the [[Prototype]] property of the newly constructed object is set to the Function prototype object.');
}

// CHECK#3
to_string_result = '[object '+ 'Function' +']';

delete Function.prototype.toString;

if (f.toString() !== to_string_result) {
  $ERROR('#3: when new Function() calls the [[Class]] property of the newly constructed object is set to "Function"');
}
