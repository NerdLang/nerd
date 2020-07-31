// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.8.1.6_A3;
 * @section: 15.8.1.6;
 * @assertion: Value Property PI of the Math Object has the attribute DontDelete;
 * @description: Checking if Math.PI property has the attribute DontDelete;
 */

// CHECK#1
if (delete Math.PI === true) {
    $ERROR('#1: Value Property PI of the Math Object hasn\'t attribute DontDelete: \'Math.PI === true\'');
}

