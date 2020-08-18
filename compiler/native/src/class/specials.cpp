#include "specials.h"
#include "base.cpp"
#include "../values.cpp"

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
	throw __NJS_VAR("TypeError: Cannot read property '" + (std::string)_index + "' of " + (std::string)*this);
}
NJS::VAR &NJS::Class::Value::undefined::operator[](NJS::VAR _index)
{
	throw __NJS_VAR("TypeError: Cannot read property '" + (std::string)_index + "' of " + (std::string)*this);
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


/** Infinity **/
NJS::Class::Value::Infinity::Infinity()
{
	Number();
}

NJS::Class::Value::Infinity::operator NJS::VAR() const
{
	return NJS::Value::Infinity * (*this);
}

explicit NJS::Class::Value::NaN::operator std::string() const
{
	return ((int)*this < 0 ? "-" : "") + "Infinity";
}
