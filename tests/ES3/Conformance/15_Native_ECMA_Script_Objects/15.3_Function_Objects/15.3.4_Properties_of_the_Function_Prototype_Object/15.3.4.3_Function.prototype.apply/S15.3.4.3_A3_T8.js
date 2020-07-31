// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.3.4.3_A3_T8;
* @section: 15.3.4.3;
* @assertion: If thisArg is null or undefined, the called function is passed the global object as the this value;
* @description: Argument at apply function is undefined and it called inside function declaration;
*/

(function FACTORY(){
  (function(){this.feat="kamon beyba"}).apply(undefined);
})();

//CHECK#1
if (this["feat"] !== "kamon beyba") {
  $ERROR('#1: If thisArg is null or undefined, the called function is passed the global object as the this value');
}
