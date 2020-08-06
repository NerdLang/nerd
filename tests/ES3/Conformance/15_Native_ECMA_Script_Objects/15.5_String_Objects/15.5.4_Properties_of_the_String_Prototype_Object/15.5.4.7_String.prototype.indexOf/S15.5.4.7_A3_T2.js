// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.7_A3_T2;
* @section: 15.5.4.7;
* @assertion: Since we deal with max(ToInteger(pos), 0) if ToInteger(pos) less than 0 indexOf(searchString,0) returns;
* @description: Call "$$abcdabcd".indexOf("ab",eval("\"-99\"")) and check result;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if ("$$abcdabcd".indexOf("ab",eval("\"-99\""))!==2) {
  $ERROR('#1: "$$abcdabcd".indexOf("ab",eval("\\"-99\\""))===2. Actual: '+("$$abcdabcd".indexOf("ab",eval("\"-99\"")))); 
}
//
//////////////////////////////////////////////////////////////////////////////
