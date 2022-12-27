/*
	Copyright (c) 2021 NerdLang - Adrien THIERRY and contributors

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

*/
#ifdef __NERD_ENV_ARDUINO
	bool operator==(std::string_view sw, const char* c)
	{
		return sw == std::string_view(c);
	}

	bool operator!=(std::string_view sw, const char* c)
	{
		return sw != std::string_view(c);
	}
#else
	constexpr bool operator==(std::string_view sw, const char* c)
	{
		return sw == std::string_view(c);
	}

	constexpr bool operator!=(std::string_view sw, const char* c)
	{
		return sw != std::string_view(c);
	}
#endif

NerdCore::VAR __NERD_Boolean_Result(NerdCore::VAR _v);
std::string __NERD_DOUBLE_TO_STRING(double _var);
std::ostream &operator<<(std::ostream &os, const NerdCore::VAR &_v);
NerdCore::VAR parseInt(NerdCore::VAR _str);
NerdCore::VAR __NERD_Log_Console(NerdCore::VAR _var);
NerdCore::VAR __NERD_Log_Console(NerdCore::VAR* _var, int _length);
NerdCore::VAR __NERD_Object_Keys(NerdCore::VAR _var);
NerdCore::VAR __NERD_Object_Stringify(NerdCore::VAR _var);
NerdCore::VAR __NERD_Object_Stringify(NerdCore::VAR _var, bool _bracket);
NerdCore::VAR __NERD_Object_Clone(NerdCore::VAR& _var);
void __NERD_Object_Construct(NerdCore::VAR _this, NerdCore::VAR _prototype);
NerdCore::VAR __NERD_CREATE_Function(void *_fn);
NerdCore::VAR __NERD_Create_Native(void *_native);
void *__NERD_Get_Native(NerdCore::VAR _native);

/*** REDIFINING STD OPERATORS ***/

NerdCore::VAR operator+ (const char* _left, const NerdCore::VAR &_right);
NerdCore::VAR operator+ (std::string _left, const NerdCore::VAR &_right);

NerdCore::VAR operator- (const char* _left, const NerdCore::VAR &_right);
NerdCore::VAR operator- (std::string _left, const NerdCore::VAR &_right);

NerdCore::VAR operator* (const char* _left, const NerdCore::VAR &_right);
NerdCore::VAR operator* (std::string _left, const NerdCore::VAR &_right);

NerdCore::VAR operator/ (const char* _left, const NerdCore::VAR &_right);
NerdCore::VAR operator/ (std::string _left, const NerdCore::VAR &_right);


inline bool operator< (NerdCore::VAR _left, const int right) noexcept
{
	return _left.data.number < right;
}
inline bool operator< (NerdCore::VAR _left, const long long int right) noexcept
{
	return _left.data.number < right;
}
inline bool operator< (NerdCore::VAR _left, const double right) noexcept
{
	return _left.data.number < right;
}

NerdCore::VAR operator< (NerdCore::VAR _left, std::string right);
NerdCore::VAR operator< (NerdCore::VAR _left, const char* right);

inline bool operator<= (NerdCore::VAR _left, const int right) noexcept
{
	return _left.data.number <= right;
}
inline bool operator<= (NerdCore::VAR _left, const long long int right) noexcept
{
	return _left.data.number <= right;
}
inline bool operator<= (NerdCore::VAR _left, const double right) noexcept
{
	return _left.data.number <= right;
}

NerdCore::VAR operator<= (NerdCore::VAR _left, std::string right);
NerdCore::VAR operator<= (NerdCore::VAR _left, const char* right);

inline bool operator> (NerdCore::VAR _left, const int right) noexcept
{
	return _left.data.number > right;
}
inline bool operator> (NerdCore::VAR _left, const long long int right) noexcept
{
	return _left.data.number > right;
}
inline bool operator> (NerdCore::VAR _left, const double right) noexcept
{
	return _left.data.number > right;
}

NerdCore::VAR operator> (NerdCore::VAR _left, std::string right);
NerdCore::VAR operator> (NerdCore::VAR _left, const char* right);

inline const bool operator>= (NerdCore::VAR _left, const int right) noexcept
{
	return _left.data.number >= right;
}
inline bool operator>= (NerdCore::VAR _left, const long long int right) noexcept
{
	return _left.data.number >= right;
}
inline bool operator>= (NerdCore::VAR _left, const double right) noexcept
{
	return _left.data.number >= right;
}

NerdCore::VAR operator>= (NerdCore::VAR _left, std::string right);
NerdCore::VAR operator>= (NerdCore::VAR _left, const char* right);


/*** END REDIFINING STD OPERATORS ***/

extern NerdCore::VAR eval;
extern std::function<NerdCore::VAR(NerdCore::Type::vector_t)> *__NERD_IS_NAN;
extern NerdCore::VAR isNaN;

NerdCore::VAR __NERD_EQUAL_VALUE_AND_TYPE(NerdCore::VAR _left, NerdCore::VAR _right);
NerdCore::VAR __NERD_NOT_EQUAL_VALUE_AND_TYPE(NerdCore::VAR _left, NerdCore::VAR _right);
NerdCore::VAR operator+ (NerdCore::VAR _left, int right);
NerdCore::VAR operator+ (NerdCore::VAR _left, double right);

void operator+= (NerdCore::VAR& _left, std::string right);
void operator+= (NerdCore::VAR& _left, const char* right);
void operator+= (NerdCore::VAR& _left, int right);
void operator+= (NerdCore::VAR& _left, double right);

NerdCore::VAR operator* (NerdCore::VAR _left, int right);
NerdCore::VAR operator* (NerdCore::VAR _left, double right);
NerdCore::VAR operator* (NerdCore::VAR _left, std::string right);
NerdCore::VAR operator* (NerdCore::VAR _left, const char* right);

NerdCore::VAR operator- (NerdCore::VAR _left, int right);
NerdCore::VAR operator- (NerdCore::VAR _left, double right);
NerdCore::VAR operator- (NerdCore::VAR _left, std::string right);
NerdCore::VAR operator- (NerdCore::VAR _left, const char* right);

NerdCore::VAR operator/ (NerdCore::VAR _left, int right);
NerdCore::VAR operator/ (NerdCore::VAR _left, double right);
NerdCore::VAR operator/ (NerdCore::VAR _left, std::string right);
NerdCore::VAR operator/ (NerdCore::VAR _left, const char* right);

NerdCore::VAR operator% (NerdCore::VAR _left, int right);
NerdCore::VAR operator% (NerdCore::VAR _left, double right);
NerdCore::VAR operator% (NerdCore::VAR _left, std::string right);
NerdCore::VAR operator% (NerdCore::VAR _left, const char* right);

NerdCore::VAR operator|| (NerdCore::VAR _left, int right);
NerdCore::VAR operator|| (NerdCore::VAR _left, double right);
NerdCore::VAR operator|| (NerdCore::VAR _left, std::string right);
NerdCore::VAR operator|| (NerdCore::VAR _left, const char* right);

NerdCore::VAR operator== (NerdCore::VAR _left, int right);
NerdCore::VAR operator== (NerdCore::VAR _left, double right);
NerdCore::VAR operator== (NerdCore::VAR _left, std::string right);
NerdCore::VAR operator== (NerdCore::VAR _left, const char* right);

NerdCore::VAR operator!= (NerdCore::VAR _left, int right);
NerdCore::VAR operator!= (NerdCore::VAR _left, double right);
NerdCore::VAR operator!= (NerdCore::VAR _left, std::string right);
NerdCore::VAR operator!= (NerdCore::VAR _left, const char* right);

NerdCore::VAR operator| (NerdCore::VAR _left, int right);
NerdCore::VAR operator| (NerdCore::VAR _left, double right);
NerdCore::VAR operator| (NerdCore::VAR _left, std::string right);
NerdCore::VAR operator| (NerdCore::VAR _left, const char* right);

NerdCore::VAR operator^ (NerdCore::VAR _left, int right);
NerdCore::VAR operator^ (NerdCore::VAR _left, double right);
NerdCore::VAR operator^ (NerdCore::VAR _left, std::string right);
NerdCore::VAR operator^ (NerdCore::VAR _left, const char* right);

NerdCore::VAR operator& (NerdCore::VAR _left, int right);
NerdCore::VAR operator& (NerdCore::VAR _left, double right);
NerdCore::VAR operator& (NerdCore::VAR _left, std::string right);
NerdCore::VAR operator& (NerdCore::VAR _left, const char* right);

NerdCore::VAR operator<< (NerdCore::VAR _left, int right);
NerdCore::VAR operator<< (NerdCore::VAR _left, double right);
NerdCore::VAR operator<< (NerdCore::VAR _left, std::string right);
NerdCore::VAR operator<< (NerdCore::VAR _left, const char* right);

NerdCore::VAR operator>> (NerdCore::VAR _left, int right);
NerdCore::VAR operator>> (NerdCore::VAR _left, double right);
NerdCore::VAR operator>> (NerdCore::VAR _left, std::string right);
NerdCore::VAR operator>> (NerdCore::VAR _left, const char* right);
