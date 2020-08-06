// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S12.8_A6;
* @section: 12.8;
* @assertion: Appearing of "break" within a function call that is nested in a IterationStatement yields SyntaxError;
* @description: Checking if using "break Identifier" within a function body appears to be invalid;
* @negative;
*/

var x=0,y=0;

LABEL1 : do {
    x++;
    (function(){break LABEL1;})();
    y++;
} while(0);
