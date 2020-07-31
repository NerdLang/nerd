// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.3.4.4_A7_T2;
* @section: 15.3.4.4;
* @assertion: Function.prototype.call can't be used as [[create]] caller;
* @description: Checking if creating "new Function.prototype.call()" fails;
*/

try {
  FACTORY = Function.prototype.call;
  obj = new FACTORY();
  $ERROR('#1: Function.prototype.call can\'t be used as [[create]] caller');
} catch (e) {
  if (!(e instanceof TypeError)) {
  	$ERROR('#1.1: Function.prototype.call can\'t be used as [[create]] caller');
  }
}
