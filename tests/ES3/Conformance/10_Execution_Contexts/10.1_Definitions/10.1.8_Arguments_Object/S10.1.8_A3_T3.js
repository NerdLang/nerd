// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S10.1.8_A3_T3;
 * @section: 10.1.8;
 * @assertion: A property is created with name callee with property 
 * attributes { DontEnum } and no others;
 * @description: Checking if deleting arguments.callee property fails;  
*/

//CHECK#1
function f1(){
  return (delete arguments.callee); 
}

try{
  if(!f1()){
    $ERROR("#1: A property callee have attribute { DontDelete }");
  }
}
catch(e){
  $ERROR("#1: arguments object don't exists");
}

//CHECK#2
var f2 = function(){
  return (delete arguments.callee); 
}

try{
  if(!f2()){
    $ERROR("#2: A property callee have attribute { DontDelete }");
  }
}
catch(e){
  $ERROR("#2: arguments object don't exists");
}
