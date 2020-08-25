#include "_base.h"
#include "../memory.h"
#include <limits>

#define __NJS_CreateMethodToClass(name, fn) (*this)[name] = (NJS::VAR)NJS::Class::Function(new std::function<__NJS_VAR(std::vector<NJS::VAR>)>([&](std::vector<NJS::VAR> __NJS_VARARGS) { return fn(__NJS_VARARGS); }));

NJS::Class::Base::Base()
{
	Undefined();
}

NJS::Class::Base::Base(std::nullptr_t _ptr)
{
	Base();
	__OBJECT = _ptr;
}

inline bool NJS::Class::Base::isNull() const
{
	return __OBJECT == nullptr;
}

explicit NJS::Class::Base::operator bool() const
{
	return !isNull();
}
explicit NJS::Class::Base::operator double() const
{
	return std::numeric_limits<double>::quiet_NaN();
}
explicit NJS::Class::Base::operator int() const
{
	return 0;
}
explicit NJS::Class::Base::operator std::string() const
{
	return isNull() ? "null" : "[object Base]";
}
explicit NJS::Class::Base::operator long long() const
{
	return std::numeric_limits<long long>::quiet_NaN();
}

NJS::VAR const &NJS::Class::Base::operator[](std::string _index) const
{
	if (isNull())
	{
		return Undefined::operator[](_index);
	}
	auto &_obj = *this->__OBJECT;
	for (int _i = 0, _j = _obj.size(); _i < _j; _i++)
	{
		if (_index.compare(_obj[_i].first) == 0)
		{
			return _obj[_i].second;
		}
	}
	return NJS::Value::undefined;
}

NJS::VAR &NJS::Class::Base::operator[](std::string _index)
{
	if (isNull())
	{
		return Undefined::operator[](_index);
	}
	auto &_obj = *this->__OBJECT;
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
