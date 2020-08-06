// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.4_A5;
* @section: 15.5.4.4;
* @assertion: When String.prototype.charAt(pos) calls first calls ToString, giving it the this value as its argument;
* @description: Change toString function, it trow exception, and call charAt();
*/

__obj={
    valueOf:1,
    toString:function(){throw 'intostring'},
    charAt:String.prototype.charAt
}

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
try {
  var x = __obj.charAt();
  $FAIL('#1: __obj={valueOf:1,toString:function(){throw \'intostring\'},charAt:String.prototype.charAt}; "var x = __obj.charAt()" lead to throwing exception');
} catch (e) {
  if (e !== 'intostring') {
    $ERROR('#1.1: Exception === \'intostring\'. Actual: exception ==='+e ); 
  }
}
//
//////////////////////////////////////////////////////////////////////////////
