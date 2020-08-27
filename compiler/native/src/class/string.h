#pragma once
<<<<<<< HEAD
#include "object.h"

namespace NJS::Class
{
	class String : public Object
	{
	public:
		const char *name = "string";
		const NJS::Enum::Type type = NJS::Enum::Type::STRING;
		String();
		String(const char *str);
		String(std::string str);
		std::string __NJS_VALUE;
		explicit operator bool() const;
		explicit operator double() const;
		explicit operator int() const;
		explicit operator std::string() const;
		explicit operator long long() const;
		NJS::VAR &operator[](NJS::VAR _index) const;
		NJS::VAR &operator[](NJS::VAR _index);
		NJS::VAR __iterator();
		String charAt(std::vector<NJS::VAR> args);
		int charCodeAt(std::vector<NJS::VAR> args);
		int codePointAt(std::vector<NJS::VAR> args);
		String concat(std::vector<NJS::VAR> args);
		bool endsWith(std::vector<NJS::VAR> args);
		String fixed();
		bool includes(std::vector<NJS::VAR> args);
		int indexOf(std::vector<NJS::VAR> args);
		int lastIndexOf();
		String localeCompare();
		String match();
		String normalize();
		String padEnd();
		String padStart();
		String repeat();
		String replace();
		String search();
		String slice();
		String split();
		bool startsWith();
		String substr();
		String substring();
		String toLocaleLowerCase();
		String toLocaleUpperCase();
		String toLowerCase();
		String toUpperCase();
		String trim();
		String trimEnd();
		String trimStart();
	};
=======
#include "string_header.h"
#include <string>
#include <limits>

namespace NJS::Class
{
	// Constructors
	String::String() { ++counter; }
	String::String(std::string val)
	{
		String();
		value = val;
		(*this)["length"] = (int)val.size();
	}
	String::String(const char* val)
	{
		String();
		value = val;
		(*this)["length"] = (int)value.size();
	}
	// Methods
	String::~String()
	{
		object.~vector();
	}
	void String::Delete() noexcept
	{
		if (--counter == 0)
		{
			delete this;
		}
	}
	// Native cast
	explicit String::operator bool() const noexcept { return value.size() > 0; }
	explicit String::operator double() const noexcept
	{
		std::string::size_type end;
		auto res = std::stod(value, &end);
		return end == value.size() ? res : std::numeric_limits<double>::quiet_NaN();
	}
	explicit String::operator int() const noexcept
	{
		std::string::size_type end;
		auto res = std::stoi(value, &end, 10);
		return end == value.size() ? res : std::numeric_limits<int>::quiet_NaN();
	}
	explicit String::operator long long() const noexcept
	{
		std::string::size_type end;
		auto res = std::stoll(value, &end, 10);
		return end == value.size() ? res : std::numeric_limits<long long>::quiet_NaN();
	}
	explicit String::operator std::string() const noexcept { return value; }
	// Main operators
	NJS::VAR const &String::operator[](NJS::VAR key) const
	{
		if (key.type == NJS::Enum::Type::NUMBER)
		{
			auto i = (int)key;
			if (i >= 0 && i <= value.size())
			{
				return value.at(i);
			}
		}
		auto &obj = this->object;
		auto index = (std::string)key;
		for (auto pair : obj)
		{
			if (index.compare(pair.first) == 0)
			{
				return pair.second;
			}
		}
		return NJS::VAR();
	}
	NJS::VAR &String::operator[](NJS::VAR key)
	{
		if (key.type == NJS::Enum::Type::NUMBER)
		{
			auto i = (int)key;
			if (i >= 0)
			{
				if (i >= value.size())
				{
					value.resize(i + 1);
					(*this)["length"] = (int)value.size();
				}
				return NJS::VAR(value.at(i));
			}
		}
		auto &obj = this->object;
		auto index = (std::string)key;
		for (auto pair : obj)
		{
			if (index.compare(pair.first) == 0)
			{
				return pair.second;
			}
		}
		auto value = NJS::VAR();
		obj.push_back(std::pair<const char *, NJS::VAR>(index.c_str(), value));
		return value;
	}
	template <class... Args>
	NJS::VAR String::operator()(Args... args) const { throw InvalidTypeException(); }
	// Comparation operators
	String String::operator!() const { throw InvalidTypeException(); }
	bool String::operator==(const String &_v1) const { return value.compare(_v1.value) == 0; }
	// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
	// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
	bool String::operator!=(const String &_v1) const { return value.compare(_v1.value) != 0; }
	bool String::operator<(const String &_v1) const { return value.at(0) < _v1.value.at(0); }
	bool String::operator<=(const String &_v1) const { return value.at(0) <= _v1.value.at(0); }
	bool String::operator>(const String &_v1) const { return value.at(0) > _v1.value.at(0); }
	bool String::operator>=(const String &_v1) const { return value.at(0) >= _v1.value.at(0); }
	// Numeric operators
	String String::operator+() const { throw InvalidTypeException(); }
	String String::operator-() const { throw InvalidTypeException(); }
	String String::operator++(const int _v1) { throw InvalidTypeException(); }
	String String::operator--(const int _v1) { throw InvalidTypeException(); }
	String String::operator+(const String &_v1) const { return value + _v1.value; }
	String String::operator+=(const String &_v1) { value += _v1.value; return *this; }
	String String::operator-(const String &_v1) const { throw InvalidTypeException(); }
	String String::operator-=(const String &_v1) { throw InvalidTypeException(); }
	String String::operator*(const String &_v1) const { throw InvalidTypeException(); }
	String String::operator*=(const String &_v1) { throw InvalidTypeException(); }
	// TODO: "**" and "**=" operators
	String String::operator/(const String &_v1) const { throw InvalidTypeException(); }
	String String::operator/=(const String &_v1) { throw InvalidTypeException(); }
	String String::operator%(const String &_v1) const { throw InvalidTypeException(); }
	String String::operator%=(const String &_v1) { throw InvalidTypeException(); }
	String String::operator&(const String &_v1) const { throw InvalidTypeException(); }
	String String::operator|(const String &_v1) const { throw InvalidTypeException(); }
	String String::operator^(const String &_v1) const { throw InvalidTypeException(); }
	String String::operator~() const { throw InvalidTypeException(); }
	String String::operator>>(const String &_v1) const { throw InvalidTypeException(); }
	String String::operator<<(const String &_v1) const { throw InvalidTypeException(); }
	String String::operator&=(const String &_v1) { throw InvalidTypeException(); }
	String String::operator|=(const String &_v1) { throw InvalidTypeException(); }
	String String::operator^=(const String &_v1) { throw InvalidTypeException(); }
	String String::operator>>=(const String &_v1) { throw InvalidTypeException(); }
	String String::operator<<=(const String &_v1) { throw InvalidTypeException(); }
	// TODO: ">>>" and ">>>=" operators
>>>>>>> develop-classes
} // namespace NJS::Class
