#include "object.h"
#include "../memory.h"
#include <limits>

#define __NJS_CreateMethodToClass(name, fn) (*this)[name] = (NJS::VAR)NJS::Class::Function(new std::function<__NJS_VAR(std::vector<NJS::VAR>)>([&](std::vector<NJS::VAR> __NJS_VARARGS) { return fn(__NJS_VARARGS); }));

NJS::Class::Object::Object()
{
	Undefined();
	__NJS_CreateMethodToClass("valueOf", this->valueOf);
	__NJS_CreateMethodToClass("toString", this->toString);
	__NJS_CreateMethodToClass("toLocaleString", this->toLocaleString);
}

explicit NJS::Class::Object::operator bool() const
{
	return true;
}
explicit NJS::Class::Object::operator double() const
{
	return std::numeric_limits<double>::quiet_NaN();
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
	return std::numeric_limits<long long>::quiet_NaN();
}

NJS::VAR const &NJS::Class::Object::operator[](std::string _index) const
{
	auto _obj = &this->__OBJECT;
	for (int _i = 0, _j = (*_obj).size(); _i < _j; _i++)
	{
		if (_index.compare((*_obj)[_i].first) == 0)
		{
			return (*_obj)[_i].second;
		}
	}
	return NJS::Value::undefined;
}

NJS::VAR &NJS::Class::Object::operator[](NJS::VAR _index)
{
	auto &_obj = this->__OBJECT;
	auto _str = (std::string)_index;
	auto _value = NJS::VAR();
	for (int _i = 0, _j = _obj.size(); _i < _j; _i++)
	{
		if (_str.compare(_obj[_i].first) == 0)
		{
			auto &reg = NJS::MEMORY::REGISTER;
			reg[_obj[_i].second._ptr] = reg[_value._ptr];
			return _value;
		}
	}
	_obj.push_back(std::pair<const char *, NJS::VAR>(_str.c_str(), _value));
	return _value;
}

NJS::VAR NJS::Class::Object::valueOf() const
{
	return (*this);
}

NJS::VAR NJS::Class::Object::toLocaleString() const
{
	return this->toString();
}
NJS::VAR NJS::Class::Object::toString() const
{
	return (std::string)(*this);
}
