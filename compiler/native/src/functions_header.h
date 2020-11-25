/*
 * This file is part of NectarCPP
 * Copyright (c) 2020 - 2020 Adrien THIERRY
 * https://nectar-lang.org - https://seraum.com/
 *
 * sources : https://github.com/nectar-lang/NectarCPP
 * 
 * NectarCPP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NectarCPP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NectarCPP.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
 
NectarCore::VAR __Nectar_Log_Console(NectarCore::VAR _var);
NectarCore::VAR __Nectar_Object_Keys(NectarCore::VAR _var);
NectarCore::VAR __Nectar_Object_Stringify(NectarCore::VAR _var);
NectarCore::VAR __Nectar_Object_Stringify(NectarCore::VAR _var, bool _bracket);
NectarCore::VAR __Nectar_Object_Clone(NectarCore::VAR& _var);
NectarCore::VAR __Nectar_Object_Set(std::string _index, NectarCore::VAR _value, NectarCore::Type::object_t *_obj);
std::string __Nectar_DOUBLE_TO_STRING(double _var);

/*** String MANIPULATION ***/

#ifdef __Nectar_ENV_ARDUINO
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
std::string __Nectar_Concat_To_Str(m _left, n _right)
{
	std::stringstream output;
	output << _left << _right;
	return output.str();
}
/* END String MANIPULATION */

/*** Number MANIPULATION ***/
template <typename m>
int __Nectar_Str_To_Int(m _left)
{
	int out;
	std::stringstream output;
	output << _left;
	output >> out;
	return out;
}
template <typename m>
double __Nectar_Str_To_Double(m _left)
{
	double out;
	std::stringstream output;
	output << _left;
	output >> out;
	return out;
}
/* END Number MANIPULATION */

NectarCore::VAR getArguments(int argc, char** argv);