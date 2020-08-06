// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.2.2_A1_T1;
 * @section: 15.1.2.2, 9.8;
 * @assertion: Operator use ToString;
 * @description: Checking for boolean primitive;  
*/

//CHECK#1
if (!(isNaN(parseInt(true)) && isNaN(parseInt("NaN")))) {
  $ERROR('#1: parseInt(true) === Not-a-Number; parseInt("NaN") === Not-a-Number. Actual: ' + (parseInt("NaN")));
}

//CHECK#2
if (String(parseInt(false)) !== "NaN") {
  $ERROR('#2: String(parseInt(false)) === "NaN". Actual: ' + (String(parseInt(false))));
}
