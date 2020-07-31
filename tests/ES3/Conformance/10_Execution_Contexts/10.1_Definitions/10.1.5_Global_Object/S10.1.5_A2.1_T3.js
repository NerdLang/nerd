// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S10.1.5_A2.1_T3;
 * @section: 10.1.5, 15.1;
 * @assertion: Global object properties have attributes { DontEnum };
 * @description: Global execution context - Constructor Properties;
*/

//CHECK#1
for (var x in this) {
  if ( x === 'Object' ) {
    $ERROR("#1: 'property 'Object' have attribute DontEnum");
  } else if ( x === 'Function') {
    $ERROR("#1: 'Function' have attribute DontEnum");
  } else if ( x === 'String' ) {
    $ERROR("#1: 'String' have attribute DontEnum");
  } else if ( x === 'Number' ) {
    $ERROR("#1: 'Number' have attribute DontEnum");
  } else if ( x === 'Array' ) {
    $ERROR("#1: 'Array' have attribute DontEnum");
  } else if ( x === 'Boolean' ) {
    $ERROR("#1: 'Boolean' have attribute DontEnum");
  } else if ( x === 'Date' ) {
    $ERROR("#1: 'Date' have attribute DontEnum");
  } else if ( x === 'RegExp' ) {
    $ERROR("#1: 'RegExp' have attribute DontEnum");
  } else if ( x === 'Error' ) {
    $ERROR("#1: 'Error' have attribute DontEnum");
  } else if ( x === 'EvalError' ) {
    $ERROR("#1: 'EvalError' have attribute DontEnum");
  } else if ( x === 'RangeError' ) {
    $ERROR("#1: 'RangeError' have attribute DontEnum");
  } else if ( x === 'ReferenceError' ) {
    $ERROR("#1: 'ReferenceError' have attribute DontEnum");
  } else if ( x === 'SyntaxError' ) {
    $ERROR("#1: 'SyntaxError' have attribute DontEnum");
  } else if ( x === 'TypeError' ) {
    $ERROR("#1: 'TypeError' have attribute DontEnum");
  } else if ( x === 'URIError' ) {
    $ERROR("#1: 'URIError' have attribute DontEnum");
  }
}
