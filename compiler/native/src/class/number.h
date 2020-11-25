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
 
namespace NectarCore::Class::NUMBER 
{
	NectarCore::VAR _fn;
	
	std::string toString(NectarCore::VAR& __Nectar_THIS, NectarCore::VAR* _args, int _length)
	{
		return (std::string)__Nectar_THIS;
	}
	
	double valueOf(NectarCore::VAR& __Nectar_THIS, NectarCore::VAR* _args, int _length)
	{
		return __Nectar_THIS.data.number;
	}
	
	std::string toFixed(NectarCore::VAR& __Nectar_THIS, NectarCore::VAR* _args, int _length)
	{
		int precision;
		if(_length > 0)
		{
			precision = _args[0];
		}
		else precision = 0;
		std::ostringstream strout ;
		strout << std::fixed << std::setprecision(precision) << (double)__Nectar_THIS ;
		std::string str = strout.str() ;
		return str;
	}
	
	inline NectarCore::VAR& Accessor(NectarCore::VAR _this, NectarCore::VAR key)
	{
		if(((std::string)key).compare("toFixed") == 0)
		{
			_fn = __Nectar_Create_Var_Scoped_Anon( return toFixed(__Nectar_THIS, __Nectar_VARARGS, __Nectar_VARLENGTH); );
			((NectarCore::Class::Function*)_fn.data.ptr)->This = _this;
			return _fn;
		}
		else if(((std::string)key).compare("toString") == 0)
		{
			_fn = __Nectar_Create_Var_Scoped_Anon( return toString(__Nectar_THIS, __Nectar_VARARGS, __Nectar_VARLENGTH); );
			((NectarCore::Class::Function*)_fn.data.ptr)->This = _this;
			return _fn;
		}
		else if(((std::string)key).compare("valueOf") == 0)
		{
			_fn = __Nectar_Create_Var_Scoped_Anon( return valueOf(__Nectar_THIS, __Nectar_VARARGS, __Nectar_VARLENGTH); );
			((NectarCore::Class::Function*)_fn.data.ptr)->This = _this;
			return _fn;
		}
		
		return NectarCore::Global::undefined;
	}
}
