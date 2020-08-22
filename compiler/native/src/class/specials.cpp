#include "specials.h"
#include "base.cpp"
#include "../values.h"

/** undefined **/
NJS::Class::Value::undefined::undefined()
{
	Base();
}

NJS::Class::Value::undefined::operator NJS::VAR() const
{
	return NJS::Value::undefined;
}

explicit NJS::Class::Value::undefined::operator std::string() const
{
	return "undefined";
}

const NJS::VAR &NJS::Class::Value::undefined::operator[](NJS::VAR _index) const
{
	throw NJS::VAR("TypeError: Cannot read property '" + (std::string)_index + "' of " + (std::string)*this);
}
NJS::VAR &NJS::Class::Value::undefined::operator[](NJS::VAR _index)
{
	throw NJS::VAR("TypeError: Cannot read property '" + (std::string)_index + "' of " + (std::string)*this);
}


/** null **/
NJS::Class::Value::null::null()
{
	undefined();
}

NJS::Class::Value::null::operator NJS::VAR() const
{
	return NJS::Value::null;
}

explicit NJS::Class::Value::null::operator std::string() const
{
	return "null";
}


/** NaN **/
NJS::Class::Value::NaN::NaN()
{
	Number();
}

NJS::Class::Value::NaN::operator NJS::VAR() const
{
	return NJS::Value::NaN;
}

explicit NJS::Class::Value::NaN::operator std::string() const
{
	return "NaN";
}

NJS::Class::Value::NaN NJS::Class::Value::NaN::operator-() { return *this; }
NJS::Class::Value::NaN NJS::Class::Value::NaN::operator+(const NJS::Class::Value::NaN &_v1) { return *this; }
NJS::Class::Value::NaN NJS::Class::Value::NaN::operator+=(const NJS::Class::Value::NaN &_v1) { return *this; }
NJS::Class::Value::NaN NJS::Class::Value::NaN::operator-(const NJS::Class::Value::NaN &_v1) { return *this; }
NJS::Class::Value::NaN NJS::Class::Value::NaN::operator-=(const NJS::Class::Value::NaN &_v1) { return *this; }
NJS::Class::Value::NaN NJS::Class::Value::NaN::operator*(const NJS::Class::Value::NaN &_v1) { return *this; }
NJS::Class::Value::NaN NJS::Class::Value::NaN::operator*=(const NJS::Class::Value::NaN &_v1) { return *this; }
NJS::Class::Value::NaN NJS::Class::Value::NaN::operator/(const NJS::Class::Value::NaN &_v1) { return *this; }
NJS::Class::Value::NaN NJS::Class::Value::NaN::operator/=(const NJS::Class::Value::NaN &_v1) { return *this; }
NJS::Class::Value::NaN NJS::Class::Value::NaN::operator%(const NJS::Class::Value::NaN &_v1) { return *this; }
NJS::Class::Value::NaN NJS::Class::Value::NaN::operator%=(const NJS::Class::Value::NaN &_v1) { return *this; }
NJS::Class::Value::NaN NJS::Class::Value::NaN::operator++(const int _v1) { return *this; }
NJS::Class::Value::NaN NJS::Class::Value::NaN::operator--(const int _v1) { return *this; }
bool NJS::Class::Value::NaN::operator==(const NJS::Class::Value::NaN &_v1) { return false; }
bool NJS::Class::Value::NaN::operator!=(const NJS::Class::Value::NaN &_v1) { return true; }
bool NJS::Class::Value::NaN::operator<(const NJS::Class::Value::NaN &_v1) { return false; }
bool NJS::Class::Value::NaN::operator<=(const NJS::Class::Value::NaN &_v1){ return false; }
bool NJS::Class::Value::NaN::operator>(const NJS::Class::Value::NaN &_v1) { return false; }
bool NJS::Class::Value::NaN::operator>=(const NJS::Class::Value::NaN &_v1) { return false; }
