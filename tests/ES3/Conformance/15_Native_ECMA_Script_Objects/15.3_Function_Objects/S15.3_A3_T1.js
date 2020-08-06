// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.3_A3_T1;
* @section: 15.3;
* @assertion: Since when call is used for Function constructor themself new function instance creates 
* and then first argument(thisArg) should be ignored;
* @description: First argument is object;
*/

//CHECK#1
try{
  f = Function.call(mars, "return name;");
  $ERROR('#1: When applied to the Function object itself, thisArg should be ignored');
} catch(e){
  if (!(e instanceof ReferenceError)) {
  	$ERROR('#1.1: When applied to the Function object itself, thisArg should be ignored');
  }
} 

mars={name:"mars", color:"red", number:4};

f = Function.call(mars, "this.godname=\"ares\"; return this.color;");

var about_mars = f();

//CHECK#2
if (about_mars !== undefined) {
  $ERROR('#2: When applied to the Function object itself, thisArg should be ignored');
}

//CHECK#3
if (this.godname !== "ares") {
  $ERROR('#3: When applied to the Function object itself, thisArg should be ignored');
}
