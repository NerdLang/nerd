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
}

var g = new Greeter("NectarJS", 3);

g.Say();