#include "../src/nerd.hpp"
using namespace NerdCore;
using namespace NerdCore::Global;
using namespace NerdCore::Class;
using namespace NerdCore::Functions;

int main(int argc, char** argv)
{
	var arr = new Array();
	println(arr);
	
	var initArr = new Array(0, "one", 2, "three");
	println(initArr);

	var initArr2 = {"zero", 1, "two", 3};
	println(initArr2);

	return 0;
}
