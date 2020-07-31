// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S8.6.1_A3;
 * @section: 8.6.1, 15.7;
 * @assertion: A property can have attribute DontDelete like NaN propertie of Number object;
 * @description: Try to delete Number.NaN;  
*/
//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (delete Number.NaN !== false){
  $ERROR('#1: delete Number.NaN === false. Actual: ' + (delete Number.NaN));
};
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//CHECK#2
if (typeof(Number.NaN) === "undefined"){
  $ERROR('#2: delete Number.NaN; typeof(Number.NaN) !== "undefined" ');
};
//
//////////////////////////////////////////////////////////////////////////////
