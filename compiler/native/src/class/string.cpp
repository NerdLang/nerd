#include "string.h"
#include "object.cpp"
#include <limits>

NJS::Class::String::String()
{
	Object();
}

NJS::Class::String::String(const char *str)
{
	String();
	this->__NJS_VALUE = str;
}

NJS::Class::String::String(std::string str)
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
		return std::numeric_limits<OutputType>::quiet_NaN();
	return res;
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

NJS::VAR &NJS::Class::String::operator[](NJS::VAR _index) const
{
	if (_index.type != NJS::Enum::Type::NUMBER)
	{
		return Object::operator[]((std::string)_index);
	}
	auto &str = this->__NJS_VALUE;
	int i = (int)_index;
	return (i <= str.size() && i >= 0) ? str[i] : NJS::Value::undefined;
}

NJS::VAR &NJS::Class::String::operator[](NJS::VAR _index)
{
	if (_index.type != NJS::Enum::Type::NUMBER)
	{
		return Object::operator[]((std::string)_index);
	}
	auto &str = this->__NJS_VALUE;
	int i = (int)_index;
	return (i <= str.size() && i >= 0) ? str[i] : NJS::Value::undefined;
}

NJS::VAR NJS::Class::String::__iterator(){};
NJS::Class::String NJS::Class::String::charAt(std::vector<NJS::VAR> args)
{
	int index = args.size() ? (int)args[0] : 0;
	if (!isfinite(index))
	{
		index = 0;
	}
	return (std::string)(*this)[index];
};
int NJS::Class::String::charCodeAt(std::vector<NJS::VAR> args){
	return static_cast<int>(this->charAt(args).__NJS_VALUE.c_str()[0]);
};
int NJS::Class::String::codePointAt(std::vector<NJS::VAR> args){

};
NJS::Class::String NJS::Class::String::concat(std::vector<NJS::VAR> args){};
bool NJS::Class::String::endsWith(std::vector<NJS::VAR> args){};
NJS::Class::String NJS::Class::String::fixed(){};
bool NJS::Class::String::includes(std::vector<NJS::VAR> args){};
int NJS::Class::String::indexOf(std::vector<NJS::VAR> args){};
int NJS::Class::String::lastIndexOf(){};
NJS::Class::String NJS::Class::String::localeCompare(){};
NJS::Class::String NJS::Class::String::match(){};
NJS::Class::String NJS::Class::String::normalize(){};
NJS::Class::String NJS::Class::String::padEnd(){};
NJS::Class::String NJS::Class::String::padStart(){};
NJS::Class::String NJS::Class::String::repeat(){};
NJS::Class::String NJS::Class::String::replace(){};
NJS::Class::String NJS::Class::String::search(){};
NJS::Class::String NJS::Class::String::slice(){};
NJS::Class::String NJS::Class::String::split(){};
bool NJS::Class::String::startsWith(){};
NJS::Class::String NJS::Class::String::substr(){};
NJS::Class::String NJS::Class::String::substring(){};
NJS::Class::String NJS::Class::String::toLocaleLowerCase(){};
NJS::Class::String NJS::Class::String::toLocaleUpperCase(){};
NJS::Class::String NJS::Class::String::toLowerCase(){};
NJS::Class::String NJS::Class::String::toUpperCase(){};
NJS::Class::String NJS::Class::String::trim(){};
NJS::Class::String NJS::Class::String::trimEnd(){};
NJS::Class::String NJS::Class::String::trimStart(){};
