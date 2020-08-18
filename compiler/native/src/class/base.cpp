#include "base.h"

NJS::Class::Base::Base()
{
	this->cnt++;
}

void NJS::Class::Base::Delete()
{
	this->cnt--;
	if (this->cnt < 1)
	{
		delete this;
	}
}

NJS::Class::Base::operator NJS::VAR() const {
	return NJS::VAR();
}
explicit NJS::Class::Base::operator bool() const {
	return false;
}
explicit NJS::Class::Base::operator double() const {
	return 0;
}
explicit NJS::Class::Base::operator int() const {
	return 0;
}
explicit NJS::Class::Base::operator std::string() const {
	return "";
}
explicit NJS::Class::Base::operator long long() const {
	return 0;
}

NJS::VAR NJS::Class::Base::operator()() const
{
	NJS::VAR();
}
