// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.10.2.12_A4_T1;
* @section: 15.10.2.12;
* @assertion: The production CharacterClassEscape :: W evaluates by returning the set of all characters not
* included in the set returned by CharacterClassEscape :: w;
* @description: A - Z;
*/

var regexp_W = /\W/;

//CHECK#0041-005A
var result = true;  
for (alpha = 0x0041; alpha <= 0x005A; alpha++) {
  if (regexp_W.exec(String.fromCharCode(alpha)) !== null) {
    result = false;
  }
}

if (result !== true) {
  $ERROR('#1: A - Z');
}
