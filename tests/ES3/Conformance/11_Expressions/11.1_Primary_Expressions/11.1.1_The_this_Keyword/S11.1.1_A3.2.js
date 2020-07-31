// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S11.1.1_A3.2;
 * @section: 11.1.1;
 * @assertion: Being in function code, "this" and eval("this"), called as a constructors, return the object;
 * @description: Create function. It have property, that returned "this";
*/

//CHECK#1
function MyFunction() {this.THIS = this}
if ((new MyFunction()).THIS.toString() !== "[object Object]") {
  $ERROR('#1: function MyFunction() {this.THIS = this} (new MyFunction()).THIS.toString() !== "[object Object]". Actual: ' + ((new MyFunction()).THIS.toString()));  
}

//CHECK#2
function MyFunction() {this.THIS = eval("this")}
if ((new MyFunction()).THIS.toString() !== "[object Object]") {
  $ERROR('#2: function MyFunction() {this.THIS = eval("this")} (new MyFunction()).THIS.toString() !== "[object Object]". Actual: ' + ((new MyFunction()).THIS.toString()));  
}

