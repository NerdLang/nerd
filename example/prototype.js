function protoObject(){}

protoObject.prototype.hello = "Hello";
protoObject.prototype.sayHello = function(){console.log(this.hello + " from prototype");};

var greeter = new protoObject();

console.log(greeter.hello);
greeter.sayHello();

console.log("greeter instanceof protoObject: " + (greeter instanceof protoObject));

function a(){};
a.constructor = protoObject.constructor;
console.log(new a());
