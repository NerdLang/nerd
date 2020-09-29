double operator+(int _i, NJS::VAR _v)
{
	return (double) (NJS::Class::Number(_i) + _v);
}
double operator-(int _i, NJS::VAR _v)
{
	return (double) (NJS::Class::Number(_i) - _v);
}
double operator*(int _i, NJS::VAR _v)
{
	return (double) (NJS::Class::Number(_i) * _v);
}
double operator/(int _i, NJS::VAR _v)
{
	return (double) (NJS::Class::Number((double)_i) / _v);
}
double operator%(int _i, NJS::VAR _v)
{
	return (double) (NJS::Class::Number(_i) % _v);
}