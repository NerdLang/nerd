// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.3.4.3_A8_T2;
* @section: 15.3.4.3;
* @assertion: Function.prototype.apply can`t be used as [[create]] caller;
* @description: Checking if creating "new Function.prototype.apply()" fails;
*/

try {
  obj = new Function.prototype.apply();
  $ERROR('#1: Function.prototype.apply can\'t be used as [[create]] caller');
} catch (e) {
  if (!(e instanceof TypeError)) {
  	$ERROR('#1.1: Function.prototype.apply can\'t be used as [[create]] caller');
  }
}
