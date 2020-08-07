try 
{
	throw {msg: "Exception raised", code: 1}
}
catch(e)
{
	console.log(e);
}
finally
{
	console.log("Cleaning");
}
