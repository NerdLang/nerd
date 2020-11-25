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
Nectar::VAR __Nectar_Boolean_Result(Nectar::VAR _v);
std::string __Nectar_DOUBLE_TO_STRING(double _var);
std::ostream &operator<<(std::ostream &os, const Nectar::VAR &_v);
Nectar::VAR parseInt(Nectar::VAR _str);
Nectar::VAR __Nectar_Log_Console(Nectar::VAR _var);
Nectar::VAR __Nectar_Log_Console(Nectar::VAR* _var, int _length);
Nectar::VAR __Nectar_Object_Keys(Nectar::VAR _var);
Nectar::VAR __Nectar_Object_Stringify(Nectar::VAR _var);
Nectar::VAR __Nectar_Object_Stringify(Nectar::VAR _var, bool _bracket);
Nectar::VAR __Nectar_Object_Clone(Nectar::VAR& _var);
void __Nectar_Object_Construct(Nectar::VAR _this, Nectar::VAR _prototype);
Nectar::VAR __Nectar_CREATE_Function(void *_fn);
Nectar::VAR __Nectar_Create_Native(void *_native);
void *__Nectar_Get_Native(Nectar::VAR _native);

/*** REDIFINING STD OPERATORS ***/

template <typename t>
t operator+(t _left, const Nectar::VAR &_right)
{
	return _left + (t)_right;
}

template <typename t>
t operator-(t _left, const Nectar::VAR &_right)
{
	return _left - (t)_right;
}

template <typename t>
t operator*(t _left, const Nectar::VAR &_right)
{
	return _left * (t)_right;
}

template <typename t>
t operator/(t _left, const Nectar::VAR &_right)
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
t operator>(t _left, const Nectar::VAR &_right)
{
	return _left > (t)_right;
}

template <typename t>
t operator>=(t _left, const Nectar::VAR &_right)
{
	return _left >= (t)_right;
}

/*** END REDIFINING STD OPERATORS ***/

extern Nectar::VAR eval;
extern std::function<Nectar::VAR(Nectar::Type::vector_t)> *__Nectar_IS_NAN;
extern Nectar::VAR isNaN;

Nectar::VAR __Nectar_EQUAL_VALUE_AND_TYPE(Nectar::VAR _left, Nectar::VAR _right);
Nectar::VAR __Nectar_NOT_EQUAL_VALUE_AND_TYPE(Nectar::VAR _left, Nectar::VAR _right);
Nectar::VAR operator+ (Nectar::VAR _left, int right);
Nectar::VAR operator+ (Nectar::VAR _left, double right);

void operator+= (Nectar::VAR& _left, std::string right);
void operator+= (Nectar::VAR& _left, const char* right);
void operator+= (Nectar::VAR& _left, int right);
void operator+= (Nectar::VAR& _left, double right);

template<class T>
void operator-= (Nectar::VAR& _left, T right)
{
	if(_left.type == Nectar::Enum::Type::Number) _left.data.number -= right;
	else _left -= right;
}

Nectar::VAR operator* (Nectar::VAR _left, const char* right);

template<class T>
Nectar::VAR operator* (Nectar::VAR _left, T right)
{
	return (double)_left * (double)(Nectar::VAR(right));
}

Nectar::VAR operator- (Nectar::VAR _left, const char* right);

template<class T>
Nectar::VAR operator- (Nectar::VAR _left, T right)
{
	return (double)_left - (double)(Nectar::VAR(right));
}

Nectar::VAR operator/ (Nectar::VAR _left, const char* right);

template<class T>
Nectar::VAR operator/ (Nectar::VAR _left, T right)
{
	return (double)_left / (double)(Nectar::VAR(right));
}

template<class T>
Nectar::VAR operator> (Nectar::VAR _left, T right)
{
	return (double)_left > right;
}

template<class T>
Nectar::VAR operator>= (Nectar::VAR _left, T right)
{
	return (double)_left >= right;
}

template<class T>
Nectar::VAR operator< (Nectar::VAR _left, T right)
{
	return (_left.data.number < right);
}

template<class T>
Nectar::VAR operator<= (Nectar::VAR _left, T right)
{
	return (double)_left <= right;
}

template<class T>
Nectar::VAR operator% (Nectar::VAR _left, T right)
{
	return (int)_left % right;
}

Nectar::VAR operator|| (Nectar::VAR _left, int right);
Nectar::VAR operator|| (Nectar::VAR _left, double right);
Nectar::VAR operator|| (Nectar::VAR _left, std::string right);
Nectar::VAR operator|| (Nectar::VAR _left, Nectar::VAR right);

template<class T>
Nectar::VAR operator== (Nectar::VAR _left, T right)
{
	return (double)_left == right;
}

template<class T>
Nectar::VAR operator!= (Nectar::VAR _left, T right)
{
	return (double)_left != right;
}

template<class T>
Nectar::VAR operator|(Nectar::VAR _left, T right)
{
	return (int)_left | right;
}

template<class T>
Nectar::VAR operator^(Nectar::VAR _left, T right)
{
	return (int)_left ^ right;
}

template<class T>
Nectar::VAR operator&(Nectar::VAR _left, T right)
{
	return (int)_left & right;
}

template<class T>
Nectar::VAR operator<<(Nectar::VAR _left, T right)
{
	return (int)_left << right;
}

template<class T>
Nectar::VAR operator>>(Nectar::VAR _left, T right)
{
	return (int)_left >> right;
}