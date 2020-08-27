namespace NJS::Class
{

	Function::Function(void *_f)
	{
		cnt++;
		NJS::VAR __proto = __NJS_Create_Object();
		__NJS_Object_Set("prototype", __proto, &this->__OBJECT);
		
		__NJS_VALUE = _f;
	}

	void Function::Delete()
	{
		this->cnt--;
		if (this->cnt < 1)
		{
			delete this;
		}
	}
	
	NJS::VAR Function::Call(var __INJECTED_THIS, vector<var> __NJS_VARARGS)
	{
		return (*static_cast<function<NJS::VAR(var, vector<NJS::VAR>)> *>(__NJS_VALUE))(__INJECTED_THIS, __NJS_VARARGS);
	}
		
	
	template <class... Args>
	NJS::VAR Function::operator()(Args... args)
	{
		vector<NJS::VAR> _args = vector<var>{(NJS::VAR)args...};
		return (*static_cast<function<NJS::VAR(var, vector<NJS::VAR>)> *>(__NJS_VALUE))(__NJS_Create_Undefined(), _args);
	}


} // namespace NJS::Class