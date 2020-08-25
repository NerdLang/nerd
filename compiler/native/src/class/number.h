namespace NJS::Class
{
	Number::Number()
	{
		Object();
		__NJS_VALUE = 0;
	}
	Number::Number(int i)
	{
		Object();
		setSmi(i);
	}

	Number::Number(double d)
	{
		Object();
		double dummy;
		if (modf(d, &dummy) == 0.0 && d < INT32_MAX && d > INT32_MIN)
		{
			setSmi(static_cast<int>(d));
		}
		else
		{
			setHeap(d);
		}
	}

	Number::Number(long long d)
	{
		Object();
		setSmi(static_cast<int>(d));
	}

	inline bool Number::isHeap() const
	{
		return __NJS_VALUE & 1;
	}
	inline int Number::getSmi() const
	{
		return __NJS_VALUE >> 1;
	}
	inline void Number::setSmi(int v)
	{
		__NJS_VALUE = v << 1;
	}
	inline double Number::getHeap() const
	{
		return *(reinterpret_cast<double *>(__NJS_VALUE >> 1));
	}
	inline void Number::setHeap(double d)
	{
		*reinterpret_cast<double *>(__NJS_VALUE) = d;
		__NJS_VALUE = (__NJS_VALUE << 1) | 1;
	}

	Number Number::operator=(Number &_v)
	{
		__NJS_VALUE = _v.__NJS_VALUE;
		_v.Delete();
		return *this;
	}
	Number Number::operator=(int &_v)
	{
		setSmi(_v);
		return *this;
	}
	Number Number::operator=(double &_v)
	{
		setHeap(_v);
		return *this;
	}

	Number Number::operator-()
	{
		return -(isHeap() ? getHeap() : getSmi());
	}

	Number Number::operator+(const Number &_v1)
	{
		if (!isHeap() && !_v1.isHeap())
		{
			int a = (int)*this;
			int b = (int)_v1;
			int *c;
			if (!__builtin_add_overflow(a, b, c))
			{
				return a + b;
			}
		}
		return (double)*this + (double)_v1;
	}

	Number Number::operator-(const Number &_v1)
	{
		if (!isHeap() && !_v1.isHeap())
		{
			int a = (int)*this;
			int b = (int)_v1;
			int *c;
			if (!__builtin_sub_overflow(a, b, c))
			{
				return a - b;
			}
		}
		return (double)*this - (double)_v1;
	}

	Number Number::operator*(const Number &_v1)
	{
		if (!isHeap() && !_v1.isHeap())
		{
			int a = (int)*this;
			int b = (int)_v1;
			int *c;
			if (!__builtin_mul_overflow(a, b, c))
			{
				return a * b;
			}
		}
		return (double)*this * (double)_v1;
	}

	Number Number::operator/(const Number &_v1)
	{
		if (!isHeap() && !_v1.isHeap())
		{
			int a = (int)*this;
			int b = (int)_v1;
			if (a % b == 0)
			{
				return a / b;
			}
		}
		return (double)*this / (double)_v1;
	}
	Number Number::operator%(const Number &_v1)
	{
		if (!isHeap() && !_v1.isHeap())
		{
			return (int)*this % (int)_v1;
		}
		else
		{
			return std::fmod((double)*this, (double)_v1);
		}
	}

	Number Number::operator+=(const Number &_v1)
	{
		if (!isHeap() && !_v1.isHeap())
		{
			int a = (int)*this;
			int b = (int)_v1;
			int *c;
			if (!__builtin_add_overflow(a, b, c))
			{
				setSmi((int)*this + (int)_v1);
				return;
			}
		}
		setHeap((double)*this + (double)_v1);
	}
	Number Number::operator-=(const Number &_v1)
	{
		if (!isHeap() && !_v1.isHeap())
		{
			int a = (int)*this;
			int b = (int)_v1;
			int *c;
			if (!__builtin_sub_overflow(a, b, c))
			{
				setSmi(a - b);
				return;
			}
		}
		setHeap((double)*this - (double)_v1);
	}
	Number Number::operator*=(const Number &_v1)
	{
		if (!isHeap() && !_v1.isHeap())
		{
			int a = (int)*this;
			int b = (int)_v1;
			int *c;
			if (!__builtin_mul_overflow(a, b, c))
			{
				setSmi(a * b);
				return;
			}
		}
		setHeap((double)*this * (double)_v1);
	}
	Number Number::operator/=(const Number &_v1)
	{
		if (!isHeap() && !_v1.isHeap())
		{
			int a = (int)*this;
			int b = (int)_v1;
			if (a % b == 0)
			{
				setSmi(a / b);
				return;
			}
		}
		setHeap((double)*this / (double)_v1);
	}
	Number Number::operator%=(const Number &_v1)
	{
		if (!isHeap() && !_v1.isHeap())
		{
			setSmi((int)*this % (int)_v1);
		}
		else
		{
			setHeap(std::fmod((double)*this, (double)_v1));
		}
	}
	// TODO: "**" and "**=" operators
	Number Number::operator++(const int _v1)
	{
		if (isHeap())
		{
			double v = getHeap();
			setHeap(++v);
		}
		else
		{
			int v = getSmi();
			setSmi(++v);
		}
	}
	Number Number::operator--(const int _v1)
	{
		if (isHeap())
		{
			double v = getHeap();
			setHeap(--v);
		}
		else
		{
			int v = getSmi();
			setSmi(--v);
		}
	}
	// Comparison operators

	bool Number::operator<(const Number &_v1)
	{
		if (!isHeap() && !_v1.isHeap())
		{
			return (int)*this < (int)_v1;
		}
		return (double)*this < (double)_v1;
	}
	bool Number::operator<=(const Number &_v1)
	{
		if (!isHeap() && !_v1.isHeap())
		{
			return (int)*this <= (int)_v1;
		}
		return (double)*this <= (double)_v1;
	}
	bool Number::operator>(const Number &_v1)
	{
		if (!isHeap() && !_v1.isHeap())
		{
			return (int)*this > (int)_v1;
		}
		return (double)*this > (double)_v1;
	}
	bool Number::operator>=(const Number &_v1)
	{
		if (!isHeap() && !_v1.isHeap())
		{
			return (int)*this >= (int)_v1;
		}
		return (double)*this >= (double)_v1;
	}

	int Number::operator&(const Number &_v1) { return (int)*this & (int)_v1; }
	int Number::operator|(const Number &_v1) { return (int)*this | (int)_v1; }
	int Number::operator^(const Number &_v1) { return (int)*this ^ (int)_v1; }
	int Number::operator>>(const Number &_v1) { return (int)*this >> (int)_v1; }
	int Number::operator<<(const Number &_v1) { return (int)*this << (int)_v1; }
	int Number::operator~() { return ~(int)*this; }

	Number Number::operator&=(const Number &_v1)
	{
		setSmi(*this & _v1);
		return *this;
	}
	Number Number::operator|=(const Number &_v1)
	{
		setSmi(*this | _v1);
		return *this;
	}
	Number Number::operator^=(const Number &_v1)
	{
		setSmi(*this ^ _v1);
		return *this;
	}
	Number Number::operator>>=(const Number &_v1)
	{
		setSmi(*this >> _v1);
		return *this;
	}
	Number Number::operator<<=(const Number &_v1)
	{
		setSmi(*this << _v1);
		return *this;
	}

	inline bool Number::_isNaN() const
	{
		return isHeap() && std::isnan(getHeap());
	}

	inline bool Number::_isFinite() const
	{
		return !isHeap() || std::isfinite(getHeap());
	}

	inline bool Number::_isNegative() const
	{
		return isHeap() ? std::signbit(getHeap()) : getSmi() < 0;
	}
} // namespace NJS::Class
