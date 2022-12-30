#include "../src/nerd.hpp"
using namespace NerdCore;
using namespace NerdCore::Global;
using namespace NerdCore::Class;
using namespace NerdCore::Functions;

int main(int argc, char** argv)
{
	var args = getArguments(argc, argv);
	println(args);
	
	var o = new Object();
	o["int"] = 1;
	o["string"] = "str";
	println(o);

	var init = new Object(
	{
		{"one", 1}, // number
		{"two", "2"}, // string
		{"three", {1,2,3}}, // array
		{"four", new Object("key", "value")}, // sub object with only one key
		{"five", new Object({"key", 1})}, // another way with non string value
		{"six", new Object({ {"key", 2} })}, // another way with non string value
	});
	println(init);

	return 0;
}
