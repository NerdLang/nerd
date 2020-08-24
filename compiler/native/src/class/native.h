__NJS_Class_Native::__NJS_Class_Native(void *_n)
{
	cnt++;
	__NJS_VALUE = _n;
}

void __NJS_Class_Native::Delete()
{
	this->cnt--;
	if (this->cnt < 1)
	{
		delete this;
	}
}