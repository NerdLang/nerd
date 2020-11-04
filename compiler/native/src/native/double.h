inline NJS::VAR operator+(double _i, NJS::VAR _v)
{
	if(_v.type == NJS::Enum::Type::String) return __NJS_DOUBLE_TO_STRING(_i) + (std::string)_v;
	else return _i + (double)_v;
}

void operator+=(double& _i, NJS::VAR _v)
{
	_i += (double)_v;
}

inline double operator-(double _i, NJS::VAR _v)
{
	if(_v.type == NJS::Enum::Type::String) return std::numeric_limits<double>::quiet_NaN();
	return _i - (double)_v;
}

void operator-=(double& _i, NJS::VAR _v)
{
	_i -= (double)_v;
}

inline double operator*(double _i, NJS::VAR _v)
{
	if(_v.type == NJS::Enum::Type::String) return std::numeric_limits<double>::quiet_NaN();
	return _i * (double)_v;
}

void operator*=(double& _i, NJS::VAR _v)
{
	_i *= (double)_v;
}

inline double operator/(double _i, NJS::VAR _v)
{
	if(_v.type == NJS::Enum::Type::String) return std::numeric_limits<double>::quiet_NaN();
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