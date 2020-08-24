#include "native.h"
#include "function.cpp"

NJS::Class::Native::Native()
{
	Function();
}

NJS::Class::Native::Native(void *_f)
{
	Function(_f);
}

explicit NJS::Class::Native::operator std::string() const
{
	return "[native]";
}
