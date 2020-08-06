// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S7.6_A1.3_T3;
 * @section: 7.6;
 * @assertion: IdentifierStart :: _; 
 * @description: The _ as unicode character \u005F;  
*/

//CHECK#1
var identifier = String.fromCharCode(0x005F);
eval("var " + identifier + "=1");
if (eval(identifier + "===1") !== true) {
  $ERROR('#1: var identifier = String.fromCharCode(0x005F); eval("var " + identifier + "=1"); eval(identifier + "===1") === true');
}

//CHECK#2
if ("_" !== String.fromCharCode(0x005F)) {
  $ERROR('#2: "_" === String.fromCharCode(0x005F)');
}
