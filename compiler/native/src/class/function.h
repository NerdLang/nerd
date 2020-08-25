namespace NJS::Class
{
	Function::Function(void *_f)
	{
		cnt++;
		NJS::VAR __proto = __NJS_Create_Object();
		__NJS_Object_Set("prototype", __proto, &this->__OBJECT);
		__NJS_VALUE = _f;
	}

	NJS::VAR Function::__NEW(vector<NJS::VAR> _args)
	{
		return (*static_cast<function<NJS::VAR(vector<var>)> *>(this->__NJS_VALUE))(_args);
		return NJS::VAR();
	}

	void Function::Delete()
	{
		this->cnt--;
		if (this->cnt < 1)
		{
			delete this;
		}
	}
} // namespace NJS::Class