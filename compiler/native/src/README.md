# NectarCPP
Nectar C++ lib/runtime

# Gettin started

You need a C++ compile (g++ or clang++) to use NectarCPP.

Clone this repository, and create a file mycode.cpp. Add in this file the folling lines: 

```
#include "../src/nectar.hpp"
using namespace NectarCore;
using namespace NectarCore::Global;
using namespace NectarCore::Class;
using namespace NectarCore::Functions;

int main(int argc, char** argv)
{
	var args = getArguments(argc, argv);
	println(args);
	
	var o = new Object();
	o["int"] = 1;
	o["string"] = "str";
	println(o);

	return 0;
}
```

then:
- Compile the headers: `g++ -std=c++17 -c src/nectar.hpp -Ofast`
- Compile the main lib: `g++ -std=c++17 -c src/nectar.cpp -Ofast`
- Compile your code `g++ -std=c++17 nectar.o mycode.cpp -lpthread -Ofast -o myapp`

You can then modify your app, and only compile your code, because the libs are already compiled:
- Compile your code `g++ -std=c++17 nectar.o mycode.cpp -lpthread -Ofast -o myapp`

