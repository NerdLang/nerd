// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S7.6_A2.1_T1;
 * @section: 7.6;
 * @assertion: IdentifierPart :: IdentifierStart;
 * @description: IdentifierStart :: UnicodeLetter;
*/

//CHECK#6
try {
  var \u0078x = 6;
  if (xx !== 6) {
    $ERROR('#6.1: var \\u0078x = 1; xx === 6. Actual: ' + (xx));
  }
} catch (e) {
  $ERROR('#6.2: var \\u0078x = 1; xx === 6. Actual: ' + (xx));
}
