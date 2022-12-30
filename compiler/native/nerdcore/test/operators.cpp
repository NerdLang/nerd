#include "../src/nerd.hpp"

using namespace NerdCore;
using namespace NerdCore::Global;
using namespace NerdCore::Class;
using namespace NerdCore::Functions;

int main()
{
	try 
	{
		var a = 1;
		
		println(a + a);
		println(a + 1);
		println(a + "1");
		
		println(1 + a);
		println("1" + a);
		
		println(a - a);
		println(a - 1);
		println(a - "1");
		
		println(1 - a);
		println("1" - a);
		
		println(a * a);
		println(a * 1);
		println(a * "1");
		
		println(1 * a);
		println("1" * a);
		
		println(a / a);
		println(a / 1);
		println(a / "1");
		
		println(1 / a);
		println("1" / a);
		
		println(a == a);
		println(a == 1);
		println(a == "1");
		
		println(a != a);
		println(a != 1);
		println(a != "1");
		
		println(a > a);
		println(a > 1);
		println(a > "1");
		
		println(a < a);
		println(a < 1);
		println(a < "1");
		
		println(a >= a);
		println(a >= 1);
		println(a >= "1");
		
		println(a <= a);
		println(a <= 1);
		println(a <= "1");
		
		println(a | a);
		println(a | 1);
		println(a | "1");
		
		println(a & a);
		println(a & 1);
		println(a & "1");
		
		println(a ^ a);
		println(a ^ 1);
		println(a ^ "1");
	}
	catch(var& error)
	{
		println(error);
	}
	return 0;
}