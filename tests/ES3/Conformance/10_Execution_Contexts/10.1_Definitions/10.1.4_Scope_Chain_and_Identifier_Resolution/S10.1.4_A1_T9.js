// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S10.1.4_A1_T9;
 * @section: 10.1.4;
 * @assertion: Every execution context has associated with it a scope chain. 
 * A scope chain is a list of objects that are searched when evaluating an 
 * Identifier;
 * @description: Checking scope chain containing function declarations and "with";
*/

var x = 0;

var myObj = {x : "obj"};

function f1(){
  with(myObj){
    return x;
  }
}

if(!(f1() === "obj")){
  $ERROR("#1: Scope chain disturbed");
}
