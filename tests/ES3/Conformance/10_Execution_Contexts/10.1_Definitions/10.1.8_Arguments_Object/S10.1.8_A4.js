// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S10.1.8_A4;
 * @section: 10.1.8;
 * @assertion: The initial value of the created property callee is the  
 * Function object being executed;
 * @description: Checking that arguments.callee === function object;
*/

//CHECK#1
function f1(){
  return arguments.callee;
}

try{
  if(f1 !== f1()){
    $ERROR('#1: arguments.callee === f1');
  }
}
catch(e){
  $ERROR("#1: arguments object doesn't exists");
}

//CHECK#2
var f2 = function(){return arguments.callee;};

try{
  if(f2 !== f2()){
    $ERROR('#2: arguments.callee === f2');
  }
}
catch(e){
  $ERROR("#1: arguments object doesn't exists");
}
