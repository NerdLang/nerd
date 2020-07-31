// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.16_A2;
* @section: 15.5.4.16;
* @assertion: The characters in SpecialCasings.txt are converted by multi-character results;
* @description: Complex test;
*/

//CHECK
LowerSpecialCase = [["\u03A3", "\u03C2"]];

errorCount = 0;
count = 0;

for (index = 0; index < LowerSpecialCase.length; index++) {
  var capitalI = LowerSpecialCase[index][0];
  var capitalS = String.fromCharCode(capitalI);
  var smallI = LowerSpecialCase[index][1];  
  var smallS = String.fromCharCode(smallI);
  if (capitalS.toLowerCase() !== smallS) {
    var hexC = decimalToHexString(capitalI);
    var hexS = decimalToHexString(smallI);
    $ERROR('#' + hexC + '->' + hexS + ' ');
    errorCount++;
  }  
  count++;
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
