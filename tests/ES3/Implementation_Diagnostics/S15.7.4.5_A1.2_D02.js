// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.7.4.5_A1.2_D02;
 * @section: 15.7.4.5;
 * @assertion: If f < 0 or f > 20, throw a RangeError exception;
 * @description: calling on Number object;
*/

//CHECK#2
try{
  s = (new Number(1)).toFixed(-1);
  $ERROR('#2: (new Number(1)).toFixed(-1) should throw RangeError, see the diagnostics tests for this section');
}
catch(e){
  if(!(e instanceof RangeError)){
    $ERROR('#2: (new Number(1)).toFixed(-1) should throw RangeError, not the '+e);
  }
}

//CHECK#3
try{
  s = (new Number(1)).toFixed(20.1);
  $ERROR('#3: (new Number(1)).toFixed(20.1) should throw RangeError, see the diagnostics tests for this section');
}
catch(e){
  if(!(e instanceof RangeError)){
    $ERROR('#3: (new Number(1)).toFixed(20.1) should throw RangeError, not the '+e);
  }
}

//CHECK#4
try{
  s = (new Number(1)).toFixed(21);
   $ERROR('#4: (new Number(1)).toFixed(21) should throw RangeError, see the diagnostics tests for this section');
}
catch(e){
  if(!(e instanceof RangeError)){
    $ERROR('#4: (new Number(1)).toFixed(21) should throw RangeError, not the '+e);
  }
}

//CHECK#5
try{
  s = (new Number(1)).toFixed(Number.POSITIVE_INFINITY);
  $ERROR('#5: (new Number(1)).toFixed(Number.POSITIVE_INFINITY) should throw RangeError, see the diagnostics tests for this section');
}
catch(e){
  if(!(e instanceof RangeError)){
    $ERROR('#5: (new Number(1)).toFixed(Number.POSITIVE_INFINITY) should throw RangeError, not the '+e);
  }
}

//CHECK#6
try{
  s = (new Number(1)).toFixed(Number.NEGATIVE_INFINITY);
  $ERROR('#6: (new Number(1)).toFixed(Number.NEGATIVE_INFINITY) should throw RangeError, see the diagnostics tests for this section');
}
catch(e){
  if(!(e instanceof RangeError)){
    $ERROR('#6: (new Number(1)).toFixed(Number.NEGATIVE_INFINITY) should throw RangeError, not the '+e);
  }
}

//CHECK#7
try{
  s = (new Number(1)).toFixed("-0.1");
  $ERROR('#1: (new Number(1)).toFixed("-0.1") should throw RangeError, see the diagnostics tests for this section');
}
catch(e){
  if(!(e instanceof RangeError)){
    $ERROR('#1: (new Number(1)).toFixed("-0.1") should throw RangeError, not the '+e);
  }
}

//CHECK#2
try{
  s = (new Number(1)).toFixed("-1");
  $ERROR('#2: (new Number(1)).toFixed("-1") should throw RangeError, see the diagnostics tests for this section');
}
catch(e){
  if(!(e instanceof RangeError)){
    $ERROR('#2: (new Number(1)).toFixed("-1") should throw RangeError, not the '+e);
  }
}

//CHECK#3
try{
  s = (new Number(1)).toFixed("20.1");
  $ERROR('#3: (new Number(1)).toFixed("20.1") should throw RangeError, see the diagnostics tests for this section');
}
catch(e){
  if(!(e instanceof RangeError)){
    $ERROR('#3: (new Number(1)).toFixed("20.1") should throw RangeError, not the '+e);
  }
}

//CHECK#4
try{
  s = (new Number(1)).toFixed(21);
   $ERROR('#4: (new Number(1)).toFixed("21") should throw RangeError, see the diagnostics tests for this section');
}
catch(e){
  if(!(e instanceof RangeError)){
    $ERROR('#4: (new Number(1)).toFixed("21") should throw RangeError, not the '+e);
  }
}

//CHECK#5
try{
  s = (new Number(1)).toFixed("Infinity");
  $ERROR('#5: (new Number(1)).toFixed("Infinity") should throw RangeError, see the diagnostics tests for this section');
}
catch(e){
  if(!(e instanceof RangeError)){
    $ERROR('#5: (new Number(1)).toFixed("Infinity") should throw RangeError, not the '+e);
  }
}

//CHECK#6
try{
  s = (new Number(1)).toFixed("-Infinity");
  $ERROR('#6: (new Number(1)).toFixed("-Infinity") should throw RangeError, see the diagnostics tests for this section');
}
catch(e){
  if(!(e instanceof RangeError)){
    $ERROR('#6: (new Number(1)).toFixed("-Infinity") should throw RangeError, not the '+e);
  }
}

