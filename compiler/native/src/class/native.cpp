#include "native.h"
#include "function.cpp"

NJS::Class::Native::Native(void *_f)
{
	Function(_f);
}
NJS::Class::Native::operator NJS::VAR() const
{
	auto _var = NJS::VAR();
	_var.type = NJS::Enum::Type::NATIVE;
	REGISTER[_ptr].f = this;
	return _var;
}
explicit NJS::Class::Native::operator bool() const
{
	return true;
}
explicit NJS::Class::Native::operator double() const
{
	return NJS::Value::NaN;
}
explicit NJS::Class::Native::operator int() const
{
	return 0;
}
explicit NJS::Class::Native::operator std::string() const
{
	return "[native]";
}
explicit NJS::Class::Native::operator long long() const
{
	return NJS::Value::NaN;
}
