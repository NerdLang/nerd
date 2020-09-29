double operator+(double _i, NJS::VAR _v)
{
	return (double) (NJS::Class::Number(_i) + _v);
}
double operator-(double _i, NJS::VAR _v)
{
	return (double) (NJS::Class::Number(_i) - _v);
}
double operator*(double _i, NJS::VAR _v)
{
	return (double) (NJS::Class::Number(_i) * _v);
}
double operator/(double _i, NJS::VAR _v)
{
	return (double) (NJS::Class::Number(_i) / _v);
}
double operator%(double _i, NJS::VAR _v)
{
	return (double) (NJS::Class::Number(_i) % _v);
}