// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S7.9_A6.1_T13;
 * @section: 7.9, 12.6.3;
 * @assertion: Check For Statement for automatic semicolon insertion; 
 * @description: for (false \n semicolon false \n semicolon false \n);
*/

//CHECK#1
for(false
    ;false
    ;false
) {
  break;
}
