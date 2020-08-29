NJS::VAR __NJS_Log_Console(NJS::VAR _var);
NJS::VAR __NJS_Object_Keys(NJS::VAR _var);
NJS::VAR __NJS_Object_Stringify(NJS::VAR _var);
NJS::VAR __NJS_Object_Stringify(NJS::VAR _var, bool _bracket);
NJS::VAR __NJS_Create_Object();
NJS::VAR __NJS_Create_Array();
NJS::VAR __NJS_Object_Clone(NJS::VAR _var);
NJS::VAR __NJS_Object_Set(const char *_index, NJS::VAR _value, vector<pair<const char *, NJS::VAR>> *_obj);

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