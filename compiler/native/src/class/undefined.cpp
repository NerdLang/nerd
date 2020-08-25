#include "undefined.h"

NJS::Class::Undefined::Undefined()
{
	this->cnt++;
}

void NJS::Class::Undefined::Delete()
{
	this->cnt--;
	if (this->cnt == 0)
	{
		delete this;
	}
}

explicit NJS::Class::Undefined::operator bool() const
{
	return false;
}
explicit NJS::Class::Undefined::operator double() const
{
	return 0;
}
explicit NJS::Class::Undefined::operator int() const
{
	return 0;
}
explicit NJS::Class::Undefined::operator std::string() const
{
	return "undefined";
}
explicit NJS::Class::Undefined::operator long long() const
{
	return 0;
}

template<typename T> NJS::VAR NJS::Class::Undefined::operator=(T &_v)
{
	__NJS_VALUE = _v.__NJS_VALUE;
	_v.Delete();
	return *this;
}

const NJS::VAR &NJS::Class::Undefined::operator[](std::string _index) const
{
	throw NJS::VAR("TypeError: Cannot read property '" + _index + "' of " + (std::string) * this);
}
NJS::VAR &NJS::Class::Undefined::operator[](std::string _index)
{
	throw NJS::VAR("TypeError: Cannot read property '" + _index + "' of " + (std::string) * this);
}

template <class... Args>
NJS::VAR NJS::Class::Undefined::operator()(Args... args) const
{
	throw NJS::VAR("TypeError: " + (std::string) * this + " is not a function")
}
