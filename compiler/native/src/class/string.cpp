#include "string.h"
#include "baseobject.cpp"

NJS::Class::String::String()
{
	BaseObject();
}

NJS::Class::String::String(const char *str)
{
	String();
	this->__NJS_VALUE = str;
}

template <typename ConvertFunc, typename OutputType>
const OutputType convertWith(const std::string str)
{
	std::string::size_type last;
	OutputType res = ConvertFunc(str.c_str(), &last, 10);
	if (last == str.end())
		return NAN;
	return res;
}

NJS::Class::String::operator NJS::VAR() const
{
	auto _var = NJS::VAR();
	_var.type = NJS::Enum::Type::STRING;
	REGISTER[_ptr].s = this;
	return _var;
}
explicit NJS::Class::String::operator bool() const
{
	return this->__NJS_VALUE.size();
}
explicit NJS::Class::String::operator double() const
{
	return convertWith<std::stod, double>(this->__NJS_VALUE);
}
explicit NJS::Class::String::operator int() const
{
	return convertWith<std::stoi, int>(this->__NJS_VALUE);
}
explicit NJS::Class::String::operator std::string() const
{
	return this->__NJS_VALUE;
}
explicit NJS::Class::String::operator long long() const
{
	return convertWith<std::stoll, long long>(this->__NJS_VALUE);
}
NJS::VAR & NJS::Class::String::operator[](NJS::VAR _index) const
{
	if (_index.type != NJS::Enum::Type::NUMBER)
	{
		return BaseObject::operator[](_index);
	}
	auto &str = this->__NJS_VALUE;
	int i = (int)_index;
	return (i <= str.size() && i >= 0) ? str[i] : NJS::Value::undefined;
}
NJS::VAR & NJS::Class::String::operator[](NJS::VAR _index)
{
	if (_index.type != NJS::Enum::Type::NUMBER)
	{
		return BaseObject::operator[](_index);
	}
	auto &str = this->__NJS_VALUE;
	int i = (int)_index;
	return (i <= str.size() && i >= 0) ? str[i] : NJS::Value::undefined;
}

NJS::VAR NJS::Class::String::__iterator(){};
NJS::VAR NJS::Class::String::charAt(std::vector<NJS::VAR> args)
{
	int index = args.size() ? (int)args[0] : 0;
	if (!isfinite(index))
	{
		index = 0;
	}
	return (*this)[index];
};
NJS::VAR NJS::Class::String::charCodeAt(){};
NJS::VAR NJS::Class::String::codePointAt(){};
NJS::VAR NJS::Class::String::concat(){};
NJS::VAR NJS::Class::String::endsWith(){};
NJS::VAR NJS::Class::String::fixed(){};
NJS::VAR NJS::Class::String::includes(){};
NJS::VAR NJS::Class::String::indexOf(){};
NJS::VAR NJS::Class::String::lastIndexOf(){};
NJS::VAR NJS::Class::String::localeCompare(){};
NJS::VAR NJS::Class::String::match(){};
NJS::VAR NJS::Class::String::normalize(){};
NJS::VAR NJS::Class::String::padEnd(){};
NJS::VAR NJS::Class::String::padStart(){};
NJS::VAR NJS::Class::String::repeat(){};
NJS::VAR NJS::Class::String::replace(){};
NJS::VAR NJS::Class::String::search(){};
NJS::VAR NJS::Class::String::slice(){};
NJS::VAR NJS::Class::String::split(){};
NJS::VAR NJS::Class::String::startsWith(){};
NJS::VAR NJS::Class::String::substr(){};
NJS::VAR NJS::Class::String::substring(){};
NJS::VAR NJS::Class::String::toLocaleLowerCase(){};
NJS::VAR NJS::Class::String::toLocaleUpperCase(){};
NJS::VAR NJS::Class::String::toLowerCase(){};
NJS::VAR NJS::Class::String::toUpperCase(){};
NJS::VAR NJS::Class::String::trim(){};
NJS::VAR NJS::Class::String::trimEnd(){};
NJS::VAR NJS::Class::String::trimStart(){};
