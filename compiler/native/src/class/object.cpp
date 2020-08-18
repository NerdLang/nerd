#include "object.h"
#include "baseobject.cpp"

NJS::Class::Object::Object()
{
	BaseObject();
}

NJS::Class::Object::operator NJS::VAR() const
{
	auto _var = NJS::VAR();
	_var.type = NJS::Enum::Type::OBJECT;
	REGISTER[_ptr].a = this;
	return _var;
}

explicit NJS::Class::Object::operator bool() const
{
	return true;
}
explicit NJS::Class::Object::operator double() const
{
	return NAN;
}
explicit NJS::Class::Object::operator int() const
{
	return 0;
}
explicit NJS::Class::Object::operator std::string() const
{
	return "[object Object]";
}
explicit NJS::Class::Object::operator long long() const
{
	return NAN;
}
