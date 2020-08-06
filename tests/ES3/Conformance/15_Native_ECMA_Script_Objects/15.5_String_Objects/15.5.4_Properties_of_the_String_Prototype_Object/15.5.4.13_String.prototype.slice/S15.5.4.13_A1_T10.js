// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.13_A1_T10;
* @section: 15.5.4.13;
* @assertion: String.prototype.slice (start, end);
* @description: Arguments are object and function call, and instance is String, object have overrided valueOf function;
*/

var __obj = {valueOf:function(){return 2;}};

var __str = "\u0035ABBBABAB";

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
with(__str){
    if (slice(__obj, function(){return slice(0,1);}()) !== "BBB") {
      $ERROR('#1: var x; var __obj = {valueOf:function(){return 2;}}; var __str = "\u0035ABBBABAB"; slice(__obj, function(){return slice(0,1);}()) === "BBB". Actual: '+slice(__obj, function(){return slice(0,1);}()) );
    }
}
//
//////////////////////////////////////////////////////////////////////////////

var x;
