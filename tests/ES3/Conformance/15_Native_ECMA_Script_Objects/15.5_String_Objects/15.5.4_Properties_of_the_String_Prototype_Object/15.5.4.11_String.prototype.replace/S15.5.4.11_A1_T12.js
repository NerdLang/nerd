// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.11_A1_T12;
* @section: 15.5.4.11;
* @assertion: String.prototype.replace (searchValue, replaceValue);
* @description: Call replace (searchValue, replaceValue) function with objects arguments of String object. 
* First objects have overrided toString and valueOf functions, valueOf throw exception. 
* Second objects have overrided toString function, that throw exception;
*/

var __obj = {toString:function(){return {};}, valueOf:function(){throw "insearchValue";}};
var __obj2 = {toString:function(){throw "inreplaceValue";}};
var __str = new String("ABB\u0041BABAB");

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
with(__str){
    try {
      var x = replace(__obj, __obj2);
      $FAIL('#1: "var x = replace(__obj,__obj2)" lead to throwing exception');
    } catch (e) {
      if (e!=="insearchValue") {
        $ERROR('#1.1: Exception === "insearchValue". Actual: '+e);
      }
    }
}
//
//////////////////////////////////////////////////////////////////////////////
