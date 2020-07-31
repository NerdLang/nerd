// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.4_A1_T3;
* @section: 15.5.4.4;
* @assertion: String.prototype.charAt(pos);
* @description: Use numbers and strings as pos; 
*/

charAt = String.prototype.charAt;

if (typeof toString === "undefined"){
    toString = Object.prototype.toString;
}

__class__ = toString();

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (charAt("1") + charAt(2) + charAt("3") + charAt(4) + charAt("5") + charAt(6) !== "object") {
  $ERROR('#1: charAt = String.prototype.charAt; charAt("1") + charAt(2) + charAt("3") + charAt(4) + charAt("5") + charAt(6) === "object". Actual: '+charAt("1") + charAt(2) + charAt("3") + charAt(4) + charAt("5") + charAt(6) ); 
}
//
//////////////////////////////////////////////////////////////////////////////
