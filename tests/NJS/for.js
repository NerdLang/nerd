var _object = 
{
	"one" : 1,
	"two" : "2",
	"three" : "three"
};

console.log("Object.keys(_object).length: " + Object.keys(_object).length);

console.log();
console.log("for(var o in _object):");
console.log();

for(var o in _object)
{
	console.log(o + ":" + _object[o]);
}
