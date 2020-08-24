__NJS_Class_Object::__NJS_Class_Object()
{
	cnt++;
}

void __NJS_Class_Object::Delete()
{
	this->cnt--;
	if (this->cnt < 1)
	{
		delete this;
	}
}