__NJS_Class_Array::__NJS_Class_Array()
{
	cnt++;
	function<NJS::VAR()> *__OBJ_TO_NJS_STRING = new function<NJS::VAR()>([&]() { return __NJS_Create_String("Array"); });
	NJS::VAR toString = NJS::VAR(NJS::Enum::Type::FUNCTION, __OBJ_TO_NJS_STRING);
	__NJS_Object_Set("toString", toString, &this->__OBJECT);

	function<NJS::VAR(vector<var>)> *__ARRAY_PUSH = new function<NJS::VAR(vector<var>)>([&](vector<var> _NJS_VARARGS) {
		var _add;
		if (_NJS_VARARGS.size() > 0)
			_add = _NJS_VARARGS[0];
		else
			return (int)this->__NJS_VALUE.size();

		this->__NJS_VALUE.push_back(_add);
		__NJS_Object_Set("length", (int)this->__NJS_VALUE.size(), &this->__OBJECT);

		return (int)this->__NJS_VALUE.size();
	});
	NJS::VAR arrayPush = NJS::VAR(NJS::Enum::Type::FUNCTION, __ARRAY_PUSH);
	__NJS_Object_Set("push", arrayPush, &this->__OBJECT);

	__NJS_Object_Set("length", 0, &this->__OBJECT);
}

void __NJS_Class_Array::Delete()
{
	this->cnt--;
	if (this->cnt < 1)
	{
		delete this;
	}
}