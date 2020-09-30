double operator+(int _i, NJS::VAR _v)
{
	return (double) (NJS::VAR(_i) + _v);
}
double operator-(int _i, NJS::VAR _v)
{
	return (double) (NJS::VAR(_i) - _v);
}
double operator*(int _i, NJS::VAR _v)
{
	return (double) (NJS::VAR(_i) * _v);
}
double operator/(int _i, NJS::VAR _v)
{
	return (double) (NJS::VAR((double)_i) / _v);
}
double operator%(int _i, NJS::VAR _v)
{
	return (double) (NJS::VAR(_i) % _v);
}

double operator==(int _i, NJS::VAR _v)
{
	return (double) (NJS::VAR(_i) == _v);
}

double operator!=(int _i, NJS::VAR _v)
{
	return (double) (NJS::VAR(_i) != _v);
}

double operator>(int _i, NJS::VAR _v)
{
	return (double) (NJS::VAR(_i) > _v);
}

double operator>=(int _i, NJS::VAR _v)
{
	return (double) (NJS::VAR(_i) >= _v);
}

double operator<(int _i, NJS::VAR _v)
{
	return (double) (NJS::VAR(_i) < _v);
}

double operator<=(int _i, NJS::VAR _v)
{
	return (double) (NJS::VAR(_i) <= _v);
}