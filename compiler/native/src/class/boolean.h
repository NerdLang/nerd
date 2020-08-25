namespace NJS::Class
{
	Boolean::Boolean()
	{
		Object();
		__NJS_VALUE = false;
	}
	Boolean::Boolean(bool b)
	{
		Object();
		__NJS_VALUE = b;
	}

	Boolean Boolean::operator=(const Boolean &_v)
	{
		__NJS_VALUE = _v.__NJS_VALUE;
		_v.Delete();
		return *this;
	}
	Boolean Boolean::operator=(const bool &_v)
	{
		__NJS_VALUE = _v;
		return *this;
	}
} // namespace NJS::Class