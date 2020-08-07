console.log("E: " + Math.E);
console.log("LN2: " + Math.LN2);
console.log("LOG2E: " + Math.LOG2E);
console.log("LOG10E: " + Math.LOG10E);
console.log("PI: " + Math.PI);
console.log("SQRT1_2: " + Math.SQRT1_2);
console.log("SQRT2: " + Math.SQRT2);

console.log("Math.abs(-123): " + Math.abs(-123));
console.log("Math.acos(0): " + Math.acos(0));
console.log("Math.acosh(2): " + Math.acosh(2));
console.log("Math.asin(1): " + Math.asin(1));
console.log("Math.asinh(1): " + Math.asinh(1));
console.log("Math.atan(1): " + Math.atan(1));
console.log("Math.atanh(1): " + Math.atanh(1));
console.log("Math.atan2(1): " + Math.atan2(1, 1));
console.log("Math.cbrt(1): " + Math.cbrt(1));
console.log("Math.ceil(1.0001): " + Math.ceil(1.0001));
console.log("Math.clz32(1024): " + Math.clz32(1024));
console.log("Math.cos(0): " + Math.cos(0));
console.log("Math.cosh(0): " + Math.cosh(0));
console.log("Math.exp(1): " + Math.exp(1));
console.log("Math.expm1(1): " + Math.expm1(1));
console.log("Math.floor(1.9999): " + Math.floor(1.9999));
console.log("Math.fround(1.1): " + Math.fround(1.1));
console.log("Math.hypot(-10, 10): " + Math.hypot(-10, 10));
console.log("Math.imul(1e5, 1e5): " + Math.imul(1e5, 1e5));
console.log("Math.log(0): " + Math.log(0));
console.log("Math.log1p(-1): " + Math.log1p(-1));
console.log("Math.log10(100): " + Math.log10(100));
console.log("Math.log2(4): " + Math.log2(4));
console.log("Math.max(1, -2, 3, -4, 5): " + Math.max(1, -2, 3, -4, 5));
console.log("Math.min(-1, 2, -3, 4, -5): " + Math.min(-1, 2, -3, 4, -5));
console.log("Math.pow(2, 8): " + Math.pow(2, 8));
console.log("Math.random(): " + Math.random());
console.log("Math.round(2.5): " + Math.round(2.5));
console.log("Math.sign(-1.2): " + Math.sign(-1.2));
console.log("Math.sin(1): " + Math.sin(1));
console.log("Math.sinh(1): " + Math.sinh(1));
console.log("Math.sqrt(36): " + Math.sqrt(36));
console.log("Math.tan(1): " + Math.tan(1));
console.log("Math.tanh(1): " + Math.tanh(1));
console.log("Math.trunc(1.5): " + Math.trunc(1.5));

console.log("-------------");

var i = 11;
console.log("var i = 11;");

i++;
console.log("i++, i should be 12: " + i);

i *= 2;
console.log("i *= 2, i should be 24: " + i);

i /= 2;
console.log("i /= 2, i should be 12: " + i);

i -= 2;
console.log("i -= 2, i should be 10: " + i);

i %= 3;
console.log("i %= 3, i should be 1: " + i);

i--;
console.log("i--. i should be 0: " + i);
