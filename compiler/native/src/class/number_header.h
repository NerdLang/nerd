namespace NJS::Class::NUMBER 
{
	NJS::VAR _fn;
	
	std::string toString(NJS::VAR& __NJS_THIS, NJS::VAR* _args, int _length)
	{
		return (std::string)__NJS_THIS;
	}
	
	double valueOf(NJS::VAR& __NJS_THIS, NJS::VAR* _args, int _length)
	{
		return __NJS_THIS.data.number;
	}
	
	std::string toFixed(NJS::VAR& __NJS_THIS, NJS::VAR* _args, int _length)
	{
		int precision;
		if(_length > 0)
		{
			precision = _args[0];
		}
		else precision = 0;
		std::ostringstream strout ;
		strout << std::fixed << std::setprecision(precision) << (double)__NJS_THIS ;
		std::string str = strout.str() ;
		return str;
	}
	
	inline NJS::VAR& Accessor(NJS::VAR _this, NJS::VAR key)
	{
		if(((std::string)key).compare("toFixed") == 0)
		{
			_fn = __NJS_Create_Var_Scoped_Anon( return toFixed(__NJS_THIS, __NJS_VARARGS, __NJS_VARLENGTH); );
			((NJS::Class::Function*)_fn.data.ptr)->This = _this;
			return _fn;
		}
		else if(((std::string)key).compare("toString") == 0)
		{
			_fn = __NJS_Create_Var_Scoped_Anon( return toString(__NJS_THIS, __NJS_VARARGS, __NJS_VARLENGTH); );
			((NJS::Class::Function*)_fn.data.ptr)->This = _this;
			return _fn;
		}
		else if(((std::string)key).compare("valueOf") == 0)
		{
			_fn = __NJS_Create_Var_Scoped_Anon( return valueOf(__NJS_THIS, __NJS_VARARGS, __NJS_VARLENGTH); );
			((NJS::Class::Function*)_fn.data.ptr)->This = _this;
			return _fn;
		}
		
		return NJS::Global::undefined;
	}
}
