/*
 * This file is part of NectarCPP
 * Copyright (c) 2020 - 2020 Adrien THIERRY
 * https://nectar-lang.org - https://seraum.com/
 *
 * sources : https://github.com/nectar-lang/NectarCPP
 * 
 * NectarCPP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NectarCPP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NectarCPP.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
 
#pragma once
#include "_meta.h"

namespace NectarCore::Class
{
	class Function : public virtual Base
	{
	public:
		// Constructors
		Function();
		Function(void* val);
		Function(void* val, NectarCore::VAR bind);
		// Properties
		count_t counter = 0;
		#ifdef __Nectar_DEBUG
		std::string code = "[native code]";
		#endif
		NectarCore::Type::function_t* value = nullptr;
		NectarCore::VAR This;
		NectarCore::Type::object_t object;
		// Methods
		inline void Delete() noexcept;
		inline void jsDelete(std::string _key) noexcept;
		inline void* Copy() noexcept;
		inline NectarCore::VAR Call(NectarCore::VAR& __Nectar_THIS, NectarCore::VAR* _args, int i)
		{
			return (*static_cast<NectarCore::Type::function_t *>(value))(__Nectar_THIS, _args, i);
		}
		template <class... Args>
		NectarCore::VAR New(Args... args)
		{
			NectarCore::VAR _args[] = {args...};
			int i = sizeof...(args);
			
			NectarCore::VAR _this = __Nectar_Object_Clone((*this)["prototype"]);
			if(_this.type == NectarCore::Enum::Type::Undefined) _this = new NectarCore::Class::Object();
			
			NectarCore::VAR _ret = this->Call(_this, _args, i);

			if(_ret.type == NectarCore::Enum::Type::Object)
			{
				((NectarCore::Class::Object*)_ret.data.ptr)->property.set(1,1);
				((NectarCore::Class::Object*)_ret.data.ptr)->instance.push_back((*this)["prototype"].data.ptr);
				return _ret;
			}
			else
			{
				((NectarCore::Class::Object*)_this.data.ptr)->property.set(1,1);
				((NectarCore::Class::Object*)_this.data.ptr)->instance.push_back((*this)["prototype"].data.ptr);
				return _this;
			}

		}
		
		template <class... Args>
		NectarCore::VAR operator()(Args... args)
		{
			NectarCore::VAR _args[] = {args...};
			int i = sizeof...(args);
			return (*static_cast<NectarCore::Type::function_t *>(value))(This, _args, i);
		}
	
		// Native cast
		explicit operator bool() const noexcept;
		explicit operator double() const noexcept;
		explicit operator int() const noexcept;
		explicit operator long long() const noexcept;
		explicit operator std::string() const noexcept;
		// Main operators
		NectarCore::VAR const operator[](NectarCore::VAR key) const;
		NectarCore::VAR &operator[](NectarCore::VAR key);
		NectarCore::VAR &operator[](int key);
		NectarCore::VAR &operator[](double key);
		NectarCore::VAR &operator[](const char* key);

		// Comparation operators
		NectarCore::VAR operator!() const;
		bool operator==(const Function &_v1) const;
		// === emulated with __Nectar_EQUAL_VALUE_AND_TYPE
		// !== emulated with __Nectar_NOT_EQUAL_VALUE_AND_TYPE
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
		NectarCore::VAR toString(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR valueOf(NectarCore::VAR* _args, int _length) const;
		NectarCore::VAR bind(NectarCore::VAR* _args, int _length);
		NectarCore::VAR call(NectarCore::VAR* _args, int _length);
		NectarCore::VAR apply(NectarCore::VAR* _args, int _length);
	};
} // namespace NectarCore::Class
