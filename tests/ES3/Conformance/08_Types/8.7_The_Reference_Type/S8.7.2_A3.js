// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S8.7.2_A3;
* @section: 8.7.2;
* @assertion: this.x++ calls GetValue then PutValue so after applying postfix increment(actually conrete operator type is unimportan)
* we must have reference to defined value;
* @description: Execute this.x++, where this.x is undefined;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (this.x !== undefined) {
  $ERROR('#1: this.x === undefined. Actual: ' + (this.x));
}
//
//////////////////////////////////////////////////////////////////////////////
this.x++;
//////////////////////////////////////////////////////////////////////////////
//CHECK#2
if (x === undefined) {
  $ERROR('#2: this.x; this.x++; x !== undefined');
}
//
//////////////////////////////////////////////////////////////////////////////
