// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.10.2.12_A6_T1;
* @section: 15.10.2.12;
* @assertion: The production CharacterClassEscape :: D evaluates by returning the set of all characters not
* included in the set returned by CharacterClassEscape :: d;
* @description: 0 - 9;
*/

var regexp_D = /\D/;

//CHECK#0030-0039
var result = true; 
for (alpha = 0x0030; alpha <= 0x0039; alpha++) {
  if (regexp_D.exec(String.fromCharCode(alpha)) !== null) {  
    result = false;
  }
}

if (result !== true) {
  $ERROR('#1: 0 - 9');
}

//CHECK#005F 
str = String.fromCharCode(alpha);
var arr = regexp_D.exec(str); 
if ((arr === null) || (arr[0] !== str)) {
  $ERROR('#2: _');
}

//CHECK#0020
str = String.fromCharCode(alpha);
var arr = regexp_D.exec(str); 
if ((arr === null) || (arr[0] !== str)) {
  $ERROR('#3:  ');
}

