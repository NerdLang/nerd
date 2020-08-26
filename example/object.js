var _str = "One string";
var obj = 
{
	"key": "value",
	"a": 1,
	"b": 2,
	"subobj":
	{
		in: "in obj",
	},
	"operation": this.a + this.b,
	"str": _str,
};

obj.fn = function(_txt) { console.log("obj.fn(): " + _txt); };

console.log("obj.key: " + obj.key);
console.log("obj.a + obj.b: " + (obj.a + obj.b));
console.log("obj.subobj.in: " + obj.subobj.in);
console.log("obj.operation this.a + this.b : " + obj.operation);
obj.fn("Hello !");
console.log("obj.toString(): " + obj.toString());

console.log("obj.toString = 'Hello'");
obj.toString = "Hello";
console.log("obj.toString: " + obj.toString);

console.log("obj.valueOf(): " + obj.valueOf());