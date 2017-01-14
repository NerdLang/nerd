console.log("BEFORE REQUIRE FIBO");
console.write("FIBO RESULT : ");
require("fibo.js");
console.log("AFTER REQUIRE FIBO");
console.log("--------------------------");

console.log("BEFORE REQUIRE OBJECT");
require("object.js");
console.log("AFTER REQUIRE OBJECT");
console.log("--------------------------");

var a = {d:[0,1,2], c:[3,4,5],b:[{b:" so", d:" good ", c:"It works"}], ha:"ha", ho:"ho", hi:"hi", hy:"hi", hu:"hu", yo: "!"};

console.write(a.b[0].c);
console.write(a.b[0].b);
console.write(a.b[0].d);
console.write(a.yo);
