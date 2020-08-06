// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S7.6_A1.4_T4;
 * @section: 7.6;
 * @assertion: IdentifierName must begin at IdentifierStart;
 * @description: IdentifierStart is not UnicodeConnectorPunctuation ("Pc") without $.
 * Complex test with eval;
*/

//CHECK
Pc = [[0x005F, 0x005F], [0x203F, 0x2040], [0x30FB, 0x30FB], [0xFE33, 0xFE34], [0xFE4D, 0xFE4F], [0xFF3F, 0xFF3F], [0xFF65, 0xFF65]];

errorCount = 0;
count = 0;
for (indexI = 0; indexI < Pc.length; indexI++) {
  for (indexJ = Pc[indexI][0]; indexJ <= Pc[indexI][1]; indexJ++) {
    try {
      var identifier = String.fromCharCode(indexJ);
      var hex = decimalToHexString(indexJ);
      if (hex !== "0078") {
        eval("var " + identifier + "=1");
        $ERROR('#' + hex + ' ');
        errorCount++;
      }
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
