var _str = "One string";
var obj = 
{
	"key": "value",
	"a": 1,
	"b": 2,
	"str": _str,
};

obj.fn = function(_txt) { console.log("obj->fn(): " + _txt); };

console.log("obj->key: " + obj.key);
console.log("obj->a + obj->b: " + (obj.a + obj.b));

obj.fn("Hello !");