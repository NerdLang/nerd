__NJS_VAR __NJS_Log_Console(__NJS_VAR _var);
__NJS_VAR __NJS_Object_Keys(__NJS_VAR _var);
__NJS_VAR __NJS_Object_Stringify(__NJS_VAR _var);
__NJS_VAR __NJS_Object_Stringify(__NJS_VAR _var, bool _bracket);
__NJS_VAR __NJS_Create_Object();
__NJS_VAR __NJS_Create_Array();
__NJS_VAR __NJS_Object_Clone(__NJS_VAR _var);
__NJS_VAR __NJS_Object_Set(const char *_index, __NJS_VAR _value, vector<pair<const char *, __NJS_VAR>> *_obj);

/*** STRING MANIPULATION ***/
#ifdef __NJS_ARDUINO
template <typename m>
string to_string(m _var)
{
	std::stringstream output;
	output << _var;
	return output.str();
}
template <typename m, typename n>
m remainder(m _dividend, n _divisor)
{
	m quotient = (int)_dividend / (int)_divisor;
    m remainder = (int)_dividend % (int)_divisor;
	return remainder;
}
#endif
template <typename m, typename n>
string __NJS_Concat_To_Str(m _left, n _right)
{
	std::stringstream output;
	output << _left << _right;
	return output.str();
}
/* END STRING MANIPULATION */

/*** NUMBER MANIPULATION ***/
template <typename m>
int __NJS_Str_To_Int(m _left)
{
	int out;
	std::stringstream output;
	output << _left;
	output >> out;
	return out;
}
template <typename m>
double __NJS_Str_To_Double(m _left)
{
	double out;
	std::stringstream output;
	output << _left;
	output >> out;
	return out;
}
/* END NUMBER MANIPULATION */