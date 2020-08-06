// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.3_A1;
 * @section: 15.3;
 * @assertion: Function is the property of global;
 * @description: Compare Function with this.Function;
 */

obj = Function;

thisobj = this.Function;

if (obj !== thisobj) {
  $ERROR('Function is the property of global');
}
