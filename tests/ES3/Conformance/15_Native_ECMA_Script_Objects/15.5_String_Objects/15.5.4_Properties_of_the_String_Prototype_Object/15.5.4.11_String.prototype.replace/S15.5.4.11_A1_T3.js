// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.11_A1_T3;
* @section: 15.5.4.11;
* @assertion: String.prototype.replace (searchValue, replaceValue);
* @description: Checking by using eval;
*/

replace = String.prototype.replace;

if (typeof toString === "undefined"){
    toString = Object.prototype.toString;
}

__class__ = toString();
__toggle = 1;

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
__replaced = replace(eval("\"b\""),"^");

__golden = "";
for(var i=0; i<__class__.length; i++) {
  if ((__class__.charAt(i)==="b")&&(__toggle)) {
    __golden+="^";
    __toggle = 0;
  } else {
    __golden+=__class__.charAt(i);
  }

}
if (__replaced !==__golden) {
  $ERROR('#1: __replaced ===__golden. Actual: '+__replaced );
}
//
//////////////////////////////////////////////////////////////////////////////
