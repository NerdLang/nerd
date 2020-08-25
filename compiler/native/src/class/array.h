namespace NJS::Class
{
	Array::Array()
	{
		cnt++;
		__NJS_CreateMethodToClass("@@iterator", __iterator);
		__NJS_CreateMethodToClass("@@unscopables", __unscopables);
		__NJS_CreateMethodToClass("toString", toString);
		__NJS_CreateMethodToClass("join", join);
		
		__NJS_Object_Set("length", 0, &this->__OBJECT);

	}

	void Array::Delete()
	{
		this->cnt--;
		if (this->cnt < 1)
		{
			delete this;
		}
	}
	NJS::VAR Array::__iterator(vector<var> _NJS_VARARGS) const { return NJS::VAR();}
	NJS::VAR Array::__unscopables(vector<var> _NJS_VARARGS) const { return NJS::VAR(); }
	NJS::VAR Array::join(std::vector<NJS::VAR> args) const
	{
		auto _str = (std::string)(args.size() ? args[0] : NJS::Value::undefined);
		int l = __NJS_VALUE.size();
		if (l == 0)
			return "";
		std::stringstream stream;
		stream << (std::string)__NJS_VALUE[0];
		for (int i = 1; i < l; i++)
		{
			stream << _str << (std::string)__NJS_VALUE[i];
		}
		return stream.str();
	};
	
	NJS::VAR Array::toString(vector<var> _NJS_VARARGS) const
	{
		return join(std::vector<NJS::VAR>({","}));
	}
}