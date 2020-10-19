namespace NJS
{

	struct VAR
	{
		NJS::Enum::Type type;
		void* _ptr;

		VAR();
		~VAR();

		/**/
		VAR(VAR const &_v);
		/**/
		
		/*** CONSTRUCTOR ***/

		VAR(NJS::Enum::Type _type, int _value);
		VAR(int _value);
		VAR(double _value);
		VAR(long long _value);
		VAR(char *_value);
		VAR(std::string _value);
		VAR(const char *_value);
		VAR(NJS::Class::Array *_value);
		VAR(const NJS::Class::Array *_value);
		VAR(NJS::Class::Boolean *_value);
		VAR(NJS::Class::Function *_value);
		VAR(NJS::Class::Object *_value);
		VAR(NJS::Class::String *_value);
		VAR(NJS::Class::Number _value);
		VAR(NJS::Class::Number *_value);
		VAR(NJS::Class::Native *_value);
		VAR(NJS::Class::Undefined *_value);
		VAR(NJS::Enum::Type _type, void *_value);
		VAR(NJS::Enum::Type _type, void *_value, var _this);
		VAR(std::function<VAR(NJS::VAR*, int)> &_value);
		template <class... Args>
		VAR operator() (Args... args);
		template <class... Args>
		VAR operator() (Args... args) const;
		
		/* END CALL OVERLOAD */

		VAR & operator[] (VAR _index);
		VAR & operator[] (VAR _index) const;
		VAR & operator[] (int _index) const;
		VAR & operator[] (int _index);
		VAR & operator[] (const char* _index);
		/* END ACCESS OVERLOAD */

		/*** END CONSTRUCTOR ***/

		/*** OPERATOR ***/
		void operator=(const VAR &_v);

		/// Unary operators
		VAR operator+();
		
		VAR operator-();
		VAR operator!();

		/// Logical operators
		VAR operator&&(const VAR &_v1);
		VAR operator||(const VAR &_v1);

		/// Arithmetic operators
		VAR operator+(const VAR &_v1);
		VAR operator+(const char _v1[]);
		void operator+=(const VAR &_v1);
		VAR operator-(const VAR &_v1);
		VAR operator-=(const VAR &_v1);
		VAR operator*(const VAR &_v1);
		void operator*=(const VAR &_v1);
		VAR operator/(const VAR &_v1);
		void operator/=(const VAR &_v1);
		VAR operator%(const VAR &_v1);
		VAR operator%=(const VAR &_v1);
		// TODO: "**" and "**=" operators
		VAR operator++(const int _v1);
		void operator++();
		VAR operator--(const int _v1);
		void operator--();
		/// Comparison operators
		VAR operator==(const VAR &_v1);
		// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
		VAR operator!=(const VAR &_v1);
		// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
		VAR operator<(const VAR &_v1);
		VAR operator<=(const VAR &_v1);
		VAR operator>(const VAR &_v1);
		VAR operator>=(const VAR &_v1);
		/// Bitwise operators
		VAR operator&(const VAR &_v1);
		VAR operator&=(const VAR &_v1);
		VAR operator|(const VAR &_v1);
		VAR operator|=(const VAR &_v1);
		VAR operator^(const VAR &_v1);
		VAR operator^=(const VAR &_v1);
		VAR operator~();
		VAR operator>>(const VAR &_v1);
		VAR operator>>=(const VAR &_v1);
		VAR operator<<(const VAR &_v1);
		VAR operator<<=(const VAR &_v1);

		explicit operator int() const;
		operator int();
		explicit operator double() const;
		operator double();
		explicit operator bool() const;
		operator bool();
		explicit operator std::string() const;
		operator std::string();
		explicit operator const char*() const;	
		explicit operator long long() const;
		
	};
} // namespace NJS