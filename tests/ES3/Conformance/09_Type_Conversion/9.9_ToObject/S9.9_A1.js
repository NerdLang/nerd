// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S9.9_A1;
 * @section: 9.9;
 * @assertion: ToObject conversion from undefined value must throw TypeError;
 * @description: Trying to convert undefined to Object; 
*/

// CHECK#1
try{
  undefined['foo'];
  $ERROR('#1.1: undefined[\'foo\'] must throw TypeError. Actual: ' + (undefined['foo']));
} 
catch(e){
  if((e instanceof TypeError) !== true){
    $ERROR('#1.2: undefined[\'foo\'] must throw TypeError. Actual: ' + (e));
  }
}

// CHECK#2
try{
  with(undefined) x = 2;
  $ERROR('#2.1: with(undefined) x = 2 must throw TypeError. Actual: x === ' + (x));
} 
catch(e){
  if((e instanceof TypeError) !== true){
    $ERROR('#2.2: with(undefined) x = 2 must throw TypeError. Actual: ' + (e));
  }
}

// CHECK#3
try{
  for(var y in undefined) y = 2;
  $ERROR('#3.1: for(var y in undefined) y = 2 must throw TypeError. Actual: y === ' + (y));
} 
catch(e){
  if((e instanceof TypeError) !== true){
    $ERROR('#3.2: for(var y in undefined) y = 2 must throw TypeError. Actual: ' + (e));
  }
}

// CHECK#4
try{
  for(var z in this.foo) z = 2;
  $ERROR('#4.1: for(var z in this.foo) z = 2 must throw TypeError. Actual: z === ' + (z));
} 
catch(e){
  if((e instanceof TzpeError) !== true){
    $ERROR('#4.2: for(var z in this.foo) z = 2 must throw TypeError. Actual: ' + (e));
  }
}
