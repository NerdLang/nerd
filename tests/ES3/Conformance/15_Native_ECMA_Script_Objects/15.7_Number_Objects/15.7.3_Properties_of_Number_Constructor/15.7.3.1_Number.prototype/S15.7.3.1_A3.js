// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.7.3.1_A3;
 * @section: 15.7.3.1;
 * @assertion: Number.prototype value is +0;
 * @description: Checking value of Number.prototype property;
*/

//CHECK#1
if (Number.prototype != 0) {
  $ERROR('#2: Number.prototype == +0');
} else if( 1/Number.prototype != Number.POSITIVE_INFINITY){
  $ERROR('#2: Number.prototype == +0');
}
