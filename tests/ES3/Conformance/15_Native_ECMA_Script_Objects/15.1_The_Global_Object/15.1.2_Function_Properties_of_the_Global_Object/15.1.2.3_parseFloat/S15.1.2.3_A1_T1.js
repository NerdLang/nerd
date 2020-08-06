// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.2.3_A1_T1;
 * @section: 15.1.2.3, 9.8;
 * @assertion: Operator use ToString;
 * @description: Checking for boolean primitive;  
*/

//CHECK#1
if (!(isNaN(parseFloat(true)) && isNaN(parseFloat("NaN")))) {
  $ERROR('#1: parseFloat(true) === Not-a-Number; parseFloat("NaN") === Not-a-Number. Actual: ' + (parseFloat("NaN")));
}

//CHECK#2
if (String(parseFloat(false)) !== "NaN") {
  $ERROR('#2: String(parseFloat(false)) === "NaN". Actual: ' + (String(parseFloat(false))));
}
