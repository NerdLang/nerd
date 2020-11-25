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

namespace Nectar::Class
{
	class Function : public virtual Base
	{
	public:
		// Constructors
		Function();
		Function(void* val);
		Function(void* val, Nectar::VAR bind);
		// Properties
		count_t counter = 0;
		#ifdef __Nectar_DEBUG
		std::string code = "[native code]";
		#endif
		Nectar::Type::function_t* value = nullptr;
		Nectar::VAR This;
		Nectar::Type::object_t object;
		// Methods
		inline void Delete() noexcept;
		inline void jsDelete(std::string _key) noexcept;
		inline void* Copy() noexcept;
		inline Nectar::VAR Call(Nectar::VAR& __Nectar_THIS, Nectar::VAR* _args, int i)
		{
			return (*static_cast<Nectar::Type::function_t *>(value))(__Nectar_THIS, _args, i);
		}
		template <class... Args>
		Nectar::VAR New(Args... args)
		{
			Nectar::VAR _args[] = {args...};
			int i = sizeof...(args);
			
			Nectar::VAR _this = __Nectar_Object_Clone((*this)["prototype"]);
			if(_this.type == Nectar::Enum::Type::Undefined) _this = new Nectar::Class::Object();
			
			Nectar::VAR _ret = this->Call(_this, _args, i);

			if(_ret.type == Nectar::Enum::Type::Object)
			{
				((Nectar::Class::Object*)_ret.data.ptr)->property.set(1,1);
				((Nectar::Class::Object*)_ret.data.ptr)->instance.push_back((*this)["prototype"].data.ptr);
				return _ret;
			}
			else
			{
				((Nectar::Class::Object*)_this.data.ptr)->property.set(1,1);
				((Nectar::Class::Object*)_this.data.ptr)->instance.push_back((*this)["prototype"].data.ptr);
				return _this;
			}

		}
		
		template <class... Args>
		Nectar::VAR operator()(Args... args)
		{
			Nectar::VAR _args[] = {args...};
			int i = sizeof...(args);
			return (*static_cast<Nectar::Type::function_t *>(value))(This, _args, i);
		}
	
		// Native cast
		explicit operator bool() const noexcept;
		explicit operator double() const noexcept;
		explicit operator int() const noexcept;
		explicit operator long long() const noexcept;
		explicit operator std::string() const noexcept;
		// Main operators
		Nectar::VAR const operator[](Nectar::VAR key) const;
		Nectar::VAR &operator[](Nectar::VAR key);
		Nectar::VAR &operator[](int key);
		Nectar::VAR &operator[](double key);
		Nectar::VAR &operator[](const char* key);

		// Comparation operators
		Nectar::VAR operator!() const;
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
		Nectar::VAR toString(Nectar::VAR* _args, int _length) const;
		Nectar::VAR valueOf(Nectar::VAR* _args, int _length) const;
		Nectar::VAR bind(Nectar::VAR* _args, int _length);
		Nectar::VAR call(Nectar::VAR* _args, int _length);
		Nectar::VAR apply(Nectar::VAR* _args, int _length);
	};
} // namespace Nectar::Class
