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
	class Base
	{
	public:
		#ifdef __Nectar_ENV_ESP32
		virtual ~Base() { }
		#endif
		virtual void Delete() noexcept{};
		virtual void* Copy() noexcept{ return nullptr; };
		virtual explicit operator bool() const noexcept{ return false;};
		virtual explicit operator std::string() const noexcept{ return "";};
		virtual explicit operator int() const noexcept {return 0;};
		virtual explicit operator double() const noexcept {return 0.0;};
		virtual explicit operator long long() const noexcept {return 0;};
		virtual Nectar::VAR &operator[](Nectar::VAR key){static Nectar::VAR _ret = Nectar::VAR(); return _ret;};
		virtual Nectar::VAR &operator[](int key){static Nectar::VAR _ret = Nectar::VAR(); return _ret;};
		virtual Nectar::VAR &operator[](double key){static Nectar::VAR _ret = Nectar::VAR(); return _ret;};
		virtual Nectar::VAR &operator[](const char* key){static Nectar::VAR _ret = Nectar::VAR(); return _ret;};
	};
}