// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.15_A1_T7;
* @section: 15.5.4.15;
* @assertion: String.prototype.substring (start, end);
* @description: Arguments are symbol and undefined, and instance is String;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (String(void 0).substring("e",undefined) !== "undefined") {
  $ERROR('#1: String(void 0).substring("e",undefined) === "undefined". Actual: '+String(void 0).substring("e",undefined) );
}
//
//////////////////////////////////////////////////////////////////////////////
