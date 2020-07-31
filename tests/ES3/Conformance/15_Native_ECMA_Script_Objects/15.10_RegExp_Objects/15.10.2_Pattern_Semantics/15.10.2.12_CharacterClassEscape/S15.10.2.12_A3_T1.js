// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.10.2.12_A3_T1;
* @section: 15.10.2.12;
* @assertion: The production CharacterClassEscape :: w evaluates by returning the set of characters containing the sixty-three characters:
* a - z, A - Z, 0 - 9, _;
* @description: A - Z;
*/

var regexp_w = /\w/;

//CHECK#0041-005A
var result = true;  
for (alpha = 0x0041; alpha <= 0x005A; alpha++) {
  str = String.fromCharCode(alpha);
  arr = regexp_w.exec(str); 
  if ((arr === null) || (arr[0] !== str)) {
    result = false;
  }
}

if (result !== true) {
  $ERROR('#1: A - Z');
}
