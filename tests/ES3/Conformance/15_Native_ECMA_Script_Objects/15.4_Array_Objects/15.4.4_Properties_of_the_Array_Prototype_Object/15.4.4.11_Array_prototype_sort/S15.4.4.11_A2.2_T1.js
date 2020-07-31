// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.4.4.11_A2.2_T1;
 * @section: 15.4.4.11;
 * @assertion: My comparefn is inverse implementation comparefn; 
 * @description: Checking ENGLISH ALPHABET; 
*/

alphabetR = ["z", "y", "x", "w", "v", "u", "t", "s", "r", "q", "p", "o", "n", "M", "L", "K", "J", "I", "H", "G", "F", "E", "D", "C", "B", "A"];
 alphabet = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"];

var myComparefn = function(x,y) {
  xS = String(x);
  yS = String(y);
  if (xS < yS) return 1
  if (xS > yS) return -1;   
  return 0;
}

//CHECK#1
alphabet.sort(myComparefn);
result = true;
for (i = 0; i < 26; i++) {
  if (alphabetR[i] !== alphabet[i]) result = false;
}

if (result !== true) {
  $ERROR('#1: CHECK ENGLISH ALPHABET');
} 
