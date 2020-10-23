function test(_lambda)
{
	_lambda();
}

test(function(){console.log("Hello from Lambda")});