#include "object.h"
#include "_base.cpp"

#define __NJS_CreateMethodToClass(name, fn) (*this)[name] = (NJS::VAR)NJS::Class::Function(new std::function<__NJS_VAR(std::vector<NJS::VAR>)>([&](std::vector<NJS::VAR> __NJS_VARARGS) { return fn(__NJS_VARARGS); }));

NJS::Class::Object::Object()
{
	Base();
	(*this)["toString"] = (NJS::VAR)NJS::Class::Function(new std::function<__NJS_VAR(std::vector<NJS::VAR>)>([&](std::vector<NJS::VAR> __NJS_VARARGS) { return this->toString(__NJS_VARARGS); }));
	__NJS_CreateMethodToClass("valueOf", this->valueOf);
	__NJS_CreateMethodToClass("toString", this->toString);
	__NJS_CreateMethodToClass("toLocaleString", this->toLocaleString);
}

NJS::Class::Object::Object(std::vector<std::pair<const char *, NJS::VAR>> &obj)
{
	Object();
	__NJS_VALUE = obj;
}

NJS::VAR NJS::Class::Object::valueOf() const
{
	return *this;
}

NJS::VAR NJS::Class::Object::toLocaleString() const
{
	return this->toString();
}
NJS::VAR NJS::Class::Object::toString() const
{
	return (std::string)(*this);
}
