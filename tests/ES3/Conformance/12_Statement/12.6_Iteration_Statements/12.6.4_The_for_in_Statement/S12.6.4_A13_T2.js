// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S12.6.4_A13_T2;
* @section: 12.6.4;
* @assertion: FunctionDeclaration within a "for-in" Statement is not allowed;
* @description: Declaring function within a "for-in" Statement that is within a function call;
* @negative;
*/

(function(){

for(x in this){
    function __func(){};
};

})();
