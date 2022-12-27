#include "../src/nerd.hpp"

using namespace NerdCore;
using namespace NerdCore::Global;
using namespace NerdCore::Class;
using namespace NerdCore::Functions;

int main()
{
	try 
	{
		var _str = "string";
		std::cout << "_str: " << _str << std::endl;
		var _nbr = 123;
		std::cout << "_nbr: " << _nbr << std::endl;
		const char* c = _str;
		std::cout << "char: " << c << std::endl;
		std::string s = _str;
		std::cout << "string: " << s << std::endl;
		std::string_view sv = _str;
		std::cout << "string_view: " << sv << std::endl;
		int i = _nbr;
		std::cout << "int: " << i << std::endl;
		double d = _nbr;
		std::cout << "double: " << d << std::endl;
		long long ll = _nbr;
		std::cout << "long long: " << ll << std::endl;
		bool b = _nbr;
		std::cout << "bool: " << b << std::endl;
	}
	catch(var& error)
	{
		println(error);
	}
	return 0;
}