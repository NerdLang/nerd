// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S13.2.2_A11;
* @section: 13.2.2;
* @assertion: Calling a function as a constructor is possible as long as this.any_Function is declared and called;
* @description: Calling a function as a constructor after it has been declared with "function func()";
*/

function FACTORY(){
   this.id = 0;
      
   this.id = this.func();
   
   function func(){
      return "id_string";
   }
     
}
//////////////////////////////////////////////////////////////////////////////
//CHECK#1
try {
	var obj = new FACTORY();
	$ERROR('#1: var obj = new FACTORY() lead to throwing exception');
} catch (e) {}
//
//////////////////////////////////////////////////////////////////////////////

