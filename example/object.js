var obj = 
{
	"key": "value"
}

obj.fn = function(_txt) { console.log("Obj->fn(): " + _txt); };

console.log("Obj->key: " + obj.key);

obj.fn("Hello !");