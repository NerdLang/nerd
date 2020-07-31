// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S12.14_A11_T1;
 * @section: 12.14;
 * @assertion: Using "try" with "catch" or "finally" statement within/without a "for" statement;
 * @description: Loop inside try Block, where throw exception;
 */

// CHECK#1
try{
  for(var i=0;i<10;i++){
    if(i===5) throw i;
  }
}
catch(e){
  if(e!==5)$ERROR('#1: Exception === 5. Actual:  Exception ==='+ e  );
}
