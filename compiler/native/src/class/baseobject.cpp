#include "baseobject.h"
#include <string>
#include "base.cpp"
#include "../values.cpp"

#define __NJS_CreateMethodToClass(name, fn) (*this)[name] = (NJS::VAR)NJS::Class::Function(new function<__NJS_VAR (vector<VAR>)>([&](vector<VAR> __NJS_VARARGS){ return fn(__NJS_VARARGS); }));

NJS::Class::BaseObject::BaseObject()
{
	Base();
	__NJS_CreateMethodToClass("valueOf", this->valueOf);
	__NJS_CreateMethodToClass("toString", this->toString);
	__NJS_CreateMethodToClass("toLocaleString", this->toLocaleString);
}

NJS::VAR const &NJS::Class::BaseObject::operator[](NJS::VAR _index) const
{
	auto _obj = &this->__OBJECT;
	auto _str = (std::string)_index;
	for (int _i = 0, _j = (*_obj).size(); _i < _j; _i++)
	{
		if (_str.compare((*_obj)[_i].first) == 0)
		{
			return (*_obj)[_i].second;
		}
	}
	return NJS::Value::undefined;
}

NJS::VAR &NJS::Class::BaseObject::operator[](NJS::VAR _index)
{
	auto &_obj = this->__OBJECT;
	auto _str = (std::string)_index;
	auto _value = NJS::VAR();
	for (int _i = 0, _j = _obj.size(); _i < _j; _i++)
	{
		if (_str.compare(_obj[_i].first) == 0)
		{
			REGISTER[_obj[_i].second._ptr] = REGISTER[_value._ptr];
			return _value;
		}
	}
	_obj.push_back(std::pair<const char *, NJS::VAR>(_str.c_str(), _value));
	return _value;
}

NJS::VAR NJS::Class::BaseObject::valueOf() const
{
	return (*this);
}

NJS::VAR NJS::Class::BaseObject::toLocaleString() const
{
	return this->toString();
}
NJS::VAR NJS::Class::BaseObject::toString() const
{
	return (std::string)(*this);
}
