// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S7.6_A1.4_T3;
 * @section: 7.6;
 * @assertion: IdentifierName must begin at IdentifierStart;
 * @description: IdentifierStart is not UnicodeDigit ("Nd").
 * Complex test with eval;
*/

//CHECK
Nd = [[0x0030, 0x0039], [0x0660, 0x0669], [0x06F0, 0x06F9], [0x0966, 0x096F], [0x09E6, 0x09EF], [0x0A66, 0x0A6F], [0x0AE6, 0x0AEF], [0x0B66, 0x0B6F], [0x0BE6, 0x0BEF], [0x0C66, 0x0C6F], [0x0CE6, 0x0CEF], [0x0D66, 0x0D6F], [0x0E50, 0x0E59], [0x0ED0, 0x0ED9], [0x0F20, 0x0F29], [0x1040, 0x1049], [0x17E0, 0x17E9], [0x1810, 0x1819], [0x1946, 0x194F], [0x19D0, 0x19D9], [0xFF10, 0xFF19]];

errorCount = 0;
count = 0;
for (indexI = 0; indexI < Nd.length; indexI++) {
  for (indexJ = Nd[indexI][0]; indexJ <= Nd[indexI][1]; indexJ++) {
    try {
      var identifier = String.fromCharCode(indexJ);
      var hex = decimalToHexString(indexJ);
      eval("var " + identifier + "=1");
      $ERROR('#' + hex + ' ');
      errorCount++;
    } catch (e) {      
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
