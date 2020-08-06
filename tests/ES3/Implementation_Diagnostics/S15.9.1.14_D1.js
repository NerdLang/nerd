// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.1.14_D1;
 * @section: 15.9.1.14;
 * @assertion: Return an implementation-dependent choice of either 
 * ToInteger(Result(2)) or ToInteger(Result(2)) + (+0);
*/

// CHECK#1
var d = new Date(-0);
if ( !( 1/d.valueOf() === Number.NEGATIVE_INFINITY) ) {
  $PRINT('#1: TimeClip returns (ToInteger(value) + (+0))');
} else {
  $PRINT('#1: TimeClip returns (ToInteger(value))');
}
