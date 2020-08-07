// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S7.6_A2.1_T3;
 * @section: 7.6;
 * @assertion: IdentifierPart :: IdentifierStart;
 * @description: IdentifierStart :: _;
*/

//CHECK#6
try {
  var \u0078_ = 6;
  if (x_ !== 6) {
    $ERROR('#6.1: var \\u0078_ = 1; x_ === 6. Actual: ' + (x_));
  }
} catch (e) {
  $ERROR('#6.2: var \\u0078_ = 1; x_ === 6. Actual: ' + (x_));
}
