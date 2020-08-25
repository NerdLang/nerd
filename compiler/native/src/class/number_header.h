namespace NJS::Class
{
	class Number : public Object
	{
	private:
		inline bool isHeap() const;
		inline int getSmi() const;
		inline void setSmi(int v);
		inline double getHeap() const;
		inline void setHeap(double d);

	public:
		const char *name = "number";
		const NJS::Enum::Type type = NJS::Enum::Type::NUMBER;
		Number();
		Number(int i);
		Number(double d);
		Number(long long i);
		unsigned int __NJS_VALUE;
		explicit operator bool() const
		{
			return __NJS_VALUE != 0 && !_isNaN();
		}
		explicit operator double() const
		{
			return isHeap() ? getHeap() : (double)getSmi();
		}
		explicit operator int() const
		{
			return isHeap() ? (int)getHeap() : getSmi();
		}
		explicit operator std::string() const
		{
			if (_isFinite()) {
				return std::to_string(isHeap() ? getHeap() : getSmi());
			}
			if (_isNaN()) {
				return "NaN";
			}
			return _isNegative() ? "-Infinity" : "Infinity";
		}
		explicit operator long long() const
		{
			if (_isFinite()) {
				return (long long)(isHeap() ? getHeap() : getSmi());
			}
			if (_isNaN()) {
				return std::numeric_limits<long long>::quiet_NaN();
			}
			return std::numeric_limits<long long>::infinity() * (_isNegative() ? -1 : 1);
		}
		Number operator=(Number &_v);
		Number operator=(int &_v1);
		Number operator=(double &_v1);
		/// Unary operators

		Number operator-();

		/// Arithmetic operators

		Number operator+(const Number &_v1);
		Number operator+=(const Number &_v1);
		Number operator-(const Number &_v1);
		Number operator-=(const Number &_v1);
		Number operator*(const Number &_v1);
		Number operator*=(const Number &_v1);
		Number operator/(const Number &_v1);
		Number operator/=(const Number &_v1);
		Number operator%(const Number &_v1);
		Number operator%=(const Number &_v1);
		// TODO: "**" and "**=" operators

		Number operator++(const int _v1);
		Number operator--(const int _v1);
		// Comparison operators

		bool operator==(const Number &_v1);
		// === emulated with __NJS_EQUAL_VALUE_AND_TYPE

		bool operator!=(const Number &_v1);
		// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE

		bool operator<(const Number &_v1);
		bool operator<=(const Number &_v1);
		bool operator>(const Number &_v1);
		bool operator>=(const Number &_v1);
		// Bitwise operators

		int operator&(const Number &_v1);
		int operator|(const Number &_v1);
		int operator^(const Number &_v1);
		int operator~();
		int operator>>(const Number &_v1);
		int operator<<(const Number &_v1);
		Number operator&=(const Number &_v1);
		Number operator|=(const Number &_v1);
		Number operator^=(const Number &_v1);
		Number operator>>=(const Number &_v1);
		Number operator<<=(const Number &_v1);

		inline bool _isNaN() const;
		inline bool _isFinite() const;
		inline bool _isNegative() const;
	};
} // namespace NJS::Class
