// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S8.6.2.3_A1;
 * @section: 8.6.2.3, 8.6.2.2, 8.6.1;
 * @assertion: If the property has the ReadOnly attribute, [[CanPut]](P) return false;
 * @description: Try put other value for Math.E property; 
*/

__e = Math.E;
Math.E = 1;
if (Math.E !== __e){
  $ERROR('#1: __e = Math.E; Math.E = 1; Math.E === __e. Actual: ' + (Math.E));
}
