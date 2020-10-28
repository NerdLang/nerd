inline double operator+(double _i, NJS::VAR _v)
{
	return _i + (double)_v;
}

void operator+=(double& _i, NJS::VAR _v)
{
	_i += (double)_v;
}

inline double operator-(double _i, NJS::VAR _v)
{
	return _i - (double)_v;
}

void operator-=(double& _i, NJS::VAR _v)
{
	_i -= (double)_v;
}

inline double operator*(double _i, NJS::VAR _v)
{
	return _i * (double)_v;
}

void operator*=(double& _i, NJS::VAR _v)
{
	_i *= (double)_v;
}

inline double operator/(double _i, NJS::VAR _v)
{
	return _i / (double)_v;
}

void operator/=(double& _i, NJS::VAR _v)
{
	_i /= _v;
}

inline double operator%(double _i, NJS::VAR _v)
{
	return (int)_i % (int)_v;
}

void operator%=(double& _i, NJS::VAR _v)
{
	_i %= _v;
}

inline double operator==(double _i, NJS::VAR _v)
{
	return _i == (double)_v;
}

inline double operator!=(double _i, NJS::VAR _v)
{
	return _i != (double)_v;
}

inline double operator>(double _i, NJS::VAR _v)
{
	return _i > (double)_v;
}

inline double operator>=(double _i, NJS::VAR _v)
{
	return _i >= (double)_v;
}


inline double operator<(double _i, NJS::VAR _v)
{
	return _i < (double)_v;
}


inline double operator<=(double _i, NJS::VAR _v)
{
	return _i <= (double)_v;
}