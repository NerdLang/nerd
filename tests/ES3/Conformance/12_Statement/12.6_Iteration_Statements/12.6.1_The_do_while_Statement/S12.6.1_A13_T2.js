// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S12.6.1_A13_T2;
* @section: 12.6.1, 13;
* @assertion: FunctionDeclaration within a "do-while" Block is not allowed;
* @description: Declaring a function within a "do-while" loop that is within a function call;
* @negative;
*/

(function(){

do{
    function __func(){};
}while(0);

})();
