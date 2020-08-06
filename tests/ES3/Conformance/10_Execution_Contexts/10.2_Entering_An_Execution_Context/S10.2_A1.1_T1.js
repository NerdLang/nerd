// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S10.2_A1.1_T1;
 * @section: 10.2;
 * @assertion: Every function call enters a new execution context;
 * @description: Sequence of function calls;
*/

var y;

function f(){
  var x;
  
  if(x === undefined) {
    x = 0;
  } else {
    x = 1;
  }
  
  return x;
}

y = f();
y = f();

if(!(y === 0)){
  $ERROR("#1: Sequenced function calls shares execution context");
}
