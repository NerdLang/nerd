// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.7.4_A3.1;
 * @section: 15.7.4;
 * @assertion: The Number prototype object has the property constructor;
 * @description: The test uses hasOwnProperty() method;
*/

//CHECK#1
if(Number.prototype.hasOwnProperty("constructor") !== true){
  $ERROR('#1: The Number prototype object has the property constructor');
}

