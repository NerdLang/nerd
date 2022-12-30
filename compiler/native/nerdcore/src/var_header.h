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

namespace NerdCore
{

	union Data
	{
		void* ptr;
		double number;		
	};
	
	struct VAR
	{
		NerdCore::Enum::Type type;
		Data data;
		
		VAR();
		~VAR();

		/**/
		VAR(VAR const &_v);
		VAR(VAR const &&_v);
		/**/
		
		/*** CONSTRUCTOR ***/

		VAR(NerdCore::Enum::Type _type, int _value);
		VAR(NerdCore::Enum::Type _type, double _value);
		VAR(int _value);
		VAR(double _value);
		VAR(long long _value);
		VAR(unsigned long _value);
		VAR(long long unsigned int _value);
		VAR(char *_value);
		VAR(std::string _value);
		VAR(const char *_value);
		VAR(std::string_view _value);
		VAR(NerdCore::Class::FixedArray *_value);
		VAR(NerdCore::Class::Array *_value);
		//VAR(std::initializer_list<NerdCore::VAR> l);
		VAR(const NerdCore::Class::Array *_value);
		VAR(bool _value);
		VAR(NerdCore::Class::Function *_value);
		VAR(NerdCore::Class::Object *_value);
		VAR(NerdCore::Class::String *_value);
		VAR(NerdCore::Class::Native *_value);
		VAR(NerdCore::Class::Undefined *_value);
		VAR(void *_value, void* fn);
		VAR(NerdCore::Enum::Type _type, void *_value);
		VAR(NerdCore::Enum::Type _type, void *_value, VAR _this);
		VAR(std::function<VAR(NerdCore::VAR*, int, void*)> &_value);
		
		/*
		template<typename T>
		VAR(NerdCore::Class::NativeTPL<T>* _value)
		{
			this->type = NerdCore::Enum::Type::NativeTPL;
			data.ptr = _value;
		};
		
		template <typename T>
		T toNative (T _type)
		{
			if(type == NerdCore::Enum::Type::NativeTPL)
			{
				return (*(NerdCore::Class::NativeTPL<T>*)data.ptr)(_type);
			}
			else
			{
		#ifndef __NERD_NO_EXCEPT
				throw VAR("TypeError: Object is not a Native object");
		#endif
				exit(1);
			} 
		}
		
		template <typename T>
		T toNative ()
		{
			if(type == NerdCore::Enum::Type::NativeTPL)
			{
				return (*(NerdCore::Class::NativeTPL<T>*)data.ptr)();
			}
			else
			{
				#ifndef __NERD_NO_EXCEPT
				throw VAR("TypeError: Object is not a Native object");
				#endif
				exit(1);
			} 
		}
		
		template <typename T>
		T Ptr ()
		{
			if(type == NerdCore::Enum::Type::NativeTPL)
			{
				return (NerdCore::Class::NativeTPL<T>*)data.ptr;
			}
			else
			{
				#ifndef __NERD_NO_EXCEPT
				throw VAR("TypeError: Object is not a Native object");
				#endif
				exit(1);
			} 
		}
		*/
		
		template <class... Args>
		VAR operator() (NerdCore::VAR __NERD_THIS, Args... args) const
		{
			if (type != NerdCore::Enum::Type::Function)
			{
		#ifndef __NERD_NO_EXCEPT
				throw VAR("TypeError: object is not a function");
		#endif
				exit(1);
			}
			else return (*(NerdCore::Class::Function*)data.ptr)(__NERD_THIS, (VAR)(args)...);
		}
		
		/* END CALL OVERLOAD */

		VAR & operator[] (VAR _index);
		VAR & operator[] (VAR _index) const;
		VAR & operator[] (int _index) const;
		VAR & operator[] (int _index);
		VAR & operator[] (double _index);
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
		VAR operator&&(const VAR &_v1) const;
		VAR operator||(const VAR &_v1) const;

		/// Arithmetic operators
		VAR operator+(const VAR &_v1);
		VAR operator+(const char _v1[]);
		VAR& operator+=(const VAR &_v1);
		VAR operator-(const VAR &_v1);
		VAR& operator-=(const VAR &_v1);
		VAR operator*(const VAR &_v1);
		VAR& operator*=(const VAR &_v1);
		VAR operator/(const VAR &_v1);
		VAR& operator/=(const VAR &_v1);
		VAR operator%(const VAR &_v1);
		VAR& operator%=(const VAR &_v1);
		// TODO: "**" and "**=" operators
		
		// var++
		inline VAR& operator++(const int _v1) noexcept
		{
			if (type < NerdCore::Enum::Type::String)
			{
				data.number++;
			}
			return *this;
		}
		// ++var
		inline VAR& operator++()
		{
			if (type < NerdCore::Enum::Type::String)
			{
				++data.number;
			}
			return *this;
		}
		// var--
		inline VAR& operator--(const int _v1)
		{
			if (type < NerdCore::Enum::Type::String)
			{
				data.number--;
			}
			return *this;
		}
		// --var
		inline VAR& operator--()
		{
			if (type < NerdCore::Enum::Type::String)
			{
				--data.number;
			}
			return *this;
		}
		/// Comparison operators
		VAR operator==(const VAR &_v1) const;
		// === emulated with __NERD_EQUAL_VALUE_AND_TYPE
		VAR operator!=(const VAR &_v1);
		// !== emulated with __NERD_NOT_EQUAL_VALUE_AND_TYPE
		VAR operator<(long long int &_v1);
		VAR operator<(int &_v1);
		VAR operator<(double &_v1);
		VAR operator<(const VAR &_v1);

		VAR operator<=(const VAR &_v1);
		VAR operator>(const VAR &_v1);
		VAR operator>=(const VAR &_v1);
		/// Bitwise operators
		VAR operator&(const VAR &_v1);
		VAR& operator&=(const VAR &_v1);
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
		operator const char*() const;
		operator long long();
		explicit operator long long() const;
		operator std::string_view() const;
		
	};

} // namespace NerdCore