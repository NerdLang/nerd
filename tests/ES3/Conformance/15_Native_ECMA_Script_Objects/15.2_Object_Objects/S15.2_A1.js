// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.2_A1;
* @section: 15.2;
* @assertion: Object is the property of global;
* @description: Checking if Object equals to this.Object; 
*/

obj=Object;

thisobj=this.Object;

if(obj!==thisobj){
  $ERROR('Object is the property of global');
}
