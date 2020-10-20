NJS::VAR __NJS_Log_Console(NJS::VAR _var);
NJS::VAR __NJS_Object_Keys(NJS::VAR _var);
NJS::VAR __NJS_Object_Stringify(NJS::VAR _var);
NJS::VAR __NJS_Object_Stringify(NJS::VAR _var, bool _bracket);
NJS::Class::Object* __NJS_Create_Object();
NJS::Class::Array* __NJS_Create_Array();
NJS::VAR __NJS_Object_Clone(NJS::VAR _var);
NJS::VAR __NJS_Object_Set(std::string _index, NJS::VAR _value, NJS::Type::object_t *_obj);

/*** String MANIPULATION ***/

#ifdef __NJS_ENV_ARDUINO
namespace std
{
	template <typename m>
	string to_string(m _var)
	{
		std::stringstream output;
		output << _var;
		return output.str();
	}
	int isnan(double __x)
	{
		return ::isnan(__x);
	}
	inline int isfinite(double __x)
	{
		return ::isfinite(__x);
	}
	inline int signbit(double __x)
	{
		return ::signbit(__x);
	}
	inline double stod(std::string _str, std::string::size_type* sz)
	{
		*sz = _str.length();
		return String(_str.c_str()).toFloat();
	}
	inline int stoi(std::string _str, std::string::size_type* sz, int _base)
	{
		*sz = _str.length();
		return String(_str.c_str()).toInt();
	}
	inline long long stoll(std::string _str, std::string::size_type* sz, int _base)
	{
		*sz = _str.length();
		return atol(_str.c_str());
	}
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
std::string __NJS_Concat_To_Str(m _left, n _right)
{
	std::stringstream output;
	output << _left << _right;
	return output.str();
}
/* END String MANIPULATION */

/*** Number MANIPULATION ***/
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
/* END Number MANIPULATION */