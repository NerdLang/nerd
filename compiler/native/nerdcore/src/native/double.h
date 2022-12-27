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

NerdCore::VAR operator+(double _i, NerdCore::VAR _v)
{
	if(_v.type == NerdCore::Enum::Type::String) return __NERD_DOUBLE_TO_STRING(_i) + (std::string)_v;
	else return _i + (double)_v;
}

void operator+=(double& _i, NerdCore::VAR _v)
{
	_i += (double)_v;
}

double operator-(double _i, NerdCore::VAR _v)
{
	if(_v.type == NerdCore::Enum::Type::String) return std::numeric_limits<double>::quiet_NaN();
	return _i - (double)_v;
}

void operator-=(double& _i, NerdCore::VAR _v)
{
	_i -= (double)_v;
}

double operator*(double _i, NerdCore::VAR _v)
{
	if(_v.type == NerdCore::Enum::Type::String) return std::numeric_limits<double>::quiet_NaN();
	return _i * (double)_v;
}

void operator*=(double& _i, NerdCore::VAR _v)
{
	_i *= (double)_v;
}

double operator/(double _i, NerdCore::VAR _v)
{
	if(_v.type == NerdCore::Enum::Type::String) return std::numeric_limits<double>::quiet_NaN();
	return _i / (double)_v;
}

void operator/=(double& _i, NerdCore::VAR _v)
{
	_i /= _v;
}

double operator%(double _i, NerdCore::VAR _v)
{
	return (int)_i % (int)_v;
}

void operator%=(double& _i, NerdCore::VAR _v)
{
	_i %= _v;
}

double operator==(double _i, NerdCore::VAR _v)
{
	return _i == (double)_v;
}

double operator!=(double _i, NerdCore::VAR _v)
{
	return _i != (double)_v;
}

double operator>(double _i, NerdCore::VAR _v)
{
	return _i > (double)_v;
}

double operator>=(double _i, NerdCore::VAR _v)
{
	return _i >= (double)_v;
}


double operator<(double _i, NerdCore::VAR _v)
{
	return _i < (double)_v;
}


double operator<=(double _i, NerdCore::VAR _v)
{
	return _i <= (double)_v;
}