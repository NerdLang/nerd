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
	
	template <class... Args>
	NJS::VAR Function::operator()(Args... args)
	{
		vector<NJS::VAR> _args = vector<var>{(NJS::VAR)args...};
		return (*static_cast<function<NJS::VAR(vector<NJS::VAR>)> *>(__NJS_VALUE))(_args);
	}


} // namespace NJS::Class