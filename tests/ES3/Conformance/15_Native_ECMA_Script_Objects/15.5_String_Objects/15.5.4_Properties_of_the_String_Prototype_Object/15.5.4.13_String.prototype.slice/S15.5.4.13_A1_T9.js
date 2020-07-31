// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.13_A1_T9;
* @section: 15.5.4.13;
* @assertion: String.prototype.slice (start, end);
* @description: Arguments are undefined and object, and instance is String(object), object have overrided valueOf and toString functions;
*/

__obj = {
    valueOf:function(){},
    toString:void 0
};

//since ToInteger(undefined) yelds 0
//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (new String(__obj).slice(/*(function(){})()*/undefined,__obj) !== "") {
  $ERROR('#1: __obj = {valueOf:function(){}, toString:void 0}; new String(__obj).slice(//*(function(){})()*//undefined,__obj) === "". Actual: '+new String(__obj).slice(/*(function(){})()*/undefined,__obj) );
}
//
//////////////////////////////////////////////////////////////////////////////
