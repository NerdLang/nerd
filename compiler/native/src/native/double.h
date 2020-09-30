double operator+(double _i, NJS::VAR _v)
{
	return (double) (NJS::VAR(_i) + _v);
}
double operator-(double _i, NJS::VAR _v)
{
	return (double) (NJS::VAR(_i) - _v);
}
double operator*(double _i, NJS::VAR _v)
{
	return (double) (NJS::VAR(_i) * _v);
}
double operator/(double _i, NJS::VAR _v)
{
	return (double) (NJS::VAR(_i) / _v);
}
double operator%(double _i, NJS::VAR _v)
{
	return (double) (NJS::VAR(_i) % _v);
}

double operator==(double _i, NJS::VAR _v)
{
	return (double) (NJS::VAR(_i) == _v);
}

double operator!=(double _i, NJS::VAR _v)
{
	return (double) (NJS::VAR(_i) != _v);
}

double operator>(double _i, NJS::VAR _v)
{
	return (double) (NJS::VAR(_i) > _v);
}

double operator>=(double _i, NJS::VAR _v)
{
	return (double) (NJS::VAR(_i) >= _v);
}

double operator<(double _i, NJS::VAR _v)
{
	return (double) (NJS::VAR(_i) < _v);
}

double operator<=(double _i, NJS::VAR _v)
{
	return (double) (NJS::VAR(_i) <= _v);
}