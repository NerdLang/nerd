class Greeter 
{
	constructor(value, age)
	{
		this.name = value;
		this.age = age;
	}
	
	Say()
	{
		console.log("Hello, my name is " + this.name + ", I'm " + this.age + "yo");
	}
	
	static Welcome(name)
	{
		console.log("Welcome to a new era of coding, " + name);
	}
}

var g = new Greeter("NectarJS", 3);

g.Say();

Greeter.Welcome("John Doe");