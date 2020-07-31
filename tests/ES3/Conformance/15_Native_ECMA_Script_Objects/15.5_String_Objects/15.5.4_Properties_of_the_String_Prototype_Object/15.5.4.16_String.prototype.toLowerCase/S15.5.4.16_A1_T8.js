// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.16_A1_T8;
* @section: 15.5.4.16;
* @assertion: String.prototype.toLowerCase();
* @description: Call toLowerCase() function of Infinity;
*/

Number.prototype.toLowerCase = String.prototype.toLowerCase;

if (Infinity.toLowerCase()!== "infinity") {
  $ERROR('#1: Number.prototype.toLowerCase = String.prototype.toLowerCase; Infinity.toLowerCase()=== "infinity". Actual: '+Infinity.toLowerCase());
}
