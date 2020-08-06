// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S7.6_A5.2_T3;
 * @section: 7.6, 6;
 * @assertion: If a \UnicodeEscapeSequence sequence were replaced by its UnicodeEscapeSequence's CV, the result must still be a valid Identifier that has the exact same sequence of characters as the original Identifier;
 * @description: The CV of UnicodeEscapeSequence is Lt.
 * Complex test with eval;
*/

//CHECK
Lt = [[0x01C5, 0x01C5], [0x01C8, 0x01C8], [0x01CB, 0x01CB], [0x01F2, 0x01F2], [0x1F88, 0x1F8F], [0x1F98, 0x1F9F], [0x1FA8, 0x1FAF], [0x1FBC, 0x1FBC], [0x1FCC, 0x1FCC], [0x1FFC, 0x1FFC]];

errorCount = 0;
count = 0;
for (indexI = 0; indexI < Lt.length; indexI++) {
  for (indexJ = Lt[indexI][0]; indexJ <= Lt[indexI][1]; indexJ++) {
    try {
      var hex = decimalToHexString(indexJ);
      var identifier1 = String.fromCharCode(indexJ);
      var identifier2 = "\\u" + hex;
      eval(identifier2 + " = 1"); 
      if (eval(identifier1 + " === " + identifier2) !== true) {
        $ERROR('#' + hex + ' ');
        errorCount++;
      }
    } catch (e) {
      $ERROR('#' + hex + ' ');
      errorCount++;
    }
    count++;
  }
}

if (errorCount > 0) {  
  $ERROR('Total error: ' + errorCount + ' bad Unicode character in ' + count);
}

function decimalToHexString(n) {
  n = Number(n);
  var h = "";
  for (var i = 3; i >= 0; i--) {
    if (n >= Math.pow(16, i)) {
      var t = Math.floor(n / Math.pow(16, i));
      n -= t * Math.pow(16, i);
      if ( t >= 10 ) {
        if ( t == 10 ) { h += "A"; }
        if ( t == 11 ) { h += "B"; }
        if ( t == 12 ) { h += "C"; }
        if ( t == 13 ) { h += "D"; }
        if ( t == 14 ) { h += "E"; }
        if ( t == 15 ) { h += "F"; }
      } else {
        h += String(t);
      }
    } else {
      h += "0";
    }
  }
  return h;
}
