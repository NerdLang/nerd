double operator+(int _i, NJS::VAR _v)
{
	return _i + (double)_v;
}

void operator+=(int& _i, NJS::VAR _v)
{
	_i += (double)_v;
}

double operator-(int _i, NJS::VAR _v)
{
	return _i - (double)_v;
}

void operator-=(int& _i, NJS::VAR _v)
{
	_i -= (double)_v;
}

double operator*(int _i, NJS::VAR _v)
{
	return _i * (double)_v;
}

void operator*=(int& _i, NJS::VAR _v)
{
	_i *= _v;
}

double operator/(int _i, NJS::VAR _v)
{
	return _i / (double)_v;
}

void operator/=(int& _i, NJS::VAR _v)
{
	_i /= _v;
}

double operator%(int _i, NJS::VAR _v)
{
	return (int)_i % (int)_v;
}

void operator%=(int& _i, NJS::VAR _v)
{
	_i %= _v;
}

double operator==(int _i, NJS::VAR _v)
{
	return _i == (double)_v;
}

double operator!=(int _i, NJS::VAR _v)
{
	return _i != (double)_v;
}

double operator>(int _i, NJS::VAR _v)
{
	return _i > (double)_v;
}

double operator>=(int _i, NJS::VAR _v)
{
	return _i >= (double)_v;
}


double operator<(int _i, NJS::VAR _v)
{
	return _i < (double)_v;
}


double operator<=(int _i, NJS::VAR _v)
{
	return _i <= (double)_v;
}