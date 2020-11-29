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
NectarCore::VAR __Nectar_Boolean_Result(NectarCore::VAR _v);
std::string __Nectar_DOUBLE_TO_STRING(double _var);
std::ostream &operator<<(std::ostream &os, const NectarCore::VAR &_v);
NectarCore::VAR parseInt(NectarCore::VAR _str);
NectarCore::VAR __Nectar_Log_Console(NectarCore::VAR _var);
NectarCore::VAR __Nectar_Log_Console(NectarCore::VAR* _var, int _length);
NectarCore::VAR __Nectar_Object_Keys(NectarCore::VAR _var);
NectarCore::VAR __Nectar_Object_Stringify(NectarCore::VAR _var);
NectarCore::VAR __Nectar_Object_Stringify(NectarCore::VAR _var, bool _bracket);
NectarCore::VAR __Nectar_Object_Clone(NectarCore::VAR& _var);
void __Nectar_Object_Construct(NectarCore::VAR _this, NectarCore::VAR _prototype);
NectarCore::VAR __Nectar_CREATE_Function(void *_fn);
NectarCore::VAR __Nectar_Create_Native(void *_native);
void *__Nectar_Get_Native(NectarCore::VAR _native);

/*** REDIFINING STD OPERATORS ***/

NectarCore::VAR operator+ (const char* _left, const NectarCore::VAR &_right);

template <typename t>
t operator+(t _left, const NectarCore::VAR &_right)
{
	return _left + (t)_right;
}

template <typename t>
t operator-(t _left, const NectarCore::VAR &_right)
{
	return _left - (t)_right;
}

template <typename t>
t operator*(t _left, const NectarCore::VAR &_right)
{
	return _left * (t)_right;
}

template <typename t>
t operator/(t _left, const NectarCore::VAR &_right)
{
	return _left / (t)_right;
}

template <typename t, typename u>
t operator<(t _left, const u &_right)
{
	return _left < (t)_right;
}

template <typename t, typename u>
t operator<=(t _left, const u &_right)
{
	return _left <= (t)_right;
}

template <typename t>
t operator>(t _left, const NectarCore::VAR &_right)
{
	return _left > (t)_right;
}

template <typename t>
t operator>=(t _left, const NectarCore::VAR &_right)
{
	return _left >= (t)_right;
}

/*** END REDIFINING STD OPERATORS ***/

extern NectarCore::VAR eval;
extern std::function<NectarCore::VAR(NectarCore::Type::vector_t)> *__Nectar_IS_NAN;
extern NectarCore::VAR isNaN;

NectarCore::VAR __Nectar_EQUAL_VALUE_AND_TYPE(NectarCore::VAR _left, NectarCore::VAR _right);
NectarCore::VAR __Nectar_NOT_EQUAL_VALUE_AND_TYPE(NectarCore::VAR _left, NectarCore::VAR _right);
NectarCore::VAR operator+ (NectarCore::VAR _left, int right);
NectarCore::VAR operator+ (NectarCore::VAR _left, double right);

void operator+= (NectarCore::VAR& _left, std::string right);
void operator+= (NectarCore::VAR& _left, const char* right);
void operator+= (NectarCore::VAR& _left, int right);
void operator+= (NectarCore::VAR& _left, double right);

template<class T>
void operator-= (NectarCore::VAR& _left, T right)
{
	if(_left.type == NectarCore::Enum::Type::Number) _left.data.number -= right;
	else _left -= right;
}

NectarCore::VAR operator* (NectarCore::VAR _left, const char* right);

template<class T>
NectarCore::VAR operator* (NectarCore::VAR _left, T right)
{
	return (double)_left * (double)(NectarCore::VAR(right));
}

NectarCore::VAR operator- (NectarCore::VAR _left, const char* right);

template<class T>
NectarCore::VAR operator- (NectarCore::VAR _left, T right)
{
	return (double)_left - (double)(NectarCore::VAR(right));
}

NectarCore::VAR operator/ (NectarCore::VAR _left, const char* right);

template<class T>
NectarCore::VAR operator/ (NectarCore::VAR _left, T right)
{
	return (double)_left / (double)(NectarCore::VAR(right));
}

template<class T>
NectarCore::VAR operator> (NectarCore::VAR _left, T right)
{
	return (double)_left > right;
}

template<class T>
NectarCore::VAR operator>= (NectarCore::VAR _left, T right)
{
	return (double)_left >= right;
}

template<class T>
NectarCore::VAR operator< (NectarCore::VAR _left, T right)
{
	return (_left.data.number < right);
}

template<class T>
NectarCore::VAR operator<= (NectarCore::VAR _left, T right)
{
	return (double)_left <= right;
}

template<class T>
NectarCore::VAR operator% (NectarCore::VAR _left, T right)
{
	return (int)_left % right;
}

NectarCore::VAR operator|| (NectarCore::VAR _left, int right);
NectarCore::VAR operator|| (NectarCore::VAR _left, double right);
NectarCore::VAR operator|| (NectarCore::VAR _left, std::string right);
NectarCore::VAR operator|| (NectarCore::VAR _left, NectarCore::VAR right);

template<class T>
NectarCore::VAR operator== (NectarCore::VAR _left, T right)
{
	return (double)_left == right;
}

template<class T>
NectarCore::VAR operator!= (NectarCore::VAR _left, T right)
{
	return (double)_left != right;
}

template<class T>
NectarCore::VAR operator|(NectarCore::VAR _left, T right)
{
	return (int)_left | right;
}

template<class T>
NectarCore::VAR operator^(NectarCore::VAR _left, T right)
{
	return (int)_left ^ right;
}

template<class T>
NectarCore::VAR operator&(NectarCore::VAR _left, T right)
{
	return (int)_left & right;
}

template<class T>
NectarCore::VAR operator<<(NectarCore::VAR _left, T right)
{
	return (int)_left << right;
}

template<class T>
NectarCore::VAR operator>>(NectarCore::VAR _left, T right)
{
	return (int)_left >> right;
}