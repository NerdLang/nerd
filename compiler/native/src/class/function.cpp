#include "function.h"
#include "baseobject.cpp"

NJS::Class::Function::Function(void *_f)
{
	BaseObject();
	NJS::VAR proto = NJS::Class::Object();
	(*this)["prototype"] = proto;
	__NJS_VALUE = _f;
}
NJS::Class::Function::operator NJS::VAR() const
{
	auto _var = NJS::VAR();
	_var.type = NJS::Enum::Type::FUNCTION;
	REGISTER[_ptr].f = this;
	return _var;
}
explicit NJS::Class::Function::operator bool() const
{
	return true;
}
explicit NJS::Class::Function::operator double() const
{
	return NJS::Value::NaN;
}
explicit NJS::Class::Function::operator int() const
{
	return 0;
}
explicit NJS::Class::Function::operator std::string() const
{
	return "function () { [native code] }";
}
explicit NJS::Class::Function::operator long long() const
{
	return NJS::Value::NaN;
}
