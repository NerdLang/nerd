// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S11.2.3_A4_T5;
* @section: 11.2.3;
* @assertion: If MemberExpression does not implement the internal [[Call]] method, throw TypeError;
* @description: Checking Math object case;
*/

//CHECK#1
try {
  Math();
  $ERROR('#1.1: Math() throw TypeError. Actual: ' + (Math()));	
}
catch (e) {
  if ((e instanceof TypeError) !== true) {
    $ERROR('#1.2: Math() throw TypeError. Actual: ' + (e));	
  }
}

