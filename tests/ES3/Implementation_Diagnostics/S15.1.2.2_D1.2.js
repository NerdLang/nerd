// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.2.2_D1.2;
 * @section: 15.1.2.2, 9.8;
 * @assertion: If the length of S is at least 1 and the first character of S is 0, 
 * then R = 10;
*/

//CHECK#1
if (parseInt("08") !== parseInt("08", 10)) {
  $ERROR('#1: parseInt("08") === parseInt("08", 10)');
}

//CHECK#2
if (parseInt("09") !== parseInt("09", 10)) {
  $ERROR('#2: parseInt("09") === parseInt("09", 10)');
}

//CHECK#3
if (parseInt("010") !== parseInt("010", 10)) {
  $ERROR('#3: parseInt("010") === parseInt("010", 10)');
}
