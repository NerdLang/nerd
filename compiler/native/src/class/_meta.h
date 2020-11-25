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
#include <exception>

namespace NectarCore::Class
{
#ifdef __Nectar_ENV_ARDUINO
	typedef uint16_t count_t;
#else
	typedef int count_t;
#endif
	class InvalidTypeException : public std::exception
	{
	};
	#ifdef __Nectar_ENV_ARDUINO
	const int SMI_MAX = 32767;
	const int SMI_MIN = -32768;
	#else
	const int SMI_MAX = 1073741823;
	const int SMI_MIN = -1073741824;
	#endif
} // namespace NectarCore::Class
