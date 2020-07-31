// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.4.4.11_A2.1_T1;
 * @section: 15.4.4.11;
 * @assertion: 
 * If ToString([[Get]] ToString(j)) < ToString([[Get]] ToString(k)), return -1.
 * If ToString([[Get]] ToString(j)) > ToString([[Get]] ToString(k)), return 1; 
 * return -1
 * @description: Checking ENGLISH ALPHABET; 
*/


alphabetR = ["z", "y", "x", "w", "v", "u", "t", "s", "r", "q", "p", "o", "n", "M", "L", "K", "J", "I", "H", "G", "F", "E", "D", "C", "B", "A"];
 alphabet = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"];

//CHECK#1
alphabetR.sort();
result = true;
for (i = 0; i < 26; i++) {
  if (alphabetR[i] !== alphabet[i]) result = false;
}

if (result !== true) {
  $ERROR('#1: CHECK ENGLISH ALPHABET');
}
