function protoObject()
{
	
}

protoObject.prototype.hello = "hello";
protoObject.prototype.sayHello = function(){console.log("Hello from prototype");};

var greeter = new protoObject();

console.log(greeter.hello);
greeter.sayHello();
