#include "boolean.h"
#include "object.cpp"
#include <string>

NJS::Class::Boolean::Boolean()
{
	Object();
	__NJS_VALUE = false;
}
NJS::Class::Boolean::Boolean(bool b)
{
	Object();
	__NJS_VALUE = b;
}

explicit NJS::Class::Boolean::operator bool() const
{
	return __NJS_VALUE;
}
explicit NJS::Class::Boolean::operator double() const
{
	return __NJS_VALUE;
}
explicit NJS::Class::Boolean::operator int() const
{
	return __NJS_VALUE;
}
explicit NJS::Class::Boolean::operator std::string() const
{
	return __NJS_VALUE ? "true" : "false";
}
explicit NJS::Class::Boolean::operator long long() const
{
	return __NJS_VALUE;
}
NJS::Class::Boolean NJS::Class::Boolean::operator=(const Boolean &_v)
{
	__NJS_VALUE = _v.__NJS_VALUE;
	_v.Delete();
	return *this;
}
NJS::Class::Boolean NJS::Class::Boolean::operator=(const bool &_v)
{
	__NJS_VALUE = _v;
	return *this;
}
