// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S12.6.4_R2;
 * @section: 12.6.4, 9.9;
 * @description: The for-in statement must not throw TypeError for null
 * values, cause it's a bug in the Standard; 
*/

// CHECK#1
try{
  var x1 = 1;
  for(var y1 in null) x1 = 2;
  if (x1 === 1) {
    $PRINT("#1: passed");
  } else {
    $ERROR("#1: The for-in statement must not fullfill, the value was changed");
  }
} 
catch(e){
  if(e instanceof TypeError){
    $ERROR("#1: The for-in statement must not throw TypeError for null values, cause it's a bug in the Standard");
  } else {
    $ERROR("#1: The for-in statement must not throw Error for null values, cause it's a bug in the Standard");
  }
}

// CHECK#2
try{
  var x2 = 1;
  for(var y2 in 'bbb'.match(/aaa/)) x2 = 2;
  if (x2 === 1) {
    $PRINT("#1: passed");
  } else {
    $ERROR("#1: The for-in statement must not fullfill, the value was changed");
  }
} 
catch(e){
  if(e instanceof TypeError){
    $ERROR("#1: The for-in statement must not throw TypeError for null values, cause it's a bug in the Standard");
  } else {
    $ERROR("#1: The for-in statement must not throw Error for null values, cause it's a bug in the Standard");
  }
}
