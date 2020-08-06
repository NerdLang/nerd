// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.10_A2_T13;
* @section: 15.5.4.10, 15.10.6.2;
* @assertion: match returns array as specified in 15.10.6.2;
* @description: Regular expression is /([\d]{5})([-\ ]?[\d]{4})?$/g. 
* And regular expression object have property lastIndex = 0;
*/

__matches=["02134"];

__re = /([\d]{5})([-\ ]?[\d]{4})?$/g;
__re.lastIndex = 0;

__string = "Boston, MA 02134";

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (__string.match(__re).length!== __matches.length) {
  $ERROR('#1: __string.match(__re).length=== __matches.length. Actual: '+__string.match(__re).length);
}
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//CHECK#3
if (__string.match(__re)[0]!==__matches[0]) {
  $ERROR('#3: __string.match(__re)[0]===__matches[0]. Actual: '+__string.match(__re)[0]);
}
//
//////////////////////////////////////////////////////////////////////////////
