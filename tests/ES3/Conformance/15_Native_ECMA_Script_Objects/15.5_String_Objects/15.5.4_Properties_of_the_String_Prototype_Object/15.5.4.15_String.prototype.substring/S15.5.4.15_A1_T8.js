// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.15_A1_T8;
* @section: 15.5.4.15;
* @assertion: String.prototype.substring (start, end);
* @description: Arguments are negative number and void 0, and instance is String(object), object have overrided toString function;
*/

__obj = {toString:function(){}};

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (String(__obj).substring(-4,void 0) !== "undefined") {
  $ERROR('#1: __obj = {toString:function(){}}; String(__obj).substring(-4,void 0) === "undefined". Actual: '+String(__obj).substring(-4,void 0) );
}
//
//////////////////////////////////////////////////////////////////////////////
