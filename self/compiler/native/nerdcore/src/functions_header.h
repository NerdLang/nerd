/*
	Copyright (c) 2021 NerdLang - Adrien THIERRY and contributors

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

*/

NerdCore::VAR __NERD_Log_Console(NerdCore::VAR _var);
NerdCore::VAR __NERD_Object_Keys(NerdCore::VAR _var);
NerdCore::VAR __NERD_Object_Stringify(NerdCore::VAR _var);
NerdCore::VAR __NERD_Object_Stringify(NerdCore::VAR _var, bool _bracket);
NerdCore::VAR __NERD_Object_Clone(NerdCore::VAR& _var);
NerdCore::VAR __NERD_Object_Set(std::string _index, NerdCore::VAR _value, NerdCore::Type::object_t *_obj);
std::string __NERD_DOUBLE_TO_STRING(double _var);

/*** String MANIPULATION ***/

#ifdef __NERD_ENV_ARDUINO
namespace std
{
	template <typename m>
	string to_string(m _var)
	{
		std::stringstream output;
		output << _var;
		return output.str();
	}
	int isnan(double __x)
	{
		return ::isnan(__x);
	}
	inline int isfinite(double __x)
	{
		return ::isfinite(__x);
	}
	inline int signbit(double __x)
	{
		return ::signbit(__x);
	}
	inline double stod(std::string _str, std::string::size_type* sz)
	{
		*sz = _str.length();
		return String(_str.c_str()).toFloat();
	}
	inline int stoi(std::string _str, std::string::size_type* sz, int _base)
	{
		*sz = _str.length();
		return String(_str.c_str()).toInt();
	}
	inline long long stoll(std::string _str, std::string::size_type* sz, int _base)
	{
		*sz = _str.length();
		return atol(_str.c_str());
	}
}

template <typename m, typename n>
m remainder(m _dividend, n _divisor)
{
	m quotient = (int)_dividend / (int)_divisor;
	m remainder = (int)_dividend % (int)_divisor;
	return remainder;
}
#endif
template <typename m, typename n>
std::string __NERD_Concat_To_Str(m _left, n _right)
{
	std::stringstream output;
	output << _left << _right;
	return output.str();
}
/* END String MANIPULATION */

/*** Number MANIPULATION ***/
template <typename m>
int __NERD_Str_To_Int(m _left)
{
	int out;
	std::stringstream output;
	output << _left;
	output >> out;
	return out;
}
template <typename m>
double __NERD_Str_To_Double(m _left)
{
	double out;
	std::stringstream output;
	output << _left;
	output >> out;
	return out;
}
/* END Number MANIPULATION */

NerdCore::VAR getArguments(int argc, char** argv);