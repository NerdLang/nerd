/*
	Copyright (c) 2022 NerdLang - Adrien THIERRY and contributors

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

#pragma once
#include "_meta.h"

namespace NerdCore::Class
{
	class Function : public virtual Base
	{
	public:
		// Constructors
		Function();
		Function(void* val);
		Function(void* val, NerdCore::VAR __this);
		// Properties
		count_t counter = 0;

		NerdCore::Type::function_t* value = nullptr;
		NerdCore::Type::object_t object;
		NerdCore::VAR This;
		//void* bind = nullptr;
		// Methods
		inline void Delete() noexcept;
		inline void jsDelete(std::string _key) noexcept;
		inline void* Copy() noexcept;
		
		inline NerdCore::VAR Call(NerdCore::VAR __NERD_THIS, NerdCore::VAR* _args, int i)
		{
			#ifndef __NERD__OBJECT_VECTOR
			if(__NERD_THIS.type == NerdCore::Enum::Type::Null)
			{
				return std::invoke((*static_cast<NerdCore::Type::function_t *>(value)), This, _args, i);
			}
			else
			{
				return std::invoke((*static_cast<NerdCore::Type::function_t *>(value)), __NERD_THIS, _args, i);
			}
			#else
			return (*static_cast<NerdCore::Type::function_t *>(value))(__NERD_THIS, _args, i);
			#endif
		}
		
		template <class... Args>
		NerdCore::VAR operator()(NerdCore::VAR __NERD_THIS, Args... args)
		{
			NerdCore::VAR _args[] = {args...};
			int i = sizeof...(args);
			#ifndef __NERD__OBJECT_VECTOR
			if(__NERD_THIS.type == NerdCore::Enum::Type::Null)
			{
				return std::invoke((*static_cast<NerdCore::Type::function_t *>(value)), This, _args, i);
			}
			else
			{
				return std::invoke((*static_cast<NerdCore::Type::function_t *>(value)), __NERD_THIS, _args, i);
			}
			#else
			return (*static_cast<NerdCore::Type::function_t *>(value))(__NERD_THIS, _args, i);
			#endif
		}
		
		template <class... Args>
		NerdCore::VAR New(NerdCore::VAR __NERD_THIS, Args... args)
		{
			
			NerdCore::VAR _args[] = {args...};
			int i = sizeof...(args);
			
			NerdCore::VAR _this = new NerdCore::Class::Object(); //__NERD_Object_Clone((*this)["this"]);
			if(_this.type == NerdCore::Enum::Type::Null) _this = new NerdCore::Class::Object();
			
			//((NerdCore::Class::Object*)_this.data.ptr)->bind = bind;
			NerdCore::VAR _return = this->Call(_this, _args, i);
			if(_return.type == NerdCore::Enum::Type::Object)
			{
				_this = _return;
			}
			_this["__proto__"] = object["prototype"];
			return _this;

		}

	
		// Main operators
		NerdCore::VAR const operator[](NerdCore::VAR key) const;
		NerdCore::VAR &operator[](NerdCore::VAR key);
		NerdCore::VAR &operator[](int key);
		NerdCore::VAR &operator[](double key);
		NerdCore::VAR &operator[](const char* key);

		// Comparation operators
		NerdCore::VAR operator!() const;
		bool operator==(const Function &_v1) const;
		// === emulated with __NERD_EQUAL_VALUE_AND_TYPE
		// !== emulated with __NERD_NOT_EQUAL_VALUE_AND_TYPE
		bool operator!=(const Function &_v1) const;
		bool operator<(const Function &_v1) const;
		bool operator<=(const Function &_v1) const;
		bool operator>(const Function &_v1) const;
		bool operator>=(const Function &_v1) const;
		// Numeric operators
		Function operator+() const;
		Function operator-() const;
		Function operator++(const int _v1);
		Function operator--(const int _v1);
		Function operator+(const Function &_v1) const;
		Function operator+=(const Function &_v1);
		Function operator-(const Function &_v1) const;
		Function operator-=(const Function &_v1);
		Function operator*(const Function &_v1) const;
		Function operator*=(const Function &_v1);
		// TODO: "**" and "**=" operators
		Function operator/(const Function &_v1) const;
		Function operator/=(const Function &_v1);
		Function operator%(const Function &_v1) const;
		Function operator%=(const Function &_v1);
		Function operator&(const Function &_v1) const;
		Function operator|(const Function &_v1) const;
		Function operator^(const Function &_v1) const;
		Function operator~() const;
		Function operator>>(const Function &_v1) const;
		Function operator<<(const Function &_v1) const;
		Function operator&=(const Function &_v1);
		Function operator|=(const Function &_v1);
		Function operator^=(const Function &_v1);
		Function operator>>=(const Function &_v1);
		Function operator<<=(const Function &_v1);
		// TODO: ">>>" and ">>>=" operators
	};
} // namespace NerdCore::Class