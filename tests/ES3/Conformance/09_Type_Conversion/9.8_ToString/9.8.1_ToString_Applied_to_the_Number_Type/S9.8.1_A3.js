// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S9.8.1_A3;
 * @section: 9.8.1;
 * @assertion: If m is less than zero, return the string concatenation of the 
 * string "-" and ToString(-m);
 * @description: -1234567890 convert to String by explicit transformation;
*/

// CHECK#1
if (String(-1234567890) !== "-1234567890") {
  $ERROR('#1: String(-1234567890) === "-1234567890". Actual: ' + (String(-1234567890)));
}

// CHECK#2
if ("-"+String(-(-1234567890)) !== "-1234567890") {
  $ERROR('#2: "-"+String(-(-1234567890)) === "-1234567890". Actual: ' + ("-"+String(-(-1234567890))));
}
