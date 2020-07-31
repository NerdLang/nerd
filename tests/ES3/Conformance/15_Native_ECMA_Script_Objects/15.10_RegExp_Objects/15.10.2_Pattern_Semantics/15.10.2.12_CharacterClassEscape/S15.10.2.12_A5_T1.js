// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.10.2.12_A5_T1;
* @section: 15.10.2.12;
* @assertion: The production CharacterClassEscape :: d evaluates by returning the ten-element set of characters containing the characters 0 through 9 inclusive;
* @description: 0 - 9;
*/

var regexp_d = /\d/;

//CHECK#0030-0039
var result = true; 
for (alpha = 0x0030; alpha <= 0x0039; alpha++) {
  str = String.fromCharCode(alpha);
  arr = regexp_d.exec(str); 
  if ((arr === null) || (arr[0] !== str)) {
    result = false;
  }
}

if (result !== true) {
  $ERROR('#1: 0 - 9');
}

//CHECK#005F 
if (regexp_d.exec("_") !== null) {
  $ERROR('#2: _');
}

//CHECK#0020
if (regexp_d.exec(" ") !== null) {
  $ERROR('#3:  ');
}

