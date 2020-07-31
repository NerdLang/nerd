// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S13.2.2_A17_T1;
* @section: 13.2.2;
* @assertion: FunctionExpression containing "with" statement is admitted;
* @description: Using "with" statement within a function body;
*/

var p1="alert";

var __obj={p1:1,getRight:function(){return "right";}};

this.getRight=function(){return "napravo";};

(function(){
    with(__obj){
        p1="w1";
        function getRight(){return false;}
   }
})();

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (p1!=="alert") {
	$ERROR('#1: p1 === "alert". Actual: p1==='+p1);
}
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//CHECK#2
if (getRight()!=="napravo") {
	$ERROR('#2: getRight() === "napravo". Actual: getRight() === '+getRight());
}
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//CHECK#3
if (__obj.p1!=="w1") {
	$ERROR('#3: __obj.p1 === "w1". Actual: __obj.p1 ==='+__obj.p1);
}
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//CHECK#4
if (__obj.getRight()!=="right") {
	$ERROR('#4: __obj.getRight() === "right". Actual: __obj.getRight() ==='+__obj.getRight());
}
//
//////////////////////////////////////////////////////////////////////////////

