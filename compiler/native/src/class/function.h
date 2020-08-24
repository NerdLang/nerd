__NJS_Class_Function::__NJS_Class_Function(void *_f)
{
	cnt++;
	__NJS_VAR __proto = __NJS_Create_Object();
	__NJS_Object_Set("prototype", __proto, &this->__OBJECT);
	__NJS_VALUE = _f;
}

__NJS_VAR __NJS_Class_Function::__NEW(vector<__NJS_VAR> _args)
{
	return (*static_cast<function<__NJS_VAR(vector<var>)> *>(this->__NJS_VALUE))(_args);
	return __NJS_VAR();
}

void __NJS_Class_Function::Delete()
{
	this->cnt--;
	if (this->cnt < 1)
	{
		delete this;
	}
}