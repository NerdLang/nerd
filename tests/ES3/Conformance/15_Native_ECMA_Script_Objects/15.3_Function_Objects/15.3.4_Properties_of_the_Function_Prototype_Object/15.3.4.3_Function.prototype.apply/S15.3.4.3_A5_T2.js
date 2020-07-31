// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.3.4.3_A5_T2;
* @section: 15.3.4.3;
* @assertion: If thisArg is not null(defined) the called function is passed ToObject(thisArg) as the this value;
* @description: thisArg is boolean true;
*/

obj=true;

retobj = new Function("this.touched= true; return this;").apply(obj);

//CHECK#1
if (typeof obj.touched !== "undefined") {
  $ERROR('#1: If thisArg is not null(defined) the called function is passed ToObject(thisArg) as the this value');
}

//CHECK#2
if (!(retobj["touched"])) {
  $ERROR('#2: If thisArg is not null(defined) the called function is passed ToObject(thisArg) as the this value');
}

