// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.18_A1_T11;
* @section: 15.5.4.18;
* @assertion: String.prototype.toUpperCase();
* @description: Override toString function, toString throw exception, then call toUpperCase() function for this object;
*/

var __obj = {toString:function(){throw "intostr";}}
__obj.toUpperCase = String.prototype.toUpperCase;
//////////////////////////////////////////////////////////////////////////////
//CHECK#1
try {
  var x = __obj.toUpperCase();
   	$FAIL('#1: "var x = __obj.toUpperCase()" lead to throwing exception');
} catch (e) {
  if (e!=="intostr") {
    $ERROR('#1.1: Exception === "intostr". Actual: '+e);
  }
}
//
//////////////////////////////////////////////////////////////////////////////
