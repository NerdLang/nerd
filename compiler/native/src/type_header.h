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
 
#ifndef __Nectar__OBJECT_VECTOR
#include <unordered_map>
#endif
namespace NectarCore
{
	namespace Type
	{
		typedef std::vector<NectarCore::VAR> vector_t;
		typedef std::vector<void*> vector_p;
		typedef std::pair<std::string, NectarCore::VAR> pair_t;
		#ifndef __Nectar__OBJECT_VECTOR
		typedef std::unordered_map<std::string, NectarCore::VAR> object_t;
		#else
		typedef std::vector<pair_t> object_t;
		#endif
		typedef std::function<NectarCore::VAR (VAR&, VAR*, int)> function_t;
		typedef std::function<void (void*)> clean_struct;
		
		#ifdef __Nectar_ENV_ARDUINO
		typedef std::string StringView;
		#else 
		typedef std::string_view StringView;
		#endif
	}
}